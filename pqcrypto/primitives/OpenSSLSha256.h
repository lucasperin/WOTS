#ifndef SHA256
#define SHA256
#include "primitives/AbstractOpenSSLDigest.h"

class OpenSSLSha256 : public AbstractOpenSSLDigest {
public:
	const unsigned int bitLen() const noexcept {
		return 256; 
	};
	const unsigned int len() const noexcept {
		return 32;
	};
protected:
	const EVP_MD* algorithm() const noexcept {
		return EVP_sha256();
	};
};

#endif
