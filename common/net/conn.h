#pragma once
#include <memory>
#include <mutex>
#include "pevents.h"
class Conn {
public:
	virtual ~Conn() {};
	virtual int Connect(char* server, int port) = 0;
	virtual void Close() = 0;
	virtual int Send(char* buf, int bytesToSend, int* pBytesSent) = 0;
	virtual int Recv(char* buf, int bytesToRecv, int* pBytesRecved, uint64_t times = neosmart::WAIT_INFINITE) = 0;
	int SendAll(char* buf, int bytesToSend);
	int RecvAll(char* buf, int bytesToRecv, uint64_t times = neosmart::WAIT_INFINITE);
	virtual int SockName(struct sockaddr* name, int* namelen) = 0;
	virtual int GetConnType() = 0;
	std::string PeerIp();
	virtual int PeerName(struct sockaddr* name, int* namelen) = 0;
	virtual void CloseNotify() = 0;
};