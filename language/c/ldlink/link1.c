/* compile with: gcc link1.c link2.c */
#include <stdio.h>

void foo();

int x = 4;
int y = 9;

int main(void) {

  foo();
  printf("%p\n", &x);
  printf("%p\n", &y);
}
