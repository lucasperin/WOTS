#include "gtest/gtest.h"
#include <encoding/ConstantSum.h>
#include <iostream>


TEST(Encoding_ConstantSum, BinomBigNum_DesthTest) {
	ASSERT_EXIT( {
	{
	mpz_class a = encoding::binomial(256,16);
	} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(Encoding_ConstantSum, BinomBigNum_Cerrectness) {
	mpz_class a = encoding::binomial(256,16);
	ASSERT_EQ(a.get_str(), "10078751602022313874633200");
}

TEST(Encoding_ConstantSum, BinomBigNum_Cerrectness2) {
	mpz_class a = encoding::binomial(512,16);
	ASSERT_EQ(a.get_str(), "841141456821158064519401490400");
}

TEST(Encoding_ConstantSum, BinomBigNum_Cerrectness3) {
	mpz_class a = encoding::binomial(512,80);
	ASSERT_EQ(a.get_str(), "113719551425878050452830187150740787820353332954058668336647175220291899316436868900912110998880");
}

TEST(Encoding_ConstantSum, BinomBigNum_Cerrectness4) {
	mpz_class a = encoding::binomial(512,160);
	ASSERT_EQ(a.get_str(), "48301503443499827943695225247548343537008325678090735035218902397819809645116963790498291632660216134771272896362693752375072712265502960");
}

TEST(Encoding_ConstantSum, ConstantSumLen_DeathTest) {
	ASSERT_EXIT( {
	{
	mpz_class a = encoding::constantSumLen(3,3,6);
	} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(Encoding_ConstantSum, ConstantSumLen_Correctness) {
	mpz_class a = encoding::constantSumLen(3,3,6);
	ASSERT_EQ(a.get_str(), "10");
}

TEST(Encoding_ConstantSum, ConstantSumLen_Correctness2) {
	mpz_class a = encoding::constantSumLen(80,255,4000);
	ASSERT_EQ(a.get_str(), "548075501737486113831767060631920062125348392934232045465397258269341658134355653562100889384337981452146018680653192902048597733310342649863443761919597676218862137231");
}

TEST(Encoding_ConstantSum, toConstantSum_DeathTest) {
	ASSERT_EXIT( {
	{
	mpz_class i = 1;
	std::vector<unsigned int> m = encoding::toConstantSum(i, 80,255,4000);
	} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(Encoding_ConstantSum, toConstantSum_Correctness) {
	mpz_class i = 1;
	std::vector<unsigned int> m = encoding::toConstantSum(i, 80,255,4000);
	ASSERT_EQ(m.size(), 80);
	std::vector<unsigned int> m2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 176, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
	ASSERT_EQ(m,m2);
}
