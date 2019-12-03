#pragma once

#include "../runtime/Module.h"
#include "UdpReceiver.h"
#include "EthernetData.h"
#include "ByteData.h"

class UdpReceiveModule : public Module
{
public:
    UdpReceiveModule(const int port) 
        : Module("UdpReceiverModule")
        , receiver(new UdpReceiver(port))
        {}

public:
    inline ByteData getNextMsg();
    inline void Run() override;

private:
    UdpReceiver* receiver;
};

ByteData UdpReceiveModule::getNextMsg()
{
    ByteData dump(1024);
    int len = receiver ->receive(dump.getData(),1024);
    std::cout << "received " << len << " bytes and returning..\n";
    return dump;
}

void UdpReceiveModule::Run()
{}