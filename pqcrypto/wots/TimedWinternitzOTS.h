#ifndef TIMED_WINTERNITZ_OTS
#define TIMED_WINTERNITZ_OTS

#include "primitives/AbstractDigest.h"
#include "ByteArray.h"


template<class T, class Enable = void>
class TimedWinternitzOTS;

template <class T>
class TimedWinternitzOTS 
	<T, typename std::enable_if<std::is_base_of<WinternitzOTS, T>::value>::type> 
	: protected std::decay<T>::type {

public:
	virtual const unsigned int timedPriveteKeyGeneration() const noexcept;
	virtual const unsigned int timedPriveteKeyGeneration() const noexcept;
	virtual const unsigned int timedPriveteKeyGeneration() const noexcept;
	virtual const unsigned int timedPriveteKeyGeneration() const noexcept;
	virtual void ();
	virtual void loadPublicKey();
};
#endif
