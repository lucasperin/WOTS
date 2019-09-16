#ifndef CLASSIC_WOTS
#define CLASSIC_WOTS

#include "primitives/AbstractDigest.h"
#include "utils/ByteArray.hpp"
#include <sstream>
#include <math.h>

template<class D, int W, class Enable = void>
class ClassicWots;

template <class D, int W>
class ClassicWots <D, W, typename std::enable_if<std::is_base_of<AbstractDigest, D>::value>::type> : protected std::decay<D>::type {

public:
	ClassicWots() {
		paramCheck();
		this->current_state = ClassicWots::INITIALIZED;
		block_size = std::ceil(log2(W));
		if(private_seed.size()==0)
			private_seed = hstoba("01020304FFFF");

	};

	ClassicWots(const ByteArray& seed) : ClassicWots() {
		private_seed = seed;
	};

	//constexpr??
	virtual const unsigned int t() const noexcept { 
		return t1()+t2(); 
	};

	virtual const unsigned int t1() const noexcept {
		float u = (float)this->bitLen()/(float)this->block_size;
		return std::ceil(u);
	};

	virtual const unsigned int t2() const noexcept {
		float u = (log2(t1()*(W-1)))/(float)this->block_size;
		return (const unsigned int) floor(u) + 1;
	};

	virtual const unsigned int w() const noexcept {
		return W;
	};

	virtual const unsigned int n() const noexcept {
		return this->len();
	};

	virtual const ByteArray publicKey(){
		loadPublicKey();
		return this->public_key;
	};

	virtual const std::vector<ByteArray> privateKey() {
		loadPrivateKey();
		return this->private_key;
	};
	
	virtual void loadPrivateKey() {
		if(not this->privKeyIsLoaded()) {
			this->genPrivateKey();
			this->current_state += ClassicWots::PRIV_KEY_LOADED;
		}
	};
	
	virtual void loadPublicKey() {
		if(not this->pubKeyIsLoaded()) {
			this->genPublicKey();
			this->current_state += ClassicWots::PUB_KEY_LOADED;
		}
	};
	
	virtual void loadKeys() { 
		loadPrivateKey(); 
		loadPublicKey();
	};
	
	virtual void clearPrivateKey() {
		if(this->privKeyIsLoaded()) {
			this->private_key.clear();
			this->current_state -= ClassicWots::PRIV_KEY_LOADED;
		}
	};
	
	virtual void clearPublicKey() {
		if(this->pubKeyIsLoaded()) {
			this->public_key = ByteArray();
			this->current_state -= ClassicWots::PUB_KEY_LOADED;
		}
	};

	virtual void clearKeys() {
		this->private_key.clear();
		this->public_key = ByteArray();
		this->current_state = ClassicWots::INITIALIZED;
	};

	virtual const std::vector<ByteArray> sign(ByteArray& data) {
		std::vector<unsigned int> blocks = this->genFingerprint(data);
		std::vector<unsigned int> cs = checksum(blocks);
		blocks.insert(blocks.end(), cs.begin(), cs.end());
		std::vector<ByteArray> signature(blocks.size() + cs.size());

		//#pragma omp parallel for
		for(long unsigned int i = 0; i < blocks.size(); i++){
			signature[i] = this->digestChain(this->private_key[i], W - 1 - blocks[i]);
		}
		
		return signature;
	};
	
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature) {	
		if(not this->pubKeyIsLoaded())
			return false;
		std::vector<unsigned int> blocks = this->genFingerprint(data);
		std::vector<unsigned int> cs = checksum(blocks);
		blocks.insert(blocks.end(), cs.begin(), cs.end());
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

	virtual const std::vector<unsigned int> checksum(std::vector<unsigned int>& blocks) {
		std::vector<unsigned int> checksum;
		int sum = 0;
		for(auto &b : blocks)
			sum += W -1 - b;
		std::stringstream ss;
		ss << std::hex << sum;
		ByteArray aux = hstoba(ss.str());
		std::vector<unsigned int> ret = this->toBaseW(aux);
		int rm = ret.size() - this->t2();
		if(rm > 0) {
			ret.erase(ret.begin(), ret.begin()+rm);
		}
		if(rm < 0) {
			std::vector<unsigned int> aux(abs(rm), 0);
			ret.insert(ret.begin(), aux.begin(), aux.end());
		}
		return ret;
	};

	virtual std::vector<unsigned int> genFingerprint(ByteArray& data) {
		ByteArray fingerprint = this->digest(data);
		return this->toBaseW(fingerprint);
		
	};

protected:

	virtual void paramCheck() {
		//static_assert( W == 4 || W == 16 || W == 256 || W == 65536, "Winternitz Parameter W not supported.");
	};

	virtual void genPrivateKey() {
		const unsigned int key_len = this->t();
		//TODO(Perin): Use PRF and SEED;
		for(unsigned int i = 0; i < key_len; i++) {
			this->private_key.push_back(this->digest(this->private_seed));
		}
	};

	virtual void genPublicKey() {
		this->loadPrivateKey();
		ByteArray pub;
		const unsigned int S = W - 1;
		for(long unsigned int i = 0; i < this->private_key.size(); i++)
			pub += this->digestChain(this->private_key[i], S);
		this->public_key = this->digest(pub);
	};

	
	virtual bool privKeyIsLoaded() {
		return (current_state & ClassicWots::PRIV_KEY_LOADED) > 0;
	};
	
	virtual bool pubKeyIsLoaded() {
		return (current_state & ClassicWots::PUB_KEY_LOADED) > 0;
	};
	
	enum State {
		INITIALIZED = 1,
		PRIV_KEY_LOADED = 2,
		PUB_KEY_LOADED = 4,
	};

	//TODO: trocar parametro por template. usar SFINAE para avaliar em tempo de compilação no lugar do switch?
	std::vector<unsigned int> toBaseW(ByteArray& data) {
		if (W > 256) {
			return toBaseWBig(data);
		}
		return toBaseWSmall(data);
	};

	std::vector<unsigned int> toBaseWBig(ByteArray& data) {
		//TODO REVIEW, does this work?
		const unsigned int bytes_per_block = block_size/8;
		std::vector<unsigned int> ret;
		unsigned int total = 0;
		unsigned int s = 0;

		for(unsigned int i=0; i < data.size(); i++) {
			s = (bytes_per_block-1) - (i%bytes_per_block);
			//total += (data.at(i)<< s) & ( (1<<block_size)-1);
			total += (std::to_integer<unsigned int>(data[i])<< s) & ( (1<<block_size)-1);
			if( (i+1)%bytes_per_block == 0){
				ret.push_back(total);
				total = 0;
			}
		}
		return ret;
	};

	std::vector<unsigned int> toBaseWSmall(ByteArray& data) {
		unsigned int in = 0;
		unsigned int total = 0;
		unsigned int bits = 0;
		unsigned int consumed;
		std::vector<unsigned int> ret;
		unsigned int out_len = data.size()*8 / block_size;

		for ( consumed = 0; consumed < out_len; consumed++ ) {
			if ( bits == 0 ) {
				total = std::to_integer<unsigned int>(data[in]);
				in++;
				bits += 8;
			}
			bits -= block_size;
			ret.push_back((total >> bits) & ( (1<<(block_size)) -1));
		}
		return ret;
	};

	//Attributes
	unsigned int current_state;
	ByteArray public_key;
	std::vector<ByteArray> private_key;
	unsigned int block_size;
	ByteArray private_seed;
};
#endif
