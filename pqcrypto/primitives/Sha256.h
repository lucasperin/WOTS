#ifndef SHA256
#define SHA256
#include "OpenSSLDigest"


/**
 * Defines Sha256 as a good type
 */
template<>
struct OpenSSLDigestAlgorithm<Sha256>;

class Sha256 : public OpenSSLDigest {
	protected:
	ByteArray hash();
};
#endif
