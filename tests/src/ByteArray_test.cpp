#include "gtest/gtest.h"
#include <ByteArray.h>
#include <iostream>


TEST(ByteArray_test, Build_n_destroy) {
	ASSERT_EXIT( {
	{ByteArray data;} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ByteArray_test, constructor) {
	ASSERT_EXIT( {
	{ByteArray data(200);} 
	exit(0);
	},::testing::ExitedWithCode(0),".*");
}

TEST(ByteArray_test, constructor_negative) {
	ASSERT_EXIT( {
	{ByteArray data(-1);} 
	exit(0);
	},::testing::KilledBySignal(SIGSEGV),".*");
}


TEST(ByteArray_test, base_4) {
	const std::string test = "12348C5A";
	ByteArray data = ByteArray::fromHex(test);
	std::vector<unsigned int> base_w = data.toBaseW(4);
	ASSERT_EQ(0, base_w[0]);
	ASSERT_EQ(1, base_w[1]); //0001
	ASSERT_EQ(0, base_w[2]);
	ASSERT_EQ(2, base_w[3]); //0010
	ASSERT_EQ(0, base_w[4]);
	ASSERT_EQ(3, base_w[5]); //0011
	ASSERT_EQ(1, base_w[6]);
	ASSERT_EQ(0, base_w[7]); //0100
	ASSERT_EQ(2, base_w[8]);
	ASSERT_EQ(0, base_w[9]); //1000
	ASSERT_EQ(3, base_w[10]);
	ASSERT_EQ(0, base_w[11]); //1100
	ASSERT_EQ(1, base_w[12]);
	ASSERT_EQ(1, base_w[13]); //0101
	ASSERT_EQ(2, base_w[14]);
	ASSERT_EQ(2, base_w[15]); //1010
}

TEST(ByteArray_test, base_16) {
	const std::string test = "123456789ABCDEF";
	ByteArray data = ByteArray::fromHex(test);
	std::vector<unsigned int> base_w = data.toBaseW(16);
	for(unsigned int i = 0; i < 16;i++) {
		ASSERT_EQ(i, base_w[i]);
	}
}


TEST(ByteArray_test, DISABLED_base_65536) {
	FAIL() << "NOT IMPLEMENTED";
}


