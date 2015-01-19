/*
 * Example of dynamically linked shared library (Dynamically linked at run time
 * but statically aware, i.e. static loading, dynamic linking). The libraries
 * must be available during compile/link phase. The shared objects are not
 * included into the executable component but are tied to the execution, tested
 * on ubuntu14.04.
 *
 * 1. Compile, create object code:
 *   $ gcc -Wall -fPIC -c *.c
 * This will create two object files: ctest1.o, ctest2.o
 *
 * -fPIC: Compiler directive to output position independent code, a characteristic
 *   required by shared libraries. Also see "-fpic".
 *
 * 2. Create library "libctest.so":
 *   $ gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0 *.o
 * This will create a shared library: libctest.so.1.0
 *
 * -shared: Produce a shared object which can then be linked with other objects
 *   to form an executable.
 * -Wl,options: Pass options to linker. In this example the options to be passed
 *   on to the linker are: "-soname libctest.so.1". The name passed with the "-o"
 *   option is passed to gcc.
 *
 * 3. Make the dynamic library available:
 *   $ sudo mv libctest.so.1.0 /usr/lib
 *   $ sudo ln -sf /usr/lib/libctest.so.1.0 /usr/lib/libctest.so
 *   $ sudo ln -sf /usr/lib/libctest.so.1.0 /usr/lib/libctest.so.1
 * The link to /usr/lib/libctest.so allows the naming convention for the compile
 *   flag -lctest to work.
 * The link to /opt/lib/libctest.so.1 allows the run time binding to work.
 *
 * 4. Compile main program and link with shared object library:
 *   $ gcc -Wall prog.c -lctest -o prog
 * Since the shared library is located at /usr/lib, gcc is able to find it;
 * otherwise, we need to use -L option. Note, The libraries will NOT be included
 * in the executable but will be dynamically linked during runtime execution.
 * List dependencies: ldd prog
 *
 * In order for an executable to find the required libraries to link with during
 * run time, one must configure the system so that the libraries can be found.
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
