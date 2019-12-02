/**
 * From Jianbin Chen, CACQ
*/

#ifndef UDPSENDER_H
#define UDPSENDER_H

#ifdef __linux
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif
#include <memory>

class UdpSender
{
public:
    UdpSender(const char* ip,const int port );
    ~UdpSender();
    int send(const void* x,size_t size);
    void printInfo();

private:
    sockaddr_in receiverAddress;
    int socketFd;
};

typedef std::shared_ptr<UdpSender> UdpSenderPtr;

#endif