#pragma once
#include <unordered_map>
#include <utility>
#include "wots/BSConstantSumWots.h"

template <class D, int W, int T, int S>
class DynamicCacheConstantSumWots : public virtual BSConstantSumWots<D, W, T, S> {
public:
	DynamicCacheConstantSumWots() noexcept {};
	DynamicCacheConstantSumWots(const ByteArray& seed) noexcept : BSConstantSumWots<D,W,T,S>(W,seed) {};
	virtual ~DynamicCacheConstantSumWots() noexcept {
		std::cout << "Cache length = " << this->len << std::endl;
		std::cout << "Cache hits = " << this->hits << std::endl;
	};

protected:

	mpz_class binomial(int n, int k) {
		mpz_class ret = 0;
		if(n < k || n<0 || k<0)
			return ret;

		std::pair<int,int> query(n,k);
		auto f = this->dyn_cache.find(query);
		if(f != this->dyn_cache.end()) {
			this->hits++;
			return f->second;
		}
	
		mpz_bin_uiui(ret.get_mpz_t(), n, k);
		this->dyn_cache[query] = ret;
		this->len++;
		return ret;
	}
	int hits = 0;
	int len = 0;

	struct pair_hash {
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2> &pair) const {
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};

	std::unordered_map< std::pair<int, int >, mpz_class, pair_hash > dyn_cache;
};
