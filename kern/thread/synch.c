/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Synchronization primitives.
 * The specifications of the functions are in synch.h.
 */

#include <types.h>
#include <lib.h>
#include <spinlock.h>
#include <wchan.h>
#include <thread.h>
#include <current.h>
#include <synch.h>
#include <spl.h>
#include <membar.h>

////////////////////////////////////////////////////////////
//
// Semaphore.

struct semaphore *
sem_create(const char *name, unsigned initial_count)
{
        struct semaphore *sem;

        sem = kmalloc(sizeof(*sem));
        if (sem == NULL) {
                return NULL;
        }

        sem->sem_name = kstrdup(name);
        if (sem->sem_name == NULL) {
                kfree(sem);
                return NULL;
        }

	sem->sem_wchan = wchan_create(sem->sem_name);
	if (sem->sem_wchan == NULL) {
		kfree(sem->sem_name);
		kfree(sem);
		return NULL;
	}

	spinlock_init(&sem->sem_lock);
        sem->sem_count = initial_count;

        return sem;
}

void
sem_destroy(struct semaphore *sem)
{
        KASSERT(sem != NULL);

	/* wchan_cleanup will assert if anyone's waiting on it */
	spinlock_cleanup(&sem->sem_lock);
	wchan_destroy(sem->sem_wchan);
        kfree(sem->sem_name);
        kfree(sem);
}

void
P(struct semaphore *sem)
{
        KASSERT(sem != NULL);

        /*
         * May not block in an interrupt handler.
         *
         * For robustness, always check, even if we can actually
         * complete the P without blocking.
         */
        KASSERT(curthread->t_in_interrupt == false);

	/* Use the semaphore spinlock to protect the wchan as well. */
	spinlock_acquire(&sem->sem_lock);
        while (sem->sem_count == 0) {
		/*
		 *
		 * Note that we don't maintain strict FIFO ordering of
		 * threads going through the semaphore; that is, we
		 * might "get" it on the first try even if other
		 * threads are waiting. Apparently according to some
		 * textbooks semaphores must for some reason have
		 * strict ordering. Too bad. :-)
		 *
		 * Exercise: how would you implement strict FIFO
		 * ordering?
		 */
		wchan_sleep(sem->sem_wchan, &sem->sem_lock);
        }
        KASSERT(sem->sem_count > 0);
        sem->sem_count--;
	spinlock_release(&sem->sem_lock);
}

void
V(struct semaphore *sem)
{
        KASSERT(sem != NULL);

	spinlock_acquire(&sem->sem_lock);

        sem->sem_count++;
        KASSERT(sem->sem_count > 0);
	wchan_wakeone(sem->sem_wchan, &sem->sem_lock);

	spinlock_release(&sem->sem_lock);
}

////////////////////////////////////////////////////////////
//
// Lock.

struct lock *
lock_create(const char *name)
{
        struct lock *lock;

        lock = kmalloc(sizeof(*lock));
        if (lock == NULL) {
                return NULL;
        }

        lock->lk_name = kstrdup(name);
        if (lock->lk_name == NULL) {
                kfree(lock);
                return NULL;
        }

	HANGMAN_LOCKABLEINIT(&lock->lk_hangman, lock->lk_name);

        // add stuff here as needed

        lock->lk_wchan = wchan_create(lock->lk_name);
        if (lock->lk_wchan == NULL)
        {
                kfree(lock->lk_name);
                kfree(lock);
                return NULL;
        }

        spinlock_init(&lock->lk_spinlock);
        lock->lk_holder = NULL;

        return lock;
}

void
lock_destroy(struct lock *lock)
{
        KASSERT(lock != NULL);

        // add stuff here as needed
        KASSERT(lock->lk_holder == NULL); /* If the lock's holder is NOT null, 
                                             then some thread is holding the
                                             lock. We shouldn't destroy a lock
                                             that's currently being held. */

#if OPT_HANGMAN
        KASSERT(lock->lk_hangman.l_holding == NULL); /* This assertion is included
                                                        for the same reason as the
                                                        assertion that the lock's
                                                        holder must be null. */
#endif

	/* cleanup will assert if anyone's waiting on it */
        spinlock_cleanup(&lock->lk_spinlock);
        wchan_destroy(lock->lk_wchan);
        kfree(lock->lk_name);
        kfree(lock);
}

void
lock_acquire(struct lock *lock)
{
        // Implementation based on `spinlock_acquire()`

        KASSERT(lock != NULL);

        struct thread *mythread;

	splraise(IPL_NONE, IPL_HIGH);

	/* this must work before curcpu initialization */
        if (curthread == NULL) {
            mythread = NULL;
        }
        else {
            KASSERT(!(curthread->t_in_interrupt));
            mythread = curthread;
            if (lock->lk_holder == mythread) {
                panic("Deadlock on lock \"%s\": current thread already holds this lock\n", lock->lk_name);
            }

            /* Call this (atomically) before waiting for a lock */
            HANGMAN_WAIT(&curthread->t_hangman, &lock->lk_hangman);
        }

        // IF NECESSARY: mythread->____ = ____;

	/* Call this (atomically) before waiting for a lock */
	//HANGMAN_WAIT(&curthread->t_hangman, &lock->lk_hangman);

        volatile struct thread *holder;
        while (1) {
            holder = lock->lk_holder;
            if (holder != NULL) {
                spinlock_acquire(&lock->lk_spinlock);
                wchan_sleep(lock->lk_wchan, &lock->lk_spinlock);
                spinlock_release(&lock->lk_spinlock);
                continue;
            }
            break;
        }

        membar_store_any();
        lock->lk_holder = mythread;

        // Don't assert that `mythread` still equals `curthread`.
        // And don't use `kprintf()` here, because doing so creates
        // a deadlock on `kprintf_lock`.

	/* Call this (atomically) once the lock is acquired */
        if (curthread != NULL) {
            HANGMAN_ACQUIRE(&curthread->t_hangman, &lock->lk_hangman);
        }
}

