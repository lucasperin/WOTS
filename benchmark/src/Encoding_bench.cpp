#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/CachedWots.h"
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


template<class OTS>
class ClassicWotsFixture : public benchmark::Fixture {
public:
	ByteArray data;
	OTS* ots;
	ByteArray fp;
	virtual void SetUp(benchmark::State& state) {
		int W = state.range(0);
		if(W)
			ots = new OTS(W);
		else
			ots = new OTS();
		data = ByteArray::fromString("My document");
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
	virtual void TearDown(benchmark::State& state) {
		delete ots;
	}
};

BENCHMARK_TEMPLATE_DEFINE_F(ClassicWotsFixture, OTS_BaseW, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = fp.toBaseW(ots->w()));
	}
}
BENCHMARK_REGISTER_F(ClassicWotsFixture, OTS_BaseW)->Arg(4);
BENCHMARK_REGISTER_F(ClassicWotsFixture, OTS_BaseW)->Arg(16);
BENCHMARK_REGISTER_F(ClassicWotsFixture, OTS_BaseW)->Arg(256);

template<class OTS>
class RunLenWotsFixture : public benchmark::Fixture {
public:
	ByteArray data;
	OTS* ots;
	ByteArray fp;
	virtual void SetUp(benchmark::State& state) {
		data = ByteArray::fromString("My document");
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
	virtual void TearDown(benchmark::State& state) {
		delete ots;
	}
};

BENCHMARK_TEMPLATE_DEFINE_F(RunLenWotsFixture, RunLengthOTS_Encode, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	std::pair<std::vector<unsigned int>, unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = this->ots->encodeRunLength(fp));
	}
}



BENCHMARK_REGISTER_F(RunLenWotsFixture, RunLengthOTS_Encode);

BENCHMARK_MAIN();
