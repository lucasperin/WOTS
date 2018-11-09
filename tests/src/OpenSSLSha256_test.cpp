#include "gtest/gtest.h"
#include <primitives/OpenSSLSha256.h>
#include <iostream>


/**
 * Tested with command
 * echo -n "test" | openssl dgst -sha256 -binary | xxd -p -u
 */
TEST(OpenSSLSha256_test, simple_hashing) {
	const std::string test = "test";
	ByteArray data = ByteArray::fromString(test);
	OpenSSLSha256 md;
	ByteArray h = md.digest(data);
	char const * compare = "9F86D081884C7D659A2FEAA0C55AD015A3BF4F1B2B0B822CD15D6C15B0F00A08";
	//std::cout << h.toHex() << std::endl;
	ASSERT_STREQ(h.toHex().c_str(), compare);
}

/**
 * Tested with command
 * echo -n "test" | openssl dgst -sha256 -binary | openssl dgst -sha256 -binary | xxd -p -u
 */
TEST(OpenSSLSha256_test, hash_twice) {
	const std::string test = "test";
	ByteArray data = ByteArray::fromString(test);
	OpenSSLSha256 md;
	ByteArray h = md.digestChain(data, 2);
	char const * compare = "954D5A49FD70D9B8BCDB35D252267829957F7EF7FA6C74F88419BDC5E82209F4";
	ASSERT_STREQ(h.toHex().c_str(), compare);
}

/**
 * Tested with command
 * eval echo -n \"test\" $(perl -E "say '| openssl dgst -sha256 -binary' x 1000") | xxd -p -u
 */
TEST(OpenSSLSha256_test, hash_1k) {
	const std::string test = "test";
	ByteArray data = ByteArray::fromString(test);
	OpenSSLSha256 md;
	ByteArray h = md.digestChain(data, 1000);
	char const * compare = "C8208299A76EBE678FC90C5F52E3272314493352F3C95927839828AD83E57324";
	ASSERT_STREQ(h.toHex().c_str(), compare);
}

