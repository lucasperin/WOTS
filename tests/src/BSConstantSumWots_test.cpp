#include "gtest/gtest.h"
#include "wots/BSConstantSumWots.h"
#include "wots/OBSConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>

using BSWOTS_SHA256_255_34_3106 = BSConstantSumWots<OpenSSLSha256,255,34,3106>;
using BSWOTS_SHA256_255_55_534 = BSConstantSumWots<OpenSSLSha256,255,55,534>;
using OBSWOTS_SHA256_255_34_3106 = OBSConstantSumWots<OpenSSLSha256,255,34,3106>;
using OBSWOTS_SHA256_255_55_534 = OBSConstantSumWots<OpenSSLSha256,255,55,534>;

TEST(BSConstantSumWots_test, rank_256_255_34_3106) {
	mpz_class sum = 0;
	BSWOTS_SHA256_255_34_3106 CS;
	for(int j = 0; j <= 256; j++) {
		sum += CS.pconst(33, 255,3106-j);
		mpz_class rank = CS.prank(33,255,3106,j);
		ASSERT_EQ(sum, rank);
	}

}

TEST(BSConstantSumWots_test, constructor_256_255_34_3106) {
	ASSERT_EXIT(
	{
	{BSWOTS_SHA256_255_34_3106 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}


TEST(BSConstantSumWots_test, constructor_256_255_55_534) {
	ASSERT_EXIT(
	{
	{BSWOTS_SHA256_255_55_534 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(BSConstantSumWots_test, load_private_key_256_255_34_3106) {
	ASSERT_EXIT( {
	BSWOTS_SHA256_255_34_3106 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}


TEST(BSConstantSumWots_test, load_private_key_256_255_55_534) {
	ASSERT_EXIT( {
	BSWOTS_SHA256_255_55_534 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(BSConstantSumWots_test, load_keys_256_255_34_3106) {
	ASSERT_EXIT( {
	BSWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(BSConstantSumWots_test, load_keys_256_255_55_534) {
	ASSERT_EXIT( {
	BSWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(BSConstantSumWots_test, sign_256_255_34_3106) {
	BSWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(BSConstantSumWots_test, sign_256_255_55_534) {
	BSWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(BSConstantSumWots_test, sign_and_verify_256_255_34_3106) {
	BSWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(BSConstantSumWots_test, sign_and_verify_256_255_55_534) {
	BSWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}




TEST(BSConstantSumWots_test, sign_and_verify_256_255_34_3106_O) {
	OBSWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(BSConstantSumWots_test, sign_and_verify_256_255_55_534_O) {
	OBSWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}




TEST(BSConstantSumWots_test, fast_sign_and_verify_256_255_34_3106) {
	BSWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	std::vector<unsigned int> fp = w.genFingerprint(data);
	ASSERT_EQ(w.check_encoding(data, fp), true);
	ASSERT_EQ(w.fast_verify(data, sig, fp), true);
}

TEST(BSConstantSumWots_test, fast_sign_and_verify_256_255_55_534) {
	BSWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	std::vector<unsigned int> fp = w.genFingerprint(data);
	ASSERT_EQ(w.check_encoding(data, fp), true);
	ASSERT_EQ(w.fast_verify(data, sig, fp), true);
}

TEST(BSConstantSumWots_test, fail_fast_sign_and_verify_256_255_34_3106) {
	BSWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	std::vector<unsigned int> fp = w.genFingerprint(data);
	fp[0]++;
	ASSERT_EQ(w.check_encoding(data, fp), false);
	ASSERT_EQ(w.fast_verify(data, sig, fp), false);
}

TEST(BSConstantSumWots_test, fail_fast_sign_and_verify_256_255_55_534) {
	BSWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	std::vector<unsigned int> fp = w.genFingerprint(data);
	fp[0]++;
	ASSERT_EQ(w.check_encoding(data, fp), false);
	ASSERT_EQ(w.fast_verify(data, sig, fp), false);
}

