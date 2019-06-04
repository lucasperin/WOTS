#ifndef CONSTANTSUM_WOTS
#define CONSTANTSUM_WOTS
#include "wots/ConstantSumWots.h"
#include "wots/CachedWots.h"
#include <gmpxx.h>
#include <math.h>
#include <algorithm>

template <class D, int W, int T, int S>
class CachedConstantSumWots : public ConstantSumWots<D,W, T, S>, public CachedWots<D,W> {
public:
	CachedConstantSumWots() noexcept {};
	CachedConstantSumWots(const ByteArray& seed) noexcept : ConstantSumWots<D,W>(W,seed) {};
};

#endif
