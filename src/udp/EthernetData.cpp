#include "EthernetData.h"
#include "../runtime/timer.h"

EthernetData::~EthernetData()
{
    if (data != nullptr)
        delete[] data;
    std::cout << "Destructing EthernetData of " << this->size << " at " << (unsigned long)data << std::endl;
}

EthernetData::EthernetData(const size_t size)
{
    data = new unsigned char[size];
    this->size = size;

    std::cout << "Constructing EthernetData of " << this->size << " at " << (unsigned long)data << std::endl;
}

EthernetData::EthernetData(void *buffer, const size_t size)
{
    data = new unsigned char[size];
    memcpy(data, buffer, size);
    this->size = size;
}
EthernetData::EthernetData(const EthernetData &x)
{
    size = x.size;
    data = new unsigned char[x.size];
    memcpy(data, x.data, x.size);
    std::cout << "Copying...\n";
}

EthernetData& EthernetData::operator=(const EthernetData &x)
{
    size = x.size;
    if (data != x.data)
    {
        SimpleTimer t;
        delete[] data;
        data = new unsigned char[x.size];
        memcpy(data, x.data, x.size);
        std::cout << "Assigning memory of " << (unsigned long)x.data << " to " << (unsigned long)data << std::endl;
    }
    std::cout << "Assigning...\n";
    return *this;
}

unsigned char *EthernetData::getData() const { return data; };
size_t EthernetData::getSize() const { return size; };