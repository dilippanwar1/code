#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *p;

  printf("%ld\n", sizeof(10));
  printf("%ld\n", sizeof(10L));
  printf("%ld\n", sizeof(p));
}
