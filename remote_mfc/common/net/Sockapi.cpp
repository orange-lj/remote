#include "Sockapi.h"

int SockApi::Socket(int domain, int type, int protocol, int& sockfd)
{
    int sock = socket(domain, type, protocol);

    if (sock < 0) {
    
        return GetLastError();
    }
    else {
    
        sockfd = sock;
        //½ûÓÃ¾ä±ú¼Ì³Ð
        SetHandleInformation((HANDLE)sockfd, HANDLE_FLAG_INHERIT, 0);

        return 0;
    }
}

int SockApi::Bind(int sockfd, const sockaddr* addr, int addrlen)
{
    int ret = bind(sockfd, addr, addrlen);

    if (ret < 0){

        return GetLastError();
    }
    else {
    
        return 0;
    }
}

int SockApi::Listen(int sockfd, int backlog)
{
    listen(sockfd, backlog);
    return 0;
}

int SockApi::Close(int fd)
{
    closesocket(fd);
    return 0;
}
