#pragma once

#include "Listener.h"
#include <memory>

class TcpLis : public Listener {
public:
	TcpLis(int port);
	int Start();
	virtual std::shared_ptr<Conn> Accept();
private:
	int _port;
	int _listenSock;
};