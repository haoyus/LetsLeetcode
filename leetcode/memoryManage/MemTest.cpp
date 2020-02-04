#include <iostream>
#include <string.h>
#include "UdpPack.h"

using namespace std;

typedef unsigned char tByte;

#pragma pack(push,1)
struct Pack
{
    double A0 = 0;
    double A1 = 0;
    double A2 = 0;
    double A3 = 0;
    unsigned char reserved[30];
};
struct BytePack
{
    tByte bytes[62];
};
#pragma pack(pop)

void SetPack(Pack* p)
{
    p->A0 = 1;
    p->A1 = 2;
    p->A2 = 3;
    p->A3 = 4;
    for(int i=0; i<30; ++i)
        p->reserved[i] = i+5;
}

void SetByteArray(tByte* p, size_t len)
{
    for(int i=0; i<len; ++i)
        p[i] = i+1;
}

tByte* MakeByteArray(size_t len)
{
    tByte* p = new tByte[len];
    SetByteArray(p,len);
    return p;
}

void PrintByteArray(tByte* p, size_t len)
{
    for(int i=0; i<len; ++i){
        cout << (int)p[i] << " ";
    }
    cout << endl;
}

void SetBytePack(BytePack* p)
{
    for(int i=0; i<62; ++i)
        p->bytes[i] = i+1;
}

Pack* MakePack()
{
    Pack* p = new Pack;
    SetPack(p);
    return p;
}

void PrintPack(Pack* p)
{
    cout << "at " << (unsigned long)p << ": A0 " << p->A0 << " A1 " << p->A1 << " A2 "
         << p->A2 << " A3 " << p->A3 << " res " << (int)p->reserved[0] <<endl;
}

tByte* CopyPack(Pack* p)
{
    tByte* array = new tByte[sizeof(Pack)];
    memcpy(array,p,sizeof(Pack));
    return array;
}

tByte* CopyBytes(tByte* src, size_t len)
{
    tByte* array = new tByte[len];
    memcpy(array,src,len);
    return array;
}

int main()
{
    const size_t SIZE = 9;

    size_t packLen = sizeof(Pack);
    cout << "size of Pack: " << packLen << endl;

    cout << "---- testing ByteArray ----\n";
    tByte* pB = MakeByteArray(30);
    SetByteArray(pB,30);
    tByte* pB1 = CopyBytes(pB,30);
    tByte* pB2 = CopyBytes(pB,30);
    tByte* pB3 = CopyBytes(pB,30);

    cout << "Before and after delete pB:\n";
    PrintByteArray(pB,30);
    //delete[] pB;
    PrintByteArray(pB,30);
    cout << "Before and after delete pB1:\n";
    PrintByteArray(pB1,30);
    delete[] pB1;
    PrintByteArray(pB1,30);
    cout << "Before and after delete pB2:\n";
    PrintByteArray(pB2,30);
    delete[] pB2;
    PrintByteArray(pB2,30);
    cout << "Before and after delete pB3:\n";
    PrintByteArray(pB3,30);
    delete[] pB3;
    PrintByteArray(pB3,30);


    // cout << "\n---- testing Pack ----\n";
    // Pack* pP = MakePack();
    // tByte* head = CopyPack(pP);
    // tByte* head1 = CopyBytes(head,sizeof(Pack));

    // cout << "Before and after delete Pack*:\n";
    // PrintPack(pP);
    // delete pP;
    // PrintPack(pP);

    // cout << "Before and after delete[] head:\n";
    // PrintPack((Pack*)head);
    // delete[] head;
    // PrintPack((Pack*)head);

    // cout << "Before and after delete[] head1:\n";
    // PrintPack((Pack*)head1);
    // delete[] head1;
    // PrintPack((Pack*)head1);

    // cout << "\n---- testing byte array ----\n";
    // tByte* p = nullptr;
    // {
    //     tByte* tmp = new tByte[SIZE];
    //     for(int i=0; i< SIZE; ++i)
    //         tmp[i] = i+1;
    //     p = tmp;
    // }

    // cout << "before delete[]: ";
    // for(int i=0; i< SIZE; ++i)
    //     cout << (int)p[i] << " ";
    // cout << "\n";

    // delete[] p;
    // cout << "after  delete[]: ";
    // for(int i=0; i< SIZE; ++i)
    //     cout << (int)p[i] << " ";
    // cout << "\n";


    // cout << "---- testing UdpPack ----\n";
    // UdpPack* pPack = nullptr;
    // {
    //     UdpPack* tmp = new UdpPack;
    //     tmp->A0 = 1;
    //     tmp->A1 = 2;
    //     tmp->A2 = 3;
    //     tmp->A3 = 4;
    //     tmp->reserved[0] = 5;
    //     pPack = tmp;
    // }
    // cout << "before delete: ";
    // cout << "A0 " << pPack->A0 << " A1 " << pPack->A1 << " A2 " << pPack->A2 << " A3 " << pPack->A3 << " res " << (int)pPack->reserved[0];
    // cout << "\n";

    // delete pPack;
    // cout << "after  delete: ";
    // cout << "A0 " << pPack->A0 << " A1 " << pPack->A1 << " A2 " << pPack->A2 << " A3 " << pPack->A3 << " res " << (int)pPack->reserved[0];
    // cout << "\n";
}