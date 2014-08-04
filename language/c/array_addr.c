#include <stdio.h>
#include <stdlib.h>


int main(void) {

  int aa[10];

  printf("%p\n", &aa);
  printf("%p\n", &aa[2]);
  printf("%ld\n", (long)&aa[2] - (long)aa);
}
