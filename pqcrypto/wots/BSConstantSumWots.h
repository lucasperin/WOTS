#pragma once
#include "wots/ConstantSumWots.h"
#include <iostream>


template <class D, int W, int T, int S>
class BSConstantSumWots : public virtual ConstantSumWots<D, W, T, S> {
	public:

	BSConstantSumWots() noexcept {};
	BSConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W,T,S>(seed) {};
	
	mpz_class prank(int blocks, int max, int sum, int j) {
		return this->rank(blocks, max, sum, j);
	};

	mpz_class pconst(int blocks, int max, int sum) {
		return this->constantSumLen(blocks, max, sum);
	};

	virtual bool check_encoding(ByteArray& data, std::vector<unsigned int>& blocks) {
		ByteArray aux = this->digest(data);
		mpz_class I;
		I.set_str(std::to_string(aux), 16);
		int s = S;
		mpz_class keep;
		mpz_class keep2;
		for(int r = 1; r <=T; r++) {
			keep = rank(T-r, W, s, blocks[r-1]-1);
			if( I < keep ) { return false; }
			if( I > rank(T-r, W, s, blocks[r-1]) ) { return false; }
			s -=blocks[r-1];
			I -= keep;
		}
		return true;
	};

	virtual bool fast_verify(ByteArray& data, std::vector<ByteArray>& signature, std::vector<unsigned int>& blocks) {	
		if(not this->pubKeyIsLoaded())
			return false;
		if(! check_encoding(data, blocks) ) 
			return false;

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
protected:

	virtual mpz_class rank(int blocks, int max, int sum, int j) {
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
			int blocks, int max, int sum)
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
