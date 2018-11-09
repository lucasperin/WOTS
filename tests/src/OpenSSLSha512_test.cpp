#include "gtest/gtest.h"
#include <primitives/OpenSSLSha512.h>
#include <iostream>


/**
 * Tested with command
 * echo -n "test" | openssl dgst -sha512 -binary | xxd -p -u
 */
TEST(OpenSSLSha512_test, simple_hashing) {
	const std::string test = "test";
	ByteArray data = ByteArray::fromString(test);
	OpenSSLSha512 md;
	ByteArray h = md.digest(data);
	char const * compare = "EE26B0DD4AF7E749AA1A8EE3C10AE9923F618980772E473F8819A5D4940E0DB27AC185F8A0E1D5F84F88BC887FD67B143732C304CC5FA9AD8E6F57F50028A8FF";
	//std::cout << h.toHex() << std::endl;
	ASSERT_STREQ(h.toHex().c_str(), compare);
}

/**
 * Tested with command
 * echo -n "test" | openssl dgst -sha512 -binary | openssl dgst -sha512 -binary | xxd -p -u
 */
TEST(OpenSSLSha512_test, hash_twice) {
	const std::string test = "test";
	ByteArray data = ByteArray::fromString(test);
	OpenSSLSha512 md;
	ByteArray h = md.digestChain(data, 2);
	char const * compare = "FAADCAF60AFD35DFCDB5E9EA0D0A0531F6338C62187CFF37A1EFE11F1D41A34879731BC9DB49DF75AECF5D582AD09B5C6DED2D86BD1F07C11BD755D1FCCC81FE";
	ASSERT_STREQ(h.toHex().c_str(), compare);
}

/**
 * Tested with command
 * eval echo -n \"test\" $(perl -E "say '| openssl dgst -sha512 -binary' x 1000") | xxd -p -u
 */
TEST(OpenSSLSha512_test, hash_1k) {
	const std::string test = "test";
	ByteArray data = ByteArray::fromString(test);
	OpenSSLSha512 md;
	ByteArray h = md.digestChain(data, 1000);
	char const * compare = "A1F54AB92FB57B436FBE2A1703650DCF30CF8D380B5E7BD660723E7B6923EA7EAD2A6B4024D3F1FF710E3BDCE1C9CE8F63D53F7BF0DBF21E2EC65FC456523C1C";
	ASSERT_STREQ(h.toHex().c_str(), compare);
}
