#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/* fixed string replacement.
usage: replace_str STRING SEARCH REP
returns the result */
char *replace_str(char *str, char *orig, char *rep) {
  static char buffer[4096];
  char *p;

  /* Is 'orig' even in 'str'? */
  if (!(p = strstr(str, orig))) {
    return str;
  }

  /* Copy characters from 'str' start to 'orig' st$ */
  strncpy(buffer, str, p-str);
  buffer[p-str] = '\0';

  sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));

  return buffer;
}

int main(int argc, char *argv[]) {
  static char mtime[512], err[512];
  struct stat st;
  int i;

  /* make sure enough args are given. if not, print usage */
  if (argc < 3) {
    fprintf(stderr, "usage: %s FORMAT FILE [...]\n\n", argv[0]);
    fprintf(stderr, "prints the mtime for each FILE given according to FORMAT\n");
    fprintf(stderr, "FORMAT is any string valid for strftime(3)\n");
    fprintf(stderr, "%%N may also be used for the filename\n");

    exit(EXIT_FAILURE);
  }

  /* loop over each FILE */
  for (i=2; i<argc; i++) {
    /* stat current file, exit on error */
    if (stat(argv[i], &st) == -1) {
      snprintf(err, 512, "%s: %s", argv[0], argv[i]);
      perror(err);

      exit(EXIT_FAILURE);
    }

    /* format output according to argv[1] */
    if (strftime(mtime, sizeof(mtime), replace_str(argv[1], "%N", argv[i]),
                 localtime(&st.st_mtime)) == 0) {
      fprintf(stderr, "%s: %s: strftime error\n", argv[0], argv[i]);

      exit(EXIT_FAILURE);
    }

    /* print the formatted string */
    printf("%s\n", mtime);
  }

  return 0;
}
