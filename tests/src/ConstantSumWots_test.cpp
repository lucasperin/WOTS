#include "gtest/gtest.h"
#include "wots/ConstantSumWots.h"
#include "wots/OriginalConstantSumWots.h"
#include "wots/VariantConstantSumWots.h"
#include "wots/CachedConstantSumWots.h"
#include "wots/DynamicCacheConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>



using WOTS_SHA256_255_34_3106 = ConstantSumWots<OpenSSLSha256,255,34,3106>;
using WOTS_SHA256_255_55_534 = ConstantSumWots<OpenSSLSha256,255,55,534>;
//Cached
using CWOTS_SHA256_255_34_3106 = CachedConstantSumWots<OpenSSLSha256,255,34,3106>;
using DCWOTS_SHA256_255_34_3106 = DynamicCacheConstantSumWots<OpenSSLSha256,255,34,3106>;
//Original
using WOTS_SHA256_34_2832 =  OriginalConstantSumWots<OpenSSLSha256,2832,34,2832>;
using WOTS_SHA256_55_534 =   OriginalConstantSumWots<OpenSSLSha256,534,55,534>;
// Variant
using VWOTS_SHA256_255_34_3106 = VariantConstantSumWots<OpenSSLSha256,300,34,3106>;
using VWOTS_SHA256_255_55_534 = VariantConstantSumWots<OpenSSLSha256,31,55,534>;


TEST(ConstantSumWots_test, constructor_256_255_34_3106) {
	ASSERT_EXIT(
	{
	{WOTS_SHA256_255_34_3106 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, constructor_256_255_34_3106_C) {
	ASSERT_EXIT(
	{
	{CWOTS_SHA256_255_34_3106 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, constructor_256_34_2832) {
	ASSERT_EXIT(
	{
	{WOTS_SHA256_34_2832 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, constructor_256_255_55_534) {
	ASSERT_EXIT(
	{
	{WOTS_SHA256_255_55_534 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_255_34_3106) {
	ASSERT_EXIT( {
	WOTS_SHA256_255_34_3106 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_255_34_3106_C) {
	ASSERT_EXIT( {
	CWOTS_SHA256_255_34_3106 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_34_2832) {
	ASSERT_EXIT( {
	WOTS_SHA256_34_2832 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_private_key_256_255_55_534) {
	ASSERT_EXIT( {
	WOTS_SHA256_255_55_534 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_255_34_3106) {
	ASSERT_EXIT( {
	WOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_255_34_3106_C) {
	ASSERT_EXIT( {
	CWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_34_2832) {
	ASSERT_EXIT( {
	WOTS_SHA256_34_2832 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, load_keys_256_255_55_534) {
	ASSERT_EXIT( {
	WOTS_SHA256_255_55_534 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ConstantSumWots_test, sign_256_255_34_3106) {
	WOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_256_34_2832) {
	WOTS_SHA256_34_2832 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_256_55_534) {
	WOTS_SHA256_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_256_34_2832_DC) {
	DCWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}


TEST(ConstantSumWots_test, sign_256_255_34_3106_C) {
	CWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_256_255_55_534) {
	WOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(ConstantSumWots_test, sign_and_verify_256_255_34_3106) {
	WOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_and_verify_256_255_34_3106_C) {
	CWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_and_verify_256_34_2832) {
	WOTS_SHA256_34_2832 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_and_verify_256_55_534) {
	WOTS_SHA256_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(ConstantSumWots_test, sign_and_verify_256_255_55_534) {
	WOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}


TEST(ConstantSumWots_test, sign_and_verify_256_255_34_3106_V) {
	VWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}


TEST(ConstantSumWots_test, sign_and_verify_256_255_55_534_V) {
	VWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

