#ifndef ABSTRACT_DIGEST
#define ABSTRACT_DIGEST
#include <openssl/evp.h>
#include "ByteArray.h"
#include <assert.h>

/**
 * Struct with undefined trait for bad types;
 */
template<typename T>
struct DigestAlgorithm;


class AbstractDigest {
public:

	virtual ByteArray digest(ByteArray& data) const = 0;
	virtual ByteArray digestChain(ByteArray& data, const unsigned int n) const = 0;
	virtual const unsigned int getMdLen() const = 0;
	virtual std::vector<unsigned int> toBaseW(const ByteArray& hash, const unsigned int w) const;

	/**
	* Returns the chained message digest using OpenSSL and Algorithm.
	* The input is digested n times before return.
	*/
	//virtual ByteArray chainedDigest();

	/**
	 * Returns PRF of input, detailed in RFC8391
	 */
	//virtual ByteArray PRF();


protected:

	/**
	* Returns the message digest using OpenSSL and Algorithm.
	*/
	virtual ByteArray evpDigestChain(ByteArray& data, const EVP_MD* md, const unsigned int n) const;
};
#endif
