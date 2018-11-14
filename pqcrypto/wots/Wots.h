#ifndef WOTS
#define WOTS

#include "wots/AbstractWinternitzOTS.h"
//TODO(Perin): Test EXPECT template T not base of AbstractDigest compilation error!

template <class T>
class Wots : public  AbstractWinternitzOTS<T> {

public:
	Wots() noexcept;
	Wots(unsigned int w) noexcept;
	~Wots() noexcept;
	virtual const unsigned int t() noexcept;
	virtual const unsigned int t1() noexcept;
	virtual const unsigned int t2() noexcept;
	virtual const unsigned int w() noexcept;
	virtual const unsigned int n() noexcept;
protected:
	unsigned int block_size;

};
#endif
