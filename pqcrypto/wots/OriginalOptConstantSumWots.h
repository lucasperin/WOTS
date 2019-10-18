#pragma once
#include "wots/ConstantSumWots.h"
#include <iostream>


template <class D,int W, int T, int S>
class OriginalOptConstantSumWots : public virtual ConstantSumWots<D, S, T, S> {
	public:
	OriginalOptConstantSumWots() noexcept {};
	OriginalOptConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W,T,S>(seed) {};

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
		mpz_class left = 0;
		mpz_class right = this->binomial(sum+blocks-2,sum);
		mpz_class a = right;
		while ( !(i>= left && i < right) ) {
			k++; 
			left=right;
			a = a*(sum-k+1);
			mpz_divexact_ui(a.get_mpz_t(), a.get_mpz_t(), (sum-k+1)+blocks-2);
			right += a;
		}
		std::vector<unsigned int> ret = {k};
		i -= left;
		std::vector<unsigned int> ret2 = this->toConstantSum(i, blocks - 1, max, sum-k);
		ret.insert(ret.end(), ret2.begin(), ret2.end());
		return ret;
	}

};
