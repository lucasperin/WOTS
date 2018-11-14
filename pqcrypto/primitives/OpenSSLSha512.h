#ifndef SHA512
#define SHA512
#include "primitives/OpenSSLSha256.h"


class OpenSSLSha512 : public OpenSSLSha256 {
	public:
	ByteArray digest(ByteArray& data) const;
	ByteArray digestChain(ByteArray& data, const unsigned int n) const;
	virtual const unsigned int bitLen() const;
	virtual const unsigned int len() const;
};

#endif
