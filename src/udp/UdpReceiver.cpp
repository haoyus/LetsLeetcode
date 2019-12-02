#include "UdpReceiver.h"
#include <iostream>

using namespace std;

UdpReceiver::UdpReceiver(const int receiverPort,bool WAIT)
    :port(receiverPort),isWait(WAIT)
{
    initial(receiverPort);
}

UdpReceiver::~UdpReceiver(){close(socketFd);}


int UdpReceiver::receive(void* x,size_t size) const
{
    socklen_t len=sizeof(senderAddress);
    
    int res=-1;
    if(isWait)
    {
        res=recvfrom(socketFd,x,size,MSG_WAITALL,(sockaddr*)&senderAddress,&len);
        if(res==-1)
            cout<<"\033[31mreceive failed!\033[0m"<<endl;
    }
    else
        res=recvfrom(socketFd,x,size,MSG_DONTWAIT,(sockaddr*)&senderAddress,&len);

    return res;
}

void UdpReceiver::printUdpReceiverInformation() const
{
    cout<<"receiverAddress: "<<receiverAddress.sin_addr.s_addr<<" receiverPort: "<<ntohs(receiverAddress.sin_port)<<endl;
}


void UdpReceiver::initial(const int receiverPort)
{
    receiverAddress.sin_family=AF_INET;
    receiverAddress.sin_addr.s_addr=INADDR_ANY;
    receiverAddress.sin_port=htons(receiverPort);
    
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    if(socketFd==-1)
        cout<<"\033[31mfailed to create receiver socket\033[0m"<<endl;
    else
        cout<<"\033[32mcreated udp receiver socket \033[0m"<<socketFd<<endl;

    int ret=bind(socketFd,(sockaddr*)&receiverAddress,sizeof(receiverAddress));
    if(ret==-1)
        cout<<"\033[31mbind receiver socket failed\033[0m"<<endl;
    else
        cout<<"\033[32mbind receiver socket successful\033[0m"<<endl;
}

