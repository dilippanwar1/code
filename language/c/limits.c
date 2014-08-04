#include <stdio.h>
#include <stdlib.h>


int foo(unsigned int a) {

  int b = 0;

  switch (a+1) {
  case 0:
    b = a>>1;
  case 1:
    b = ~b;
  case 2:
    b = -b;
    break;
  case 3:
    b = a;
  case 4:
    b = a^b;
    break;
  }

  return b;
}


int main(void) {

  int x = 10;
  int y = 20;
  int z = 1;
  unsigned int a = 0xffffffff;
  unsigned int b = 1;
  unsigned long d = a + b;

  printf("%ld\n", d);
  printf("%d", x^y^(~x) == (~y));
  printf("%d", (x^y^(~x) - y) == (y^x^(~y) - x));
  printf("%d", foo(0));
  printf("%d", foo(1));
  printf("%d", foo(2));
  printf("%d", foo(3));
  printf("%d", foo(0xFFFFFFFF));
}
