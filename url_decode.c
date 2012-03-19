#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
  /* check to make sure an arg is provided */
  if (argc < 2) {
    fprintf(stderr, "%s\n", "no URL provided");
    return 1;
  }

  /* decode the url, print */
  printf("%s\n", curl_easy_unescape(NULL, argv[1], 0, NULL));

  return 0;
}
