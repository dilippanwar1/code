/*
 * Example of dynamically loaded shared library. These libraries are dynamically
 * loaded/unloaded and linked during execution.
 *  $ gcc -rdynamic -o prog prog.c -ldl
 * Where -ldl linked dlfcn.h.
 *
 * Dynamic linking actually means "dynamic linking, static loading". This is how
 * dynamic library specified at compile time usually work. The executable contains
 * a reference to the dynamic/shared library, but the symbol table is missing or
 * incomplete. Both loading and linking occur at process start.
 *
 * Dynamic loading acutally means "dynamic linking, dynamic loading". This is
 * what happens when calling dlopen.  The object file is loaded dynamically under
 * program control, and symbols bothe in the calling program and in the library
 * are resolved based on the process's memory layout at that time. The library
 * doesn't need to present during compile time.
 */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "ctest.h"

int main(int argc, char **argv)
{
  void *lib_handle;
  double (*fn)(int *);
  int x;
  char *error;

  lib_handle = dlopen("/usr/lib/libctest.so", RTLD_LAZY);
  if (!lib_handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  fn = dlsym(lib_handle, "ctest1");
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(1);
  }

  (*fn)(&x);
  printf("Valx=%d\n",x);

  dlclose(lib_handle);
  return 0;
}
