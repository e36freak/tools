#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <error.h>
#include <errno.h>

/* usage: rep_filename STRING CHAR FILENAME
replaces a %c specifier with a filename (only the first). CHAR is 'c'
returns the result */
char *rep_filename(char *str; char *tok, char *fn) {
  
}

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
  static char mtime[512];
  struct stat st;
  int i;

  /* make sure enough args are given. if not, print usage */
  if (argc < 3) {
    fprintf(stderr, "usage: %s FORMAT FILE [...]\n\n", argv[0]);
    fprintf(stderr, "prints the mtime for each FILE given according to FORMAT\n");
    fprintf(stderr, "FORMAT is any string valid for strftime(3)\n");
    fprintf(stderr, "%%N may also be used for the filename\n");
    /* note: %%N will have issues, it's just a literal replacement */

    exit(EXIT_FAILURE);
  }

  /* loop over each FILE */
  for (i=2; i<argc; i++) {
    /* stat current file, exit on error */
    if (stat(argv[i], &st) == -1) {
      error(1, errno, "%s", argv[i]);
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



/*
Copyright Daniel Mills <dm@e36freak.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/
