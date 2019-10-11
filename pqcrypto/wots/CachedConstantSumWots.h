#ifndef CACHEDCONSTANTSUM_WOTS
#define CACHEDCONSTANTSUM_WOTS
#include "wots/ConstantSumWots.h"

template <class D, int W, int T, int S>
class CachedConstantSumWots : public virtual ConstantSumWots<D, W, T, S> {
public:
	CachedConstantSumWots() noexcept {};
	CachedConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W,T,S>(seed) {};

	const std::vector<ByteArray> sign(ByteArray& data) {
		std::vector<unsigned int> blocks = this->genFingerprint(data);
		std::vector<ByteArray> signature(blocks.size());
		const unsigned int C = W/2;

		//#pragma omp parallel for
		for(long unsigned int i = 0; i < blocks.size(); i++){
			unsigned int iterations = W -blocks[i];
			if(iterations >= C)
				signature[i] = this->digestChain(this->cache[i], iterations-C);
			else
				signature[i] = this->digestChain(this->private_key[i], iterations);
		}
		
		return signature;
	};
	
	virtual void clearPublicKey() {
		cache.clear();
		ConstantSumWots<D,W,T,S>::clearPublicKey();
	};

protected:

	virtual void genPublicKey() {
		this->loadPrivateKey();
		ByteArray pub;
		this->cache = std::vector<ByteArray>(this->private_key.size());
		const int C = W/2;
		for(long unsigned int i = 0; i < this->private_key.size(); i++){
			this->cache[i] = this->digestChain(this->private_key[i], C);
			pub += this->digestChain(this->cache[i], W-C);
		}
		this->public_key = this->digest(pub);
	};

	std::vector<ByteArray> cache;
};

#endif
