#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s\n", "no URL provided");
    return 1;
  }

  printf("%s\n", curl_easy_escape(NULL, argv[1], 0));

  return 0;
}
