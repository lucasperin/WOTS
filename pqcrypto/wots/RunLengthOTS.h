#ifndef RUNLENGTHOTS
#define RUNLENGTHOTS

#include <cmath>
#include <utility>
#include "wots/WinternitzOTS.h"

template <class T>
class RunLengthOTS : public WinternitzOTS<T> {
public:
	RunLengthOTS() noexcept;
	RunLengthOTS(unsigned int r_min, unsigned int r_max) noexcept;
	RunLengthOTS(unsigned int r_min, unsigned int r_max, const ByteArray seed) noexcept;
	virtual const unsigned int rMin();
	virtual const unsigned int rMax();
	virtual const unsigned int l();
	virtual const std::vector<ByteArray> sign(ByteArray& data);
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature);
	std::pair<std::vector<unsigned int>, unsigned int> encodeRunLength(ByteArray& fingerprint);

protected:
	virtual void genPrivateKey();
	virtual void genPublicKey();

	unsigned int r_min;
	unsigned int r_max;
	unsigned int l_max;
	ByteArray private_seed;
};

template <class T>
RunLengthOTS<T>::RunLengthOTS() noexcept : RunLengthOTS (123, 131) {};

template <class T>
RunLengthOTS<T>::RunLengthOTS(unsigned int r_min, unsigned int r_max) noexcept : 
		RunLengthOTS(r_min, r_max, ByteArray::fromHex("01020304FFFF")) {};

template <class T>
RunLengthOTS<T>::RunLengthOTS(unsigned int r_min, unsigned int r_max, const ByteArray seed) noexcept {
	this->r_min = r_min;
	this->r_max = r_max;
	this->l_max = (unsigned int) floor( log2(this->bitLen()) -1 );
	this->private_seed = seed;
};

template <class T>
const unsigned int RunLengthOTS<T>::rMin() {
	return this->r_min;
};

template <class T>
const unsigned int RunLengthOTS<T>::rMax() {
	return this->r_max;
};

template <class T>
const unsigned int RunLengthOTS<T>::l() {
	return this->l_max;
};

template <class T>
const std::vector<ByteArray> RunLengthOTS<T>::sign(ByteArray& data) {
	std::vector<ByteArray> signature;

	//TODO(Perin) Here i'm taking hash of hash, instead of incrementing a counter
	//the effect should be the same.
	ByteArray fingerprint = this->digest(data);
	std::pair<std::vector<unsigned int>, unsigned int> blocks = encodeRunLength(fingerprint);

	while( !((blocks.second <= l_max) && (blocks.first.size() >= r_min) 
			&& (blocks.first.size() <= r_max)) ){
		fingerprint = this->digest(fingerprint);
		blocks = encodeRunLength(fingerprint);
	}

	for(long unsigned int i = 0; i < blocks.first.size(); i++){
		signature.push_back(this->digestChain(this->private_key[i], l_max - blocks.first[i]));
	}
	for(long unsigned int i = blocks.first.size(); i < this->r_max; i++) {
		signature.push_back(this->digestChain(this->private_key[i], l_max - 1));
	}

	return signature;
}

template <class T>
bool RunLengthOTS<T>::verify(ByteArray& data, std::vector<ByteArray>& signature) {
	if(not this->pubKeyIsLoaded())
		return false;
	ByteArray fingerprint = this->digest(data);
	std::pair<std::vector<unsigned int>, unsigned int> blocks = encodeRunLength(fingerprint);

	while( !((blocks.second <= l_max) && (blocks.first.size() >= r_min) 
			&& (blocks.first.size() <= r_max)) ){
		fingerprint = this->digest(fingerprint);
		blocks = encodeRunLength(fingerprint);
	}

	ByteArray check;
	for(long unsigned int i = 0; i < blocks.first.size(); i++){
		check = check + this->digestChain(signature[i], blocks.first[i]);
	}
	for(long unsigned int i = blocks.first.size(); i < this->r_max; i++) {
		check = check + this->digestChain(signature[i], 1);
	}

	check = this->digest(check);
	
	if( this->public_key.toHex().compare(check.toHex()) == 0 )
		return true;
	return false;
}

template <class T>
void RunLengthOTS<T>::genPrivateKey() {
	const unsigned int key_len = this->r_max;;
	for(unsigned int i = 0; i < key_len; i++) {
		//TODO(Perin): Use PRF and SEED;
		this->private_key.push_back(this->digest(private_seed));
	}
}

template <class T>
void RunLengthOTS<T>::genPublicKey() {
	this->loadPrivateKey();
	ByteArray pub;
	const unsigned int S = l_max;
	for(long unsigned int i = 0; i < this->private_key.size(); i++)
		pub = pub + this->digestChain(this->private_key[i], S);
	this->public_key = this->digest(pub);
}

template <class T>
std::pair<std::vector<unsigned int>, unsigned int> RunLengthOTS<T>::encodeRunLength(ByteArray& fingerprint) {
	std::pair<std::vector<unsigned int>, unsigned int> ret;
	std::string bin = fingerprint.toBin();
	unsigned int run_size = 1;
	char previous = bin[0];
	for(long unsigned int i = 1; i < bin.length(); i++){
		if(bin[i] != previous){
			previous = bin[i];
			ret.first.push_back(run_size);
			if(run_size > ret.second){ret.second = run_size;}
			run_size = 1;
		} else {
			run_size++;
		}
	}
	ret.first.push_back(run_size);
	if(run_size > ret.second)
		ret.second = run_size;
	return ret;
}


#endif
