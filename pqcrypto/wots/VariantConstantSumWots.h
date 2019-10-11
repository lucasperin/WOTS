#pragma once
#include "wots/ConstantSumWots.h"
#include <array>

template <class D, int W, int T, int S>
class VariantConstantSumWots : public ConstantSumWots<D, W, T, S> {
public:

	VariantConstantSumWots() noexcept {};
	VariantConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W,T,S>(seed) {};

	virtual std::vector<unsigned int> genFingerprint(ByteArray& data) {
		ByteArray aux = this->digest(data);
		mpz_class i;
		i.set_str(std::to_string(aux), 16);
		std::vector<unsigned int> ret;
		int timeout = 0;
		do{
			aux = this->digest(aux);
			i.set_str(std::to_string(aux), 16);
			ret = this->toConstantSumVariant(i, T, W, S);
			timeout++;
		}while(ret.size() <T && timeout < 20);
		if(timeout>=20){
			return {};
		}
		return ret;
	}

protected:

	virtual std::vector<unsigned int> toConstantSumVariant(mpz_class& i, 
			int blocks, int max, int sum) 
	{
		if (blocks == 1)
			return {(unsigned)sum};
		int k = 0;
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
		if(sum-k > max)
			return {};
		std::vector<unsigned int> ret = {(unsigned int)sum-k};
		i -= left;
		std::vector<unsigned int> ret2 = toConstantSumVariant(i, blocks - 1, max, k);
		ret.insert(ret.end(), ret2.begin(), ret2.end());
		return ret;
	}


};
