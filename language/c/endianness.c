#include <stdio.h>
#include <limits.h>


int A[64][64];
int B[1][1];


int main(void) {

  int a;
  long b;
  unsigned c;

  a = 0x01020304;
  b = 0x0102030405060708;
  c = 100;

  printf("%d\n", INT_MAX - INT_MIN);
  printf("%ld\n", sizeof(c));

  printf("%p\n%p\n%p\n", A, B, &A[63][63]);
  printf("%x\n", (int)B-(int)A);
}
