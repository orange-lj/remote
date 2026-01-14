#include "tcpconn.h"

TcpConn::TcpConn()
{

}

int TcpConn::Recv(char *buf, int bytesToRecv, int *pBytesRecved, uint64_t times)
{
    //什么时候time会变成-1？
    if(times == -1)
    {

    }else
    {
        //定义一个文件描述符集合fread
        fd_set fdread;
        //定义一个超时时间
        struct timeval timeout = {times/1000,(times%1000)*1000};
        //清空集合
        FD_ZERO(&fdread);
        //将套接字添加到集合中
        FD_SET(_sock,&fdread);
        //调用select函数，等待fdread集合中的文件描述符在timeout时间内变为可读。
        int ret = select(0, &fdread, NULL, NULL, &timeout);
        if (ret == 0)
        {
            return 1;
        }

    }
}
