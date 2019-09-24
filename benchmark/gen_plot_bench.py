from math import factorial as fac, sqrt, floor, log
from functools import reduce, lru_cache
from multiprocessing import Pool
from itertools import product, chain
from random import getrandbits
from scipy.special import comb


myfile = "src/Plot_Encoding_bench.cpp"
header = """
#include <benchmark/benchmark.h>
#include "wots/ClassicWots.h"
#include "wots/ConstantSumWots.h"
#include "wots/MConstantSumWots.h"
#include "wots/BSConstantSumWots.h"
#include "primitives/OpenSSLSha256.h"
#include "primitives/OpenSSLSha512.h"


template<class OTS>
class OTSFixture : public benchmark::Fixture, protected OpenSSLSha256 {
public:
	ByteArray data;
	OTS ots;
	virtual void SetUp(benchmark::State& state) {
		data = hstoba("0102030F");
	}
};
"""

template = """
BENCHMARK_TEMPLATE_F(OTSFixture, plot_{},ConstantSumWots<{}, {}, {}, {}>)(benchmark::State& state) {{ 
	std::vector<unsigned int> a;
	for (auto _ : state){{
		data = digest(data);
		benchmark::DoNotOptimize(a = ots.genFingerprint(data));
	}}
}}

"""

tail = 'BENCHMARK_MAIN();'

@lru_cache(maxsize=2**30)
def binomial(n, k):
    return comb(n, k, exact=True)


def T_len(blocks, maxi, block_sum=None):
    if block_sum is None:
        block_sum = maxi

    kmax = min(blocks, floor(block_sum / (maxi + 1)))
    t = 0

    for k in range(kmax + 1):
        t += (
            (-1) ** k
            * binomial(blocks, k)
            * binomial(block_sum - (maxi + 1) * k + blocks - 1, blocks - 1)
        )

    return t

def wrap2(t, n):
    res = []
    for s in range(n, 4000):
        tlen = T_len(t, n, s)
        if tlen < 1:
            break
        elif 257 > log(tlen, 2) > 256:
            res.append((t, n, s, t * n, log(tlen, 2)))
    return res



def method3(to_write, h="OpenSSLSha256"):
    tn = product(range(16, 256), [(1 << w) - 1 for w in range(2, 10)])
    with Pool(processes=4) as pool:
        results = pool.starmap(wrap2, tn)
        for t, n, s, tsn, tlog in chain.from_iterable(results):
            to_write += template.format(str(t)+str(n)+str(s), h, n, t, s)
            #print("{:3d} {:4d} {:6d} {:6d} {:.10f}".format(t, n, s, tsn, tlog))
            #print(map_to_const_sum(getrandbits(256), t, n, s))
    return to_write



if __name__ == "__main__":

    h = 'OpenSSLSha256'


    to_write = header
    to_write = method3(to_write, h)
    to_write += tail
    print(to_write)














