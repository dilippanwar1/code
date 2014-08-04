#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) {
  int i = 0, j = 0;

  printf("Command line arguments:\n");
  for (i = 0; i < argc; i++) {
    printf("argv[%2d]: %s\n", i, argv[i]);
  }

  printf("Environmental variables:\n");
  while (envp[j] != NULL) {
    printf("envp[%2d]: %s\n", j, envp[j]);
    j++;
  }

  char* test;

  test = (char *)malloc(16 * sizeof(int));
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      test[i][j] = 10;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      printf("%d ", test[i][j]);
  printf("\n");
}
