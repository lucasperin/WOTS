#include "primitives/OpenSSLSha256.h"

ByteArray OpenSSLSha256::digest(ByteArray& data) const {
	return evpDigestChain(data, EVP_sha256(), 1);
}

ByteArray OpenSSLSha256::digestChain(ByteArray& data, const unsigned int n) const {
	return evpDigestChain(data, EVP_sha256(), n);
};

const unsigned int OpenSSLSha256::bitLen() const {
	return 256;
};

const unsigned int OpenSSLSha256::len() const {
	return 32;
};

ByteArray OpenSSLSha256::evpDigestChain(ByteArray& data, const EVP_MD* md, const unsigned int n) const {
	if(n <= 0)
		return data;
	//Check for null ctx 
	//TODO(perin) wrap around safe block n> 1?'
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	ByteArray ret(this->len());
	EVP_DigestInit_ex(ctx, md, NULL);
	EVP_DigestUpdate(ctx, data.getDataPointer(), data.size());
	EVP_DigestFinal_ex(ctx, ret.getDataPointer(), NULL);
	for(unsigned int i = 1; i < n; i++) {
		EVP_DigestInit_ex(ctx, md, NULL);
		EVP_MD_CTX_reset(ctx);
		EVP_DigestInit_ex(ctx, md, NULL);
		EVP_DigestUpdate(ctx, ret.getDataPointer(), ret.size());
		EVP_DigestFinal_ex(ctx, ret.getDataPointer(), NULL);
	}
	EVP_MD_CTX_free(ctx);
	return ret;
};

