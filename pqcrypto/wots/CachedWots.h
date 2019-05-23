#include "wots/ClassicWots.h"

template <class T, int W>
class CachedWots : public  ClassicWots<T> {
protected:
	std::vector<ByteArray> cache;
	virtual void genPublicKey();
public:
	CachedWots() noexcept: ClassicWots<T>(W) {};
	CachedWots(const ByteArray& seed) noexcept : ClassicWots<T>(W,seed) {};

};

template <class T, int W>
void CachedWots<T,W>::genPublicKey() {
	this->loadPrivateKey();
	ByteArray pub;
	const unsigned int S = this->block_max - 1;
	this->cache = std::vector<ByteArray>(this->private_key.size());
	const unsigned int C = this->block_max/2;
	for(long unsigned int i = 0; i < this->private_key.size(); i++){
		this->cache[i] = this->digestChain(this->private_key[i], C);
		pub = pub + this->digestChain(this->cache[i], S-C);
	}
	this->public_key = this->digest(pub);
};

/*
template <class T, typename W>
const std::vector<ByteArray> CachedWots<T,W>::sign(ByteArray& data) {
	ByteArray fingerprint = this->digest(data);
	std::vector<unsigned int> blocks = fingerprint.toBaseW(block_max);
	std::vector<unsigned int> cs = checksum(blocks);
	std::vector<ByteArray> signature(blocks.size() + cs.size());

	//#pragma omp parallel for
	for(long unsigned int i = 0; i < blocks.size(); i++){
		signature[i] = this->digestChain(this->private_key[i], blocks[i]);
	}

	//#pragma omp parallel for
	for(long unsigned int i = blocks.size(); i < this->private_key.size(); i++) {
		int a = i-blocks.size();
		signature[i] = this->digestChain(this->private_key[i], cs[a]);
	}
	
	return signature;
}
*/
