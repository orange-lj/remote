#include "Tcpconn.h"
#include "Sockapi.h"
#include <string>
TcpConn::TcpConn(int s) :_sock(s){

}

TcpConn::TcpConn() :_sock(-1)
{
}

TcpConn::~TcpConn()
{
    Close();
}

int TcpConn::Connect(char* server, int port)
{
    int error = 0;
    int sockfd = -1;
    struct addrinfo* answer, hint, * curr;

    do
    {
        memset((char*)&hint, 0, sizeof(hint));
        hint.ai_family = AF_INET;
        hint.ai_socktype = SOCK_STREAM;

        answer = NULL;
        int error = SockApi::GetAddrInfo_x(server, std::to_string(port).c_str(), &hint, &answer);
        if (error != 0)
        {
            return error;
        }

        for (curr = answer; curr != NULL; curr = curr->ai_next)
        {
            error = 0;
            error = SockApi::Socket(AF_INET, SOCK_STREAM, 0, sockfd);
            if (error)
            {
                break;
            }

            error = SockApi::Connect(sockfd, curr->ai_addr, curr->ai_addrlen);
            if (error)
            {
                SockApi::Close(sockfd);
                sockfd = -1;
            }
            else
            {
                break;
            }
        }

        SockApi::FreeAddrInfoWrap_x(answer);

        if (error)
        {
            return error;
        }
    } while (0);

    _sock = sockfd;
    return 0;
}

void TcpConn::Close()
{
    m_relase_lock.lock();
    if (_sock != -1)
    {
        SockApi::Close(_sock);
        _sock = -1;
    }
    m_relase_lock.unlock();
}

int TcpConn::Recv(char* buf, int bytesToRecv, int* pBytesRecved, uint64_t times)
{
    if (times == -1)
    {
        return SockApi::Recv(_sock, buf, bytesToRecv, *pBytesRecved);
    }
    else
    {
        fd_set fdread;

        struct timeval timeout = { times / 1000, (times % 1000) * 1000 };

        FD_ZERO(&fdread);
        FD_SET(_sock, &fdread);

        int ret = select(0, &fdread, NULL, NULL, &timeout);
        if (ret == 0)
        {
            return 1;
        }

        if (FD_ISSET(_sock, &fdread))
        {
            return SockApi::Recv(_sock, buf, bytesToRecv, *pBytesRecved);
        }

        return 1;
    }
}

int TcpConn::SockName(sockaddr* name, int* namelen)
{
    return SockApi::Getsockname(_sock, name, namelen);
}

int TcpConn::Send(char* buf, int bytesToSend, int* pBytesSent)
{
    return SockApi::Send(_sock, buf, bytesToSend, *pBytesSent);
}
