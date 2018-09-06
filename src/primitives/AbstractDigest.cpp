#include "primitives/AbstractDigest.h"

ByteArray AbstractDigest::evpDigestChain(ByteArray& data, const EVP_MD* md, const unsigned int n) const {
	//Check for null ctx 
	//TODO(perin) wrap around safe block n> 1?'
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	ByteArray ret(getMdLen());
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

std::vector<unsigned int> AbstractDigest::toBaseW(const ByteArray& hash, const unsigned int w) const {
	//TODO(Perin): assert w and size is power of 2 and w | size 
	std::vector<unsigned int> teste;
	return teste;
}
