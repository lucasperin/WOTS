#pragma once
/*
 * MIT License
 *
 * Copyright (c) 2013-2018 Megaxela
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Source: https://github.com/Megaxela/bytearray
 */

#include "bytearray_processor.hpp"

/**
 * @brief Class, that implements byte array, that
 * holds std::vector object and has bytearray_processor
 * interface.
 * @tparam Allocator Allocator for std::vector.
 */
template< typename Allocator=std::allocator<std::byte> >
class bytearray : public bytearray_processor<std::byte, Allocator>,
	private std::vector<std::byte, Allocator>
{
	using vector = std::vector<std::byte, Allocator>;
	using processor = bytearray_processor<std::byte, Allocator>;

	public:

	using typename processor::size_type;
	using typename processor::value_type;
	using typename vector::iterator;
	using typename vector::const_iterator;
	using typename vector::reverse_iterator;
	using typename vector::const_reverse_iterator;

	/**
	 * @brief Default constructor.
	 */
	bytearray() :
		processor(*static_cast<vector*>(this)),
		vector()
	{

	}

	/**
	 * @brief Move constructor.
	 */
	bytearray(bytearray<Allocator>&& rhs) noexcept :
		processor(*static_cast<vector*>(this)),
		vector(std::move(rhs.container()))
		{

		}

	/**
	 * @brief Default copy constructor.
	 */
	bytearray(const bytearray<Allocator>& rhs) :
		processor(*static_cast<vector*>(this)),
		vector(rhs.container())
	{

	}

	/**
	 * @brief Constructor with initial size.
	 */
	explicit bytearray(size_type sizeValue) :
		processor(*static_cast<vector*>(this)),
		vector(sizeValue)
	{

	}

	/**
	 * @brief Initializer constructor.
	 */
	bytearray(const value_type* val, size_type amount) :
		processor(*static_cast<vector*>(this)),
		vector(val, val + amount)
	{

	}

	/**
	 * @brief Copy operator.
	 */
	bytearray<Allocator>& operator=(const bytearray<Allocator>& rhs)
	{
		vector::operator=(rhs.container());

		return (*this);
	}

	/**
	 * @brief Move operator.
	 */
	bytearray<Allocator>& operator=(bytearray<Allocator>&& rhs) noexcept
	{
		vector::operator=(std::move(rhs.container()));

		return (*this);
	}

	using vector::operator[];
	using vector::begin;
	using vector::end;
	using vector::cbegin;
	using vector::cend;
	using vector::rbegin;
	using vector::rend;
	using vector::crbegin;
	using vector::crend;
	using vector::capacity;
	using vector::size;
	using vector::reserve;
	using vector::empty;
	using vector::clear;
	using vector::at;
	using processor::push_back;
	using processor::insert;
	};



static inline bytearray<> operator "" _ba(const char* str, std::size_t len)
{
	bytearray array{};

	array.load_from_hex(std::string_view{str, len});

	return array;
}

static inline bytearray<> hstoba(const std::string str)
{
	bytearray array{};
	array.load_from_hex(str);
	return array;
}

//TODO need to convert to hex
//static inline bytearray<> itoba(int value)
//{
	//return stoba(std::to_string(value));
//}

// Allowed
namespace std
{
    template<typename ValueType, typename Allocator>
    std::string to_string(const bytearray_processor<ValueType, Allocator>& processor)
    {
        std::stringstream ss;

        for (auto&& b : processor.container())
        {
            ss
                << std::uppercase
                << std::setfill('0')
                << std::setw(2)
                << std::hex
                << int(b);
        }

        return ss.str();
    }

}

