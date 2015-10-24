// Linux also maintains a data structure for all the mountpoints of the system.
// It includes information like what disk partitions are mounted, where they
// are mounted, whether they are readonly, et cetera. With Linux namespaces,
// one can have this data structure cloned, so that processes under different
// namespaces can change the mountpoints without affecting each other.
// http://stackoverflow.com/questions/22889241/linux-understanding-the-mount-namespace-clone-clone-newns-flag
//
// 1. $ sudo mount --make-rprivate /
//    This is important to makes mount points private
// 2. $ gcc pid_namespace.c
//    $ sudo ./a.out bash
//    # mkdir /mytmp
//    # mount -t tmpfs none /mytmp
//    Now we can see mount points in the new namespace, and umount it; but we
//    can't umount it in parent namespace.

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

static char child_stack[1048576];

struct clone_args {
  char **argv;
};

static int child_exec(void *stuff) {
  struct clone_args *args = (struct clone_args *)stuff;
  if (execvp(args->argv[0], args->argv) != 0) {
    fprintf(stderr, "failed to execvp argments\n");
    exit(-1);
  }
  // we should never reach here!
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  struct clone_args args;
  args.argv = &argv[1];
  pid_t child_pid = clone(child_exec, child_stack+1048576, CLONE_NEWNS | SIGCHLD, &args);
  printf("clone() = %ld\n", (long)child_pid);
  waitpid(child_pid, NULL, 0);
  return 0;
}
