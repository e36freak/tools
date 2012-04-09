#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i;

  printf("%d arg%s:", argc - 1, argc == 2 ? "" : "s");
  for (i=1; i<argc; i++) {
    printf(" <%s>", argv[i]);
  }
  printf("\n");

  return 0;
}
