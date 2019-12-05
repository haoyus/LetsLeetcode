#include "ByteArray.h"

using std::cout;
using std::endl;

ByteArray::ByteArray()
    : head(nullptr)
    , size(0) 
    {
        cout << "Constructing null ByteArray\n";
    }

ByteArray::ByteArray(size_t len)
{
    head = new tByte[len];
    size = len;
    cout << "Constructing " << size << " bytes\n";  
}

ByteArray::~ByteArray()
{
    if(head!=nullptr)
        delete[] head;
    head = nullptr;
    cout << "released " << size << " bytes\n";
}

void ByteArray::Resize(size_t len)
{
    if(head!=nullptr)
        delete[] head;
    head = new tByte[len];
    size = len;
}

ByteArrayPtr MakeByteArray(size_t size)
{
    return std::make_shared<ByteArray>(size);
}

int main()
{
    ByteArrayPtr Ptr(new ByteArray(5));//Ptr(make_shared<ByteArray>(5), = ..., Ptr, Ptr(5))
    {
        ByteArrayPtr tmp(new ByteArray(10));//tmp(make_shared), = make_shared, = MakeByteArray(10)
        Ptr = tmp;
        cout << "After assign\n";
    }
    cout<< "Out of block\n";
}