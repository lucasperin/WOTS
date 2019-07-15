#pragma once
#include "wots/MConstantSumWots.h"
#include "wots/CachedWots.h"
#include <gmpxx.h>
#include <math.h>
#include <algorithm>

template <class D, int W, int T, int S>
class MCachedConstantSumWots : public MConstantSumWots<D, W, T, S>, public CachedWots<D,W> {
public:
	MCachedConstantSumWots() noexcept {};
	MCachedConstantSumWots(const ByteArray& seed) noexcept : MConstantSumWots<D,W,T,S>(W,seed) {};
};

