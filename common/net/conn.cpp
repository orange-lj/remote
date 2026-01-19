#include "conn.h"

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
