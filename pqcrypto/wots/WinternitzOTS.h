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
	virtual const unsigned int t() const noexcept = 0;
	virtual const unsigned int t1() const noexcept = 0;
	virtual const unsigned int t2() const noexcept = 0;
	virtual const unsigned int w() const noexcept = 0;
	virtual const unsigned int n() const noexcept = 0;
	virtual const ByteArray publicKey() = 0;
	virtual void loadPrivateKey() = 0;
	virtual void loadPublicKey() = 0;
	virtual void loadKeys() { loadPrivateKey(); loadPublicKey();};
	virtual const std::vector<ByteArray> sign(ByteArray& data) = 0;
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature) = 0;

protected:
	virtual const std::vector<ByteArray> privateKey() = 0;
	enum State {
		INITIALIZED = 1,
		PRIV_KEY_LOADED = 2,
		PUB_KEY_LOADED = 4,
	};
};
#endif
