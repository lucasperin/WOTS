#include "gtest/gtest.h"
#include "wots/ConstantSumWots.h"
#include "wots/CachedConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>


//using WOTS_256_4 = ConstantSumWots<OpenSSLSha256,4>;
//using WOTS_512_4 = ConstantSumWots<OpenSSLSha512,4>;
//using WOTS_256_16 =ConstantSumWots<OpenSSLSha256,16>;
//using WOTS_512_16 =ConstantSumWots<OpenSSLSha512,16>;
using WOTS_256_256_35_4462 = ConstantSumWots<OpenSSLSha256,256,35,4462>;
using WOTS_256_256_37_1972 = ConstantSumWots<OpenSSLSha256,256,37,1972>;
using CWOTS_256_256_35_4462 = ConstantSumWots<OpenSSLSha256,256,35,4462>;
//using WOTS_512_256 =ConstantSumWots<OpenSSLSha512,256>;
//using WOTS_256_65536 = ConstantSumWots<OpenSSLSha256,65536>;
//using WOTS_512_65536 = ConstantSumWots<OpenSSLSha512,65536>;


TEST(ConstantSumWots_test, constructor_256_256_35_4462) {
	ASSERT_EXIT(
	{
	{WOTS_256_256_35_4462 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, constructor_256_256_35_4462_C) {
	ASSERT_EXIT(
	{
	{CWOTS_256_256_35_4462 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, constructor_256_256_37_1972) {
	ASSERT_EXIT(
	{
	{WOTS_256_256_37_1972 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_256_35_4462) {
	ASSERT_EXIT( {
	WOTS_256_256_35_4462 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_256_35_4462_C) {
	ASSERT_EXIT( {
	CWOTS_256_256_35_4462 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_256_37_1972) {
	ASSERT_EXIT( {
	WOTS_256_256_37_1972 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_256_35_4462) {
	ASSERT_EXIT( {
	WOTS_256_256_35_4462 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_256_35_4462_C) {
	ASSERT_EXIT( {
	CWOTS_256_256_35_4462 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_256_37_1972) {
	ASSERT_EXIT( {
	WOTS_256_256_37_1972 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, sign_256_256_35_4462) {
	WOTS_256_256_35_4462 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_256_256_35_4462_C) {
	CWOTS_256_256_35_4462 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_256_256_37_1972) {
	WOTS_256_256_37_1972 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_and_verify_256_256_35_4462) {
	WOTS_256_256_35_4462 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_and_verify_256_256_35_4462_C) {
	CWOTS_256_256_35_4462 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_and_verify_256_256_37_1972) {
	WOTS_256_256_37_1972 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}


/*

TEST(ConstantSumWots_test, constructor_OpenSSLSha256) {
	ASSERT_EXIT(
	{
	{WOTS_256_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, constructor_OpenSSLSha512) {
	ASSERT_EXIT( {
	{WOTS_512_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, params_4_OpenSSLSha256) {
	WOTS_256_4 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  4);
	ASSERT_EQ(w.t(),  133);
	ASSERT_EQ(w.t1(), 128);
	ASSERT_EQ(w.t2(), 5);
}

TEST(ConstantSumWots_test, params_16_OpenSSLSha256) {
	WOTS_256_16 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  16);
	ASSERT_EQ(w.t(),  67);
	ASSERT_EQ(w.t1(), 64);
	ASSERT_EQ(w.t2(), 3);
}

TEST(ConstantSumWots_test, params_256_OpenSSLSha256) {
	WOTS_256_256 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  256);
	ASSERT_EQ(w.t(),  34);
	ASSERT_EQ(w.t1(), 32);
	ASSERT_EQ(w.t2(), 2);
}

TEST(ConstantSumWots_test, params_65536_OpenSSLSha256) {
	WOTS_256_65536 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  65536);
	ASSERT_EQ(w.t(),  18);
	ASSERT_EQ(w.t1(), 16);
	ASSERT_EQ(w.t2(), 2);
}

TEST(ConstantSumWots_test, load_private_key_OpenSSLSha256_4) {
	ASSERT_EXIT( {
	WOTS_256_4 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_OpenSSLSha256_16) {
	ASSERT_EXIT( {
	WOTS_256_16 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_4_OpenSSLSha256) {
	ASSERT_EXIT( {
	WOTS_256_4 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_16_OpenSSLSha256) {
	ASSERT_EXIT( {
	WOTS_256_16 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_OpenSSLSha256) {
	ASSERT_EXIT( {
	WOTS_256_256 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}


TEST(ConstantSumWots_test, sign_4_OpenSSLSha256) {
	WOTS_256_4 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_and_verify_4_OpenSSLSha256) {
	WOTS_256_4 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_16_OpenSSLSha256) {
	WOTS_256_16 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_and_verify_16_OpenSSLSha256) {
	WOTS_256_16 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_256_OpenSSLSha256) {
	WOTS_256_256 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_and_verify_256_OpenSSLSha256) {
	WOTS_256_256 w;
	w.loadKeys();
	ByteArray data = ByteArray::fromString("My document");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}
*/
