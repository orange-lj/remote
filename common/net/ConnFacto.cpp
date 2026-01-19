#include "ConnFacto.h"
#include "Tcpconn.h"

Conn* ConnFacto::CreateConnect2(int connType, int flag, char* server, int port)
{
    Conn* con = NULL;

    switch (connType)
    {
    case CONN_TYPE_TCP:
    {
        con = new TcpConn;
    }
    break;
    }

    if (con)
    {
        if (con->Connect(server, port))
        {
            delete con;
            con = NULL;
        }
    }
    return con;
}
