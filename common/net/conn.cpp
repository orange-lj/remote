#include "conn.h"
#include "Sockapi.h"
int Conn::SendAll(char* buf, int bytesToSend)
{
	int left = bytesToSend;
	char* ptr = buf;
	int bytesSend;
	int error = 1;

	while (left > 0)
	{
		error = Send(ptr, left, &bytesSend);
		if (error)
		{
			break;
		}

		ptr += bytesSend;
		left -= bytesSend;
	}

	return error;
}

int Conn::RecvAll(char* buf, int bytesToRecv, uint64_t times)
{
	int left = bytesToRecv;
	char* ptr = buf;
	int bytesRead;
	int error = 1;


	while (left > 0)
	{
		error = Recv(ptr, left, &bytesRead, times);
		if (error)
		{
			break;
		}

		ptr += bytesRead;
		left -= bytesRead;
	}

	return error;
}

std::string Conn::PeerIp()
{
	struct sockaddr_in addr = { 0 };
	int len = sizeof(addr);

	PeerName((struct sockaddr*)&addr, &len);

	std::string ip = inet_ntoa(addr.sin_addr);
	return ip;
}
