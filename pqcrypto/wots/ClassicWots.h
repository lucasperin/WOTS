#ifndef CLASSIC_WOTS
#define CLASSIC_WOTS

#include <cmath>
#include <sstream>
#include "wots/WinternitzOTS.h"
//TODO(Perin): Test EXPECT template T not base of AbstractDigest compilation error!

template <class T>
class ClassicWots : public  WinternitzOTS<T> {
public:
	ClassicWots() noexcept;
	ClassicWots(unsigned int w) noexcept;
	ClassicWots(unsigned int w, const ByteArray& seed) noexcept;
	virtual ~ClassicWots() noexcept;
	virtual const unsigned int t() const noexcept;
	virtual const unsigned int t1() const noexcept;
	virtual const unsigned int t2() const noexcept;
	virtual const unsigned int w() const noexcept;
	virtual const unsigned int n() const noexcept;
	virtual const std::vector<ByteArray> sign(ByteArray& data);
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature);

protected:
	virtual void genPrivateKey();
	virtual void genPublicKey();
	virtual const std::vector<unsigned int> checksum(std::vector<unsigned int>& blocks);

	//Attributes
	unsigned int block_size;
	unsigned int block_max;
	ByteArray private_seed;

};

template <class T>
ClassicWots<T>::ClassicWots() noexcept : ClassicWots(16) {}

template <class T>
ClassicWots<T>::ClassicWots(unsigned int w) noexcept : ClassicWots(w, ByteArray::fromHex("01020304FFFF")) {}

template <class T>
ClassicWots<T>::ClassicWots(unsigned int w, const ByteArray& seed) noexcept : block_max(w) {
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
}

template <class T>
ClassicWots<T>::~ClassicWots() noexcept {}

template <class T>
const unsigned int ClassicWots<T>::t() const noexcept 
{
	return t1()+t2();
}

template <class T>
const unsigned int ClassicWots<T>::t1() const noexcept {
	return this->bitLen()/block_size;
}

template <class T>
const unsigned int ClassicWots<T>::t2() const noexcept {
	float u = log2(t1()*(block_max-1));
	return (const unsigned int) floor(u/block_size) + 1;
}

template <class T>
const unsigned int ClassicWots<T>::w() const noexcept {
	return this->block_size;
}

template <class T>
const unsigned int ClassicWots<T>::n() const noexcept {
	return this->len();
}

template <class T>
void ClassicWots<T>::genPrivateKey(){
	const unsigned int key_len = t();
	for(unsigned int i = 0; i < key_len; i++) {
		//TODO(Perin): Use PRF and SEED;
		this->private_key.push_back(this->digest(private_seed));
	}
}

template <class T>
void ClassicWots<T>::genPublicKey() {
	this->loadPrivateKey();
	ByteArray pub;
	const unsigned int S = block_max - 1;
	for(long unsigned int i = 0; i < this->private_key.size(); i++)
		pub = pub + this->digestChain(this->private_key[i], S);
	this->public_key = this->digest(pub);
}

template<class T>
const std::vector<ByteArray> ClassicWots<T>::sign(ByteArray& data) {
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

template<class T>
bool ClassicWots<T>::verify(ByteArray& data, std::vector<ByteArray>& signature) {
	if(not this->pubKeyIsLoaded())
		return false;
	ByteArray fingerprint = this->digest(data);
	std::vector<unsigned int> blocks = fingerprint.toBaseW(block_max);
	std::vector<unsigned int> cs = checksum(blocks);
	std::vector<ByteArray> check_vector(blocks.size() + cs.size());
	ByteArray check;

	//#pragma omp parallel for
	for(long unsigned int i = 0; i < blocks.size(); i++) {
		int remain = block_max - 1 -blocks[i];
		check_vector[i] = this->digestChain(signature[i], remain);
		//check = check + this->digestChain(signature[i], remain);
	}

	//#pragma omp parallel for
	for(long unsigned int i = blocks.size(); i < this->private_key.size(); i++) {
		int a = i-blocks.size();
		check_vector[i] = this->digestChain(signature[i], block_max - 1 - cs[a]);
	}

	for(long unsigned int i = 0; i < check_vector.size(); i++) {
		check = check + check_vector[i];
	}

	check = this->digest(check);
	
	if( this->public_key.toHex().compare(check.toHex()) == 0 )
		return true;

	return false;
}

template<class T>
const std::vector<unsigned int> ClassicWots<T>::checksum(std::vector<unsigned int>& blocks){
	std::vector<unsigned int> checksum;
	int sum = 0;
	for(auto &b : blocks)
		sum += block_max -1 - b;
	std::stringstream ss;
	ss << std::hex << sum;
	std::vector<unsigned int> ret = ByteArray::fromHex(ss.str()).toBaseW(block_max);
	int rm = ret.size() - this->t2();
	if(rm > 0) {
		ret.erase(ret.begin(), ret.begin()+rm);
	}
	if(rm < 0) {
		std::vector<unsigned int> aux(abs(rm), 0);
		ret.insert(ret.begin(), aux.begin(), aux.end());
	}
	return ret;
}
#endif
















