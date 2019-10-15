#include <math.h>
#include <gmpxx.h>
#include <benchmark/benchmark.h>
#include <iostream>
#include "primitives/OpenSSLSha256.h"

class BinFixture : public benchmark::Fixture, protected OpenSSLSha256{
public:
	ByteArray data;
	mpz_class I;
	void SetUp(const ::benchmark::State& state) {
		this->data = hstoba("0102030F");
		this->data = digest(data);
	}
};

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
	std::vector<unsigned int> ret = {max - k};
	i -= left;
	std::vector<unsigned int> ret2 = toConstantSum(i, blocks - 1, max, sum-k);
	ret.insert(ret.end(), ret2.begin(), ret2.end());
	return ret;
}

BENCHMARK_DEFINE_F(BinFixture, BinomialEncoding_Original)(benchmark::State& st) {
	int t = st.range(0);
	int n = st.range(1);
	int s = st.range(2);
	std::vector<unsigned int> ret;
	for (auto _ : st) {
		data = digest(data);
		I.set_str(std::to_string(data), 16);
		benchmark::DoNotOptimize(ret = toConstantSumOriginal(I,t,n,s));
		benchmark::ClobberMemory();
	}
}

BENCHMARK_DEFINE_F(BinFixture, BinomialEncoding_General)(benchmark::State& st) {
	int t = st.range(0);
	int n = st.range(1);
	int s = st.range(2);
	std::vector<unsigned int> ret;
	for (auto _ : st) {
		data = digest(data);
		I.set_str(std::to_string(data), 16);
		benchmark::DoNotOptimize(ret = toConstantSum(I,t,n,s));
		benchmark::ClobberMemory();
	}
}

BENCHMARK_DEFINE_F(BinFixture, BinomialEncoding_Inverted)(benchmark::State& st) {
	int t = st.range(0);
	int n = st.range(1);
	int s = st.range(2);
	std::vector<unsigned int> ret;
	for (auto _ : st) {
		data = digest(data);
		I.set_str(std::to_string(data), 16);
		benchmark::DoNotOptimize(ret = toConstantSumInverted(I,t,n,s));
		benchmark::ClobberMemory();
	}
}


BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_Original)->Args({56,510,510});
BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_Inverted)->Args({56,510,510});
BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_General)->Args({56,510,510});

BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_Original)->Args({70,313,313});
BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_Inverted)->Args({70,313,313});
BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_General)->Args( {70,313,313});

BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_Original)->Args({84,228,228});
BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_Inverted)->Args({84,228,228});
BENCHMARK_REGISTER_F(BinFixture, BinomialEncoding_General)->Args( {84,228,228});

BENCHMARK_MAIN();
