#pragma once
#include "wots/ConstantSumWots.h"
#include <iostream>


template <class D, int W, int T, int S>
class BSConstantSumWots : public virtual ConstantSumWots<D, W, T, S> {
	public:
	mpz_class prank(unsigned int blocks, unsigned int max, unsigned int sum, unsigned int j) {
		return this->rank(blocks, max, sum, j);
	};

	mpz_class pconst(unsigned int blocks, unsigned int max, unsigned int sum) {
		return this->constantSumLen(blocks, max, sum);
	};

protected:

	mpz_class rank(int blocks, int max, int sum, int j) {
		mpz_class ret = 0;
		int aux = floor(float(sum)/float(max+1));
		int kmax = std::min(blocks, aux);
		for(int k = 0; k <= kmax; k++ ) {
			ret += std::pow(-1,k) * this->binomial(blocks, k) * (
				   this->binomial(sum - (max+1)*k + blocks, blocks)
				 - this->binomial(sum - (max+1)*k + blocks -1 -j, blocks) 
				 );
		}
		return ret;
	};

	/*
	 * std::upper_bound (C++20) implementation for the binary search
	 * https://en.cppreference.com/w/cpp/algorithm/lower_bound
	 */
	virtual std::vector<unsigned int> toConstantSum(mpz_class& I,
			unsigned int blocks, unsigned int max, unsigned int sum)
	{
		//Surpress
		(void)blocks;
		(void)max;
		(void)sum;

		unsigned int count, k, it, step;
		std::vector<unsigned int> ret;
		unsigned int s = S;
		for (unsigned int b = 1; b <= T; b++ ) {
			count = ( W < s)?W:s;
			k = 0;
			mpz_class keep;
			while ( count > 0 ) {
				it = k;
				step = count/2;
				it += step;
				keep = this->rank(T-b, W, s, it);
				if ( keep < I ) {
					k = ++it;
					count -= step + 1;
				} else {
					count = step;
				}
			}
			ret.push_back(k);
			if(k>0) {
				I -= this->rank(T-b, W, s, k-1);
				s -= k;
			}
		}
		return ret;
	}

};
