#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <mstcpip.h>

namespace SockApi {
	int Socket(int domain, int type, int protocol, int& sockfd);
}