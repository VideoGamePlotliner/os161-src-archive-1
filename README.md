# Helpful GitHub URLs
- https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/about-rulesets
- https://docs.github.com/en/account-and-profile/setting-up-and-managing-your-github-profile/customizing-your-profile/managing-your-profile-readme
- https://docs.github.com/en/get-started/getting-started-with-git/ignoring-files
- https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository
- https://github.com/features/actions
- https://github.com/marketplace/category/continuous-integration
- https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/collaborating-on-repositories-with-code-quality-features/about-status-checks
- https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
- https://docs.github.com/en/actions
- https://docs.github.com/en/actions/learn-github-actions/understanding-github-actions
- https://docs.github.com/en/actions/quickstart
- https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions

# Tips
- To enable the "hangman" option (and thus the `HANGMAN_*()` macros), all you need to do is add the line `options hangman` to [kern/conf/conf.kern](kern/conf/conf.kern), right below `defoption hangman`.

# `man` page for each program that is executable with the `p` command in OS/161
- man/bin/cat.html
- man/bin/cp.html
- man/bin/false.html
- man/bin/ln.html
- man/bin/ls.html
- man/bin/mkdir.html
- man/bin/mv.html
- man/bin/pwd.html
- man/bin/rm.html
- man/bin/rmdir.html
- man/bin/sh.html
- man/bin/sync.html
- man/bin/tac.html
- man/bin/true.html
- man/sbin/dumpsfs.html
- man/sbin/halt.html
- man/sbin/mksfs.html
- man/sbin/poweroff.html
- man/sbin/reboot.html
- man/sbin/sfsck.html
- man/testbin/add.html
- man/testbin/argtest.html
- man/testbin/badcall.html
- man/testbin/bigexec.html
- man/testbin/bigfile.html
- man/testbin/bigfork.html
- man/testbin/bigseek.html
- man/testbin/bloat.html
- man/testbin/conman.html
- man/testbin/crash.html
- man/testbin/ctest.html
- man/testbin/dirconc.html
- man/testbin/dirseek.html
- man/testbin/dirtest.html
- man/testbin/f_test.html
- man/testbin/factorial.html
- man/testbin/farm.html
- man/testbin/faulter.html
- man/testbin/filetest.html
- man/testbin/forkbomb.html
- man/testbin/forktest.html
- man/testbin/frack.html
- man/testbin/guzzle.html
- man/testbin/hash.html
- man/testbin/hog.html
- man/testbin/huge.html
- man/testbin/kitchen.html
- man/testbin/malloctest.html
- man/testbin/matmult.html
- man/testbin/multiexec.html
- man/testbin/palin.html
- man/testbin/parallelvm.html
- man/testbin/poisondisk.html
- man/testbin/psort.html
- man/testbin/quinthuge.html
- man/testbin/quintmat.html
- man/testbin/quintsort.html
- man/testbin/randcall.html
- man/testbin/redirect.html
- man/testbin/rmdirtest.html
- man/testbin/rmtest.html
- man/testbin/sbrktest.html
- man/testbin/schedpong.html
- man/testbin/sink.html
- man/testbin/sort.html
- man/testbin/sparsefile.html
- man/testbin/sty.html
- man/testbin/tail.html
- man/testbin/tictac.html
- man/testbin/triplehuge.html
- man/testbin/triplemat.html
- man/testbin/triplesort.html
- man/testbin/usemtest.html
- man/testbin/userthreads.html
- man/testbin/zero.html

# Syscalls required for such programs, according to the `man` pages above
These syscalls are not those programs' *only* requirements, by the way.
- man/bin/cat.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/bin/cp.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/bin/false.html
  - man/syscall/_exit.html

- man/bin/ln.html
  - man/syscall/link.html
  - man/syscall/symlink.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/bin/ls.html
  - man/syscall/open.html
  - man/syscall/write.html
  - man/syscall/fstat.html
  - man/syscall/getdirentry.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/bin/mkdir.html
  - man/syscall/mkdir.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/bin/mv.html
  - man/syscall/rename.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/bin/pwd.html
  - man/syscall/__getcwd.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/bin/rm.html
  - man/syscall/remove.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/bin/rmdir.html
  - man/syscall/rmdir.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/bin/sh.html
  - man/syscall/chdir.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/_exit.html
  - man/syscall/__time.html

- man/bin/sync.html
  - man/syscall/sync.html
  - man/syscall/_exit.html

- man/bin/tac.html
  - man/syscall/getpid.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/remove.html
  - man/syscall/_exit.html

- man/bin/true.html
  - man/syscall/_exit.html

- man/sbin/dumpsfs.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/fstat.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/sbin/halt.html
  - man/syscall/reboot.html

- man/sbin/mksfs.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/fstat.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/sbin/poweroff.html
  - man/syscall/reboot.html

- man/sbin/reboot.html
  - man/syscall/reboot.html

- man/sbin/sfsck.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/fstat.html
  - man/syscall/close.html
  - man/syscall/sbrk.html
  - man/syscall/_exit.html

- man/testbin/add.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/argtest.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/badcall.html
  - man/syscall/read.html
  - man/syscall/write.html

- man/testbin/bigexec.html
  - man/syscall/execv.html
  - man/syscall/write.html
  - man/syscall/execv.html
  - man/syscall/_exit.html

- man/testbin/bigfile.html
  - man/syscall/open.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/bigfork.html
  - man/syscall/write.html
  - man/syscall/fork.html
  - man/syscall/waitpid.html
  - man/syscall/_exit.html

