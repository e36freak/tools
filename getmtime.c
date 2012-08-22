#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct stat st;
  char mtime[128];
  int i;

  if (argc < 3) {
    fprintf(stderr, "usage: %s FORMAT FILE [...]\n\n", argv[0]);
    fprintf(stderr, "prints the mtime for each FILE given according to FORMAT\n");
    fprintf(stderr, "FORMAT is any string valid for strftime(3)\n");

    return 1;
  }

  for (i=2; i<argc; i++) {
    if (stat(argv[i], &st) == -1) {
      perror(argv[0]);
      return 1;
    }

    strftime(mtime, sizeof(mtime), argv[1], localtime(&st.st_mtime));
    printf("%s\n", mtime);
  }

  return 0;
}
