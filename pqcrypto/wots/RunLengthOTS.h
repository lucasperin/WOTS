#ifndef RUNLENGTHOTS
#define RUNLENGTHOTS

#include <cmath>
#include <utility>
#include "wots/ClassicWots.h"

template <class D>
class RunLengthOTS : public ClassicWots<D, 4> {
public:
	RunLengthOTS() noexcept;
	RunLengthOTS(unsigned int r_min, unsigned int r_max) noexcept;
	RunLengthOTS(unsigned int r_min, unsigned int r_max, const ByteArray seed) noexcept;
	virtual ~RunLengthOTS() noexcept;
	virtual const unsigned int rMin();
	virtual const unsigned int rMax();
	virtual const unsigned int l();
	virtual const std::vector<ByteArray> sign(ByteArray& data);
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature);
	std::pair<std::vector<unsigned int>, unsigned int> encodeRunLength(ByteArray& fingerprint);
	//special functions to RunLength including R to signature
	const std::pair<std::vector<ByteArray>, int> sign2(ByteArray& data);
	bool verify(ByteArray& data, std::vector<ByteArray>& signature, int R);

protected:
	virtual void genPrivateKey();
	virtual void genPublicKey();
	std::string toBin(ByteArray& data);

	unsigned int r_min;
	unsigned int r_max;
	unsigned int l_max;
	ByteArray private_seed;
};

template <class D>
RunLengthOTS<D>::RunLengthOTS() noexcept : RunLengthOTS (123, 131) {};

template <class D>
RunLengthOTS<D>::RunLengthOTS(unsigned int r_min, unsigned int r_max) noexcept : 
		RunLengthOTS(r_min, r_max, hstoba("01020304FFFF")) {};

template <class D>
RunLengthOTS<D>::RunLengthOTS(unsigned int r_min, unsigned int r_max, const ByteArray seed) noexcept {
	this->r_min = r_min;
	this->r_max = r_max;
	this->l_max = (unsigned int) floor( log2(this->bitLen()) -1 );
	this->private_seed = seed;
};

template <class D>
RunLengthOTS<D>::~RunLengthOTS() noexcept {}

template <class D>
const unsigned int RunLengthOTS<D>::rMin() {
	return this->r_min;
};

template <class D>
const unsigned int RunLengthOTS<D>::rMax() {
	return this->r_max;
};

template <class D>
const unsigned int RunLengthOTS<D>::l() {
	return this->l_max;
};

template <class D>
const std::vector<ByteArray> RunLengthOTS<D>::sign(ByteArray& data) {
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

template <class D>
const std::pair<std::vector<ByteArray>, int> RunLengthOTS<D>::sign2(ByteArray& data) {
	std::vector<ByteArray> signature;

	int R = 1;
	ByteArray randomized(data);
    randomized	+= hstoba(std::to_string(R));
	ByteArray fingerprint = this->digest(randomized);
	std::pair<std::vector<unsigned int>, unsigned int> blocks = encodeRunLength(fingerprint);

	while( !((blocks.second <= l_max) && (blocks.first.size() >= r_min) 
			&& (blocks.first.size() <= r_max)) ){
		R++;
		randomized = ByteArray(data);
		randomized	+= hstoba(std::to_string(R));
		fingerprint = this->digest(randomized);
		blocks = encodeRunLength(fingerprint);
	}

	for(long unsigned int i = 0; i < blocks.first.size(); i++){
		signature.push_back(this->digestChain(this->private_key[i], l_max - blocks.first[i]));
	}
	for(long unsigned int i = blocks.first.size(); i < this->r_max; i++) {
		signature.push_back(this->digestChain(this->private_key[i], l_max - 1));
	}

	std::pair<std::vector<ByteArray>, int> ret(signature, R);

	return ret;
}

template <class D>
bool RunLengthOTS<D>::verify(ByteArray& data, std::vector<ByteArray>& signature) {
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
		check += this->digestChain(signature[i], blocks.first[i]);
	}
	for(long unsigned int i = blocks.first.size(); i < this->r_max; i++) {
		check += this->digestChain(signature[i], 1);
	}

	check = this->digest(check);
	
	if( std::to_string(this->public_key).compare(std::to_string(check)) == 0 )
		return true;
	return false;
}

template <class D>
bool RunLengthOTS<D>::verify(ByteArray& data, std::vector<ByteArray>& signature, int R) {
	if(not this->pubKeyIsLoaded())
		return false;
	ByteArray randomized(data);
    randomized	+= hstoba(std::to_string(R));
	ByteArray fingerprint = this->digest(randomized);
	std::pair<std::vector<unsigned int>, unsigned int> blocks = encodeRunLength(fingerprint);

	ByteArray check;
	for(long unsigned int i = 0; i < blocks.first.size(); i++){
		check += this->digestChain(signature[i], blocks.first[i]);
	}
	for(long unsigned int i = blocks.first.size(); i < this->r_max; i++) {
		check += this->digestChain(signature[i], 1);
	}

	check = this->digest(check);
	
	if( std::to_string(this->public_key).compare(std::to_string(check)) == 0 )
		return true;
	return false;
}

template <class D>
void RunLengthOTS<D>::genPrivateKey() {
	const unsigned int key_len = this->r_max;;
	for(unsigned int i = 0; i < key_len; i++) {
		//TODO(Perin): Use PRF and SEED;
		this->private_key.push_back(this->digest(private_seed));
	}
}

template <class D>
void RunLengthOTS<D>::genPublicKey() {
	this->loadPrivateKey();
	ByteArray pub;
	const unsigned int S = l_max;
	for(long unsigned int i = 0; i < this->private_key.size(); i++)
		pub += this->digestChain(this->private_key[i], S);
	this->public_key = this->digest(pub);
}

template <class D>
std::pair<std::vector<unsigned int>, unsigned int> RunLengthOTS<D>::encodeRunLength(ByteArray& fingerprint) {
	std::pair<std::vector<unsigned int>, unsigned int> ret;
	std::string bin = toBin(fingerprint);
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

template <class D>
std::string RunLengthOTS<D>::toBin(ByteArray& data) {

	std::string hex = std::to_string(data);
	std::string bin = "";
	for(char& c : hex) {
		switch(c)
         {
             case '0': bin.append("0000"); break;
             case '1': bin.append("0001"); break;
             case '2': bin.append("0010"); break;
             case '3': bin.append("0011"); break;
             case '4': bin.append("0100"); break;
             case '5': bin.append("0101"); break;
             case '6': bin.append("0110"); break;
             case '7': bin.append("0111"); break;
             case '8': bin.append("1000"); break;
             case '9': bin.append("1001"); break;
             case 'A': bin.append("1010"); break;
             case 'B': bin.append("1011"); break;
             case 'C': bin.append("1100"); break;
             case 'D': bin.append("1101"); break;
             case 'E': bin.append("1110"); break;
             case 'F': bin.append("1111"); break;
             case 'a': bin.append("1010"); break;
             case 'b': bin.append("1011"); break;
             case 'c': bin.append("1100"); break;
             case 'd': bin.append("1101"); break;
             case 'e': bin.append("1110"); break;
             case 'f': bin.append("1111"); break;
         }
	}
	return bin;
}

#endif
