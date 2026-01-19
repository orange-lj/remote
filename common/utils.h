#include <Windows.h>
#include <Shlwapi.h>
#include <Shlobj.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#pragma comment(lib, "Shlwapi.lib")
class CLock {
public:
	CLock()
	{
		InitializeCriticalSection(&m_cs);
	}
	~CLock()
	{
		DeleteCriticalSection(&m_cs);
	}

public:
	void Enter()
	{
		EnterCriticalSection(&m_cs);
	}

	void Leave()
	{
		LeaveCriticalSection(&m_cs);
	}

protected:

	CRITICAL_SECTION m_cs;
};



std::string UtGetOnlineInfo(std::string lanip);