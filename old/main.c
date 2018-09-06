#include <stdio.h>      /* printf, scanf, puts, NULL */
#include "wots.c"

//gcc -ggdb main.c -lcrypto -Wall -DPARALLEL -fopenmp && time ./a.out

int main(int argc, const char* argv[]) {
	srand((unsigned int) time (NULL));
	srand(1);
	WKP kp;
	setup(&kp);
	print_wkp(&kp);
	unsigned int exp[16];
	get_wots_exponents(kp.X[0].value, kp.X[0].len, exp, 16);
	return 0;
}
