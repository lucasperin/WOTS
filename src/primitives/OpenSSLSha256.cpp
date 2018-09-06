#include "primitives/OpenSSLSha256.h"

ByteArray OpenSSLSha256::digest(ByteArray& data) const {
	return evpDigestChain(data, EVP_sha256(), 1);
}

ByteArray OpenSSLSha256::digestChain(ByteArray& data, const unsigned int n) const {
	return evpDigestChain(data, EVP_sha256(), n);
};

const unsigned int OpenSSLSha256::getMdLen() const {
	return 32;
};
