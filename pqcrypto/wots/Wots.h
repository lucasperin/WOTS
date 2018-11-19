#ifndef WOTS
#define WOTS

#include <cmath>
#include <sstream>
#include "wots/AbstractWinternitzOTS.h"
//TODO(Perin): Test EXPECT template T not base of AbstractDigest compilation error!

template <class T>
class Wots : public  AbstractWinternitzOTS<T> {
public:
	Wots() noexcept;
	Wots(unsigned int w) noexcept;
	Wots(unsigned int w, const ByteArray& seed) noexcept;
	~Wots() noexcept;
	virtual const unsigned int t() const noexcept;
	virtual const unsigned int t1() const noexcept;
	virtual const unsigned int t2() const noexcept;
	virtual const unsigned int w() const noexcept;
	virtual const unsigned int n() const noexcept;
	virtual const ByteArray publicKey();
	virtual void loadPrivateKey();
	virtual void loadPublicKey();
	virtual const std::vector<ByteArray> sign(ByteArray& data);
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature);

protected:
	virtual const std::vector<ByteArray> privateKey();
	virtual void genPrivateKey();
	virtual void genPublicKey();
	virtual bool privKeyIsLoaded();
	virtual bool pubKeyIsLoaded();
	virtual const std::vector<unsigned int> checksum(std::vector<unsigned int>& blocks);

	//Attributes
	unsigned int current_state;
	unsigned int block_size;
	unsigned int block_max;
	std::vector<ByteArray> private_key;
	ByteArray private_seed;
	ByteArray public_key;

};

template <class T>
Wots<T>::Wots() noexcept : Wots(16) {}

template <class T>
Wots<T>::Wots(unsigned int w) noexcept : Wots(w, ByteArray::fromHex("01020304FFFF")) {}

template <class T>
Wots<T>::Wots(unsigned int w, const ByteArray& seed) noexcept : block_max(w) {
	switch(w){
		case(4): block_size = 2; break;
		case(16): block_size = 4; break;
		case(256): block_size = 8; break;
		default: 
			block_size = 16;
			block_max = 65536;
			break;
	}
	private_seed = seed;
	current_state = Wots::INITIALIZED;
}

template <class T>
Wots<T>::~Wots() noexcept {}

template <class T>
const unsigned int Wots<T>::t() const noexcept 
{
	return t1()+t2();
}

template <class T>
const unsigned int Wots<T>::t1() const noexcept {
	return this->bitLen()/block_size;
}

template <class T>
const unsigned int Wots<T>::t2() const noexcept {
	float u = log2(t1()*(block_max-1));
	return (const unsigned int) floor(u/block_size) + 1;
}

template <class T>
const unsigned int Wots<T>::w() const noexcept {
	return this->block_size;
}

template <class T>
const unsigned int Wots<T>::n() const noexcept {
	return this->len();
}

template <class T>
const std::vector<ByteArray> Wots<T>::privateKey(){
	loadPrivateKey();
	return this->private_key;
}

template <class T>
const ByteArray Wots<T>::publicKey() {
	loadPublicKey();
	return this->public_key;
}

template <class T>
void Wots<T>::loadPrivateKey() {
	if(not this->privKeyIsLoaded()) {
		genPrivateKey();
		current_state += Wots::PRIV_KEY_LOADED;
	}
}

template <class T>
void Wots<T>::loadPublicKey() {
	if(not this->pubKeyIsLoaded()) {
		genPublicKey();
		current_state += Wots::PUB_KEY_LOADED;
	}
}

template <class T>
void Wots<T>::genPrivateKey(){
	const unsigned int key_len = t();
	for(unsigned int i = 0; i < key_len; i++) {
		//TODO(Perin): Use PRF and SEED;
		private_key.push_back(this->digest(private_seed));
	}
}

template <class T>
void Wots<T>::genPublicKey() {
	loadPrivateKey();
	ByteArray pub;
	const unsigned int S = block_max - 1;
	for(long unsigned int i = 0; i < this->private_key.size(); i++)
		pub = pub + this->digestChain(this->private_key[i], S);
	this->public_key = this->digest(pub);
}

template <class T>
bool Wots<T>::privKeyIsLoaded() {
	return (current_state & Wots::PRIV_KEY_LOADED) > 0;
}

template <class T>
bool Wots<T>::pubKeyIsLoaded() {
	return (current_state & Wots::PUB_KEY_LOADED) > 0;
}

template<class T>
const std::vector<ByteArray> Wots<T>::sign(ByteArray& data) {
	loadPrivateKey();
	std::vector<ByteArray> signature;
	ByteArray fingerprint = this->digest(data);
	std::vector<unsigned int> blocks = fingerprint.toBaseW(block_max);
	std::vector<unsigned int> cs = checksum(blocks);

	/*
	std::cout << blocks.size() << std::endl;
	for(auto b : blocks)
		std::cout << b << " ";
	std::cout << std::endl;
		
	std::cout << cs.size() << std::endl;
	for(auto c : cs)
		std::cout << c << " ";
	std::cout << std::endl;
	*/
	
	for(long unsigned int i = 0; i < this->private_key.size(); i++)
		signature.push_back(this->digestChain(private_key[i], blocks[i]));
	
	return signature;
}

template<class T>
bool Wots<T>::verify(ByteArray& data, std::vector<ByteArray>& signature) {
	loadPublicKey();
	ByteArray fingerprint = this->digest(data);
	std::vector<unsigned int> blocks = fingerprint.toBaseW(block_max);
	ByteArray check;

	for(long unsigned int i = 0; i < blocks.size(); i++)
		check = check + this->digestChain(signature[i], block_max - 1 - blocks[i]);

	check = this->digest(check);

	std::cout << check.toHex() << std::endl;
	
	if( public_key.toHex().compare(check.toHex()) == 0 )
		return true;

	return false;
}

template<class T>
const std::vector<unsigned int> Wots<T>::checksum(std::vector<unsigned int>& blocks){
	std::vector<unsigned int> checksum;
	int sum = 0;
	for(auto &b : blocks)
		sum += block_max -1 - b;
	std::stringstream ss;
	ss << std::hex << sum;
	return ByteArray::fromHex(ss.str()).toBaseW(block_max);
}
#endif
















