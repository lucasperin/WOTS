#include <benchmark/benchmark.h>
#include "wots/ConstantSumWots.h"
#include "wots/MConstantSumWots.h"
#include "wots/CachedConstantSumWots.h"
#include "wots/MCachedConstantSumWots.h"
#include "wots/BSConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


/* SIGNATURE AND VERIFICATION */
template<class OTS>
class OTSFixture : public benchmark::Fixture, protected OpenSSLSha256 {
public:
	ByteArray data;
	std::vector<ByteArray> signature;
	OTS ots;
	ByteArray fp;
	virtual void SetUp(benchmark::State& state) {
		data = hstoba("F0102030F");
		ots.loadKeys();
		signature = ots.sign(this->data);
		OpenSSLSha256 md;
		fp = md.digest(data);
	}
};


//t=34
using CS_2832_34_2832   = ConstantSumWots<OpenSSLSha256,2832,34,2832>;
using CS_255_34_3106    = ConstantSumWots<OpenSSLSha256,255,34,3106>;
using CS_255_34_3106_C  = CachedConstantSumWots<OpenSSLSha256,255,34,3106>;
using CS_255_34_3106_M  = MConstantSumWots<OpenSSLSha256,255,34,3106>;
using CS_255_34_3106_MC = MCachedConstantSumWots<OpenSSLSha256,255,34,3106>;
using CS_255_34_3106_BS = BSConstantSumWots<OpenSSLSha256,255,34,3106>;

//t=55
using CS_534_55_534    = ConstantSumWots<OpenSSLSha256,534,55,534>;
using CS_255_55_534    = ConstantSumWots<OpenSSLSha256,255,55,534>;
using CS_255_55_534_C  = CachedConstantSumWots<OpenSSLSha256,255,55,534>;
using CS_255_55_534_M  = MConstantSumWots<OpenSSLSha256,255,55,534>;
using CS_255_55_534_MC = MCachedConstantSumWots<OpenSSLSha256,255,55,534>;
using CS_255_55_534_BS = BSConstantSumWots<OpenSSLSha256,255,55,534>;

using CS_31_55_581    = ConstantSumWots<OpenSSLSha256,31,55,581>;
using CS_31_55_581_C  = CachedConstantSumWots<OpenSSLSha256,31,55,581>;
using CS_31_55_581_M  = MConstantSumWots<OpenSSLSha256,31,55,581>;
using CS_31_55_581_MC = MCachedConstantSumWots<OpenSSLSha256,31,55,581>;
using CS_31_55_581_BS = BSConstantSumWots<OpenSSLSha256,31,55,581>;

//t=66
using CS_352_66_352    = ConstantSumWots<OpenSSLSha256,352,66,352>;
using CS_15_66_442    = ConstantSumWots<OpenSSLSha256,15,66,442>;
using CS_15_66_442_C  = CachedConstantSumWots<OpenSSLSha256,15,66,442>;
using CS_15_66_442_M  = MConstantSumWots<OpenSSLSha256,15,66,442>;
using CS_15_66_442_MC = MCachedConstantSumWots<OpenSSLSha256,15,66,442>;
using CS_15_66_442_BS = BSConstantSumWots<OpenSSLSha256,15,66,442>;

//t=80

using CS_247_80_247 = ConstantSumWots<OpenSSLSha256, 247, 80, 247>;
using CS_15_80_251 = ConstantSumWots<OpenSSLSha256, 15, 80, 251>;
using CS_15_80_251_C  = CachedConstantSumWots<OpenSSLSha256,15,80,251>;
using CS_15_80_251_M  = MConstantSumWots<OpenSSLSha256,15,80,251>;
using CS_15_80_251_MC = MCachedConstantSumWots<OpenSSLSha256,15,80,251>;
using CS_15_80_251_BS = BSConstantSumWots<OpenSSLSha256,15,80,251>;



//Private Key Generation Benchmark
//t=34
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_2832_34_2832, CS_2832_34_2832)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_255_34_3106, CS_255_34_3106)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_255_34_3106_C, CS_255_34_3106_C)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};

//t=55
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_534_55_534, CS_534_55_534)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_255_55_534, CS_255_55_534)(benchmark::State& state)
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_255_55_534_C, CS_255_55_534_C)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};

BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_31_55_581, CS_31_55_581)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_31_55_581_C, CS_31_55_581_C)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};

//t=66
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_352_66_352, CS_352_66_352)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_15_66_442, CS_15_66_442)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_15_66_442_C, CS_15_66_442_C)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};

