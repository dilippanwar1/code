#include <stdio.h>
#include <stdlib.h>


int main(void) {

  int *p = (int *) malloc(sizeof(int) * 1);
  printf("%p\n", p);
  p = (int *) malloc(sizeof(int) * 1);
  printf("%p\n", p);

  /* ignore free */
}
