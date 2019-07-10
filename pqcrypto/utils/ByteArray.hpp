#include "bytearray.hpp"

typedef bytearray<std::allocator<std::byte> > ByteArray;

static inline std::byte operator "" _b(const char c) {
	return (std::byte)c;
}


/* Helper stuff! constexpr char to std::byte solver.
#include <cstddef>
#include <limits>
#include <type_traits>

template <char c>
struct dependent_false : std::false_type {
};

template <char c>
inline constexpr bool dependent_false_v = dependent_false<c>::value;

template <std::size_t Index, char c0, char... cs>
constexpr void lit_impl(std::byte &retval)
{
    if constexpr (Index >= std::numeric_limits<unsigned char>::digits + 2) {
        static_assert(dependent_false_v<c0>);
    }
    if constexpr (Index == 0u) {
        if constexpr(c0 != '0') {
            static_assert(dependent_false_v<c0>);
        }
        lit_impl<Index + 1u, cs...>(retval);
    } else if constexpr (Index == 1u) {
        if constexpr(c0 != 'b' && c0 != 'B') {
            static_assert(dependent_false_v<c0>);
        }
        lit_impl<Index + 1u, cs...>(retval);
    } else {
        if constexpr(c0 != '0' && c0 != '1') {
            static_assert(dependent_false_v<c0>);
        }
        if constexpr(c0 == '1') {
            retval = static_cast<std::byte>(static_cast<unsigned char>(retval) + 1u);
        }
        if constexpr (sizeof...(cs) != 0u) {
            retval <<= 1;
            lit_impl<Index + 1u, cs...>(retval);
        }
    }
}

template <char... cs> constexpr std::byte operator "" _bl()
{
    std::byte retval{};
    lit_impl<0, cs...>(retval);
    return retval;
}

int main()
{
    static_assert(static_cast<unsigned char>(0b0_bl) == 0u);
    static_assert(static_cast<unsigned char>(0b1_bl) == 1u);
    static_assert(static_cast<unsigned char>(0b10_bl) == 2u);
    static_assert(static_cast<unsigned char>(0b11_bl) == 3u);
    static_assert(static_cast<unsigned char>(0b01_bl) == 1u);
    static_assert(static_cast<unsigned char>(0b00001_bl) == 1u);
    static_assert(static_cast<unsigned char>(0b00101_bl) == 5u);
    static_assert(static_cast<unsigned char>(0b01001_bl) == 9u);
    static_assert(static_cast<unsigned char>(0b101101_bl) == 45u);
}

*/
