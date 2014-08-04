#include <stdio.h>
#include <stdlib.h>


int foo1(int a) {
  return a * 1;
}

int foo2(int a) {
  return a * 2;
}

int foo3(int a) {
  return a * 3;
}


int main(void) {

  /* 'f' is a function pointer. */
  int (*f)(int) = foo2;
  printf("%d\n", foo2(1));
  printf("%d\n", (*f)(1));

  /* 'p' is an array of function pointers. */
  int (*p[3]) (int) = {foo1, foo2, foo3};
  printf("%d\n", (*p[0])(1));
  printf("%d\n", (*p[1])(1));
  printf("%d\n", (*p[2])(1));

  /* 'g' is xxx. */
  int (*g(int))[3];

}
