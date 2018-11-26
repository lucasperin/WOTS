#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"

/* Benchmarking constructor to obtain performance impact on the following tests. */
template<class T>
static void Constructor(benchmark::State& state) {
	for (auto _ : state){
		T wots(state.range(0));
		benchmark::DoNotOptimize(wots);
		benchmark::ClobberMemory();
	}
}

/* GENERATE PRIVATE KEY */
template<class T>
static void PRIVATE_KEY_gen(benchmark::State& state) {
	for (auto _ : state){
		T wots(state.range(0));
		wots.loadPrivateKey();
	}
}

/* GENERATE PUBLIC KEY (PRIVETEKEY TIME IS INCLUDED)*/
template<class T>
static void PUBLIC_KEY_gen(benchmark::State& state) {
	for (auto _ : state){
		T wots(state.range(0));
		wots.loadPublicKey();
	}
}

extern ByteArray data = ByteArray::fromString("My document");
//extern WinternitzOTS* global_wots;




/* SIGN SMALL DATA */
template<class T>
static void SIGN_small(benchmark::State& state) {
		T wots(state.range(0));
		wots.loadKeys();
	for (auto _ : state){
//		global_wots = new T(state.range(0));
//		global_wots->loadKeys();
//		global_wots->sign(data);
		wots.sign(data);
	}
}

/* SIGN AND VERIFYSMALL DATA */
template<class T>
static void VERIFY_small(benchmark::State& state) {
		T wots(state.range(0));
		wots.loadKeys();
		std::vector<ByteArray> sig = wots.sign(data);
	for (auto _ : state){
		wots.verify(data, sig);
	}
}


/* Register test function order */

/* 
// Uncomment this block to obtain constructor times
BENCHMARK_TEMPLATE(Constructor, ClassicWots<OpenSSLSha256>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(Constructor, ClassicWots<OpenSSLSha256>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(Constructor, ClassicWots<OpenSSLSha256>)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(Constructor, ClassicWots<OpenSSLSha512>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(Constructor, ClassicWots<OpenSSLSha512>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(Constructor, ClassicWots<OpenSSLSha512>)->Arg(256)->Unit(benchmark::kMicrosecond);
*/


//KEY GEN
BENCHMARK_TEMPLATE(PRIVATE_KEY_gen, ClassicWots<OpenSSLSha256>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(PUBLIC_KEY_gen, ClassicWots<OpenSSLSha256>)->Arg(4)->Unit(benchmark::kMicrosecond);

BENCHMARK_TEMPLATE(PRIVATE_KEY_gen, ClassicWots<OpenSSLSha256>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(PUBLIC_KEY_gen, ClassicWots<OpenSSLSha256>)->Arg(16)->Unit(benchmark::kMicrosecond);

BENCHMARK_TEMPLATE(PRIVATE_KEY_gen, ClassicWots<OpenSSLSha256>)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(PUBLIC_KEY_gen, ClassicWots<OpenSSLSha256>)->Arg(256)->Unit(benchmark::kMicrosecond);

BENCHMARK_TEMPLATE(PRIVATE_KEY_gen, ClassicWots<OpenSSLSha512>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(PUBLIC_KEY_gen, ClassicWots<OpenSSLSha512>)->Arg(4)->Unit(benchmark::kMicrosecond);

BENCHMARK_TEMPLATE(PRIVATE_KEY_gen, ClassicWots<OpenSSLSha512>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(PUBLIC_KEY_gen, ClassicWots<OpenSSLSha512>)->Arg(16)->Unit(benchmark::kMicrosecond);

BENCHMARK_TEMPLATE(PRIVATE_KEY_gen, ClassicWots<OpenSSLSha512>)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(PUBLIC_KEY_gen, ClassicWots<OpenSSLSha512>)->Arg(256)->Unit(benchmark::kMicrosecond);

//SIGN
BENCHMARK_TEMPLATE(SIGN_small, ClassicWots<OpenSSLSha256>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(SIGN_small, ClassicWots<OpenSSLSha256>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(SIGN_small, ClassicWots<OpenSSLSha256>)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(SIGN_small, ClassicWots<OpenSSLSha512>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(SIGN_small, ClassicWots<OpenSSLSha512>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(SIGN_small, ClassicWots<OpenSSLSha512>)->Arg(256)->Unit(benchmark::kMicrosecond);

//VERIFY
BENCHMARK_TEMPLATE(VERIFY_small, ClassicWots<OpenSSLSha256>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(VERIFY_small, ClassicWots<OpenSSLSha256>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(VERIFY_small, ClassicWots<OpenSSLSha256>)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(VERIFY_small, ClassicWots<OpenSSLSha512>)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(VERIFY_small, ClassicWots<OpenSSLSha512>)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(VERIFY_small, ClassicWots<OpenSSLSha512>)->Arg(256)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
