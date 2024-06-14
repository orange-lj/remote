#ifndef SOCKETAPI_H
#define SOCKETAPI_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
namespace SocketApi
{
    int Socket(int domain,int type,int protocol,int& sockfd);
    int Bind(int sockfd,const struct sockaddr* addr,int addrlen);
    int Listen(int sockfd, int backlog);
    int Accept(int sockfd,struct sockaddr* addr,int* addrlen,int& clientfd);
    int Close(int fd);
}

#endif // SOCKETAPI_H