- man/testbin/bigseek.html
  - man/syscall/open.html
  - man/syscall/lseek.html
  - man/syscall/write.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/bloat.html
  - man/syscall/sbrk.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/conman.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/crash.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/ctest.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/dirconc.html
  - man/syscall/getpid.html
  - man/syscall/fork.html
  - man/syscall/waitpid.html
  - man/syscall/mkdir.html
  - man/syscall/rmdir.html
  - man/syscall/chdir.html
  - man/syscall/rename.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/dirseek.html
  - man/syscall/chdir.html
  - man/syscall/close.html
  - man/syscall/getdirentry.html
  - man/syscall/lseek.html
  - man/syscall/mkdir.html
  - man/syscall/open.html
  - man/syscall/remove.html
  - man/syscall/rmdir.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/dirtest.html
  - man/syscall/mkdir.html
  - man/syscall/rmdir.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/f_test.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/mkdir.html
  - man/syscall/rmdir.html
  - man/syscall/remove.html
  - man/syscall/_exit.html

- man/testbin/factorial.html
  - man/syscall/write.html
  - man/syscall/execv.html
  - man/syscall/_exit.html

- man/testbin/farm.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/write.html
  - man/syscall/_exit.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/close.html

- man/testbin/faulter.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/filetest.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/close.html
  - man/syscall/remove.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/filetestaltered.html
  - man/syscall/open.html
  - man/syscall/close.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/forkbomb.html
  - man/syscall/fork.html
  - man/syscall/getpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/forktest.html
  - man/syscall/fork.html
  - man/syscall/getpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/frack.html
  - man/syscall/open.html
  - man/syscall/fstat
  - man/syscall/ftruncate
  - man/syscall/lseek.html
  - man/syscall/getdirentry
  - man/syscall/read
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/link
  - man/syscall/remove
  - man/syscall/chdir
  - man/syscall/mkdir
  - man/syscall/rmdir
  - man/syscall/rename
  - man/syscall/sync
  - man/syscall/_exit.html

- man/testbin/guzzle.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/hash.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/hog.html
  - man/syscall/_exit.html

- man/testbin/huge.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/kitchen.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/write.html
  - man/syscall/_exit.html
  - man/syscall/read.html

- man/testbin/malloctest.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/matmult.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/multiexec.html
  - man/syscall/getpid.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/remove.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/_exit.html

- man/testbin/palin.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/parallelvm.html
  - man/syscall/getpid.html
  - man/syscall/fork.html
  - man/syscall/fork.html
  - man/syscall/write.html
  - man/syscall/_exit.html
  - man/syscall/open.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/remove.html

- man/testbin/poisondisk.html
  - man/syscall/open.html
  - man/syscall/fstat.html
  - man/syscall/lseek.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/psort.html
  - man/syscall/open.html
  - man/syscall/dup2.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/close.html
  - man/syscall/stat.html or
    - Or man/syscall/fstat.html (optional)
  - man/syscall/remove.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/_exit.html

- man/testbin/quinthuge.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/quintmat.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/quintsort.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/redirect.html
  - man/syscall/open.html
  - man/syscall/dup2.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/remove.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/_exit.html

- man/testbin/rmdirtest.html
  - man/syscall/chdir.html
  - man/syscall/close.html
  - man/syscall/__getcwd.html
  - man/syscall/getdirentry.html
  - man/syscall/mkdir.html
  - man/syscall/open.html
  - man/syscall/rmdir.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/rmtest.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/close.html
  - man/syscall/_exit.html
  - man/syscall/remove.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/sbrktest.html
  - man/syscall/sbrk.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/fork.html
  - man/syscall/waitpid.html
  - man/syscall/_exit.html

- man/testbin/schedpong.html
  - man/syscall/__time.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/close.html
  - man/syscall/fork.html
  - man/syscall/waitpid.html
  - man/syscall/_exit.html
  - man/syscall/remove.html
  - man/syscall/sbrk.html

- man/testbin/sink.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/sort.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/sparsefile.html
  - man/syscall/open.html
  - man/syscall/lseek.html
  - man/syscall/write.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/sty.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/tail.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/lseek.html
  - man/syscall/close.html
  - man/syscall/_exit.html

- man/testbin/tictac.html
  - man/syscall/read.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/triplehuge.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/triplemat.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/triplesort.html
  - man/syscall/fork.html
  - man/syscall/execv.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/usemtest.html
  - man/syscall/fork.html
  - man/syscall/open.html
  - man/syscall/read.html
  - man/syscall/read.html
  - man/syscall/waitpid.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/userthreads.html
  - man/syscall/write.html
  - man/syscall/_exit.html

- man/testbin/zero.html
  - man/syscall/write.html
  - man/syscall/sbrk.html (optionally)
  - man/syscall/_exit.html


# `man` page for each syscall
- man/syscall/__getcwd.html
- man/syscall/__time.html
- man/syscall/_exit.html
- man/syscall/chdir.html
- man/syscall/close.html
- man/syscall/dup2.html
- man/syscall/execv.html
- man/syscall/fork.html
- man/syscall/fstat.html
- man/syscall/fsync.html
- man/syscall/ftruncate.html
- man/syscall/getdirentry.html
- man/syscall/getpid.html
- man/syscall/ioctl.html
- man/syscall/link.html
- man/syscall/lseek.html
- man/syscall/lstat.html
- man/syscall/mkdir.html
- man/syscall/open.html
- man/syscall/pipe.html
- man/syscall/read.html
- man/syscall/readlink.html
- man/syscall/reboot.html
- man/syscall/remove.html
- man/syscall/rename.html
- man/syscall/rmdir.html
- man/syscall/sbrk.html
- man/syscall/stat.html
- man/syscall/symlink.html
- man/syscall/sync.html
- man/syscall/waitpid.html
- man/syscall/write.html
