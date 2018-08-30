#ifndef SHA256
#define SHA256

/**
 * Struct with undefined trait for bad types;
 */
template<typename T>
struct OpenSSLDigestAlgorithm;


class OpenSSLDigest {
public:

	/**
	* Returns the message digest using OpenSSL and Algorithm.
	*/
	virtual ByteArray digest();

	/**
	* Returns the chained message digest using OpenSSL and Algorithm.
	* The input is digested n times before return.
	*/
	virtual ByteArray chainedDigest();

	/**
	 * Returns PRF of input, detailed in RFC8391
	 */
	virtual ByteArray PRF();


protected:
	virtual ByteArray hash() = 0;

};
#endif
