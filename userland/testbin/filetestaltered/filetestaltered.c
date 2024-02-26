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
 * filetestaltered.c
 *
 * 	Tests the filesystem by opening, writing to and reading from a
 * 	user specified file.
 *
 * This should run (on SFS) even before the file system assignment is started.
 * It should also continue to work once said assignment is complete.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

int
main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int fd1 = -1;
	int fd2 = -1;
	int fd3 = -1;
	int fd4 = -1;

	fd1 = open("testfile1", O_WRONLY|O_CREAT|O_TRUNC, 0664);
	if (fd1 < 0) {
		err(1, "open for fd1");
	}

	fd2 = open("testfile2", O_WRONLY|O_CREAT|O_TRUNC, 0664);
	if (fd2 < 0) {
		close(fd1);
		err(2, "open for fd2");
	}

	fd3 = open("testfile3", O_WRONLY|O_CREAT|O_TRUNC, 0664);
	if (fd3 < 0) {
		close(fd1);
		close(fd2);
		err(3, "open for fd3");
	}

	fd4 = open("testfile4", O_WRONLY|O_CREAT|O_TRUNC, 0664);
	if (fd4 < 0) {
		close(fd1);
		close(fd2);
		close(fd3);
		err(4, "open for fd4");
	}

	int rv1 = -1;
	int rv2 = -1;
	int rv3 = -1;
	int rv4 = -1;

	rv2 = close(fd2);
	if (rv2 < 0) {
		close(fd1);
		close(fd3);
		close(fd4);
		err(5, "close for fd2");
	}

	rv4 = close(fd4);
	if (rv4 < 0) {
		close(fd1);
		close(fd3);
		err(6, "close for rv4");
	}

	rv1 = close(fd1);
	if (rv1 < 0) {
		close(fd3);
		err(7, "close for rv1");
	}

	rv3 = close(fd3);
	if (rv3 < 0) {
		err(8, "close for rv3");
	}

	printf("Passed filetestaltered.\n");
	return 0;
}
