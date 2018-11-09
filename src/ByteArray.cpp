#include <ByteArray.h>

ByteArray::ByteArray() noexcept
{
    this->m_data = NULL;
    this->length = 0;
}

ByteArray::~ByteArray()
{
    delete[] this->m_data;
}

ByteArray::ByteArray(unsigned int length) noexcept
{
	if(length){
		this->length = length;
		this->m_data = new unsigned char[length + 1];
		this->m_data[length] = '\0';
	}
	else
		ByteArray();
}

ByteArray::ByteArray(const ByteArray& value) noexcept
{
    this->length = value.length;
    this->m_data = new unsigned char[this->length + 1];
    memcpy(this->m_data, value.m_data, value.length);
    this->m_data[length] = '\0';
}

ByteArray ByteArray::fromData(const unsigned char* data, unsigned int length) noexcept
{
	ByteArray ret;
	ret.copyFrom(data,length);
	return ret;
}

ByteArray ByteArray::fromHex(const std::string& hex) noexcept
{
	std::string hex_copy;
	if(hex.length()%2 == 1)
		hex_copy = '0' + hex;
	else
		hex_copy = hex;
	ByteArray ret(hex_copy.length()/2);
	for (unsigned int i = 0; i < hex_copy.length(); i += 2) {
		std::string byteString = hex_copy.substr(i, 2);
		ret[i/2] = (char) strtol(byteString.c_str(), NULL, 16);
	}
	return ret;
}

ByteArray ByteArray::fromString(const std::string& string) noexcept
{
	ByteArray ret;
	ret.length = string.size();
    ret.m_data = new unsigned char[ret.length + 1]; 
    memcpy(ret.m_data, string.c_str(), ret.length);
    ret.m_data[ret.length] = '\0';
	return ret;
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

void ByteArray::copyFrom(const unsigned char* d, unsigned int length)
{
    if(this->m_data){ delete this->m_data; }
    this->length = length;
    this->m_data   = new unsigned char[this->length + 1];
    memcpy(this->m_data, d, length);
    this->m_data[length] = '\0';
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

std::vector<unsigned int> ByteArray::toBaseW(const unsigned int w) {
	switch(w) {
		case 4	: return toBaseWSmall(2); break;
		case 16	: return toBaseWSmall(4); break;
		case 256: return toBaseWSmall(8); break;
		case 65536: return toBaseWBig(16); break;

	}
	std::vector<unsigned int> dummy;
	return dummy;
}

std::vector<unsigned int> ByteArray::toBaseWBig(const unsigned int w) {
	const unsigned int bytes_per_block = w/8;
	std::vector<unsigned int> ret;
	unsigned int total = 0;
	unsigned int s = 0;

	for(unsigned int i=0; i < this->length; i++) {
		s = (bytes_per_block-1) - (i%bytes_per_block);
		total += (at(i)<< s) & ( (1<<w)-1);
		if( (i+1)%bytes_per_block == 0){
			ret.push_back(total);
			total = 0;
		}
	}
	return ret;
}

std::vector<unsigned int> ByteArray::toBaseWSmall(const unsigned int w) {
	unsigned int in = 0;
	unsigned int total = 0;
	unsigned int bits = 0;
	unsigned int consumed;
	std::vector<unsigned int> ret;
	unsigned int out_len = length*8 / w;

	for ( consumed = 0; consumed < out_len; consumed++ ) {
		if ( bits == 0 ) {
			total = at(in);
			in++;
			bits += 8;
		}
		bits -= w;
		ret.push_back((total >> bits) & ( (1<<(w)) -1));
	}
	return ret;
}

