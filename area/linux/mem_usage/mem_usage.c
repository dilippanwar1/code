// https://peteris.rocks/blog/htop/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  printf("Started\n");
  sleep(5);

  // htop VIRT will add 10 MB to the process accounting, even though process
  // doesn't really use the memory. VIRT is virtual memory usage. It includes
  // everything, including memory mapped files.
  size_t memory = 10 * 1024 * 1024;
  char* buffer = malloc(memory);
  printf("Allocated 10M\n");
  sleep(5);

  // htop RES will add 5 MB to the process accounting. RES is resident memory
  // usage i.e. what's currently in the physical memory.
  size_t i = 0;
  for (i = 0; i < memory/2; i++)
    buffer[i] = 42;
  printf("Used 5M\n");
  sleep(5);

  // For child process, VIRT and RES is the same as parent, even if the memory
  // is COW from parent. As stated in the blog: If a process uses 1 GB of
  // memory and it calls fork(), the result of forking will be two processes
  // whose RES is both 1 GB but only 1 GB will actually be used since Linux
  // uses copy-on-write.
  int pid = fork();
  if (pid != 0) {
    printf("Forked: in parent, child pid %d\n", pid);
    sleep(10);
  } else {
    printf("Forked: in child\n");
    sleep(10);
  }

  if (pid != 0) {
    for (i = memory/2; i < memory/2 + memory/5; i++)
      buffer[i] = 42;
    printf("Child used extra 2M\n");
  }
  sleep(10);
}
