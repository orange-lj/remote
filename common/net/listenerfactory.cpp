#include "listenerfactory.h"
#include "tcplistener.h"

std::shared_ptr<Listener> ListenerFactory::CreateListener(int connType, int flag, int bindPort)
{
    switch(connType)
    {
        case CONN_TYPE_TCP:return std::make_shared<TcpListener>(bindPort);

    }
}
