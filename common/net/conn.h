#ifndef CONN_H
#define CONN_H
#include "pevents.h"

class Conn
{
public:
    //接收信息（buf,接收的字节数,等待时间）。默认情况下，函数会一直等待接收所有数据，如果提供了times，则会等待指定时间
    int RecvAll(char* buf,int bytesToRecv,uint64_t times = neosmart::WAIT_INFINITE);
    virtual int Recv(char* buf,int bytesToRecv,int* pBytesRecved,uint64_t times = neosmart::WAIT_INFINITE) = 0;
};

#endif // CONN_H
