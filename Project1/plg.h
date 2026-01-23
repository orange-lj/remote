#pragma once
#include <Windows.h>
#include <string>
#include "../common/proto.h"
#define MAX_PLUG_COUNT 20
#define PLUG_MAP_NAME  L"PL[%x]"
#define WAIT_TIMES     30*1000
typedef int (WINAPI* FPlgRecvPkt)(HANDLE con, PACKET_HEADER* pkt);
typedef int (WINAPI* FPlgLoad)(HMODULE h, int id, FPlgRecvPkt OnRecv, const char* name);
typedef int (WINAPI* FPlgSockName)(HANDLE con, struct sockaddr* name, int* namelen);
typedef int (WINAPI* FPlgSendAll)(HANDLE con, char* buf, int bytesToSend);
typedef int (WINAPI* FPlgRecvAll)(HANDLE con, char* buf, int bytesToRecv, uint64_t times);


typedef struct _PlgFunc
{
	FPlgLoad PlgLoad;
	FPlgSockName PlgSockName;
	FPlgSendAll PlgSendAll;
	FPlgRecvAll PlgRecvAll;
}PLGFUNC, * PPLGFUNC;