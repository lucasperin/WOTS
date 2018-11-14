#ifndef ABSTRACT_DIGEST
#define ABSTRACT_DIGEST
#include <openssl/evp.h>
#include "ByteArray.h"
#include <assert.h>

class AbstractDigest {
public:

	virtual ByteArray digest(ByteArray& data) const = 0;
	virtual ByteArray digestChain(ByteArray& data, const unsigned int n) const = 0;
	virtual const unsigned int bitLen() const = 0;
	virtual const unsigned int len() const = 0;
	/**
	 * Returns PRF of input, detailed in RFC8391
	 */
	//virtual ByteArray PRF();
};
#endif
