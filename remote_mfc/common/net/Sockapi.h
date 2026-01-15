#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <mstcpip.h>

namespace SockApi {
	int Socket(int domain, int type, int protocol, int& sockfd);
	int Bind(int sockfd, const struct sockaddr* addr, int addrlen);
	int Listen(int sockfd, int backlog);
	int Close(int fd);
}