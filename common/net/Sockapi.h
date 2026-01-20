#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <mstcpip.h>

namespace SockApi {
	int Socket(int domain, int type, int protocol, int& sockfd);
	int Bind(int sockfd, const struct sockaddr* addr, int addrlen);
	int Listen(int sockfd, int backlog);
	int Connect(int sockfd, const struct sockaddr* name, int namelen);
	int Accept(int sockfd, struct sockaddr* addr, int* addrlen, int& clientfd);
	int Send(int sockfd, const void* buf, int len, int& bytesWritten);
	int Recv(int sockfd, void* buf, int len, int& bytesRead);
	int GetAddrInfo_x(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res);
	int FreeAddrInfoWrap_x(struct addrinfo* res);
	int Shutdown(int sockfd);
	int Close(int fd);
	int Getsockname(int sockfd, struct sockaddr* addr, int* addrlen);
	int Getpeername(int sockfd, struct sockaddr* addr, int* addrlen);
}