#include "gtest/gtest.h"
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>

TEST(RunLengthOTS_test, constructor_OpenSSLSha256) {
	ASSERT_EXIT( {
	{RunLengthOTS<OpenSSLSha256> ots;} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(RunLengthOTS_test, constructor_OpenSSLSha512) {
	ASSERT_EXIT( {
	{RunLengthOTS<OpenSSLSha512> ots;} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(RunLengthOTS_test, params_OpenSSLSha256) {
	RunLengthOTS<OpenSSLSha256> ots;
	ASSERT_EQ(ots.rMin(),  123);
	ASSERT_EQ(ots.rMax(),  131);
	ASSERT_EQ(ots.l(), 7);
}

TEST(RunLengthOTS_test, params_OpenSSLSha512) {
	RunLengthOTS<OpenSSLSha512> ots;
	ASSERT_EQ(ots.rMin(),  123);
	ASSERT_EQ(ots.rMax(),  131);
	ASSERT_EQ(ots.l(), 8);
}

TEST(RunLengthOTS_test, load_private_key_OpenSSLSha256) {
	ASSERT_EXIT( {
	RunLengthOTS<OpenSSLSha256> ots;
	ots.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(RunLengthOTS_test, load_private_key_OpenSSLSha512) {
	ASSERT_EXIT( {
	RunLengthOTS<OpenSSLSha512> ots;
	ots.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(RunLengthOTS_test, print_key) {
	RunLengthOTS<OpenSSLSha256> ots;
	ots.loadKeys();

	std::cout << " -- Public Key -- " << std::endl;
	ByteArray pub = ots.publicKey();
	std::cout << pub.toHex() << std::endl;
}

TEST(RunLengthOTS_test, sign_OpenSSLSha256) {
	RunLengthOTS<OpenSSLSha256> ots;
	ots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = ots.sign(data);
}

/* Too slow..
TEST(RunLengthOTS_test, sign_OpenSSLSha512) {
	RunLengthOTS<OpenSSLSha512> ots;
	ots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = ots.sign(data);
}
*/

TEST(RunLengthOTS_test, sign_and_verify_OpenSSLSha256) {
	RunLengthOTS<OpenSSLSha256> ots;
	ots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = ots.sign(data);
	ASSERT_EQ(ots.verify(data, sig), true);
}

/*
TEST(RunLengthOTS_test, sign_and_verify_OpenSSLSha512) {
	RunLengthOTS<OpenSSLSha512> ots;
	ots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = ots.sign(data);
	ASSERT_EQ(ots.verify(data, sig), true);
}
*/

TEST(RunLengthOTS_test, sign_and_verify_R_OpenSSLSha256) {
	RunLengthOTS<OpenSSLSha256> ots;
	ots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::pair<std::vector<ByteArray>,int> sig = ots.sign2(data);
	ASSERT_EQ(ots.verify(data, sig.first, sig.second), true);
}

