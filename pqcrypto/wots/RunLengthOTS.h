
#include "wots/ClassicWots.h"

template <Class T>
class RunLengthOTS : ClassicWots<T> 
public:
	RunLengthOTS() noexcept;
		RunLengthOTS() noexcept;
	virtual const std::vector<ByteArray> sign(ByteArray& data);
	virtual bool verify(ByteArray& data, std::vector<ByteArray>& signature);

protected:
	virtual void genPrivateKey();
	virtual void genPublicKey();
	virtual const std::vector<unsigned int> checksum(std::vector<unsigned int>& blocks);

}
