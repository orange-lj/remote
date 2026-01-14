#include "Tcplis.h"
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


	} while (0);
	return 0;
}
