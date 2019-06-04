#include "gtest/gtest.h"
#include "wots/ClassicWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>

using WOTS_256_4 = ClassicWots<OpenSSLSha256,4>;
using WOTS_512_4 = ClassicWots<OpenSSLSha512,4>;
using WOTS_256_16 =ClassicWots<OpenSSLSha256,16>;
using WOTS_512_16 =ClassicWots<OpenSSLSha512,16>;
using WOTS_256_256 =ClassicWots<OpenSSLSha256,256>;
using WOTS_512_256 =ClassicWots<OpenSSLSha512,256>;
using WOTS_256_65536 = ClassicWots<OpenSSLSha256,65536>;
using WOTS_512_65536 = ClassicWots<OpenSSLSha512,65536>;

TEST(ClassicWots_test, constructor_OpenSSLSha256) {
	ASSERT_EXIT(
	{
	{WOTS_256_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ClassicWots_test, constructor_OpenSSLSha512) {
	ASSERT_EXIT( {
	{WOTS_512_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ClassicWots_test, params_4_OpenSSLSha256) {
	WOTS_256_4 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  4);
	ASSERT_EQ(wots.t(),  133);
	ASSERT_EQ(wots.t1(), 128);
	ASSERT_EQ(wots.t2(), 5);
}

TEST(ClassicWots_test, params_16_OpenSSLSha256) {
	WOTS_256_16 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  16);
	ASSERT_EQ(wots.t(),  67);
	ASSERT_EQ(wots.t1(), 64);
	ASSERT_EQ(wots.t2(), 3);
}

TEST(ClassicWots_test, params_256_OpenSSLSha256) {
	WOTS_256_256 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  256);
	ASSERT_EQ(wots.t(),  34);
	ASSERT_EQ(wots.t1(), 32);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(ClassicWots_test, params_65536_OpenSSLSha256) {
	WOTS_256_65536 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  65536);
	ASSERT_EQ(wots.t(),  18);
	ASSERT_EQ(wots.t1(), 16);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(ClassicWots_test, load_private_key_OpenSSLSha256_4) {
	ASSERT_EXIT( {
	WOTS_256_4 wots;
	wots.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ClassicWots_test, load_private_key_OpenSSLSha256_16) {
	ASSERT_EXIT( {
	WOTS_256_16 wots;
	wots.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ClassicWots_test, load_keys_4_OpenSSLSha256) {
	ASSERT_EXIT( {
	WOTS_256_4 wots;
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ClassicWots_test, load_keys_16_OpenSSLSha256) {
	ASSERT_EXIT( {
	WOTS_256_16 wots;
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ClassicWots_test, load_keys_256_OpenSSLSha256) {
	ASSERT_EXIT( {
	WOTS_256_256 wots;
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}


TEST(ClassicWots_test, sign_4_OpenSSLSha256) {
	WOTS_256_4 wots;
	wots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = wots.sign(data);
}

TEST(ClassicWots_test, sign_and_verify_4_OpenSSLSha256) {
	WOTS_256_4 wots;
	wots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = wots.sign(data);
	ASSERT_EQ(wots.verify(data, sig), true);
}

TEST(ClassicWots_test, sign_16_OpenSSLSha256) {
	WOTS_256_16 wots;
	wots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = wots.sign(data);
}

TEST(ClassicWots_test, sign_and_verify_16_OpenSSLSha256) {
	WOTS_256_16 wots;
	wots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = wots.sign(data);
	ASSERT_EQ(wots.verify(data, sig), true);
}

TEST(ClassicWots_test, sign_256_OpenSSLSha256) {
	WOTS_256_256 wots;
	wots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = wots.sign(data);
}

TEST(ClassicWots_test, sign_and_verify_256_OpenSSLSha256) {
	WOTS_256_256 wots;
	wots.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = wots.sign(data);
	ASSERT_EQ(wots.verify(data, sig), true);
}
