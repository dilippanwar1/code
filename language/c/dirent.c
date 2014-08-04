#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int main(void) {

  DIR * dirp = opendir(".");
  struct dirent * dp;

  while ((dp = readdir(dirp)) != NULL)
    printf("%s\n", dp->d_name);

  return 0;
}
