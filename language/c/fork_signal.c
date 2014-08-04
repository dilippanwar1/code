#include <stdio.h>
#include <signal.h>

int main(void) {

  int pid = fork();

  if (pid > 0) {
    /* parent process */
    kill(pid, SIGKILL);
    printf("parent\n");
  } else {
    /* child process */
    kill(getppid(), SIGKILL);
    printf("child\n");
  }
}
