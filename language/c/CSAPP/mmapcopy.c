#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


void mmapcopy(char * filename) {
  char * buf = NULL;
  int fd = 0;
  struct stat st;

  if ((fd = open(filename, O_RDONLY)) < 0) {
    printf("error open file\n");
    exit(1);
  }

  fstat(fd, &st);
  buf = (char*)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

  write(1, buf, st.st_size);
  munmap(buf, st.st_size);
}



int main(int argc, char** argv) {

  if (argc != 2) {
    printf("Please specify file\n");
    exit(1);
  }

  mmapcopy(argv[1]);
}


