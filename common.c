#include <stdio.h>
#include <string.h>
#include "common.h"

void println_file_type(__mode_t mode) {
  char *ptr;
  if (S_ISREG(mode))
    ptr = "regular file";
  else if (S_ISDIR(mode))
    ptr = "directory";
  else if (S_ISCHR(mode))
    ptr = "character special file";
  else if (S_ISBLK(mode))
    ptr = "block special file";
  else if (S_ISFIFO(mode))
    ptr = "pipe";
  else if (S_ISLNK(mode))
    ptr = "symbolic link";
  else
    ptr = "unknown";
  PRINTLN("file type: %s", ptr);
}

void print_time(struct timespec time, char *form) {
  if (form == NULL){
    form = "%Y/%m/%d %H:%M:%S";
  }
  char buffer[26];
  strftime(buffer, sizeof(buffer), form, localtime(&time.tv_sec));
  printf("%s", buffer);
}

void println_user(unsigned uid) {
  struct passwd *pwd = getpwuid(uid);
  PRINTLN("Uid: %u/%s", uid, pwd->pw_name);
}

void println_group(unsigned gid) {
  struct group *gr = getgrgid(gid);
  PRINTLN("Gid: %u/%s", gid, gr->gr_name);
}

void print_permissions(__mode_t st_mode) {
  printf((S_ISDIR(st_mode)) ? "d" : "-");
  printf((st_mode & S_IRUSR) ? "r" : "-");
  printf((st_mode & S_IWUSR) ? "w" : "-");
  printf((st_mode & S_IXUSR) ? "x" : "-");
  printf((st_mode & S_IRGRP) ? "r" : "-");
  printf((st_mode & S_IWGRP) ? "w" : "-");
  printf((st_mode & S_IXGRP) ? "x" : "-");
  printf((st_mode & S_IROTH) ? "r" : "-");
  printf((st_mode & S_IWOTH) ? "w" : "-");
  printf((st_mode & S_IXOTH) ? "x" : "-");
}

char *get_abs_path(char *p, char *f) {
  char *prefix = malloc(strlen(p) + 1), *filename = malloc(strlen(f) + 1);
  strcpy(prefix, p);
  strcpy(filename, f);

  char *path;
  int s1 = strlen(prefix), s2 = strlen(filename);
  if (prefix[s1 - 1] != '/') {
    prefix = realloc(prefix, sizeof(char) * (s1 + 2));
    prefix[s1] = '/';
    prefix[s1 + 1] = '\0';
  }

  s1++;
  path = malloc(sizeof(char) * (s1 + s2 + 2));
  strcpy(path, prefix);
  strcat(path, filename);
  free(prefix);
  return path;
}
