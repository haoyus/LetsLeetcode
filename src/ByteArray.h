#pragma once

#include <string.h>
#include <memory>
#include <iostream>

class ByteArray
{
public:
    ByteArray();
    ByteArray(size_t len);
    //ByteArray(const ByteArray&) = delete;
    //ByteArray& operator=(const ByteArray&) = delete;
    ~ByteArray();

    void Resize(size_t len);
    unsigned char* getHead() const {return head;}
    size_t getSize() const {return size;}

private:
    typedef unsigned char tByte;
    tByte* head;
    size_t size;
};

void DeleteByteArray(ByteArray* p);

typedef std::shared_ptr<ByteArray> ByteArrayPtr;