#include <ByteArray.h>

ByteArray::ByteArray()
{
    this->m_data = NULL;
    this->length = 0;
}

ByteArray::~ByteArray()
{
    delete[] this->m_data;
}

ByteArray::ByteArray(unsigned int length)
{
    this->length = length;
    this->m_data = new unsigned char[length + 1];

    for(unsigned int i = 0; i <= length; i++)
    {
        this->m_data[i] = '\0';
    }
}

ByteArray::ByteArray(int length)
{
    this->length = (unsigned int)length;
    this->m_data = new unsigned char[length + 1];

    for(unsigned int i = 0; i <= this->length; i++)
    {
        this->m_data[i] = '\0';
    }
}

ByteArray::ByteArray(const unsigned char* data, unsigned int length)
{
    this->length = length;
    this->m_data = new unsigned char[length + 1];

    memcpy(this->m_data, data, length);

    this->m_data[length] = '\0';
}

ByteArray::ByteArray(const char *data)
{
	this->length = strlen(data);
    this->m_data = new unsigned char[this->length + 1];
    memcpy(this->m_data, data, length);
    this->m_data[this->length] = '\0';
}

ByteArray::ByteArray(const ByteArray& value)
{
    this->length = value.length;
    this->m_data = new unsigned char[this->length + 1];

    memcpy(this->m_data, value.m_data, value.length);

    this->m_data[length] = '\0';
}

ByteArray& ByteArray::operator =(const ByteArray& value)
{
    if(this->m_data){ delete this->m_data; }

    this->length = value.length;
    this->m_data = new unsigned char[this->length + 1];

    memcpy(this->m_data, value.m_data, this->length);

    this->m_data[this->length] = '\0';

    return (*this);
}

unsigned char& ByteArray::operator [](int pos)
{
    if(pos < 0 || pos >= (int)this->length)
    {
        throw std::out_of_range("");
    }
    return this->m_data[pos];
}

unsigned char ByteArray::at(int pos) const {
    if(pos < 0 || pos >= (int)this->length)     {
        throw std::out_of_range("");
    }
    return this->m_data[pos];
}

ByteArray operator ^(const ByteArray& left, const ByteArray& right) noexcept
{
    const ByteArray* biggest;
    const ByteArray* smallest;
    if (left.size() > right.size()) {
        biggest = &left;
        smallest = &right;
    } else {
        biggest = &right;
        smallest = &left;
    }
    
    ByteArray xored(*biggest);
    for (unsigned int i = 0; i < smallest->size(); i++) {
        xored[i] = xored[i] ^ smallest->at(i);
    }
    return xored;
}

void ByteArray::copyFrom(unsigned char* d, unsigned int length)
{
    if(this->m_data){ delete this->m_data; }

    this->length = length;
    this->m_data   = new unsigned char[this->length + 1];

    memcpy(this->m_data, d, length);

    this->m_data[length] = '\0';
}

void ByteArray::setDataPointer(unsigned char* d, unsigned int length)
{
    if(this->m_data){ delete this->m_data; }

    this->length = length;
    this->m_data = d;
}

unsigned char* ByteArray::getDataPointer()
{
    return this->m_data;
}

unsigned int ByteArray::size() const
{
    return this->length;
}

std::string ByteArray::toString() noexcept
{
	std::string data;
	data = (char *)this->m_data;
    return data;
}

std::string ByteArray::toHex()
{
	//sets the hexadecimal lenght for twice the lenght of the bytearray
	//because each byte contains 2 hexadecimals characters
	//go trought the bytearray m_data, coping each byte to two hex in the hex_data
	std::string data;
    char *hex_data = new char[this->length*2 +1];

    int j = 0;
    for(unsigned int i = 0; i < this->length; i++)
    {
		sprintf(&hex_data[j], "%02X", this->m_data[i]);
		j+=2;
    }
    hex_data[j] = '\0';
	data = hex_data;
	delete[] hex_data;
    return data;
}

