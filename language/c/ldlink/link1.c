/*
 * Compile with: gcc link1.c link2.c
 *
 * Libraries are typically names with the prefix "lib". This is true for all
 * the C standard libraries. When linking, the command line reference to the
 * library will not contain the library prefix or suffix. Thus the following
 * link command: "gcc src-file.c -lm -lpthread". The libraries referenced in
 * this example for inclusion during linking are the math library and the thread
 * library. They are found in /usr/lib/libm.a and /usr/lib/libpthread.a.
 */

#include <stdio.h>

void foo();

int x = 4;
int y = 9;

int main(void) {
  foo();
  printf("%p: %d\n", &x, x);    /* 0x105b60018: 4 */
  printf("%p: %d\n", &y, y);    /* 0x105b6001c: 9 */
}
