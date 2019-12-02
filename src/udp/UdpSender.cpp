#include "UdpSender.h"
#include <cstring>
#include <iostream>

//using namespace std;
using std::cout;
using std::endl;

UdpSender::UdpSender(const char* ip,const int port)
{
    receiverAddress.sin_family=AF_INET;
    receiverAddress.sin_addr.s_addr=inet_addr(ip);
    receiverAddress.sin_port=htons(port);

    socketFd=socket(AF_INET,SOCK_DGRAM,0);

    if(socketFd==-1)
        cout<<"\033[31m failed to create sender socket\033[0m"<<endl;

}

UdpSender::~UdpSender()
{
    close(socketFd);
}

void UdpSender::printInfo()
{
    cout<<"send to: "<<inet_ntoa(receiverAddress.sin_addr)<<"  port: "<<ntohs(receiverAddress.sin_port)<<endl;
}


int UdpSender::send(const void* x,size_t size)
{
    int res=sendto(socketFd,x,size,0,(sockaddr*)&receiverAddress,sizeof(receiverAddress));
    if(res==-1)
        cout<<"\033[31msend failed\033[0m"<<endl;
    return res;
}