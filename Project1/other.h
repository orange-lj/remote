#pragma once
#include "plug.h"

class CPlgOhter
{
private:
	CPlgOhter();
	~CPlgOhter();
public:
	static CPlgOhter* GetInstance();
public:
	int Load(HMODULE hmodule);
private:
	static int WINAPI OnRecv(HANDLE con, PACKET_HEADER* pkt);
	static int OnOnlineInfo(HANDLE con, PACKET_HEADER* pkt);
private:
	static PLGFUNC* GetPlgMap();
};

