#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include "listener.h"

class TcpListener : public Listener
{
public:
    TcpListener(int port);
    virtual int Start();
    virtual std::shared_ptr<Conn> Accept();
private:
    int _port;
    int _listenSock;
};

#endif // TCPLISTENER_H
