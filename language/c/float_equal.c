#include <stdio.h>
#include <stdlib.h>


int main(void) {

  float f1[10];
  float f2;

  printf("%p\n", &f2);

  f1[0] = 1;
  f2 = 1;

  if (f1[0] == f2) {
    printf("Yes\n");
  }
}
