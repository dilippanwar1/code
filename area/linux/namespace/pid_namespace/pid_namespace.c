// PID namespace 'Hello world'.
//
// Steps:
// 1. Build and run:
//    $ gcc pid_namespace.c
//    $ sudo ./a.out echo "running" (root privilege is required to create pid namespace)
//  We'll see that the child process has pid 1
// 2. List all processes:
//    $ sudo ./a.out bash
//    # ps aux
//  We'll see that the new namespace can still see all processes. To make it
//  only see the processes in its namespace, we need to mount /proc.
//  (Notes from LWN. However, in order to make the /proc/PID directories that
//  correspond to a PID namespace visible, the proc filesystem ("procfs" for
//  short) needs to be mounted from within that PID namespace.)
//    # mount -t proc proc /proc/
//    # ps aux
//  Note mounting on /proc will make parent PID namespace unable to see its
//  own PIDs, since we don't have mount namespace. Alternatively, we can mount
//  on another directory:
//    # mount -t proc proc /proc2/
//  So parent pid namespace uses '/proc' and child pid namespace uses '/proc2'.
//  However, tools like 'ps' won't work properly as they usually look at '/proc'
//  directory.
//  (Notes from LWN. However, mounting the procfs at /proc2 during our demonstration
//  provides an easy way to avoid creating problems for the rest of the processes
//  on the system: since those processes are in the same mount namespace as our
//  test program, changing the filesystem mounted at /proc would confuse the rest
//  of the system by making the /proc/PID directories for the root PID namespace
//  invisible.)
//  (Notes from LWN. It's worth mentioning that although the processes in the
//  child PID namespace will be able to see the PID directories exposed by the
//  /proc mount point, those PIDs will not be meaningful for the processes in the
//  child PID namespace, since system calls made by those processes interpret PIDs
//  in the context of the PID namespace in which they reside, e.g. kill xxx won't
//  work)
//  (Notes from LWN. To use /proc for child namespace, we can 1. use mount namespace;
//  2. use chroot to change root direcotry of child process).

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

struct clone_args {
  char **argv;
};

static int child_exec(void *stuff) {
  // Because the parent of the child created by clone() is in a different
  // namespace, the child cannot "see" the parent; therefore, getppid()
  // reports the parent PID as being zero.
  printf("PID: %ld\n", (long)getpid());         /* 1 */
  printf("Parent PID: %ld\n", (long)getppid()); /* 0 */

  struct clone_args *args = (struct clone_args *)stuff;
  if (execvp(args->argv[0], args->argv) != 0) {
    fprintf(stderr, "failed to execvp argments %d\n", strerror(errno));
    exit(-1);
  }
  // We should never reach here!
  exit(-1);
}

int main(int argc, char **argv) {
  struct clone_args args;
  args.argv = &argv[1];
  // The clone() function will create a new process by cloning the current one
  // and start execution at the beginning of the child_fn() function. However,
  // while doing so, it detaches the new process from the original process tree
  // and creates a separate process tree for the new process.
  // `child_stack+STACK_SIZE` means pointing to the start of downwardly growing
  // stack - 'child_stack' has a lower address.
  pid_t child_pid = clone(child_exec, child_stack+STACK_SIZE, CLONE_NEWPID | SIGCHLD, &args);
  // The child pid here is the pid of the new child process in 'current namespace';
  // in the new namespace, the pid is 0, as printed in the child_fn() above.
  printf("clone() = %ld\n", (long)child_pid); /* e.g. 25658 */

  // Note these processes still have unrestricted access to other common or
  // shared resources. For example, the networking interface: if the child
  // process created above were to listen on port 80, it would prevent every
  // other process on the system from being able to listen on it. Therefore,
  // we need other kind of namespace, e.g. net.

  waitpid(child_pid, NULL, 0);
  return 0;
}
