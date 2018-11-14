#include "primitives/OpenSSLSha512.h"

ByteArray OpenSSLSha512::digest(ByteArray& data) const {
	return this->evpDigestChain(data, EVP_sha512(), 1);
}

ByteArray OpenSSLSha512::digestChain(ByteArray& data, const unsigned int n) const {
	return this->evpDigestChain(data, EVP_sha512(), n);
};

const unsigned int OpenSSLSha512::bitLen() const {
	return 512;
};

const unsigned int OpenSSLSha512::len() const {
	return 64;
};

