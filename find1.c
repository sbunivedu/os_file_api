#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "common.h"

void find(char *, int);

int main(int argc, char *argv[]) {
  char *path;
  if (argc == 2) {
    path = argv[1];
  } else {
    path = "./";
  }
  find(path, 0);

  return 0;
}

void find(char *path, int indent) {
  DIR *dir = opendir(path);
  struct dirent *d;
  struct stat st;

  while ((d = readdir(dir)) != NULL) {
    if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) {
      char *p = get_abs_path(path, d->d_name);
      assert(stat(p, &st) == 0);
      if (S_ISDIR(st.st_mode)) {
        printf("%*c-%s:\n", indent, ' ', d->d_name);
        find(p, indent+1);
        free(p);
      } else {
        printf("%*c%s\n", indent, ' ', d->d_name);
      }
    }
  }
}

/*
gcc -o find find.c common.c
*/
