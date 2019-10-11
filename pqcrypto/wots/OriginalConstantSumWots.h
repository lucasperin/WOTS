#pragma once
#include "wots/ConstantSumWots.h"
#include <iostream>


template <class D,int W, int T, int S>
class OriginalConstantSumWots : public virtual ConstantSumWots<D, S, T, S> {
	public:
	OriginalConstantSumWots() noexcept {};
	OriginalConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W,T,S>(seed) {};

protected:

	/*
	 * Original implementation from paper.
	 */
	virtual std::vector<unsigned int> toConstantSum(mpz_class& i, 
			int blocks, int max, int sum) 
	{
		(void)max;
		if (blocks == 1)
			return {(unsigned)sum};
		unsigned int k = 0;
		mpz_class a = 1;
		mpz_class left = 0;
		mpz_class right = a;
		while ( !(i>= left && i < right) ) {
			k++; 
			a = a*(k+blocks-2);
			mpz_divexact_ui(a.get_mpz_t(), a.get_mpz_t(), k);
			left=right;
			right += a;
		}
		std::vector<unsigned int> ret = {sum-k};
		i -= left;
		std::vector<unsigned int> ret2 = toConstantSum(i, blocks - 1, max, k);
		ret.insert(ret.end(), ret2.begin(), ret2.end());
		return ret;
	}

};
