#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
  printf("%s\n", curl_easy_escape(NULL, argv[1], 0));

  return 0;
}
