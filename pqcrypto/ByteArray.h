#ifndef BYTEARRAY
#define BYTEARRAY

#include <string.h>
#include <stdexcept>
#include <vector>
#include <algorithm>

class ByteArray {
	unsigned char* m_data;
    unsigned int length;
public:
	ByteArray();
	virtual ~ByteArray();
	ByteArray(unsigned int len);
	ByteArray(int length);
	ByteArray(const unsigned char* data, unsigned int length);
	ByteArray(const char *data);
	ByteArray(const ByteArray& value);

	ByteArray& operator =(const ByteArray& value);
	unsigned char& operator [](int pos);
	unsigned char at(int pos) const;
	friend ByteArray operator ^(const ByteArray& left, const ByteArray& right) noexcept;
	void copyFrom(unsigned char* data, unsigned int length);
	void setDataPointer(unsigned char* data, unsigned int length);
	unsigned char* getDataPointer();
	unsigned int size() const;
	virtual std::string toString() noexcept;
	virtual std::string toHex();
	//virtual std::vector<ByteArray> toBaseW();
};

#endif
