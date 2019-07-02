/*
 * floyd.c
 *
 *  Created on: Jan 9, 2019
 *      Author: anonymous
 */
#include "gmp.h"

/* Method *******************************************************************/
void
prfloyd(mpz_t factor, const mpz_t n, mpz_t start)
{	mpz_init(factor);				// possible factor
	mpz_t x;	mpz_init(x);			// tortoise
	mpz_t y;	mpz_init(y);			// hare
	mpz_t g;	mpz_init(g);			// result of gcd
	mpz_t tmp;	mpz_init(tmp);			// result of (x - y)
	mpz_init_set(x, start);				// x = tortoise = start
	mpz_init_set(y, start);				// y = hare = start

	do
	{ 	mpz_mul(x, x, x);			// x * x
		mpz_add_ui(x, x, 1);			// x + 1
	  	mpz_mod(x, x, n);			// x % n

	  	mpz_mul(y, y, y);			// y * y
	  	mpz_add_ui(y, y, 1);			// y + 1
	  	mpz_mod(y, y, n);			// y % n

	  	mpz_mul(y, y, y);			// y * y
	  	mpz_add_ui(y, y, 1);			// y + 1
	  	mpz_mod(y, y, n);			// y % n

	  	mpz_sub(tmp, x, y);			// x - y
	  	mpz_abs(tmp, tmp);			// abs
	  	mpz_gcd(g, tmp, n);			// gcd
	}while (mpz_cmp_ui(g,1) == 0); 			// end do/while
	mpz_set(factor, g);				// load factor

	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(g);
	mpz_clear(tmp);
} // end prfloyd()
