#ifndef ABSTRACT_WINTERNITZ_OTS
#define ABSTRACT_WINTERNITZ_OTS

#include "OpenSSLDigest.h"


typedef int cardinality;
typedef int length;

template <typename T>
class AbstractWinternitzOTS : private OpenSSLDigestAlgorithm<T> {
public:
	AbstractWinternitzOTS();
	
	virtual cardinality t();
	virtual carcardinality t1();
	virtual carcardinality t2();
	virtual carlength w();
	virtual carlength n();


protected:
	virtual void convertBaseW();

private:
	virtual void init();

	cardinality fingerprint_blocks;
	cardinality checksum_blocks;
	length block;
	
};
#endif
