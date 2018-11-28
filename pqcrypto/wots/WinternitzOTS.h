#ifndef WINTERNITZ_OTS
#define WINTERNITZ_OTS

#include "primitives/AbstractDigest.h"
#include "ByteArray.h"


template<class T, class Enable = void>
class WinternitzOTS;

template <class T>
class WinternitzOTS 
	<T, typename std::enable_if<std::is_base_of<AbstractDigest, T>::value>::type> 
	: protected std::decay<T>::type {

public:
	WinternitzOTS() {
		this->current_state = WinternitzOTS::INITIALIZED;
	}

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
			this->current_state += WinternitzOTS::PRIV_KEY_LOADED;
		}
	};
	
	virtual void loadPublicKey() {
		if(not this->pubKeyIsLoaded()) {
			this->genPublicKey();
			this->current_state += WinternitzOTS::PUB_KEY_LOADED;
		}
	};
	
	virtual void loadKeys() { 
		loadPrivateKey(); 
		loadPublicKey();
	};
	
	virtual void clearPrivateKey() {
		if(this->privKeyIsLoaded()) {
			this->private_key.clear();
			this->current_state -= WinternitzOTS::PRIV_KEY_LOADED;
		}
	};
	
	virtual void clearPublicKey() {
		if(this->pubKeyIsLoaded()) {
			this->public_key = ByteArray();
			this->current_state -= WinternitzOTS::PUB_KEY_LOADED;
		}
	};

	virtual void clearKeys() {
		this->private_key.clear();
		this->public_key = ByteArray();
		this->current_state = WinternitzOTS::INITIALIZED;
	};

	virtual const std::vector<ByteArray> sign(ByteArray& data) = 0;
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature) = 0;

protected:
	virtual void genPrivateKey() = 0;
	virtual void genPublicKey() = 0;
	
	virtual bool privKeyIsLoaded() {
		return (current_state & WinternitzOTS::PRIV_KEY_LOADED) > 0;
	};
	
	virtual bool pubKeyIsLoaded() {
		return (current_state & WinternitzOTS::PUB_KEY_LOADED) > 0;
	};
	
	enum State {
		INITIALIZED = 1,
		PRIV_KEY_LOADED = 2,
		PUB_KEY_LOADED = 4,
	};

	unsigned int current_state;
	ByteArray public_key;
	std::vector<ByteArray> private_key;
};
#endif
