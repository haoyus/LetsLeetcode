#ifndef BYTEDATA_H
#define BYTEDATA_H
#include "string.h"

class ByteData
{
public:
	ByteData()=default;
	~ByteData();
	ByteData(const size_t size);
	ByteData(void* buffer,const size_t size);
	ByteData(const ByteData& x);
	//ByteData& operator=(const ByteData& x);

	unsigned char* getData() const;
	size_t getSize() const;
private:
	unsigned char* data=nullptr;
	size_t size = 0;
};
#endif //BYTEDATA_H