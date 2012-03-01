#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i, err;
  err = 0;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "no filenames provided");
    return 2;
  }

  for (i=0; i<argc-1; i++) {
    if (unlink(argv[i+1])) {
      fprintf(stderr, "%s: %s\n", argv[i+1], strerror(errno));
      err = 1;
    }
  }

  return err;
}
