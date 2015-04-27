// PID namespace 'Hello world'.
// Build: $ gcc pid_namespace.c
// Run: $ sudo ./a.out (root privilege is required)
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1048576];

static int child_fn() {
  printf("PID: %ld\n", (long)getpid()); /* 1 */
  printf("Parent PID: %ld\n", (long)getppid()); /* 0 */
  return 0;
}

int main() {
  // The clone() function has created a new process by cloning the current one
  // and started execution at the beginning of the child_fn() function. However,
  // while doing so, it detached the new process from the original process tree
  // and created a separate process tree for the new process.
  pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWPID | SIGCHLD, NULL);
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
