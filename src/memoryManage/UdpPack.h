#pragma once

#include <memory>

#pragma pack(push,1)

struct UdpPack
{
    double A0 = 0;
    double A1 = 0;
    double A2 = 0;
    double A3 = 0;
    unsigned char reserved[1024-32];
};

#pragma pack(pop)

