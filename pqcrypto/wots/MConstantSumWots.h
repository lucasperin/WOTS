#pragma once
#include "wots/ConstantSumWots.h"
#include <array>

template <class D, int W, int T, int S>
class MConstantSumWots : public virtual ConstantSumWots<D, W, T, S> {
public:
	MConstantSumWots() noexcept {
		this->memoizeParams();
	};

	MConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W,T,S>(seed) {
		memoizeParams();
	};

protected:

	void memoizeParams(){
		for(unsigned int b = 1; b < T; b++) {
			for(unsigned int s = 0; s<= S; s++) {
				this->mparam[b-1][s] = ConstantSumWots<D,W,T,S>::constantSumLen(b,W,s);
			}
		}
	};

	mpz_class constantSumLen(unsigned int blocks, unsigned int max, unsigned int sum) {
		return this->mparam[blocks-1][sum];
	};

	//std::unordered_map<unsigned int, std::unordered_map<unsigned int, mpz_class> > mparam;
	std::array<std::array<mpz_class, S+1>, T-1> mparam;
};

