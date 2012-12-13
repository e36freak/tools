#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
  mpz_t i, m, t;
  mpz_init_set_si(i, 2);
  mpz_init(t);
  mpz_init_set_str(m, argv[argc-1], 10);
  mpz_t last, cur;
  mpz_init_set_si(last, 1);
  mpz_init_set_si(cur, 1);
  mpz_t temp;
  mpz_init(temp);

  while (mpz_cmp(i, m) <= 0) {
    mpz_add_ui(i, i, 1);
    mpz_set(temp, cur);
    mpz_add(cur, last, cur);
    mpz_set(last, temp);
  }

  gmp_printf("%Zd\n", last);
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
