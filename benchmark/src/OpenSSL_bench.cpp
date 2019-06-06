#include <benchmark/benchmark.h>
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"
#include <iostream>

template<class D>
class OpenSSLFixture : public benchmark::Fixture {
public:
	ByteArray data;
	D md;
	int it = 1000;
	virtual void SetUp(benchmark::State& state) {
		int aux = state.range(0);
		if(aux)
			it = aux;
		const std::string test = "test";
		data = ByteArray::fromString(test);
	}
};

BENCHMARK_TEMPLATE_DEFINE_F(OpenSSLFixture, OpenSSLDigestChain, OpenSSLSha256)(benchmark::State& state) {
	ByteArray h;
		const std::string test = "test";
		data = ByteArray::fromString(test);
	for (auto _ : state){
		benchmark::DoNotOptimize
		(
			h = md.digestChain(data, it)
		);
	}
}


BENCHMARK_REGISTER_F(OpenSSLFixture, OpenSSLDigestChain)->Arg(1000)->Unit(benchmark::kMicrosecond);;
BENCHMARK_REGISTER_F(OpenSSLFixture, OpenSSLDigestChain)->Arg(4000)->Unit(benchmark::kMicrosecond);;
BENCHMARK_REGISTER_F(OpenSSLFixture, OpenSSLDigestChain)->Arg(100000)->Unit(benchmark::kMicrosecond);;


BENCHMARK_MAIN();
