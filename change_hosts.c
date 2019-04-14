#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char hosts_path[FILENAME_MAX];
FILE*(*next_fopen)(const char *, const char *);

void init(void) __attribute__((constructor));
void init(void) {
    char* new_path = getenv("INJECT_HOSTS");
    if(!new_path) {
      fprintf(stderr, "Missing environment INJECT_HOSTS set\n");
      exit(1);
    }

    if(strlen(new_path) >= sizeof(hosts_path)) {
      fprintf(stderr, "INJECT_HOSTS path too long\n");
      exit(1);
    }
    strcpy(hosts_path, new_path);

    next_fopen = dlsym(RTLD_NEXT, "fopen");
    if(!next_fopen) {
      fprintf(stderr, "Could not get fopen symbol\n");
      exit(1);
    }
}

FILE *fopen(const char *pathname, const char *mode) {
//  printf("OPENED: %s\n", pathname);
  if(strcmp(pathname, "/etc/hosts") == 0) {
     pathname = hosts_path;
  }

  return next_fopen(pathname, mode);
}
