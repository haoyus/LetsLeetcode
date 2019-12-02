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

using namespace std;

void cycleSend(UdpSender* sender, UdpPack* packToSend,size_t len)
{
    while(1)
    {
        this_thread::sleep_for(chrono::seconds(2));

        packToSend->A0 += 1.0;
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
    UdpReceiver* precver = new UdpReceiver(55551);

    size_t len = sizeof(UdpPack);
    cout << "UDP Pack length: " << len <<endl;
    UdpPack* src_pack = new UdpPack(), *dump_pack = new UdpPack();
    thread send_thread(cycleSend,psender,src_pack, len);
    send_thread.detach();
    thread recv_thread(cycleRecv,precver,dump_pack,len);
    recv_thread.detach();

    string cmd = " ";
    cin>>cmd;
    cout << "Src pack A0: " << src_pack->A0 << ", Dest pack A0: " << dump_pack->A0 << endl;
}