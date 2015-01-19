/*
 * Example of static link, tested on ubuntu14.04:
 *
 * 1. Compile:
 *   $ gcc -Wall -c ctest1.c ctest2.c
 * This will create two object files: ctest1.o, ctest2.o
 *
 * 2. Create library "libctest.a":
 *   $ ar -cvq libctest.a ctest1.o ctest2.o
 * This will create a static library: libctest.a. List files in the
 * library: $ ar -t libctest.a
 *
 * 3. Linking with the library:
 *   $ gcc -o prog prog.c libctest.a
 *   Or:
 *   $ gcc -o prog prog.c -L./ -lctest
 * Note gcc options:
 *  -l: Search the library named 'library' when linking.
 *  -L: Add directory dir to the list of directories to be searched for -l.
 *  -I: Add the directory dir to the head of the list of directories to be
 *      searched for header files.
 */

#include <stdio.h>

void ctest1(int *i);
void ctest2(int *i);

int main() {
  int x;

  ctest1(&x);
  printf("Valx=%d\n",x);

  return 0;
}
