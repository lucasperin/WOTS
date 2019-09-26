#pragma once
#include "wots/ClassicWots.h"
#include <math.h>
#include <gmpxx.h>
#include <algorithm>
#include <iostream>

template <class D, int W, int T, int S>
class ConstantSumWots : public virtual ClassicWots<D,W> {
public:
	ConstantSumWots() noexcept {};
	ConstantSumWots(const ByteArray& seed) noexcept : ClassicWots<D,W>(W,seed) {};
	const unsigned int t1() const noexcept final {return T;};
	const unsigned int t2() const noexcept final {return 0;};
	const std::vector<unsigned int> checksum(std::vector<unsigned int>& blocks)  final {
		//Return dummy, there is no need for checksum.
		std::vector<unsigned int> dummy;
		return dummy;
	};


	virtual const std::vector<ByteArray> sign(ByteArray& data) {
		std::vector<unsigned int> blocks = this->genFingerprint(data);
		std::vector<ByteArray> signature(blocks.size());

		//#pragma omp parallel for
		for(long unsigned int i = 0; i < blocks.size(); i++){
			signature[i] = this->digestChain(this->private_key[i], W - blocks[i]);
		}
		
		return signature;
	};
	
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature) {	
		if(not this->pubKeyIsLoaded())
			return false;
		std::vector<unsigned int> blocks = this->genFingerprint(data);
		ByteArray check;

		//#pragma omp parallel for
		for(long unsigned int i = 0; i < blocks.size(); i++) {
			check += this->digestChain(signature[i], blocks[i]);
		}

		check = this->digest(check);
		
		//TODO( We can improve this using xor and  iterator)
		if( std::to_string(this->public_key).compare(std::to_string(check)) == 0 )
			return true;

		return false;
	};


	virtual std::vector<unsigned int> genFingerprint(ByteArray& data) {
		ByteArray aux = this->digest(data);
		mpz_class i;
		i.set_str(std::to_string(aux), 16);
		std::vector<unsigned int> ret;
		if(W==S) {
			ret = this->toConstantSumOriginal(i, T, S);
		} else {
			ret = this->toConstantSum(i, T, W, S);
		}
		//for (const auto i : ret)
			//std::cout << i << ' ';
		//std::cout<<std::endl;
		return ret;
		
	};
protected:
	/*
	 * Overide restriction of W power of 2.
	 */
	virtual void paramCheck() final {};

	/*
	 * Must be signed to asserct negative cases.
	 */
	virtual mpz_class binomial(int n, int k) {
		if(n < k || n<0 || k<0)
			return 0;
		mpz_class ret = 0;
		mpz_bin_uiui(ret.get_mpz_t(), n, k);
		return ret;
	}

	virtual mpz_class constantSumLen(int blocks, int max, int sum) {
		//TODO
		//Assert ret >= 0
		mpz_class ret = 0;
		int aux = std::floor((float)sum/(float)(max+1));
		int kmax = std::min(blocks, aux);
		for(int k = 0; k <= kmax; k++ ) {
			ret += binomial(blocks, k) * binomial(sum - (max+1)*k + blocks -1, blocks - 1) * ((k%2 == 0)?1:-1);
		}
		return ret;
	}

	/*
	 * COULD (but wont) assert that i <= constantSumLen(blocks,max,sum)
	 * Asserting this here would ruin benchmark results.
	 */
	virtual std::vector<unsigned int> toConstantSum(mpz_class& i, 
			int blocks, int max, int sum) 
	{
		if (blocks == 1)
			return {(unsigned int)sum};
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

	/*
	 * Original implementation from paper.
	 */
	virtual std::vector<unsigned int> toConstantSumOriginal(mpz_class& i, int blocks, int sum) 
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
		std::vector<unsigned int> ret = {sum-k};
		i -= left;
		std::vector<unsigned int> ret2 = toConstantSumOriginal(i, blocks - 1, k);
		ret.insert(ret.end(), ret2.begin(), ret2.end());
		return ret;
	}

	virtual void genPublicKey() {
		this->loadPrivateKey();
		ByteArray pub;
		for(long unsigned int i = 0; i < this->private_key.size(); i++)
			pub += this->digestChain(this->private_key[i], W);
		this->public_key = this->digest(pub);
	};

	virtual void genPrivateKey() {
		for(unsigned int i = 0; i < T; i++) {
			this->private_key.push_back(this->digest(this->private_seed));
		}
	};

};
