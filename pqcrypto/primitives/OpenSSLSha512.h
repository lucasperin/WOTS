#ifndef SHA512
#define SHA512
#include "primitives/AbstractDigest.h"


class OpenSSLSha512 : public AbstractDigest {
	public:
	ByteArray digest(ByteArray& data) const;
	ByteArray digestChain(ByteArray& data, const unsigned int n) const;
	const unsigned int getMdLen() const;
};

/**
 * Defines Sha256 as a good type
 */
template<>
struct DigestAlgorithm<OpenSSLSha512>;

#endif
