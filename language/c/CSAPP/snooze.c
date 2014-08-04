#include <stdio.h>
#include <unistd.h>
#include <signal.h>

unsigned int snooze(unsigned int secs) {
  int remain = sleep(secs);
  printf("Slept %d for %d secs\n", secs - remain, secs);
  return remain;
}

void handler(int signum) {
  return;
}

int main(void) {
  signal(SIGINT, handler);
  snooze(5);
}
