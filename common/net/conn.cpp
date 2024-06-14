#include "conn.h"


int Conn::RecvAll(char *buf, int bytesToRecv, uint64_t times)
{
    int left = bytesToRecv;
    char* ptr = buf;
    int bytesRead;
    int error = 1;
    while(left > 0)
    {
        error = Recv(ptr,left,&bytesRead,times);
    }
}
