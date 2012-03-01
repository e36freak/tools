#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i;

  printf("%d arg%s: ", argc - 1, argc > 2 ? "s" : "");
  for (i=1; i<argc; i++) {
    printf((i==argc-1)?"<%s>\n":"<%s> ", argv[i]);
  }

  return 0;
}
