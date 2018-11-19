#include "gtest/gtest.h"
#include "wots/Wots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"

TEST(Wots_test, constructor_OpenSSLSha256) {
	ASSERT_EXIT( {
	{Wots<OpenSSLSha256> wots;} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(Wots_test, constructor_OpenSSLSha512) {
	ASSERT_EXIT( {
	{Wots<OpenSSLSha512> wots;} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(Wots_test, params_4_OpenSSLSha256) {
	Wots<OpenSSLSha256> wots(4);
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  2);
	ASSERT_EQ(wots.t(),  133);
	ASSERT_EQ(wots.t1(), 128);
	ASSERT_EQ(wots.t2(), 5);
}

TEST(Wots_test, params_16_OpenSSLSha256) {
	Wots<OpenSSLSha256> wots(16);
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  4);
	ASSERT_EQ(wots.t(),  67);
	ASSERT_EQ(wots.t1(), 64);
	ASSERT_EQ(wots.t2(), 3);
}

TEST(Wots_test, params_default_OpenSSLSha256) {
	Wots<OpenSSLSha256> wots(16);
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  4);
	ASSERT_EQ(wots.t(),  67);
	ASSERT_EQ(wots.t1(), 64);
	ASSERT_EQ(wots.t2(), 3);
}

TEST(Wots_test, params_256_OpenSSLSha256) {
	Wots<OpenSSLSha256> wots(256);
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  8);
	ASSERT_EQ(wots.t(),  34);
	ASSERT_EQ(wots.t1(), 32);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(Wots_test, params_65536_OpenSSLSha256) {
	Wots<OpenSSLSha256> wots(65536);
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  16);
	ASSERT_EQ(wots.t(),  18);
	ASSERT_EQ(wots.t1(), 16);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(Wots_test, params_any_OpenSSLSha256) {
	Wots<OpenSSLSha256> wots(777);
	ASSERT_EQ(wots.n(),  32);
	ASSERT_EQ(wots.w(),  16);
	ASSERT_EQ(wots.t(),  18);
	ASSERT_EQ(wots.t1(), 16);
	ASSERT_EQ(wots.t2(), 2);
}

TEST(Wots_test, load_private_key_OpenSSLSha256) {
	ASSERT_EXIT( {
	Wots<OpenSSLSha256> wots(777);
	wots.loadPrivKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(Wots_test, load_keys_65536_OpenSSLSha256) {
	ASSERT_EXIT( {
	Wots<OpenSSLSha256> wots(777);
	wots.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}
