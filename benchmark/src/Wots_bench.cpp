#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


/* SIGNATURE AND VERIFICATION */
template<class OTS>
class OTSFixture : public benchmark::Fixture {
public:
	ByteArray data;
	std::vector<ByteArray> signature;
	OTS* ots;
	virtual void SetUp(benchmark::State& state) {
		ots = new OTS(state.range(0));
		data = ByteArray::fromString("My document");
		ots->loadKeys();
		signature = ots->sign(this->data);
	}
	virtual void TearDown(benchmark::State& state) {
		delete ots;
	}
};

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, SIGNATURE_256, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->sign(this->data);
	}
}
BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, SIGNATURE_512, ClassicWots<OpenSSLSha512>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->sign(this->data);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, VERIFICATION_256, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->verify(this->data, this->signature);
	}
}
BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, VERIFICATION_512, ClassicWots<OpenSSLSha512>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, GEN_KEY_256, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearKeys();
		this->ots->loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, GEN_KEY_512, ClassicWots<OpenSSLSha512>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearKeys();
		this->ots->loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, PRIVATE_GEN_KEY_256, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearPrivateKey();
		this->ots->loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, PRIVATE_GEN_KEY_512, ClassicWots<OpenSSLSha512>)(benchmark::State& state) {
	for (auto _ : state){
			this->ots->clearPrivateKey();
		this->ots->loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, PUBLIC_GEN_KEY_256, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearPublicKey();
		this->ots->loadPublicKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, PUBLIC_GEN_KEY_512, ClassicWots<OpenSSLSha512>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearPublicKey();
		this->ots->loadPublicKey();
	}
}
/* Register test function order */


BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_256)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_256)->Arg(256)->Unit(benchmark::kMicrosecond);

BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_256)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_256)->Arg(256)->Unit(benchmark::kMicrosecond);

BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_512)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_512)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_512)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_512)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_512)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_512)->Arg(256)->Unit(benchmark::kMicrosecond);

BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_512)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_512)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_512)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_512)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_512)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_512)->Arg(256)->Unit(benchmark::kMicrosecond);




BENCHMARK_MAIN();
