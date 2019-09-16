#ifndef CONSTANTSUM_WOTS
#define CONSTANTSUM_WOTS
#include "wots/ClassicWots.h"
#include <gmpxx.h>
#include <math.h>
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
		
		//TODO( We can improve this using xor and vactor iterator)
		if( std::to_string(this->public_key).compare(std::to_string(check)) == 0 )
			return true;

		return false;
	};


	std::vector<unsigned int> genFingerprint(ByteArray& data) final {
		ByteArray aux = this->digest(data);
		mpz_class i;
		i.set_str(std::to_string(aux), 16);
		auto ret = this->toConstantSum(i, T, W, S);
		for (const auto i : ret)
			std::cout << i << ' ';
		std::cout<<std::endl;
		return ret;
		//return this->toConstantSum(i, T, W, S);
		
	};
protected:
	/*
	 * Overide restriction of W power of 2.
	 */
	virtual void paramCheck() final {};

	/*
	 * Must be signed to asserct negative cases.
	 */
	mpz_class binomial(int n, int k) {
		if(n < k || n<0 || k<0)
			return 0;
		mpz_class ret = 0;
		mpz_bin_uiui(ret.get_mpz_t(), n, k);
		return ret;
	}

	virtual mpz_class constantSumLen(unsigned int blocks, unsigned int max, unsigned int sum) {
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
	virtual std::vector<unsigned int> toConstantSum(mpz_class& i, 
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

	virtual void genPublicKey() {
		this->loadPrivateKey();
		ByteArray pub;
		for(long unsigned int i = 0; i < this->private_key.size(); i++)
			pub += this->digestChain(this->private_key[i], W);
		this->public_key = this->digest(pub);
	};


};

#endif
