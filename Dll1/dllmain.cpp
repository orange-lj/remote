// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "PlgFile.h"

extern "C" _declspec(dllexport) int fmain(HMODULE hModule, DWORD  ul_reason_for_call)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: return PlgFile::GetInstance()->Load(hModule);
    }

    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    return TRUE;
}

