#include <benchmark/benchmark.h>
#include "wots/ConstantSumWots.h"
#include "wots/MConstantSumWots.h"
#include "wots/CachedConstantSumWots.h"
#include "wots/MCachedConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


/* SIGNATURE AND VERIFICATION */
template<class OTS>
class OTSFixture : public benchmark::Fixture {
public:
	ByteArray data;
	std::vector<ByteArray> signature;
	OTS ots;
	ByteArray fp;
	virtual void SetUp(benchmark::State& state) {
		data = hstoba("0102030F");
		ots.loadKeys();
		signature = ots.sign(this->data);
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
};

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_256_4, ConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_256_16, ConstantSumWots<OpenSSLSha256, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_256_256, ConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

/*
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_512_4, ConstantSumWots<OpenSSLSha512, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_512_16, ConstantSumWots<OpenSSLSha512, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_512_256, ConstantSumWots<OpenSSLSha512, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}
*/

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_256_4, ConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_256_16, ConstantSumWots<OpenSSLSha256, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_256_256, ConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

/*
BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_512_4, ConstantSumWots<OpenSSLSha512, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_512_16, ConstantSumWots<OpenSSLSha512, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_512_256, ConstantSumWots<OpenSSLSha512, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}
*/

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_4, ConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_4_M, MConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_4_C, CachedConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}


BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_4_C_M, MCachedConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_16, ConstantSumWots<OpenSSLSha256, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_16_C, CachedConstantSumWots<OpenSSLSha256, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_2k, ConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_2k_M, MConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_2k_C, CachedConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_C_2k_M, MCachedConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}


BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_1k, ConstantSumWots<OpenSSLSha256, 256, 43, 1108>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_1k_M, MConstantSumWots<OpenSSLSha256, 256, 43, 1108>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_1k_C, CachedConstantSumWots<OpenSSLSha256, 256, 43, 1108>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_C_1k_M, MCachedConstantSumWots<OpenSSLSha256, 256, 43, 1108>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

/*
BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_4, ConstantSumWots<OpenSSLSha512, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_4_C, CachedWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_16, ConstantSumWots<OpenSSLSha512, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_16_C, CachedWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_256, ConstantSumWots<OpenSSLSha512, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_256_C, CachedWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}
*/

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_4, ConstantSumWots<OpenSSLSha256, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_16, ConstantSumWots<OpenSSLSha256, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_256_2k, ConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_256_2k_M, MConstantSumWots<OpenSSLSha256, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_256_1k, ConstantSumWots<OpenSSLSha256, 256, 43, 1108>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_256_1k_M, MConstantSumWots<OpenSSLSha256, 256, 43, 1108>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

/*
BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_512_4, ConstantSumWots<OpenSSLSha512, 4, 140, 143>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_512_16, ConstantSumWots<OpenSSLSha512, 16, 80, 251>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_512_256, ConstantSumWots<OpenSSLSha512, 256, 37, 1972>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}
*/


BENCHMARK_MAIN();
