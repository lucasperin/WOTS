#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/CachedWots.h"
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
		data = hstoba("0102030f");
		ots.loadKeys();
		signature = ots.sign(this->data);
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
};

// Key Generation benchmark

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_256_4, ClassicWots<OpenSSLSha256, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_256_16, ClassicWots<OpenSSLSha256, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_256_256, ClassicWots<OpenSSLSha256, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_512_4, ClassicWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_512_16, ClassicWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_KEY_512_256, ClassicWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearKeys();
		this->ots.loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_256_4, ClassicWots<OpenSSLSha256, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_256_16, ClassicWots<OpenSSLSha256, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_256_256, ClassicWots<OpenSSLSha256, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_512_4, ClassicWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_512_16, ClassicWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, PUBLIC_KEY_512_256, ClassicWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.clearPublicKey();
		this->ots.loadPublicKey();
	}
}

// Signature benchmark

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_4, ClassicWots<OpenSSLSha256, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_4_C, CachedWots<OpenSSLSha256, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_16, ClassicWots<OpenSSLSha256, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_16_C, CachedWots<OpenSSLSha256, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256, ClassicWots<OpenSSLSha256, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_256_256_C, CachedWots<OpenSSLSha256, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_4, ClassicWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_4_C, CachedWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_16, ClassicWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_16_C, CachedWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_256, ClassicWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, SIGNATURE_512_256_C, CachedWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.sign(this->data);
	}
}

//Signature Verification Benchmark

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_4, ClassicWots<OpenSSLSha256, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_16, ClassicWots<OpenSSLSha256, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_256_256, ClassicWots<OpenSSLSha256, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

/////
BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_512_4, ClassicWots<OpenSSLSha512, 4>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_512_16, ClassicWots<OpenSSLSha512, 16>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_F(OTSFixture, VERIFICATION_512_256, ClassicWots<OpenSSLSha512, 256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots.verify(this->data, this->signature);
	}
}


BENCHMARK_MAIN();
