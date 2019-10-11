#include <math.h>
#include <gmpxx.h>
#include <benchmark/benchmark.h>
#include <iostream>


static mpz_class binomial(int n, int k) {
		mpz_class ret = 0;
		mpz_bin_uiui(ret.get_mpz_t(), n, k);
		return ret;
}

static void common_binomial(benchmark::State& state) {
	
	int n = state.range(0);
	int k = state.range(1);

	for ( auto _ : state ) {
		mpz_class ret;
		for (int i =0; i <=k; i++){
			benchmark::DoNotOptimize( ret = binomial(n,i) );
		}
		benchmark::ClobberMemory();
	}
}

static void fast_binomial(benchmark::State& state) {
	
	int n = state.range(0);
	int k = state.range(1);

	for ( auto _ : state ) {
		mpz_class ret = 1;
		for (int i =0; i <=k; i++) {
			ret *= (n-i+1);
			mpz_divexact_ui(ret.get_mpz_t(), ret.get_mpz_t(), n);
		}
		benchmark::ClobberMemory();
	}
}

static void fast_binomial2(benchmark::State& state) {
	
	float n = state.range(0);
	float k = state.range(1);

	for ( auto _ : state ) {
		unsigned long long ret = 1;
		for (int i =0; i <=k; i++) {
			ret *= (n-i+1);
			ret /= n;
		}
		benchmark::ClobberMemory();
	}
}

BENCHMARK(common_binomial)->Ranges({{40,60},{3,6}});
BENCHMARK(fast_binomial)->Ranges({{40,60},{3,6}});
BENCHMARK(fast_binomial2)->Ranges({{40,60},{3,6}});
BENCHMARK_MAIN();
