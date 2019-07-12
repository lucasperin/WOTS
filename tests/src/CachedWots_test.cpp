#include "gtest/gtest.h"
#include "wots/CachedWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>

using CWOTS_256_4 = CachedWots<OpenSSLSha256,4>;
using CWOTS_512_4 = CachedWots<OpenSSLSha512,4>;
using CWOTS_256_16 =CachedWots<OpenSSLSha256,16>;
using CWOTS_512_16 =CachedWots<OpenSSLSha512,16>;
using CWOTS_256_256 =CachedWots<OpenSSLSha256,256>;
using CWOTS_512_256 =CachedWots<OpenSSLSha512,256>;
using CWOTS_256_65536 = CachedWots<OpenSSLSha256,65536>;
using CWOTS_512_65536 = CachedWots<OpenSSLSha512,65536>;


TEST(CachedWots_test, constructor_OpenSSLSha256) {
	ASSERT_EXIT(
	{
	{CWOTS_256_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(CachedWots_test, constructor_OpenSSLSha512) {
	ASSERT_EXIT( {
	{CWOTS_512_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(CachedWots_test, params_4_OpenSSLSha256) {
	CWOTS_256_4 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  4);
	ASSERT_EQ(wots.t(),  133);
	ASSERT_EQ(wots.t1(), 128);
	ASSERT_EQ(wots.t2(), 5);
}

TEST(CachedWots_test, params_16_OpenSSLSha256) {
	CWOTS_256_16 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  16);
	ASSERT_EQ(wots.t(),  67);
	ASSERT_EQ(wots.t1(), 64);
	ASSERT_EQ(wots.t2(), 3);
}

TEST(CachedWots_test, params_256_OpenSSLSha256) {
	CWOTS_256_256 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  256);
	ASSERT_EQ(wots.t(),  34);
	ASSERT_EQ(wots.t1(), 32);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(CachedWots_test, params_65536_OpenSSLSha256) {
	CWOTS_256_65536 wots;
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  65536);
	ASSERT_EQ(wots.t(),  18);
	ASSERT_EQ(wots.t1(), 16);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(CachedWots_test, load_private_key_OpenSSLSha256_4) {
	ASSERT_EXIT( {
	CWOTS_256_4 wots;
	wots.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(CachedWots_test, load_private_key_OpenSSLSha256_16) {
	ASSERT_EXIT( {
	CWOTS_256_16 wots;
	wots.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(CachedWots_test, load_keys_4_OpenSSLSha256) {
	ASSERT_EXIT( {
	CWOTS_256_4 wots;
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(CachedWots_test, load_keys_16_OpenSSLSha256) {
	ASSERT_EXIT( {
	CWOTS_256_16 wots;
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(CachedWots_test, load_keys_256_OpenSSLSha256) {
	ASSERT_EXIT( {
	CWOTS_256_256 wots;
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}


TEST(CachedWots_test, sign_4_OpenSSLSha256) {
	CWOTS_256_4 wots;
	wots.loadKeys();
	ByteArray data = hstoba("My document");
	std::vector<ByteArray> sig = wots.sign(data);
}

TEST(CachedWots_test, sign_and_verify_4_OpenSSLSha256) {
	CWOTS_256_4 wots;
	wots.loadKeys();
	ByteArray data = hstoba("My document");
	std::vector<ByteArray> sig = wots.sign(data);
	ASSERT_EQ(wots.verify(data, sig), true);
}

TEST(CachedWots_test, sign_16_OpenSSLSha256) {
	CWOTS_256_16 wots;
	wots.loadKeys();
	ByteArray data = hstoba("My document");
	std::vector<ByteArray> sig = wots.sign(data);
}

TEST(CachedWots_test, sign_and_verify_16_OpenSSLSha256) {
	CWOTS_256_16 wots;
	wots.loadKeys();
	ByteArray data = hstoba("My document");
	std::vector<ByteArray> sig = wots.sign(data);
	ASSERT_EQ(wots.verify(data, sig), true);
}

TEST(CachedWots_test, sign_256_OpenSSLSha256) {
	CWOTS_256_256 wots;
	wots.loadKeys();
	ByteArray data = hstoba("My document");
	std::vector<ByteArray> sig = wots.sign(data);
}

TEST(CachedWots_test, sign_and_verify_256_OpenSSLSha256) {
	CWOTS_256_256 wots;
	wots.loadKeys();
	ByteArray data = hstoba("My document");
	std::vector<ByteArray> sig = wots.sign(data);
	ASSERT_EQ(wots.verify(data, sig), true);
}
