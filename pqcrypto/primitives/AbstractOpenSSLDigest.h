#ifndef ABSTRACT_OPENSSL_DIGEST
#define ABSTRACT_OPENSSL_DIGEST
#include <openssl/evp.h>
#include "primitives/AbstractDigest.h"

class AbstractOpenSSLDigest : public AbstractDigest {
public:
	virtual ByteArray digest(ByteArray& data) const noexcept {
		return evpDigestChain(data, 1);
	};
	virtual ByteArray digestChain(ByteArray& data, const unsigned int n) const noexcept {
		return evpDigestChain(data, n);
	};

protected:
	virtual const EVP_MD* algorithm() const noexcept = 0;

	virtual ByteArray evpDigestChain(ByteArray& data, const unsigned int n) const noexcept 
	{
		if(n <= 0)
			return data;
		//Check for null ctx 
		//TODO(perin) wrap around safe block n> 1?'
		const EVP_MD* md = this->algorithm();
		EVP_MD_CTX* ctx = EVP_MD_CTX_new();
		ByteArray ret(this->len());
		unsigned char* in_data = reinterpret_cast<unsigned char*>(data.data());
		unsigned char* out_data = reinterpret_cast<unsigned char*>(ret.data());
		EVP_DigestInit_ex(ctx, md, NULL);
		EVP_DigestUpdate(ctx, in_data, data.size());
		EVP_DigestFinal_ex(ctx, out_data, NULL);
		for(unsigned int i = 1; i < n; i++) {
			EVP_DigestInit_ex(ctx, md, NULL);
			EVP_MD_CTX_reset(ctx);
			EVP_DigestInit_ex(ctx, md, NULL);
			EVP_DigestUpdate(ctx, out_data, ret.size());
			EVP_DigestFinal_ex(ctx, out_data, NULL);
		}
		EVP_MD_CTX_free(ctx);
		return ret;
	};

};
#endif
