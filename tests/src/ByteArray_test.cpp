#include "gtest/gtest.h"
#include <utils/ByteArray.hpp>
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
	EXPECT_THROW( {
	{ByteArray data(-1);} 
	exit(0);
	}, std::exception);
}

TEST(ByteArray_test, constructor_std_byte_array) {
	std::byte c[2] = {std::byte{0x41}, std::byte{0x42}}; 
	ASSERT_EXIT( {
	{ByteArray t(c, 2);}
	exit(0);
	},::testing::ExitedWithCode(0),".*");		
}

TEST(ByteArray_test, constructor_std_byte_array_value) {
	std::byte c[2] = {std::byte{0x41}, std::byte{0x42}}; 
	ByteArray data(c, 2);
	ASSERT_EQ(std::to_string(data), "4142");
}

TEST(ByteArray_test, constructor_char_cast) {
	char c[2] = {0x41, 0x42}; 
	ASSERT_EXIT( {
	{ByteArray t(reinterpret_cast<std::byte*>(c), 2);}
	exit(0);
	},::testing::ExitedWithCode(0),".*");		
}

TEST(ByteArray_test, constructor_char_cast_value) {
	char c[2] = {0x41, 0x42}; 
	ByteArray data(reinterpret_cast<std::byte*>(c), 2);
	ASSERT_EQ(std::to_string(data), "4142");
}

TEST(ByteArray_test, bytes_to_char_indirect_conversion) {
	char c[2] = {0x41, 0x42}; 
	ByteArray ba(reinterpret_cast<std::byte*>(c), 2);
	std::vector<std::byte> bytes = ba.container();
	char* cbytes = reinterpret_cast<char*>(bytes.data());
	ASSERT_EQ(cbytes[0], 0x41);
	ASSERT_EQ(cbytes[1], 0x42);
}

TEST(ByteArray_test, bytes_to_char_direct_conversion) {
	char c[2] = {0x41, 0x42}; 
	ByteArray ba(reinterpret_cast<std::byte*>(c), 2);
	char* cbytes = reinterpret_cast<char*>(ba.data());
	ASSERT_EQ(cbytes[0], 0x41);
	ASSERT_EQ(cbytes[1], 0x42);
}

TEST(ByteArray_test, manipulate_internal_data_as_char) {
	ByteArray ba(3);
	unsigned char* cbytes = reinterpret_cast<unsigned char*>(ba.data());
	cbytes[0] = 0x40;
	cbytes[1] = 0x41;
	cbytes[2] = 0x42;
	ASSERT_EQ(std::to_string(ba), "404142");
}

TEST(ByteArray_test, hex_conversion) {
	auto data = "00"_ba;
	ASSERT_EQ(std::to_string(data), "00");
	data = "01"_ba;
	ASSERT_EQ(std::to_string(data), "01");
	auto data2 = hstoba("02");
	ASSERT_EQ(std::to_string(data2), "02");
	data2 = hstoba("020FFFFA");
	ASSERT_EQ(std::to_string(data2), "020FFFFA");
	//Last digit is cut off due to odd length
	data2 = hstoba("020FFFFA1");
	ASSERT_EQ(std::to_string(data2), "020FFFFA");
	ByteArray data3 = "11"_ba;
	ASSERT_EQ(std::to_string(data3), "11");
	ByteArray data4 = hstoba("22");
	ASSERT_EQ(std::to_string(data4), "22");
}




