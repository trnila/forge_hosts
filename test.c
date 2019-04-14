#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  FILE* a = fopen("/etc/hosts", "r");
  if(!a) { 
    exit(1);
  }

  char buf[128];
  int n;
  while((n = fread(buf, 1, sizeof(buf), a)) > 0) {
    write(1, buf, n);
  }

}
