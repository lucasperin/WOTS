#ifndef CACHED_WOTS
#define CACHED_WOTS
#include "wots/ClassicWots.h"

template <class D, int W>
class CachedWots : public virtual ClassicWots<D,W> {
public:
	CachedWots() noexcept {};
	CachedWots(const ByteArray& seed) noexcept : ClassicWots<D,W>(W,seed) {};
	
	const std::vector<ByteArray> sign(ByteArray& data) final {
		std::vector<unsigned int> blocks = this->genFingerprint(data);
		std::vector<unsigned int> cs = this->checksum(blocks);
		std::vector<ByteArray> signature(blocks.size() + cs.size());
		const unsigned int C = W/2;

		//#pragma omp parallel for
		for(long unsigned int i = 0; i < blocks.size(); i++){
			if(blocks[i] >= C)
				signature[i] = this->digestChain(this->cache[i], blocks[i]-C);
			else
				signature[i] = this->digestChain(this->private_key[i], blocks[i]);
		}

		//#pragma omp parallel for
		for(long unsigned int i = blocks.size(); i < this->private_key.size(); i++) {
			int a = i-blocks.size();
			if(cs[a] >= C)
				signature[i] = this->digestChain(this->cache[i], cs[a]-C);
			else
				signature[i] = this->digestChain(this->private_key[i], cs[a]);
		}
		
		return signature;
	};

protected:

	virtual void genPublicKey() final {
		this->loadPrivateKey();
		ByteArray pub;
		const unsigned int S = W - 1;
		this->cache = std::vector<ByteArray>(this->private_key.size());
		const unsigned int C = W/2;
		for(long unsigned int i = 0; i < this->private_key.size(); i++){
			this->cache[i] = this->digestChain(this->private_key[i], C);
			pub = pub + this->digestChain(this->cache[i], S-C);
		}
		this->public_key = this->digest(pub);
	};

	std::vector<ByteArray> cache;
};

#endif