void
lock_release(struct lock *lock)
{
        // Implementation based on `spinlock_release()`

        KASSERT(lock != NULL);

        if (curthread != NULL) {
            KASSERT(lock->lk_holder == curthread);
            // IF NECESSARY: KASSERT(curthread->____ __ ____);
            // IF NECESSARY: curthread->____ = ____;

            /* Call this (atomically) when the lock is released */
            HANGMAN_RELEASE(&curthread->t_hangman, &lock->lk_hangman);
        }

        lock->lk_holder = NULL;
	membar_any_store();

        spinlock_acquire(&lock->lk_spinlock);
        wchan_wakeall(lock->lk_wchan, &lock->lk_spinlock);
        spinlock_release(&lock->lk_spinlock);

	spllower(IPL_HIGH, IPL_NONE);
}

bool
lock_do_i_hold(struct lock *lock)
{
        // Implementation based on `spinlock_do_i_hold()`

        KASSERT(lock != NULL);

        if (curthread == NULL)
        {
                return true;
        }

        int s = splhigh();
        bool i_am_holding = (lock->lk_holder == curthread); // Assume that this line's code is atomic
        splx(s);
        return i_am_holding;
}

////////////////////////////////////////////////////////////
//
// CV


struct cv *
cv_create(const char *name)
{
        struct cv *cv;

        cv = kmalloc(sizeof(*cv));
        if (cv == NULL) {
                return NULL;
        }

        cv->cv_name = kstrdup(name);
        if (cv->cv_name==NULL) {
                kfree(cv);
                return NULL;
        }

        // add stuff here as needed

        cv->cv_wchan = wchan_create(cv->cv_name);
        if (cv->cv_wchan == NULL) {
                kfree(cv->cv_name);
                kfree(cv);
                return NULL;
        }

        spinlock_init(&cv->cv_spinlock);

        return cv;
}

void
cv_destroy(struct cv *cv)
{
        KASSERT(cv != NULL);

        // add stuff here as needed

	/* cleanup will assert if anyone's waiting on it */
        spinlock_cleanup(&cv->cv_spinlock);
        wchan_destroy(cv->cv_wchan);

        kfree(cv->cv_name);
        kfree(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
        // Write this
        (void)cv;    // suppress warning until code gets written
        (void)lock;  // suppress warning until code gets written

        KASSERT(cv != NULL);
        KASSERT(lock != NULL);

        /* Call `splhigh()` twice, because calling it here once lets
           `lock_release()` turn interrupts on (which would prevent
           atomicity), assuming that `curthread->t_iplhigh_count`
           was 0 right when this function started being executed. */
        int s1 = splhigh();
        int s2 = splhigh();
        KASSERT(lock_do_i_hold(lock));
        lock_release(lock);                                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        spinlock_acquire(&cv->cv_spinlock);                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        wchan_sleep(cv->cv_wchan, &cv->cv_spinlock);            // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        spinlock_release(&cv->cv_spinlock);                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        lock_acquire(lock);                                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        splx(s2);
        splx(s1);

        // panic("cv_wait() has not yet been implemented\n");
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
        // Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written

        KASSERT(cv != NULL);
        KASSERT(lock != NULL);

        /* Call `splhigh()` twice, because calling it here once lets
           `lock_release()` turn interrupts on (which would prevent
           atomicity), assuming that `curthread->t_iplhigh_count`
           was 0 right when this function started being executed.

           Actually, `lock_release()` and `lock_acquire()` are no
           longer here, but this comment is included regardless.

           Keep this function's double call to `splhigh()` and this
           function's double call to `splx()`, just in case. */
        int s1 = splhigh();
        int s2 = splhigh();
        KASSERT(lock_do_i_hold(lock));
        spinlock_acquire(&cv->cv_spinlock);                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        wchan_wakeone(cv->cv_wchan, &cv->cv_spinlock);          // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        spinlock_release(&cv->cv_spinlock);                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        splx(s2);
        splx(s1);

        // panic("cv_signal() has not yet been implemented\n");
}

void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written

        KASSERT(cv != NULL);
        KASSERT(lock != NULL);

        /* Call `splhigh()` twice, because calling it here once lets
           `lock_release()` turn interrupts on (which would prevent
           atomicity), assuming that `curthread->t_iplhigh_count`
           was 0 right when this function started being executed.

           Actually, `lock_release()` and `lock_acquire()` are no
           longer here, but this comment is included regardless.

           Keep this function's double call to `splhigh()` and this
           function's double call to `splx()`, just in case. */
        int s1 = splhigh();
        int s2 = splhigh();
        KASSERT(lock_do_i_hold(lock));
        spinlock_acquire(&cv->cv_spinlock);                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        wchan_wakeall(cv->cv_wchan, &cv->cv_spinlock);          // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        spinlock_release(&cv->cv_spinlock);                     // kprintf("THREAD \"%s\": line %d in %s()\n", curthread->t_name, __LINE__, __func__);
        splx(s2);
        splx(s1);

        // panic("cv_broadcast() has not yet been implemented\n");
}
