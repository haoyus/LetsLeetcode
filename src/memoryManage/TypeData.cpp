#include "TypeData.h"
#include <iostream>
#include "UdpPack.h"

template <typename T>
TypeData<T>::~TypeData()
{
    UdpPack* tmp = (UdpPack*)data;
    std::cout << "Destructing TypeData at " << (unsigned long)data << "; "
              << "before delete, A0: " << tmp->A0 << ", A1: "
              << tmp->A1 << ", char[0]: " << (int)tmp->reserved[0] <<";  ";

    if (data != nullptr)
        delete data;

    std::cout << "after delete, A0: " << tmp->A0 << ", A1: "
              << tmp->A1 << ", char[0]: " << (int)tmp->reserved[0] <<"\n";
}

template <typename T>
TypeData<T>::TypeData()
{
    data = new T;
    this->size = sizeof(T);
    std::cout << "Constructing TypeData of " << this->size << " at " << (unsigned long)data << std::endl;
}

// template<typename T>
// TypeData<T>::TypeData(void *buffer, const size_t size)
// {
//     data = new unsigned char[size];
//     memcpy(data, buffer, size);
//     this->size = size;
//     std::cout << "Constructing TypeData of " << this->size << " at " << (unsigned long)data << " by memcpy" << std::endl;
// }
// TypeData::TypeData(const TypeData &x)
// {
//     size = x.size;
//     data = new unsigned char[x.size];
//     memcpy(data, x.data, x.size);
//     std::cout << "Copying...\n";
// }

template <typename T>
TypeData<T>& TypeData<T>::operator=(const TypeData<T> &x)
{
    size = x.size;
    if (data != x.data)
    {
        delete data;
        data = new T;
        memcpy(data, x.data, x.size);
        std::cout << "Assigning memory of " << (unsigned long)x.data << " to " << (unsigned long)data << std::endl;
    }
    return *this;
}

template <typename T>
T* TypeData<T>::getData() const
{
    return data;
}

template <typename T>
size_t TypeData<T>::getSize() const { return size; };