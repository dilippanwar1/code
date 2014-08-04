#include <stdio.h>


int x = 1;
int y = 1;

int modify1() {
  x = 4;
  y = 4;
}

void printY() {
  printf("%d", y);
}
