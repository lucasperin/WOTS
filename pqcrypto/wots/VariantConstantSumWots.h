#pragma once
#include "wots/ConstantSumWots.h"
#include <array>

template <class D, int W, int T, int S>
class VariantConstantSumWots : public virtual ConstantSumWots<D, W, T, S> {
public:


	virtual std::vector<unsigned int> genFingerprint(ByteArray& data) {
		ByteArray aux = this->digest(data);
		mpz_class i;
		i.set_str(std::to_string(aux), 16);
		std::vector<unsigned int> ret;
		int timeout = 20;
		if(W==S) {
			ret = this->toConstantSumOriginal(i, T, S);
		} else {
			do{
				aux = this->digest(aux);
				i.set_str(std::to_string(aux), 16);
				ret = this->toConstantSum(i, T, S);
				timeout++;
			}while(ret.size() <T && timeout < 20);
		}
		if(timeout>=20){
			std::cout << "e";
			return {};
		}
		//for (const auto i : ret)
			//std::cout << i << ' ';
		//std::cout<<std::endl;
		return ret;
	}

protected:

	virtual std::vector<unsigned int> toConstantSum(mpz_class& i, 
			int blocks, int sum) 
	{
		if (blocks == 1)
			return {(unsigned)sum};
		unsigned int k = 0;
		mpz_class a = 1;
		mpz_class left = 0;
		mpz_class right = a;
		while ( !(i>= left && i < right) ) {
			k++; 
			a = a*(k+blocks-2)/k;
			left=right;
			right += a;
		}
		if(sum-k > W)
			return {};
		std::vector<unsigned int> ret = {sum-k};
		i -= left;
		std::vector<unsigned int> ret2 = toConstantSum(i, blocks - 1, k);
		ret.insert(ret.end(), ret2.begin(), ret2.end());
		return ret;
	}


};
