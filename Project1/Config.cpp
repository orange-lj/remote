#include "Config.h"
#include "../common/bytearray.h"
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

int g_ipindex = 0;
CONFIG g_config = { 0 };
void ResetConfigReg()
{
	g_ipindex = 0;

	wchar_t wWorkPath[MAX_PATH] = { 0 };
	//获取当前进程所在路径
	//ExpandEnvironmentStringsW(L"%ALLUSERSPROFILE%\\DE", wWorkPath, MAX_PATH);
	if (GetModuleFileNameW(NULL, wWorkPath, MAX_PATH) > 0)
	{
		// 去掉文件名，只保留目录
		PathRemoveFileSpecW(wWorkPath);
	}
	wchar_t szWorkCfg[MAX_PATH] = { 0 };
	PathCombineW(szWorkCfg, wWorkPath, L"devenv.cfg");

	ByteArray byte4;
	byte4.ReadF(szWorkCfg);

	CONFIG* cfg = (CONFIG*)byte4.m_buffer;

	int cb = byte4.m_size;

	memcpy(&g_config, cfg, cb);
}

int GetHost(PHOST hs)
{
	while (g_ipindex < 4)
	{
		if (strlen(g_config.cconfig.hs[g_ipindex].szIp) && g_config.cconfig.hs[g_ipindex].wPort)
		{
			memcpy(hs, &g_config.cconfig.hs[g_ipindex], sizeof(HOST));
			g_ipindex++;
			return 0;
		}
		else
		{
			g_ipindex++;
		}
	}

	return 1;
}