//t=80
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_247_80_247, CS_247_80_247)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_15_80_251, CS_15_80_251)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PRIV_GEN_15_80_251_C, CS_15_80_251_C)(benchmark::State& state) 
	{for (auto _ : state){ this->ots.clearKeys(); this->ots.loadPrivateKey();}};



//Public Key Generation Benchmark
//t=34
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_2832_34_2832, CS_2832_34_2832)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_255_34_3106, CS_255_34_3106)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_255_34_3106_C, CS_255_34_3106_C)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};

//t=55
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_534_55_534, CS_534_55_534)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_255_55_534, CS_255_55_534)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_255_55_534_C, CS_255_55_534_C)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};

BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_31_55_581, CS_31_55_581)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_31_55_581_C, CS_31_55_581_C)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};

//t=66
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_352_66_352, CS_352_66_352)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_15_66_442, CS_15_66_442)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_15_66_442_C, CS_15_66_442_C)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};

//t=80
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_247_80_247, CS_247_80_247)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_15_80_251, CS_15_80_251)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};
BENCHMARK_TEMPLATE_F(OTSFixture, PUB_GEN_15_80_251_C, CS_15_80_251_C)(benchmark::State& state) 
	{for (auto _ : state){this->ots.clearPublicKey(); this->ots.loadPublicKey();}};


//Signature Generation Benchmark

//t=34
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_2832_34_2832,   CS_2832_34_2832  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_34_3106,    CS_255_34_3106   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_34_3106_C,  CS_255_34_3106_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_34_3106_M,  CS_255_34_3106_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_34_3106_MC, CS_255_34_3106_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_34_3106_BS, CS_255_34_3106_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};

//t=55
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_534_55_534,    CS_534_55_534   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_55_534,    CS_255_55_534   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_55_534_C,  CS_255_55_534_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_55_534_M,  CS_255_55_534_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_55_534_MC, CS_255_55_534_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_255_55_534_BS, CS_255_55_534_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};

BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_31_55_581,    CS_31_55_581     )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_31_55_581_C,  CS_31_55_581_C   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_31_55_581_M,  CS_31_55_581_M   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_31_55_581_MC, CS_31_55_581_MC  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_31_55_581_BS, CS_31_55_581_BS  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};

//t=66
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_352_66_352,   CS_352_66_352  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_66_442,    CS_15_66_442   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_66_442_C,  CS_15_66_442_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_66_442_M,  CS_15_66_442_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_66_442_MC, CS_15_66_442_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_66_442_BS, CS_15_66_442_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};

//t=80
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_247_80_247,   CS_247_80_247  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_80_251,    CS_15_80_251   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_80_251_C,  CS_15_80_251_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_80_251_M,  CS_15_80_251_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_80_251_MC, CS_15_80_251_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_GEN_15_80_251_BS, CS_15_80_251_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.sign(this->data);}};



//Signature Verification Benchmark

//t=34
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_2832_34_2832,   CS_2832_34_2832  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_34_3106,    CS_255_34_3106   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_34_3106_C,  CS_255_34_3106_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_34_3106_M,  CS_255_34_3106_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_34_3106_MC, CS_255_34_3106_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_34_3106_BS, CS_255_34_3106_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};

//t=55
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_534_55_534,    CS_534_55_534   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_55_534,    CS_255_55_534   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_55_534_C,  CS_255_55_534_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_55_534_M,  CS_255_55_534_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_55_534_MC, CS_255_55_534_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_255_55_534_BS, CS_255_55_534_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};

BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_31_55_581,    CS_31_55_581     )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_31_55_581_C,  CS_31_55_581_C   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_31_55_581_M,  CS_31_55_581_M   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_31_55_581_MC, CS_31_55_581_MC  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_31_55_581_BS, CS_31_55_581_BS  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};

//t=66
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_352_66_352,   CS_352_66_352  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_66_442,    CS_15_66_442   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_66_442_C,  CS_15_66_442_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_66_442_M,  CS_15_66_442_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_66_442_MC, CS_15_66_442_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_66_442_BS, CS_15_66_442_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};

//t=80
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_247_80_247,   CS_247_80_247  )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_80_251,    CS_15_80_251   )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_80_251_C,  CS_15_80_251_C )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_80_251_M,  CS_15_80_251_M )(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_80_251_MC, CS_15_80_251_MC)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};
BENCHMARK_TEMPLATE_F(OTSFixture, SIG_VER_15_80_251_BS, CS_15_80_251_BS)(benchmark::State& state) 
	{for (auto _ : state){data=digest(data); this->ots.verify(this->data, this->signature);}};

BENCHMARK_MAIN();
