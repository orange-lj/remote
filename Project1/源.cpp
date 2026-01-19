#include <WinSock2.h>
#include <windows.h>
#include "plug.h"
#include "NetCore.h"
#pragma comment(lib, "ws2_32.lib")


int main() 
{
	WSADATA data;

	WSAStartup(MAKEWORD(2, 2), &data);

	Plug::GetInstance()->start();

	NetCore network;
	network.start();
}