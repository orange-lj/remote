#pragma once
#include "../common/ch.h"

class PlgFile
{
private:
	PlgFile();
public:
	static PlgFile* GetInstance();
public:
	int Load(HMODULE hmodule);
private:
	static int WINAPI OnRecv(HANDLE con, PACKET_HEADER* pkt);
	static int OnEnumDisk(HANDLE con, PACKET_HEADER* pkt);
	static PLGFUNC* GetPlgMap();
};

