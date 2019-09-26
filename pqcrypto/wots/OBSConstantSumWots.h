#pragma once
#include "wots/BSConstantSumWots.h"

template <class D, int W, int T, int S>
class OBSConstantSumWots : public virtual BSConstantSumWots<D, W, T, S> {
public:
	OBSConstantSumWots() noexcept {};
	OBSConstantSumWots(const ByteArray& seed) noexcept : BSConstantSumWots<D,W,T,S>(W,seed) {};

protected:

	virtual mpf_class prod_diff(int p, int range) {
		mpf_class ret = p;
		for(int i=1; i <=range; i++){
			ret *= p-i;
		}
		return ret;
	}

	virtual mpz_class magic(int blocks, int head, int j) {
		if(head + blocks-1-j < blocks || blocks < 0) {
		   return this->binomial(head + blocks, blocks);
		}
		mpf_class a(this->binomial(head+ blocks -1 -j, blocks));
		a*= ((prod_diff(head + blocks, j)/prod_diff(head,j)) -1);
		return mpz_class(a);
	}

	virtual mpz_class rank(int blocks, int max, int sum, int j) {
		mpz_class ret = 0;
		int aux = floor(float(sum)/float(max+1));
		int kmax = std::min(blocks, aux);
		int head;
		for(int k = 0; k <= kmax; k++ ) {
			head = sum-(max+1)*k;
			ret += std::pow(-1,k) * this->binomial(blocks, k) * magic(blocks, head, j);
		}
		return ret;
	};
};
