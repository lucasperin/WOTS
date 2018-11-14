#ifndef SHA256
#define SHA256
#include "primitives/AbstractDigest.h"


class OpenSSLSha256 : public AbstractDigest {
public:
	virtual ByteArray digest(ByteArray& data) const;
	virtual ByteArray digestChain(ByteArray& data, const unsigned int n) const;
	virtual const unsigned int bitLen() const;
	virtual const unsigned int len() const;
protected:
	virtual ByteArray evpDigestChain(ByteArray& data, const EVP_MD* md, const unsigned int n) const;
};

#endif
