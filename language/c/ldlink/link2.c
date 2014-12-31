#include <stdio.h>

/* Weak symbol */
int x;

int foo(void) {
  printf("%p: %d\n", &x, x);    /* 0x105b60018: 4 */
}
