#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


class UdpReceiver
{
public:
    UdpReceiver(const int receiverPort,bool WAIT=true);
    ~UdpReceiver();
    
    int getPort(){return port;}

    int receive(void* x,size_t size) const;
    void printUdpReceiverInformation() const; 
private:
    void initial(const int receiverPort);
private:
    sockaddr_in senderAddress;
    sockaddr_in receiverAddress;
    int socketFd;
    int port;
    bool isWait;
};





#endif