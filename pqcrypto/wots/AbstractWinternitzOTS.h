#ifndef ABSTRACT_WINTERNITZ_OTS
#define ABSTRACT_WINTERNITZ_OTS

#include "primitives/AbstractDigest.h"


template<class T, class Enable = void>
class AbstractWinternitzOTS;

template <class T>
class AbstractWinternitzOTS 
	<T, typename std::enable_if<std::is_base_of<AbstractDigest, T>::value>::type> 
	: private std::decay<T>::type {

public:
	AbstractWinternitzOTS();
	
	virtual int t();
	virtual int t1();
	virtual int t2();
	virtual int w();
	virtual int n();

private:
	virtual void init();

	cardinality fingerprint_blocks;
	cardinality checksum_blocks;
	length block;
	
};
#endif
