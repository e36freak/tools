#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

/* sane URL length limit */
#define LEN 4096

int main(int argc, char *argv[]) {
  char *p, out[LEN], cur[LEN];
  int i=0;

  /* check to make sure an arg is provided */
  if (argc < 2) {
    fprintf(stderr, "%s\n", "no URL provided");
    return 1;
  }

  /* tokenize on '/' */
  for (p = strtok(argv[1], "/"); p; p = strtok(NULL, "/")) {
    sprintf(cur, "%s", p);

    /* for first iteration, do not escape, and append an extra '/' if it
       ends with ':' to supply the protocol */
    if (!i++) {
      if (cur[strlen(cur) - 1] == ':') {
        sprintf(out, "%s/", cur);
      } else {
        sprintf(out, "%s", p);
      }

      continue;
    }

    /* escape string, append to out */
    sprintf(out, "%s/%s", out, curl_easy_escape(NULL, cur, 0));
  }

  /* print the damn thing */
  printf("%s\n", out);

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
