#include <stdio.h>
extern void modify1();
extern void printY();

double x;

void modify() {
  x = 100;
}

int main(void) {
  modify1();
  modify();

  printY();
}
