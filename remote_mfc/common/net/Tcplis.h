#pragma once

#include "Listener.h"
class TcpLis : public Listener {
public:
	TcpLis(int port);
	int Start();
private:
	int _port;
	int _listenSock;
};