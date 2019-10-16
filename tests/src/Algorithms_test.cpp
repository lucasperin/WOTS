#include "gtest/gtest.h"
#include <primitives/OpenSSLSha256.h>
#include <math.h>
#include <gmpxx.h>
#include <iostream>

static mpz_class binomial(int n, int k) {
	if(n < k || n<0 || k<0)
		return 0;
	mpz_class ret = 0;
	mpz_bin_uiui(ret.get_mpz_t(), n, k);
	return ret;
}

static std::vector<unsigned int> toConstantSumOriginal(mpz_class& i, 
		int blocks, int max, int sum) 
{
	(void)max;
	if (blocks == 1)
		return {(unsigned)sum};
	unsigned int k = 0;
	mpz_class a = 1;
	mpz_class left = 0;
	mpz_class right = a;
	while ( !(i>= left && i < right) ) {
		k++; 
		a = a*(k+blocks-2);
		mpz_divexact_ui(a.get_mpz_t(), a.get_mpz_t(), k);
		left=right;
		right += a;
	}
	std::vector<unsigned int> ret = {sum-k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSumOriginal(i, blocks - 1, max, k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}

static std::vector<unsigned int> toConstantSumOriginalBin(mpz_class& i, 
		int blocks, int max, int sum) 
{
	(void)max;
	if (blocks == 1)
		return {(unsigned)sum};
	unsigned int k = 0;
	mpz_class left = 0;
	mpz_class right = 1;
	while ( !(i>= left && i < right) ) {
		k++; 
		left=right;
		right += binomial(k+blocks-2,k);
	}
	std::vector<unsigned int> ret = {sum-k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSumOriginalBin(i, blocks - 1, max, k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}

static std::vector<unsigned int> toConstantSumOriginalInverted(mpz_class& i, 
		int blocks, int max, int sum) 
{
	(void)max;
	if (blocks == 1)
		return {(unsigned)sum};
	unsigned int k = 0;
	mpz_class left = 0;
	mpz_class right = binomial(sum+blocks-2,sum);
	while ( !(i>= left && i < right) ) {
		k++; 
		left=right;
		right += binomial(sum+blocks-2-k,sum-k);
	}
	std::vector<unsigned int> ret = {k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSumOriginalInverted(i, blocks - 1, max, sum-k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}

static std::vector<unsigned int> toConstantSumOriginalInvertedOpt(mpz_class& i, 
		int blocks, int max, int sum) 
{
	(void)max;
	if (blocks == 1)
		return {(unsigned)sum};
	unsigned int k = 0;
	mpz_class left = 0;
	mpz_class right = binomial(sum+blocks-2,sum);
	mpz_class a = right;
	while ( !(i>= left && i < right) ) {
		k++; 
		left=right;
		a = a*(sum-k+1);
		mpz_divexact_ui(a.get_mpz_t(), a.get_mpz_t(), (sum-k+1)+blocks-2);
		right += a;
	}
	std::vector<unsigned int> ret = {k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSumOriginalInvertedOpt(i, blocks - 1, max, sum-k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}


static mpz_class constantSumLen(int blocks, int max, int sum) {
	//TODO
	//Assert ret >= 0
	mpz_class ret = 0;
	int aux = std::floor((float)sum/(float)(max+1));
	int kmax = std::min(blocks, aux);
	for(int k = 0; k <= kmax; k++ ) {
		ret += binomial(blocks, k) * binomial(sum - (max+1)*k + blocks -1, blocks - 1) * ((k%2 == 0)?1:-1);
	}
	return ret;
}

static std::vector<unsigned int> toConstantSum(mpz_class& i, 
		int blocks, int max, int sum) 
{
	if (blocks == 1)
		return {(unsigned int)sum};
	unsigned int k = 0;
	mpz_class left = 0;
	mpz_class right = constantSumLen(blocks - 1, max, sum);
	while ( !(i>= left && i < right) ) {
		k++; 
		left=right;
		right += constantSumLen(blocks - 1, max, sum-k);
	}
	std::vector<unsigned int> ret = {k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSum(i, blocks - 1, max, sum-k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}

static std::vector<unsigned int> toConstantSumInverted(mpz_class& i, 
		int blocks, int max, int sum) 
{
	if (blocks == 1)
		return {(unsigned int)sum};
	unsigned int k = std::min(sum, max);
	mpz_class left = 0;
	mpz_class right = constantSumLen(blocks - 1, max, sum-k);
	while ( !(i>= left && i < right) ) {
		k--; 
		left=right;
		right += constantSumLen(blocks - 1, max, sum-k);
	}
	std::vector<unsigned int> ret = {k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSumInverted(i, blocks - 1, max, sum-k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}


TEST(AlgorithmsTest, BinomialEncoding_Original) {
	OpenSSLSha256 md;
	ByteArray data;
	mpz_class I;
	data = hstoba("12345678AAFF");
	data = md.digest(data);
	I.set_str(std::to_string(data), 16);
	std::vector<unsigned int> ret = toConstantSumOriginal(I,56,510,510);
	for(auto e : ret)
		std::cout << e << " ";
	std::cout << std::endl << ret.size() << std::endl<< std::flush;
}

TEST(AlgorithmsTest, BinomialEncoding_OriginalBin){
	OpenSSLSha256 md;
	ByteArray data;
	mpz_class I;
	data = hstoba("12345678AAFF");
	data = md.digest(data);
	I.set_str(std::to_string(data), 16);
	std::vector<unsigned int> ret = toConstantSumOriginalBin(I,56,510,510);
	for(auto e : ret)
		std::cout << e << " ";
	std::cout << std::endl << ret.size() << std::endl<< std::flush;
}

TEST(AlgorithmsTest, BinomialEncoding_Inverted){
	OpenSSLSha256 md;
	ByteArray data;
	mpz_class I;
	data = hstoba("12345678AAFF");
	data = md.digest(data);
	I.set_str(std::to_string(data), 16);
	std::vector<unsigned int> ret = toConstantSumInverted(I,56,510,510);
	for(auto e : ret)
		std::cout << e << " ";
	std::cout << std::endl << ret.size() << std::endl<< std::flush;
}

TEST(AlgorithmsTest, BinomialEncoding_OriginalInverted){
	OpenSSLSha256 md;
	ByteArray data;
	mpz_class I;
	data = hstoba("12345678AAFF");
	data = md.digest(data);
	I.set_str(std::to_string(data), 16);
	std::vector<unsigned int> ret = toConstantSumOriginalInverted(I,56,510,510);
	for(auto e : ret)
		std::cout << e << " ";
	std::cout << std::endl << ret.size() << std::endl<< std::flush;
}

TEST(AlgorithmsTest, BinomialEncoding_OriginalInvertedOpt){
	OpenSSLSha256 md;
	ByteArray data;
	mpz_class I;
	data = hstoba("12345678AAFF");
	data = md.digest(data);
	I.set_str(std::to_string(data), 16);
	std::vector<unsigned int> ret = toConstantSumOriginalInvertedOpt(I,56,510,510);
	for(auto e : ret)
		std::cout << e << " ";
	std::cout << std::endl << ret.size() << std::endl<< std::flush;
}

TEST(AlgorithmsTest, BinomialEncoding_General){
	OpenSSLSha256 md;
	ByteArray data;
	mpz_class I;
	data = hstoba("12345678AAFF");
	data = md.digest(data);
	I.set_str(std::to_string(data), 16);
	std::vector<unsigned int> ret = toConstantSum(I,56,510,510);
	for(auto e : ret)
		std::cout << e << " ";
	std::cout << std::endl << ret.size() << std::endl<< std::flush;
}


