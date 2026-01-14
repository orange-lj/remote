#include "tcplistener.h"
#include "socketapi.h"

TcpListener::TcpListener(int port)
    :_port(port),
      _listenSock(-1)
{

}

int TcpListener::Start()
{
    int error = 0;
    int sockfd = -1;
    do
    {
        //创建socket
       error = SocketApi::Socket(AF_INET,SOCK_STREAM,0,sockfd);
       if(error)break;
        //定义结构体，填充ip和端口
       struct sockaddr_in addr ={0};
       addr.sin_family = AF_INET;
       addr.sin_addr.s_addr = htonl(INADDR_ANY);
       addr.sin_port = htons(_port);
       error = SocketApi::Bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
       if(error)break;
       SocketApi::Listen(sockfd,10);
    }while(0);
    if (error)
    {
        if (sockfd != -1)
            SocketApi::Close(sockfd);
        return error;
    }

    _listenSock = sockfd;
    return 0;
}

std::shared_ptr<Conn> TcpListener::Accept()
{
    int error;
    int client;
    error = SocketApi::
}
