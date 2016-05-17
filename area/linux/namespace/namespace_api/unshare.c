// Linux provides unshare(). This special system call allows a process to
// isolate itself from the original namespace, instead of having the parent
// isolate the child in the first place. You may need sudo privilege.

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1048576];

static int child_fn() {
  // Calling unshare() from inside the init process lets you create a new
  // namespace after a new process has been spawned.
  unshare(CLONE_NEWNET);

  printf("New `net` Namespace:\n");
  system("ip link");
  printf("\n\n");
  return 0;
}

int main() {
  printf("Original `net` Namespace:\n");
  system("ip link");
  printf("\n\n");

  pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWPID | SIGCHLD, NULL);

  waitpid(child_pid, NULL, 0);
  return 0;
}
