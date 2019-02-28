#ifndef SHA512
#define SHA512
#include "primitives/AbstractOpenSSLDigest.h"

class OpenSSLSha512 : public AbstractOpenSSLDigest {
public:
	virtual const unsigned int bitLen() const noexcept {
		return 512;
	};
	virtual const unsigned int len() const noexcept {
		return 64;
	};
protected:
	virtual const EVP_MD* algorithm() const noexcept {
		return EVP_sha512();
	};
};

#endif
