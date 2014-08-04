#include <stdio.h>
#include <stdlib.h>

int main(void) {

  char *p = (char*)malloc(sizeof(int) * 2);

  free(p);
  free(p);                      /* core dump */

  return 0;
}
