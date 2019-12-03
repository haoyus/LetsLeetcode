#include "ByteData.h"
#include <iostream>

ByteData::~ByteData()
{
    // if (data != nullptr)
    //     delete[] data;
    std::cout << "Destructing ByteData at " << (unsigned long)data << std::endl;
}

ByteData::ByteData(const size_t size)
{
    data = new unsigned char[size];
    this->size = size;
    std::cout << "Constructing ByteData of " << this->size << " at " << (unsigned long)data << std::endl;
}

ByteData::ByteData(void *buffer, const size_t size)
{
    data = new unsigned char[size];
    memcpy(data, buffer, size);
    this->size = size;
    std::cout << "Constructing ByteData of " << this->size << " at " << (unsigned long)data << " by memcpy" << std::endl;
}
ByteData::ByteData(const ByteData &x)
{
    size = x.size;
    data = new unsigned char[x.size];
    memcpy(data, x.data, x.size);
    std::cout << "Copying...\n";
}

// ByteData& ByteData::operator=(const ByteData &x)
// {
//     size = x.size;
//     if (data != x.data)
//     {
//         delete[] data;
//         data = new unsigned char[x.size];
//         memcpy(data, x.data, x.size);
//     }
//     return *this;
// }

unsigned char *ByteData::getData() const { return data; };
size_t ByteData::getSize() const { return size; };