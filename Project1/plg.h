#pragma once
#include <Windows.h>
#include <string>
#include "../common/proto.h"
#define MAX_PLUG_COUNT 20
#define PLUG_MAP_NAME  L"PL[%x]"
typedef int (WINAPI* FPlgRecvPkt)(HANDLE con, PACKET_HEADER* pkt);
typedef int (WINAPI* FPlgLoad)(HMODULE h, int id, FPlgRecvPkt OnRecv, const char* name);
typedef int (WINAPI* FPlgSockName)(HANDLE con, struct sockaddr* name, int* namelen);
typedef int (WINAPI* FPlgSendAll)(HANDLE con, char* buf, int bytesToSend);


typedef struct _PlgFunc
{
	FPlgLoad PlgLoad;
	FPlgSockName PlgSockName;
	FPlgSendAll PlgSendAll;
}PLGFUNC, * PPLGFUNC;