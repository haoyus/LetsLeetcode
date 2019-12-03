#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <pthread.h>
#include <memory>
#include "UdpReceiver.h"
#include "UdpReceiver.cpp"
#include "UdpSender.h"
#include "UdpSender.cpp"
#include "UdpPack.h"
#include "EthernetData.h"
//#include "./udp/EthernetData.cpp"
#include "UdpReceiveModule.h"

using namespace std;

void cycleSend(UdpSender* sender, UdpPack* packToSend,size_t len)
{
    while(1)
    {
        this_thread::sleep_for(chrono::seconds(2));

        packToSend->A0 += 1.0;
        packToSend->A1 += 1.0;
        packToSend->reserved[0] += 1;
        int ses = sender->send(packToSend,len);

        cout<<"\033[32mSent \033[0m" << ses << " bytes, A0: " << packToSend->A0 << endl;
    }
}

void cycleRecv(UdpReceiver* receiver, UdpPack* dest, size_t len)
{
    while(1)
    {
        int res = receiver->receive(dest,len);
        cout<<"\033[33mReceived \033[0m" << res << " bytes" << ", A0: " << dest->A0 <<endl;
    }
}

int main()
{
    cout<<"---- Testing UDP ----\n";
    UdpSender* psender = new UdpSender("127.0.0.1",55551);

    size_t len = sizeof(UdpPack);
    cout << "UDP Pack length: " << len <<endl;
    UdpPack* src_pack = new UdpPack();

    thread send_thread(cycleSend,psender,src_pack, len);
    send_thread.detach();

    // EthernetData dump_pack(len*2);
    // UdpReceiver* precver = new UdpReceiver(55551);
    // thread recv_thread(cycleRecv,precver,((UdpPack*)dump_pack.getData()),len*2);
    // recv_thread.detach();

    UdpReceiveModule rcvMod(55551);
    //EthernetData dump_pack;
    int i=5;
    UdpPack* tmp = nullptr;
    while(i-->0){
        ByteData dump_pack;
        dump_pack = rcvMod.getNextMsg();
        cout << "\033[33mReceived \033[0m" << "A0: " << ((UdpPack*)dump_pack.getData())->A0 << endl;
        cout << "-----\n";

        tmp = (UdpPack*)dump_pack.getData();
        cout << " Before delete[], A0: " << tmp->A0 << ", A1: " << tmp->A1 << ", char[0]: " << (int)tmp->reserved[0] <<endl;
        delete[] dump_pack.getData();
        cout << " After  delete[], A0: " << tmp->A0 << ", A1: " << tmp->A1 << ", char[0]: " << (int)tmp->reserved[0] <<endl;
        tmp = (UdpPack*)dump_pack.getData();
    }
    
    cout << " Out of while loop, A0: " << tmp->A0 << ", A1: " << tmp->A1 << ", char[0]: " << (int)tmp->reserved[0] <<endl;
    string cmd;
    cin>>cmd;
    //cout << "Src pack A0: " << src_pack->A0 << ", Dest pack A0: " << ((UdpPack*)dump_pack.getData())->A0 << endl;
}