#ifndef ETHERNETDATA_H
#define ETHERNETDATA_H
#include "string.h"
#include <iostream>

class EthernetData
{
public:
	EthernetData()=default;
	~EthernetData();
	EthernetData(const size_t size);
	EthernetData(void* buffer,const size_t size);
	EthernetData(const EthernetData& x);
	EthernetData& operator=(const EthernetData& x);

	unsigned char* getData() const;
	size_t getSize() const;
private:
	unsigned char* data=nullptr;
	size_t size = 0;
};
#endif //ETHERNETDATA_H