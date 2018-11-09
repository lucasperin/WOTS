#ifndef BYTEARRAY
#define BYTEARRAY

#include <string.h>
#include <stdexcept>
#include <stdlib.h> //strtol
#include <vector>
#include <algorithm>

class ByteArray {
	unsigned char* m_data;
    unsigned int length;
public:
	ByteArray() noexcept;
	virtual ~ByteArray() noexcept;
	ByteArray(unsigned int len) noexcept;
	ByteArray(const ByteArray& value) noexcept;

	static ByteArray fromData(const unsigned char* data, unsigned int length) noexcept;
	static ByteArray fromHex(const std::string& hex) noexcept;
	static ByteArray fromString(const std::string& string) noexcept;

	ByteArray& operator =(const ByteArray& value);
	unsigned char& operator [](int pos);
	unsigned char at(int pos) const;
	friend ByteArray operator ^(const ByteArray& left, const ByteArray& right) noexcept;
	void copyFrom(const unsigned char* data, unsigned int length);
	unsigned char* getDataPointer();
	unsigned int size() const;
	virtual std::string toString() noexcept;
	virtual std::string toHex();
	std::vector<unsigned int> toBaseW(const unsigned int w);
protected:
	std::vector<unsigned int> toBaseWSmall(const unsigned int w);
	std::vector<unsigned int> toBaseWBig(const unsigned int w);

};

#endif
