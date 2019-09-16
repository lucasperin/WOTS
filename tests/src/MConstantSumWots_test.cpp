#include "gtest/gtest.h"
#include "wots/MConstantSumWots.h"
#include "wots/MCachedConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>


//using MWOTS256_4 = ConstantSumWots<OpenSSLSha256,4>;
//using MWOTS512_4 = ConstantSumWots<OpenSSLSha512,4>;
//using MWOTS256_16 =ConstantSumWots<OpenSSLSha256,16>;
//using MWOTS512_16 =ConstantSumWots<OpenSSLSha512,16>;
using MWOTS_SHA256_255_34_3106 = MConstantSumWots<OpenSSLSha256,255,34,3106>;
using MWOTS_SHA256_255_55_534 = MConstantSumWots<OpenSSLSha256,255,55,534>;
using CMWOTS_SHA256_255_34_3106 = MCachedConstantSumWots<OpenSSLSha256,255,34,3106>;
//using MWOTS512_256 =ConstantSumWots<OpenSSLSha512,256>;
//using MWOTS256_65536 = ConstantSumWots<OpenSSLSha256,65536>;
//using MWOTS512_65536 = ConstantSumWots<OpenSSLSha512,65536>;


TEST(MConstntSumWots_test, constructor_256_255_34_3106) {
	ASSERT_EXIT(
	{
	{MWOTS_SHA256_255_34_3106 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, constructor_256_255_34_3106_C) {
	ASSERT_EXIT(
	{
	{CMWOTS_SHA256_255_34_3106 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, constructor_256_255_55_534) {
	ASSERT_EXIT(
	{
	{MWOTS_SHA256_255_55_534 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_private_key_256_255_34_3106) {
	ASSERT_EXIT( {
	MWOTS_SHA256_255_34_3106 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_private_key_256_255_34_3106_C) {
	ASSERT_EXIT( {
	CMWOTS_SHA256_255_34_3106 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_private_key_256_255_55_534) {
	ASSERT_EXIT( {
	MWOTS_SHA256_255_55_534 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_keys_256_255_34_3106) {
	ASSERT_EXIT( {
	MWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_keys_256_255_34_3106_C) {
	ASSERT_EXIT( {
	CMWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_keys_256_255_55_534) {
	ASSERT_EXIT( {
	MWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, sign_256_255_34_3106) {
	MWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(MConstntSumWots_test, sign_256_255_34_3106_C) {
	CMWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(MConstntSumWots_test, sign_256_255_55_534) {
	MWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(MConstntSumWots_test, sign_and_verify_256_255_34_3106) {
	MWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(MConstntSumWots_test, sign_and_verify_256_255_34_3106_C) {
	CMWOTS_SHA256_255_34_3106 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(MConstntSumWots_test, sign_and_verify_256_255_55_534) {
	MWOTS_SHA256_255_55_534 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}


/*

TEST(MConstntSumWots_test, constructor_OpenSSLSha256) {
	ASSERT_EXIT(
	{
	{MWOTS256_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, constructor_OpenSSLSha512) {
	ASSERT_EXIT( {
	{MWOTS512_4 w;}
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, params_4_OpenSSLSha256) {
	MWOTS256_4 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  4);
	ASSERT_EQ(w.t(),  133);
	ASSERT_EQ(w.t1(), 128);
	ASSERT_EQ(w.t2(), 5);
}

TEST(MConstntSumWots_test, params_16_OpenSSLSha256) {
	MWOTS256_16 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  16);
	ASSERT_EQ(w.t(),  67);
	ASSERT_EQ(w.t1(), 64);
	ASSERT_EQ(w.t2(), 3);
}

TEST(MConstntSumWots_test, params_256_OpenSSLSha256) {
	MWOTS256_256 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  256);
	ASSERT_EQ(w.t(),  34);
	ASSERT_EQ(w.t1(), 32);
	ASSERT_EQ(w.t2(), 2);
}

TEST(MConstntSumWots_test, params_65536_OpenSSLSha256) {
	MWOTS256_65536 w;
	ASSERT_EQ(w.n(),  32);
	ASSERT_EQ(w.w(),  65536);
	ASSERT_EQ(w.t(),  18);
	ASSERT_EQ(w.t1(), 16);
	ASSERT_EQ(w.t2(), 2);
}

TEST(MConstntSumWots_test, load_private_key_OpenSSLSha256_4) {
	ASSERT_EXIT( {
	MWOTS256_4 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_private_key_OpenSSLSha256_16) {
	ASSERT_EXIT( {
	MWOTS256_16 w;
	w.loadPrivateKey();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_keys_4_OpenSSLSha256) {
	ASSERT_EXIT( {
	MWOTS256_4 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_keys_16_OpenSSLSha256) {
	ASSERT_EXIT( {
	MWOTS256_16 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(MConstntSumWots_test, load_keys_256_OpenSSLSha256) {
	ASSERT_EXIT( {
	MWOTS256_256 w;
	w.loadKeys();
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}


TEST(MConstntSumWots_test, sign_4_OpenSSLSha256) {
	MWOTS256_4 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(MConstntSumWots_test, sign_and_verify_4_OpenSSLSha256) {
	MWOTS256_4 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(MConstntSumWots_test, sign_16_OpenSSLSha256) {
	MWOTS256_16 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(MConstntSumWots_test, sign_and_verify_16_OpenSSLSha256) {
	MWOTS256_16 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}

TEST(MConstntSumWots_test, sign_256_OpenSSLSha256) {
	MWOTS256_256 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
}

TEST(MConstntSumWots_test, sign_and_verify_256_OpenSSLSha256) {
	MWOTS256_256 w;
	w.loadKeys();
	ByteArray data = hstoba("0102030F");
	std::vector<ByteArray> sig = w.sign(data);
	ASSERT_EQ(w.verify(data, sig), true);
}
*/
