#ifndef ABSTRACT_DIGEST
#define ABSTRACT_DIGEST
#include "utils/ByteArray.hpp"

class AbstractDigest {
public:
	virtual ByteArray digest(ByteArray& data) const noexcept = 0;
	virtual ByteArray digestChain(ByteArray& data, const unsigned int n) const noexcept = 0;
	virtual const unsigned int bitLen() const noexcept = 0;
	virtual const unsigned int len() const noexcept = 0;
	/**
	 * Returns PRF of input, detailed in RFC8391
	 */
	//virtual ByteArray PRF();
};
#endif
