#include "socketapi.h"


int SocketApi::Socket(int domain, int type, int protocol, int &sockfd)
{
    int sock = socket(domain,type,protocol);
    if(sock < 0)
    {
        return GetLastError();
    }else
    {
        sockfd =sock;
        //取消继承
        SetHandleInformation((HANDLE)sockfd,HANDLE_FLAG_INHERIT,0);
        return 0;
    }
}

int SocketApi::Bind(int sockfd, const sockaddr *addr, int addrlen)
{
    int ret = bind(sockfd,addr,addrlen);
    if(ret < 0)
    {
        return GetLastError();
    }else
    {
        return 0;
    }
}

int SocketApi::Listen(int sockfd, int backlog)
{
    listen(sockfd, backlog);
    return 0;
}

int SocketApi::Close(int fd)
{
    closesocket(fd);
    return 0;
}

int SocketApi::Accept(int sockfd, sockaddr *addr, int *addrlen, int &clientfd)
{
    clientfd = accept(sockfd,addr,(socklen_t*)addrlen);
    if(clientfd <= 0)
    {
        return GetLastError();
    }else
    {
        tcp_keepalive ka;
        ka.onoff = 1;
        ka.keepalivetime = 1000*30;
        ka.keepaliveinterval = 1000*10;

        DWORD cb = 0;
        //WSAIoctl用来设置TCP KEEP-ALIVE选项，以便在指定时间间隔后发keep-alive包
        WSAIoctl(clientfd,SIO_KEEPALIVE_VALS,&ka,sizeof(ka),NULL, 0, &cb, NULL, NULL);
        DWORD enableka = 1;
        //调用 setsockopt 函数并设置 SO_KEEPALIVE 选项
        setsockopt(clientfd,SOL_SOCKET,SO_KEEPALIVE,(PCHAR)&enableka, sizeof(enableka));
        linger lingerData;
        lingerData.l_onoff = 1;
        lingerData.l_linger = 10;
        //对于需要在关闭连接时确保所有数据都已发送的情况特别有用。通过设置 l_linger 为 10 秒，系统会在调用 closesocket 时最多等待 10 秒来发送未发送的数据。
        setsockopt(clientfd,SOL_SOCKET,SO_LINGER,(PCHAR)&lingerData,sizeof(linger));
        SetHandleInformation((HANDLE)clientfd, HANDLE_FLAG_INHERIT, 0);
        return 0;
    }
}
