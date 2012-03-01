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
