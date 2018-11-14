#include "wots/Wots.h"

template <class T>
Wots<T>::Wots() noexcept : block_size(4) {}

template <class T>
Wots<T>::Wots(unsigned int w) noexcept : block_size(w) {}

template <class T>
Wots<T>::~Wots() noexcept {}

template <class T>
const unsigned int Wots<T>::t() noexcept {
	return 12123;
}

template <class T>
const unsigned int Wots<T>::t1() noexcept {
	return 1;
}

template <class T>
const unsigned int Wots<T>::t2() noexcept {
	return 1;
}

template <class T>
const unsigned int Wots<T>::w() noexcept {
	return 1;
}

template <class T>
const unsigned int Wots<T>::n() noexcept {
	return this->len();
}
