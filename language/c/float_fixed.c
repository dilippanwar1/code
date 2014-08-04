#include <stdio.h>


int float2fixed(float num) {
  return (int)(num * 256);
}

float fixed2float(int num) {
  return num / 256.0;
}

void fixed2string(int num) {

  int i;
  int before = num >> 8;
  int after = 0;
  int weight = 1;

  for (i = 0; i < 8; i++)
    weight *= 10;

  for (i = 7; i >= 0; i--) {
    weight = weight / 2;
    after += weight * !!((1 << i) & num);
  }

  printf("%d.%d\n", before, after);
}

int main(void) {

  int x = float2fixed(1.313);
  int y = float2fixed(23.449);

  //int r = (a * b) >> 8;
  int temp = (x * y);
  int r = temp + ((temp & 1<<(8-1))<<1);
  r >>= 8;

  printf("%f\n", fixed2float(r));
}
