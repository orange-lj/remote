#include "other.h"

CPlgOhter::CPlgOhter()
{

}


CPlgOhter::~CPlgOhter()
{

}

CPlgOhter* CPlgOhter::GetInstance()
{
	static CPlgOhter* lp = NULL;

	if (lp == NULL)
	{
		lp = new CPlgOhter;
	}

	return lp;
}

int CPlgOhter::Load(HMODULE hmodule)
{
	return GetPlgMap()->PlgLoad(hmodule, CMD_PULG_OTHER, OnRecv, "other");
}

int __stdcall CPlgOhter::OnRecv(HANDLE con, PACKET_HEADER* pkt)
{
	switch (pkt->cmd)
	{
	case CMD_INFO: return OnOnlineInfo(con, pkt); break;
	}
	return -1;
}

int CPlgOhter::OnOnlineInfo(HANDLE con, PACKET_HEADER* pkt)
{
	int error = 0;

	struct sockaddr_in clientAddr;
	int namelen = sizeof(clientAddr);

	GetPlgMap()->PlgSockName(con, (struct sockaddr*)&clientAddr, &namelen);

	std::string info = UtGetOnlineInfo(inet_ntoa(clientAddr.sin_addr));
	return 0;
}

PLGFUNC* CPlgOhter::GetPlgMap()
{
	static PLGFUNC* pi = NULL;

	if (pi)
	{
		return pi;
	}

	WCHAR name[32] = { 0 };

	wsprintfW(name, PLUG_MAP_NAME, GetCurrentProcessId());

	HANDLE hmap;

	if (NULL == (hmap = OpenFileMappingW(FILE_MAP_READ, FALSE, name)))
	{
		return NULL;
	}

	if (NULL == (pi = (PLGFUNC*)MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0)))
	{
		return NULL;
	}

	CloseHandle(hmap);

	return pi;
}
