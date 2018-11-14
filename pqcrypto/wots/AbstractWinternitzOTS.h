#ifndef ABSTRACT_WINTERNITZ_OTS
#define ABSTRACT_WINTERNITZ_OTS

#include "primitives/AbstractDigest.h"


template<class T, class Enable = void>
class AbstractWinternitzOTS;

template <class T>
class AbstractWinternitzOTS 
	<T, typename std::enable_if<std::is_base_of<AbstractDigest, T>::value>::type> 
	: std::decay<T>::type {

public:
	virtual const unsigned int t() noexcept = 0;
	virtual const unsigned int t1() noexcept = 0;
	virtual const unsigned int t2() noexcept = 0;
	virtual const unsigned int w() noexcept = 0;
	virtual const unsigned int n() noexcept = 0;
};
#endif
