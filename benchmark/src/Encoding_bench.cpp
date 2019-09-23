#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/ConstantSumWots.h"
#include "wots/MConstantSumWots.h"
#include "wots/BSConstantSumWots.h"
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"

using OCS_34 = ConstantSumWots<OpenSSLSha256,2832,34,2832>;
using OCS_55 = ConstantSumWots<OpenSSLSha256,534,55,534>;
using CS_34 = ConstantSumWots<OpenSSLSha256,255,34,3106>;
using CS_55 = ConstantSumWots<OpenSSLSha256,255,55,534>;
using MCS_34 = MConstantSumWots<OpenSSLSha256,255,34,3106>;
using MCS_55 = MConstantSumWots<OpenSSLSha256,255,55,534>;
using BSCS_34 = BSConstantSumWots<OpenSSLSha256,255,34,3106>;
using BSCS_55 = BSConstantSumWots<OpenSSLSha256,255,55,534>;

template<class OTS>
class OTSFixture : public benchmark::Fixture, protected OpenSSLSha256 {
public:
	ByteArray data;
	OTS ots;
	virtual void SetUp(benchmark::State& state) {
		data = hstoba("0102030F");
	}
};

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

//ORIGINAL CONSTANT SUM ENCODING


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_34_2832, OCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_55_534, OCS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}



// CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_34_3106, CS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_55_534, CS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


//MEMOIZED CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_34_3106_M, MCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_55_534_M, MCS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


//Memoized Binary Search CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_34_3106_BS, BSCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_55_534_BS, BSCS_55)(benchmark::State& state) {
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
