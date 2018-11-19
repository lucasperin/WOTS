#ifndef ABSTRACT_WINTERNITZ_OTS
#define ABSTRACT_WINTERNITZ_OTS

#include "primitives/AbstractDigest.h"


template<class T, class Enable = void>
class AbstractWinternitzOTS;

template <class T>
class AbstractWinternitzOTS 
	<T, typename std::enable_if<std::is_base_of<AbstractDigest, T>::value>::type> 
	: protected std::decay<T>::type {

public:
	virtual const unsigned int t() const noexcept = 0;
	virtual const unsigned int t1() const noexcept = 0;
	virtual const unsigned int t2() const noexcept = 0;
	virtual const unsigned int w() const noexcept = 0;
	virtual const unsigned int n() const noexcept = 0;
	virtual const std::vector<ByteArray> privateKey() = 0;
	virtual const std::vector<ByteArray> publicKey() = 0;
	virtual void loadPrivKey() = 0;
	virtual void loadPubKey() = 0;
	virtual void loadKeys() { loadPrivKey(); loadPubKey();};

protected:
	enum State {
		INITIALIZED = 1,
		PRIV_KEY_LOADED = 2,
		PUB_KEY_LOADED = 4,
	};
};
#endif
