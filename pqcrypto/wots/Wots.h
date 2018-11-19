#ifndef WOTS
#define WOTS

#include <cmath>
#include "wots/AbstractWinternitzOTS.h"
//TODO(Perin): Test EXPECT template T not base of AbstractDigest compilation error!

template <class T>
class Wots : public  AbstractWinternitzOTS<T> {
public:
	Wots() noexcept;
	Wots(unsigned int w) noexcept;
	~Wots() noexcept;
	virtual const unsigned int t() const noexcept;
	virtual const unsigned int t1() const noexcept;
	virtual const unsigned int t2() const noexcept;
	virtual const unsigned int w() const noexcept;
	virtual const unsigned int n() const noexcept;
	virtual const std::vector<ByteArray> privateKey();
	virtual const std::vector<ByteArray> publicKey();
	virtual void loadPrivKey();
	virtual void loadPubKey();
protected:
	virtual const std::vector<ByteArray> genPrivateKey();
	virtual const std::vector<ByteArray> genPublicKey();
	virtual bool privKeyIsLoaded();
	virtual bool pubKeyIsLoaded();

	//Attributes
	unsigned int current_state;
	unsigned int block_size;
	unsigned int block_max;
	std::vector<ByteArray> private_key;
	std::vector<ByteArray> public_key;

};

template <class T>
Wots<T>::Wots() noexcept : Wots(16) {}

template <class T>
Wots<T>::Wots(unsigned int w) noexcept : block_max(w) {
	switch(w){
		case(4): block_size = 2; break;
		case(16): block_size = 4; break;
		case(256): block_size = 8; break;
		default: 
			block_size = 16;
			block_max = 65536;
			break;
	}
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
	if(this->privKeyIsLoaded())
		return this-> private_key;
	return genPrivateKey();
}

template <class T>
const std::vector<ByteArray> Wots<T>::publicKey() {
	if(this->pubKeyIsLoaded())
		return this-> private_key;
	return genPrivateKey();
}

template <class T>
void Wots<T>::loadPrivKey() {
	if(not this->privKeyIsLoaded()) {
		this->private_key = genPrivateKey();
		current_state += Wots::PRIV_KEY_LOADED;
	}
}

template <class T>
void Wots<T>::loadPubKey() {
	if(not this->pubKeyIsLoaded()) {
		this->public_key = genPublicKey();
		current_state += Wots::PUB_KEY_LOADED;
	}
}

template <class T>
const std::vector<ByteArray> Wots<T>::genPrivateKey(){
	std::vector<ByteArray> k;
	const unsigned int key_len = t();
	const std::string seed = "test";
	for(unsigned int i = 0; i < key_len; i++) {
		//TODO(Perin): Use PRF and SEED;
		ByteArray segment = ByteArray::fromString(seed);
		k.push_back(this->digest(segment));
	}
	return k;
}

template <class T>
const std::vector<ByteArray> Wots<T>::genPublicKey() {
	std::vector<ByteArray>* priv;
	std::vector<ByteArray> aux;
	std::vector<ByteArray> pub;
	if(this->privKeyIsLoaded()) {
		priv = &private_key;
	} else {
		aux = privateKey();
		priv = &aux;
	}
	const unsigned int S = block_max - 1;
	for(long unsigned int i = 0; i < priv->size(); i++)
		pub.push_back(this->digestChain((*priv)[i], S));
	return pub;
}

template <class T>
bool Wots<T>::privKeyIsLoaded() {
	return (current_state & Wots::PRIV_KEY_LOADED) > 0;
}

template <class T>
bool Wots<T>::pubKeyIsLoaded() {
	return (current_state & Wots::PUB_KEY_LOADED) > 0;
}
#endif
















