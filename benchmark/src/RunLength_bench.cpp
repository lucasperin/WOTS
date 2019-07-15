#include <benchmark/benchmark.h>
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


template<class OTS>
class OTSFixture2 : public benchmark::Fixture {
public:
	ByteArray data;
	std::vector<ByteArray> signature;
	std::vector<ByteArray> signature2;
	OTS* ots;
	ByteArray fp;
	int R;
	virtual void SetUp(benchmark::State& state) {
		ots = new OTS();
		data = hstoba("0102030F");
		ots->loadKeys();
		signature = ots->sign(this->data);
		signature = ots->sign2(this->data).first;
		R = ots->sign2(this->data).second;
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
	virtual void TearDown(benchmark::State& state) {
		delete ots;
	}
};

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_SIGNATURE_256, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->sign(this->data);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_VERIFICATION_256, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->verify(this->data, this->signature);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_SIGNATURE_256_R, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->sign2(this->data);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_VERIFICATION_256_R, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->verify(this->data, this->signature, this->R);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_GEN_KEY_256, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearKeys();
		this->ots->loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_PRIVATE_GEN_KEY_256, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearPrivateKey();
		this->ots->loadPrivateKey();
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_PUBLIC_GEN_KEY_256, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->clearPublicKey();
		this->ots->loadPublicKey();
	}
}

BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_PRIVATE_GEN_KEY_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_PUBLIC_GEN_KEY_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_SIGNATURE_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_VERIFICATION_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_SIGNATURE_256_R)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_VERIFICATION_256_R)->Unit(benchmark::kMicrosecond);


BENCHMARK_MAIN();
