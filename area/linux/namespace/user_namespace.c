// The user namespace allows a process to have root privileges within the
// namespace, without giving it that access to processes outside of the
// namespace.

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

static char child_stack[1048576];

struct clone_args {
  char **argv;
};

static int child_exec(void *stuff) {
  cap_t caps;
  printf("eUID=%ld; eGID=%ld; ", (long)geteuid(), (long)getegid());
  caps = cap_get_proc();
  printf("capabilities: %s\n", cap_to_text(caps, NULL));
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
  pid_t child_pid = clone(child_exec, child_stack+1048576, CLONE_NEWUSER | SIGCHLD, &args);
  printf("clone() = %ld\n", (long)child_pid); /* e.g. 25658 */
  waitpid(child_pid, NULL, 0);
  return 0;
}
