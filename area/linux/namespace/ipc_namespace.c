// Isolating a process by the IPC namespace gives it its own interprocess
// communication resources, for example, System V IPC and POSIX messages.
//
// Steps:
// 1. Create a message queue:
//    $ ipcmk -Q
// 2. Now list all ipcs, we'll see the newly created IPC queue.
// 3. Build and run the file:
//    $ gcc ipc_namespace.c -o ipc_namespace
//    $ sudo ./ipc_namespace ipcs
//    We won't see the IPC queue now.

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
    fprintf(stderr, "failed to execvp argments %d\n", strerror(errno));
    exit(-1);
  }
  // We should never reach here!
  exit(-1);
}

int main(int argc, char **argv) {
  struct clone_args args;
  args.argv = &argv[1];
  pid_t child_pid = clone(child_exec, child_stack+1048576, CLONE_NEWIPC | SIGCHLD, &args);
  waitpid(child_pid, NULL, 0);
  return 0;
}
