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

int SockApi::Connect(int sockfd, const sockaddr* name, int namelen)
{
    if (connect(sockfd, name, (socklen_t)namelen) < 0)
    {
        return GetLastError();
    }
    else {
    
        tcp_keepalive ka;

        ka.onoff = 1;
        ka.keepalivetime = 1000 * 30;
        ka.keepaliveinterval = 1000 * 10;

        DWORD cb = 0;
        WSAIoctl(sockfd, SIO_KEEPALIVE_VALS, &ka, sizeof(ka), NULL, 0, &cb, NULL, NULL);

        DWORD enableka = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (PCHAR)&enableka, sizeof(enableka));

        linger lingerData;

        lingerData.l_onoff = 1;
        lingerData.l_linger = 10;

        setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (PCHAR)&lingerData, sizeof(linger));

        SetHandleInformation((HANDLE)sockfd, HANDLE_FLAG_INHERIT, 0);

        return 0;
    }
}

int SockApi::Accept(int sockfd, sockaddr* addr, int* addrlen, int& clientfd)
{
    clientfd = accept(sockfd, addr, (socklen_t*)addrlen);
    if (clientfd <= 0)
    {
        return GetLastError();
    }
    else {
        tcp_keepalive ka;

        ka.onoff = 1;
        ka.keepalivetime = 1000 * 30;
        ka.keepaliveinterval = 1000 * 10;

        DWORD cb = 0;
        WSAIoctl(clientfd, SIO_KEEPALIVE_VALS, &ka, sizeof(ka), NULL, 0, &cb, NULL, NULL);

        DWORD enableka = 1;
        setsockopt(clientfd, SOL_SOCKET, SO_KEEPALIVE, (PCHAR)&enableka, sizeof(enableka));

        linger lingerData;

        lingerData.l_onoff = 1;
        lingerData.l_linger = 10;

        setsockopt(clientfd, SOL_SOCKET, SO_LINGER, (PCHAR)&lingerData, sizeof(linger));
        SetHandleInformation((HANDLE)clientfd, HANDLE_FLAG_INHERIT, 0);
        return 0;
    }    
}

int SockApi::Send(int sockfd, const void* buf, int len, int& bytesWritten)
{
    int n = send(sockfd, (const char*)buf, len, 0);
    if (n <= 0) {
        return 1;
    }
    else {
        bytesWritten = n;
        return 0;
    }
}

int SockApi::Recv(int sockfd, void* buf, int len, int& bytesRead)
{
    int n = recv(sockfd, (char*)buf, len, 0);
    if (n <= 0)
    {
        return 4;
    }
    else
    {
        bytesRead = n;
        return 0;
    }
}

int SockApi::GetAddrInfo_x(const char* node, const char* service, const addrinfo* hints, addrinfo** res)
{
    if (getaddrinfo(node, service, hints, res) == 0)
    {
        //success
        return 0;
    }
    else
    {
        //failed
        return 1;
    }
}

int SockApi::FreeAddrInfoWrap_x(addrinfo* res)
{
    freeaddrinfo(res);
    return 0;
}

int SockApi::Shutdown(int sockfd)
{
    return 0;
}

int SockApi::Close(int fd)
{
    closesocket(fd);
    return 0;
}

int SockApi::Getsockname(int sockfd, sockaddr* addr, int* addrlen)
{
    if (getsockname(sockfd, addr, (socklen_t*)addrlen) < 0)
    {
        return GetLastError();
    }
    else
    {
        return 0;
    }
}

int SockApi::Getpeername(int sockfd, sockaddr* addr, int* addrlen)
{
    if (getpeername(sockfd, addr, (socklen_t*)addrlen) < 0)
    {
        return GetLastError();
    }
    else 
    {
        return 0;
    }
}
