#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/ConstantSumWots.h"
#include "wots/MConstantSumWots.h"
#include "wots/BSConstantSumWots.h"
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


template<class OTS>
class OTSFixture : public benchmark::Fixture, protected OpenSSLSha256 {
public:
	ByteArray data;
	OTS ots;
	virtual void SetUp(benchmark::State& state) {
		data = hstoba("0102030F");
	}
};

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_4, ClassicWots<OpenSSLSha256, 4>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_16, ClassicWots<OpenSSLSha256, 16>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256, ClassicWots<OpenSSLSha256, 256>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_4, ClassicWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_16, ClassicWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_256, ClassicWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

/*
 * Nao sei pq nao funciona.. trava em loop
BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_4_129_193, ConstantSumWots<OpenSSLSha256, 4, 129, 194>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}
*/

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_16_66_495, ConstantSumWots<OpenSSLSha256, 16, 66, 495>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256_35_4462, ConstantSumWots<OpenSSLSha256, 256, 35, 4462>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256_37_1972, ConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


//MEMOIZED CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_16_66_495_M, MConstantSumWots<OpenSSLSha256, 16, 66, 495>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256_35_4462_M, MConstantSumWots<OpenSSLSha256, 256, 35, 4462>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256_37_1972_M, MConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


//Memoized Binary Search CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_16_66_495_BS, BSConstantSumWots<OpenSSLSha256, 16, 66, 495>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256_35_4462_BS, BSConstantSumWots<OpenSSLSha256, 256, 34, 4462>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_256_37_1972_BS, BSConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}
////


/*
BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_4, ConstantSumWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_16, ConstantSumWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_256, ConstantSumWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}
*/

BENCHMARK_MAIN();
