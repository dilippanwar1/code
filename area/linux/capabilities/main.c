// Basic linux capabilities, compile with:
//  $ gcc main.c -lcap
// Required libcap-dev.

#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/capability.h>

#define STACK_SIZE (1024*1024)

static char child_stack[STACK_SIZE];
char * const child_args[]={
  "/bin/bash",
  NULL
};

int child_main(void * args){
  printf("In child main\n");
  cap_t caps;                   // cap_t defines the core capability struct
  printf("eUID = %ld; eGID = %ld\n", (long)geteuid(), (long)getegid());
  caps = cap_get_proc();        // Get capabilities of current user
  printf("capabilities:%s\n", cap_to_text(caps,NULL));
  execv(child_args[0], child_args);
  return 1;
}

int main() {
  int child_pid = clone(child_main, child_stack + STACK_SIZE, SIGCHLD|CLONE_NEWUSER, NULL);
  printf("%d",child_pid);
  waitpid(child_pid,NULL,0);
}
