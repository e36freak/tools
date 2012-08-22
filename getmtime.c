#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct stat st;
  char mtime[512], err[512];
  int i;

  if (argc < 3) {
    fprintf(stderr, "usage: %s FORMAT FILE [...]\n\n", argv[0]);
    fprintf(stderr, "prints the mtime for each FILE given according to FORMAT\n");
    fprintf(stderr, "FORMAT is any string valid for strftime(3)\n");

    exit(EXIT_FAILURE);
  }

  for (i=2; i<argc; i++) {
    if (stat(argv[i], &st) == -1) {
      sprintf(err, "%s: %s", argv[0], argv[i]);
      perror(err);

      exit(EXIT_FAILURE);
    }

    if (strftime(mtime, sizeof(mtime), argv[1], localtime(&st.st_mtime)) == 0) {
      fprintf("%s: %s: strftime error\n", argv[0], argv[i]);

      exit(EXIT_FAILURE);
    }

    printf("%s\n", mtime);
  }

  return 0;
}
