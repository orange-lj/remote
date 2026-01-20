#pragma once
#include "conn.h"
#include "cotp.h"
class TcpConn : public Conn {

public:
	TcpConn(int s);
	TcpConn();
	~TcpConn();
	virtual int Connect(char* server, int port);
	virtual void Close();
	virtual int Recv(char* buf, int bytesToRecv, int* pBytesRecved, uint64_t times = neosmart::WAIT_INFINITE);
	virtual int SockName(struct sockaddr* name, int* namelen);
	virtual int Send(char* buf, int bytesToSend, int* pBytesSent);
	virtual int GetConnType();
	virtual int PeerName(struct sockaddr* name, int* namelen);
	virtual void CloseNotify();
private:
	int _sock;
	std::mutex      m_relase_lock;
};