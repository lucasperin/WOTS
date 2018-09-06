#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <gmp.h>

typedef struct{
	unsigned char value[EVP_MAX_MD_SIZE];
	unsigned int len;
} KeyBlock; /* Hash output */

typedef struct{
	int w, n, t, t1, t2;
	KeyBlock* X;
	KeyBlock* Y;
} WKP; /* WOTS Key Pair */

/**
 * Randomize bytes in KeyBlock using rand()
 */
void randomize_block(KeyBlock* block, unsigned int len) {
	for (unsigned int i = 0; i < len; i++)	{
		block->value[i] = rand();
	}
	block->len = len;
}

/**
 * hash bytes n times, recursively.
 */
void hash(char* hashname, KeyBlock* in, KeyBlock* out, unsigned int n) {
	const EVP_MD* md = EVP_get_digestbyname(hashname);
	if(!md) {
		printf("Unknown message digest %s\n", hashname);
		exit(1);
	}
	
	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();

	memcpy(out->value, in->value, in->len);
	for( unsigned int i = 1; i < n; i++) {
		EVP_DigestInit_ex(mdctx, md, NULL);
		EVP_DigestUpdate(mdctx, out->value, in->len);
		EVP_DigestFinal_ex(mdctx, out->value, &out->len);
		if(!EVP_MD_CTX_reset(mdctx)) {
			printf("Could not reset md context.\n");
			exit(1);
		}
	}
	EVP_MD_CTX_free(mdctx);
}

void print_bytes(unsigned char* bytes, int len) {
	for (int i = 0; i < len; i++) {
		printf("%.2X", bytes[i]);
	}
}


void get_wots_exponents(unsigned char* bytes, int blen, unsigned int* exp, int explen) {
	//create bigint with bytes
	mpz_t bi;
	mpz_init(bi);
	char strbytes[(2*blen)+1];
	char * aux = strbytes;
	for(int i = 0; i < blen; i++){
		aux += sprintf(aux, "%.2X", bytes[i]);
	}
	mpz_set_str(bi, strbytes, 16);
	
	//create bitmask of size explen
	mpz_t mask;
	mpz_init(mask);
	mpz_set_ui(mask, 1);
	mpz_mul_2exp(mask, mask, explen);
	mpz_sub_ui(mask, mask, 1);
	
	
	//assign exponents
	mpz_t ret;
	mpz_init(ret);
	int t = ((blen*8) + explen -1)/explen;
	for(int i = 0; i < t; i++) {
		mpz_and(ret, bi, mask);
		exp[i] = (unsigned int) mpz_get_ui(ret);
		mpz_tdiv_q_2exp(bi,bi,explen);
	}		
	

	mpz_clear(bi);
}

/**
 * Generates the signature key X using parameters in WKP
 */
void generate_sig_key(WKP* kp) {
	if(!kp->t){
		printf("use setup(WKP*)");
		exit(1);
	}
	kp->X = malloc(kp->t * sizeof(KeyBlock));
	#ifdef PARALLEL
	#pragma omp parallel for
	#endif
	for(int i = 0; i < kp->t; i++) {
		randomize_block(&kp->X[i], kp->n/8);
	}
}

/**
 * Generates the verification key X using parameters in WKP
 */
void generate_ver_key(WKP* kp) {
	if(!kp->t){
		printf("use setup(WKP*)");
		exit(1);
	}
	kp->Y = malloc(kp->t * sizeof(KeyBlock));
	int exp = 1 << kp->w;
	double time = omp_get_wtime();
	#ifdef PARALLEL
	#pragma omp parallel for
	#endif
	for(int i = 0; i < kp->t; i++) {
		hash("sha256", &kp->X[i], &kp->Y[i], exp);
	}
	time = time - omp_get_wtime();
	printf(">>Benchmark: %f usecs in %s\n", time, __func__);
}

/**
 * Setup the WKP struct with default parameters.
 * Initializes Signature key and Verification key
 */
void setup(WKP* kp) {
	kp->w = 16;
	kp->n = 256;
	kp->t = 18;
	kp->t1 = 16;
	kp->t2 = 2;
	generate_sig_key(kp);
	generate_ver_key(kp);
}

void WOTS_SIGN(unsigned char* bytes, WKP* kp) {

}

void WOTS_VERIFY(){}


/**
 * Print util function
 **/
void print_wkp(WKP* kp) {
	printf("WKP Params:\nw=%d n=%d t=%d, t1=%d t2=%d\n",
		kp->w, kp->n, kp->t, kp->t1, kp->t2);
	printf("--- Signature Key ---\n");
	for(int i = 0; i < kp->t; i++){
		printf("X%d:\t",i); 
		for(int h = 0; h < kp->X[i].len; h++) {
			printf("%.2X", kp->X[i].value[h]);
		}
		printf("\t len: %d Bytes\n", kp->X[i].len);
	}
	printf("--- Verification Key ---\n");
	for(int i = 0; i < kp->t; i++){
		printf("Y%d:\t",i); 
		for(int h = 0; h < kp->Y[i].len; h++) {
			printf("%.2X", kp->Y[i].value[h]);
		}
		printf("\t len: %d Bytes\n", kp->Y[i].len);
	}
}
