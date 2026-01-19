#include "Tcplis.h"
#include "Tcpconn.h"
#include "Sockapi.h"
TcpLis::TcpLis(int port)
	:_port(port),
	_listenSock(-1)
{

}

int TcpLis::Start()
{
	int error = 0;
	int sockfd = -1;

	do
	{
		error = SockApi::Socket(AF_INET, SOCK_STREAM, 0, sockfd);

		if (error)
			break;

		struct sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(_port);

		error = SockApi::Bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
		if (error)
			break;

		SockApi::Listen(sockfd, 10);
	} while (0);

	if (error)
	{
		if (sockfd != -1)
			SockApi::Close(sockfd);

		return error;
	}

	_listenSock = sockfd;
	return 0;
}

std::shared_ptr<Conn> TcpLis::Accept()
{
	int error;
	int client;

	error = SockApi::Accept(_listenSock, NULL, NULL, client);
	if (error)
	{
		return nullptr;
	}
	else
	{
		return std::make_shared<TcpConn>(client);
	}
}
