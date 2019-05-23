#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/CachedWots.h"
#include "wots/RunLengthOTS.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


/* SIGNATURE AND VERIFICATION */
template<class OTS>
class OTSFixture : public benchmark::Fixture {
public:
	ByteArray data;
	std::vector<ByteArray> signature;
	OTS* ots;
	ByteArray fp;
	virtual void SetUp(benchmark::State& state) {
		int W = state.range(0);
		if(W)
			ots = new OTS(W);
		else
			ots = new OTS();
		data = ByteArray::fromString("My document");
		ots->loadKeys();
		signature = ots->sign(this->data);
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
	virtual void TearDown(benchmark::State& state) {
		delete ots;
	}
};

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
		data = ByteArray::fromString("My document");
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

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, SIGNATURE_256, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	for (auto _ : state){
		this->ots->sign(this->data);
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, CSIGNATURE_256_256, CachedWots<OpenSSLSha256,256>)(benchmark::State& state) {
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

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture2, RunLengthOTS_Encode, RunLengthOTS<OpenSSLSha256>)(benchmark::State& state) {
	std::pair<std::vector<unsigned int>, unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = this->ots->encodeRunLength(fp));
	}
}

BENCHMARK_TEMPLATE_DEFINE_F(OTSFixture, OTS_BaseW, ClassicWots<OpenSSLSha256>)(benchmark::State& state) {
	std::vector<unsigned int> a;
	for (auto _ : state){
		benchmark::DoNotOptimize(a = fp.toBaseW(state.range(0)));
	}
}

BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PRIVATE_GEN_KEY_256)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, PUBLIC_GEN_KEY_256)->Arg(256)->Unit(benchmark::kMicrosecond);

BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, SIGNATURE_256)->Arg(256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, CSIGNATURE_256_256)->Arg(0)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_256)->Arg(4)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_256)->Arg(16)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture, VERIFICATION_256)->Arg(256)->Unit(benchmark::kMicrosecond);

/*
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
*/

BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_PRIVATE_GEN_KEY_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_PUBLIC_GEN_KEY_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_SIGNATURE_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_VERIFICATION_256)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_SIGNATURE_256_R)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_VERIFICATION_256_R)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(OTSFixture2, RunLengthOTS_Encode);
BENCHMARK_REGISTER_F(OTSFixture, OTS_BaseW)->Arg(4);
BENCHMARK_REGISTER_F(OTSFixture, OTS_BaseW)->Arg(16);
BENCHMARK_REGISTER_F(OTSFixture, OTS_BaseW)->Arg(256);



BENCHMARK_MAIN();
