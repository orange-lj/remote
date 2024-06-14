#ifndef TCPCONN_H
#define TCPCONN_H

#include "conn.h"

class TcpConn: public Conn
{
public:
    TcpConn();
    virtual int Recv(char* buf, int bytesToRecv, int* pBytesRecved, uint64_t times = neosmart::WAIT_INFINITE);
private:
    int _sock
};

#endif // TCPCONN_H
