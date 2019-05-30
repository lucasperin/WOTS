#pragma once
#include "ByteArray.h"
#include <gmpxx.h>
#include <math.h>
#include <algorithm>

namespace encoding {

mpz_class binomial(unsigned int n, unsigned int k) {
//TODO maybe remove unsigned and add assertion??
	mpz_class ret;
	mpz_bin_uiui(ret.get_mpz_t(), n, k);
	return ret;
}

mpz_class constantSumLen(unsigned int blocks, unsigned int max, unsigned int sum)
{
	//TODO
	//Assert ret >= 0
	mpz_class ret = 0;
	unsigned int aux = floor(sum/(max+1));
    unsigned int kmax = std::min(blocks, aux);
	//assert(kmax >=0);
	for( unsigned int k = 0; k <= kmax; k++ ) {
		ret += binomial(blocks, k) * binomial(sum - (max+1)*k + blocks -1, blocks - 1) * ((k%2 == 0)?1:-1);
		//ret += binomial(blocks, k) * binomial(sum - (max+1)*k + blocks -1, blocks - 1) * std::pow(-1,k);
	}
	//assert(ret >= 0);
	return ret;
}

/*
 * COULD (but wont) assert that i <= constantSumLen(blocks,max,sum)
 * Asserting this here would ruin benchmark results.
 */
std::vector<unsigned int> toConstantSum(mpz_class& i, 
		unsigned int blocks, unsigned int max, unsigned int sum) 
{
	if (blocks == 1)
		return {sum};
	unsigned int k = 0;
	mpz_class left = 0;
	mpz_class right = constantSumLen(blocks - 1, max, sum);
	while ( !(i>= left && i < right) ) {
		k++; 
		left=right;
		right += constantSumLen(blocks - 1, max, sum-k);
	}
	std::vector<unsigned int> ret = {k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSum(i, blocks - 1, max, sum-k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}

std::vector<unsigned int> toConstantSum(ByteArray& message, 
		unsigned int blocks, unsigned int max, unsigned int sum) 
{
	//CONVERT BYTEARRAY
	mpz_class i;
	//TODO try other conversions for speed
	i.set_str(message.toHex(), 16);
	return toConstantSum(i, blocks, max, sum);
}

} /* namespace encoding */
