#include <stdio.h>
#include "mm.h"


int main(void) {
  mm_init();

  char *p = (char*)mm_malloc(1);
  *p = 2;
  printf("%d\n",*p);
  
  return 0;
}
