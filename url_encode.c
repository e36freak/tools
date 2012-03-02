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
