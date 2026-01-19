
#include "LisFacto.h"
#include "Tcplis.h"
std::shared_ptr<Listener> LisFacto::CreateListener(int connType, int flag, int bindPort)
{
    switch (connType) 
    {
    case CONN_TYPE_TCP: return std::make_shared<TcpLis>(bindPort);
    }
    return std::shared_ptr<Listener>();
}
