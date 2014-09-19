#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(void) {

  int fd1 = open("bool.c", O_RDONLY);
  int fd2 = open("bool.c", O_RDONLY);
  int fd3 = open("bool.c", O_RDONLY);

  if (errno != 0) {
    printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
  }

  printf("%d, %d, %d\n", fd1, fd2, fd3);

  /* List open file descriptor using ls -l /proc/{PID}/fd */
  /* 0 -> /dev/pts/29 */
  /* 1 -> /dev/pts/29 */
  /* 2 -> /dev/pts/29 */
  /* 3 -> /home/deyuan/code/language/c/bool.c */
  /* 4 -> /home/deyuan/code/language/c/bool.c */
  /* 5 -> /home/deyuan/code/language/c/bool.c */

  close(fd1);
  close(fd2);
  close(fd3);
  close(fd3);                   /* ok to close again */
}
