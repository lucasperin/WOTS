#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/ConstantSumWots.h"
#include "wots/OriginalConstantSumWots.h"
#include "wots/VariantConstantSumWots.h"
#include "wots/MConstantSumWots.h"
#include "wots/BSConstantSumWots.h"
#include "wots/OBSConstantSumWots.h"
#include "wots/DynamicCacheConstantSumWots.h"
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"

using OCS_34  = OriginalConstantSumWots<OpenSSLSha256,2832,34,2832>;
using OCS_55  = OriginalConstantSumWots<OpenSSLSha256,534,55,534>;
using VCS_34   = VariantConstantSumWots<OpenSSLSha256,300,34,3106>;
using VCS_55   = VariantConstantSumWots<OpenSSLSha256,255,55,534>;
using VCS_55_63= VariantConstantSumWots<OpenSSLSha256,63,55,534>;
using VCS_55_31= VariantConstantSumWots<OpenSSLSha256,31,55,534>;


using CS_34   = ConstantSumWots<OpenSSLSha256,255,34,3106>;
using CS_55   = ConstantSumWots<OpenSSLSha256,255,55,534>;
using CS_55_63= ConstantSumWots<OpenSSLSha256,63,55,535>;
using CS_55_31= ConstantSumWots<OpenSSLSha256,31,55,581>;
using MCS_34  = MConstantSumWots<OpenSSLSha256,255,34,3106>;
using MCS_55  = MConstantSumWots<OpenSSLSha256,255,55,534>;
using BSCS_34 = BSConstantSumWots<OpenSSLSha256,255,34,3106>;
using BSCS_55 = BSConstantSumWots<OpenSSLSha256,255,55,534>;
using OBSCS_34= OBSConstantSumWots<OpenSSLSha256,255,34,3106>;
using OBSCS_55= OBSConstantSumWots<OpenSSLSha256,255,55,534>;
using DCCS_34 = DynamicCacheConstantSumWots<OpenSSLSha256,255,34,3106>;
using DCCS_55 = DynamicCacheConstantSumWots<OpenSSLSha256,255,55,534>;


using OCS_66_512   = OriginalConstantSumWots<OpenSSLSha512,6769,66,6769>;
using OCS_131_512  = OriginalConstantSumWots<OpenSSLSha512,845,131,845>;
using CS_66_512    = ConstantSumWots<OpenSSLSha512,255,66,6769>;
using CS_131_512   = ConstantSumWots<OpenSSLSha512,15,131,845>;
using MCS_66_512   = MConstantSumWots<OpenSSLSha512,255,66,6769>;
using MCS_131_512  = MConstantSumWots<OpenSSLSha512,15,131,845>;
using BSCS_66_512  = BSConstantSumWots<OpenSSLSha512,255,66,6769>;
using BSCS_131_512 = BSConstantSumWots<OpenSSLSha512,15,131,845>;


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


// VARIANT ONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_300_34_3106_V, VCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_55_534_V, VCS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_63_55_534_V, VCS_55_63)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_31_55_534_V, VCS_55_31)(benchmark::State& state) {
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

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_61_55_535, CS_55_63)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_31_55_581, CS_55_31)(benchmark::State& state) {
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


//Binary Search CONSTANT SUM ENCODING

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

// Optimized(?)Binary Search CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_34_3106_OBS, OBSCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_55_534_OBS, OBSCS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}



//DYNAMIC CACHE CONSTANT SUM ENCODING

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_34_3106_DC, DCCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_256_255_55_534_DC, DCCS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

//// 512 bits

// ORIGINAL CONSTANT SUM ENCODING 512


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_66_6769, OCS_66_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_131_845, OCS_131_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}


// CONSTANT SUM ENCODING 512


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_255_66_6769, CS_66_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_15_131_845, CS_131_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

//MEMOIZED CONSTANT SUM ENCODING 512


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_255_66_6769_M, MCS_66_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_15_131_845_M, MCS_131_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

//BINARY SEARCH CONSTANT SUM ENCODING 512


BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_255_66_6769_BS, BSCS_66_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, ENCODING_512_15_131_845_BS, BSCS_131_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}
}

//CHECK ENCODING 

template<class OTS>
class OTSFixture2 : public benchmark::Fixture, protected OpenSSLSha256 {
public:
	ByteArray data;
	OTS ots;
	std::vector<unsigned int> fp;
	virtual void SetUp(benchmark::State& state) {
		data = hstoba("0102030F");
		fp = ots.genFingerprint(data);
	}
};

BENCHMARK_TEMPLATE_F(OTSFixture2, CHECK_ENCODING_256_255_34_3106_BS, BSCS_34)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(ots.check_encoding(data, fp));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture2, CHWCK_ENCODING_256_255_55_534_BS, BSCS_55)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(ots.check_encoding(data, fp));
	}
}


BENCHMARK_TEMPLATE_F(OTSFixture2, CHECK_ENCODING_512_255_66_6769_BS, BSCS_66_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(ots.check_encoding(data, fp));
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture2, CHECK_ENCODING_512_15_131_845_BS, BSCS_131_512)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(ots.check_encoding(data, fp));
	}
}

BENCHMARK_MAIN();
