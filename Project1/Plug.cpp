#include "Plug.h"
#include "other.h"

Plug::Plug()
{
	memset(m_plug, 0, sizeof(PLGINFO) * MAX_PLUG_COUNT);
}

Plug::~Plug()
{

}

int Plug::PlugLoad(HMODULE hmodule, int id, FPlgRecvPkt OnRecv, const char* name)
{
	if (id >= MAX_PLUG_COUNT)
	{
		return (ERROR_NOT_ENOUGH_QUOTA);
	}

	m_cs.Enter();

	if (m_plug[id].h)
	{
		m_cs.Leave();

		return (ERROR_ALREADY_EXISTS);
	}

	m_plug[id].ref = 1;
	m_plug[id].h = hmodule;
	m_plug[id].OnRecv = OnRecv;
	wsprintfA(m_plug[id].name, name);

	m_cs.Leave();
	return 0;
}

int Plug::OnLoadPlug(HANDLE con, PACKET_HEADER* pkt)
{
	int error;
	int nlen = pkt->length;
	char* buf = (char*)malloc(nlen);

	if (error = PlgRecvAll(con, buf, nlen, WAIT_TIMES))
	{
		free(buf);
		return error;
	}

	DWORD namelen, datalen;

	memcpy(&namelen, buf, 4);
	memcpy(&datalen, buf + 4, 4);

	char* pname = buf + 8;
	char* pdata = buf + 8 + namelen;

	error = LoadPlg(pdata, datalen);

	free(buf);

	pkt->error = error;
	pkt->length = 0;
	if (error = PlgSendAll(con, (char*)pkt, sizeof(PACKET_HEADER)))
	{
		return error;
	}

	return error;
}

int Plug::LoadPlg(char* buf, int nlen)
{
	HMODULE h = LoadModule(buf);
	if (h)
	{
		int ret = CallPlg(h, DLL_PROCESS_ATTACH);
		if (ret)
		{
			VirtualFree((LPVOID)h, 0, MEM_RELEASE);
		}
		return ret;
	}

	return 1;
}

HMODULE Plug::LoadModule(char* buf)
{
	IMAGE_DOS_HEADER* lpDos = (IMAGE_DOS_HEADER*)buf;

	if (lpDos->e_magic != 0x5A4D)
	{
		return NULL;
	}

	IMAGE_NT_HEADERS* lpNtHeader = (IMAGE_NT_HEADERS*)((DWORD_PTR)lpDos + lpDos->e_lfanew);
	if (lpNtHeader->Signature != 0x4550)
	{
		return NULL;
	}

	PIMAGE_SECTION_HEADER lpSectionHeader = IMAGE_FIRST_SECTION(lpNtHeader);
	if (lpSectionHeader == NULL)
	{
		return NULL;
	}

	DWORD ImageSize = lpNtHeader->OptionalHeader.SizeOfImage;
	if (ImageSize == 0)
	{
		return NULL;
	}
	void* pMemoryAddress = VirtualAlloc((LPVOID)NULL, ImageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (pMemoryAddress == NULL)
	{
		return NULL;
	}

	int  HeaderSize = lpNtHeader->OptionalHeader.SizeOfHeaders;
	int  SectionSize = lpNtHeader->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
	int  MoveSize = HeaderSize + SectionSize;

	memmove(pMemoryAddress, buf, MoveSize);

	for (int i = 0; i < lpNtHeader->FileHeader.NumberOfSections; ++i)
	{
		if (lpSectionHeader[i].VirtualAddress == 0 || lpSectionHeader[i].SizeOfRawData == 0)
			continue;
		void* pSectionAddress = (void*)((DWORD_PTR)pMemoryAddress + lpSectionHeader[i].VirtualAddress);
		memcpy((void*)pSectionAddress, (void*)((DWORD_PTR)lpDos + lpSectionHeader[i].PointerToRawData), lpSectionHeader[i].SizeOfRawData);
	}

	lpDos = (PIMAGE_DOS_HEADER)pMemoryAddress;
	lpNtHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)pMemoryAddress + (lpDos->e_lfanew));
	lpSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD_PTR)lpNtHeader + sizeof(IMAGE_NT_HEADERS));

	PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((DWORD_PTR)pMemoryAddress + lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

	DWORD_PTR delta = (DWORD_PTR)pMemoryAddress - lpNtHeader->OptionalHeader.ImageBase;

	while ((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0)
	{
		WORD* pLocData = (WORD*)((DWORD_PTR)pLoc + sizeof(IMAGE_BASE_RELOCATION));

		int NumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
		for (int i = 0; i < NumberOfReloc; i++)
		{
			switch ((WORD)pLocData[i] >> 12)
			{
			case IMAGE_REL_BASED_HIGHLOW:
				*(DWORD_PTR*)((DWORD_PTR)pMemoryAddress + pLoc->VirtualAddress + ((WORD)pLocData[i] & 0x0fff)) += (DWORD_PTR)delta;
				break;
			case IMAGE_REL_BASED_DIR64:
				*(PULONGLONG)((DWORD_PTR)pMemoryAddress + pLoc->VirtualAddress + ((WORD)pLocData[i] & 0x0fff)) += delta;
				break;
			}
		}
		pLoc = (PIMAGE_BASE_RELOCATION)((DWORD_PTR)pLoc + pLoc->SizeOfBlock);
	}

	PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD_PTR)pMemoryAddress + lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	while (pID->Characteristics != 0)
	{
		PIMAGE_THUNK_DATA pRealIAT = (PIMAGE_THUNK_DATA)((ULONG_PTR)pMemoryAddress + pID->FirstThunk);
		PIMAGE_THUNK_DATA pOriginalIAT = (PIMAGE_THUNK_DATA)((ULONG_PTR)pMemoryAddress + pID->OriginalFirstThunk);

		char* pName = (char*)((ULONG_PTR)pMemoryAddress + pID->Name);

		HMODULE hDll = GetModuleHandleA(pName);
		if (hDll == NULL)
		{
			hDll = LoadLibraryA(pName);
		}

		for (int i = 0; ; i++)
		{
			if (pOriginalIAT[i].u1.Function == 0)
				break;

			FARPROC lpFunction = NULL;

			if (pOriginalIAT[i].u1.Ordinal & IMAGE_ORDINAL_FLAG)
			{
				lpFunction = (FARPROC)GetProcAddress(hDll, (LPCSTR)(pOriginalIAT[i].u1.Ordinal & 0x0000FFFF));
			}
			else
			{
				PIMAGE_IMPORT_BY_NAME pByName = (PIMAGE_IMPORT_BY_NAME)((ULONG_PTR)pMemoryAddress + (ULONG_PTR)(pOriginalIAT[i].u1.AddressOfData));
				lpFunction = (FARPROC)GetProcAddress(hDll, (char*)pByName->Name);
			}

			if (lpFunction != NULL)
			{
				pRealIAT[i].u1.Function = (ULONG_PTR)lpFunction;
			}
			else
			{
				VirtualFree(pMemoryAddress, 0, MEM_RELEASE);
				return NULL;
			}
		}

		++pID;
	}

	DWORD_PTR exfunc = MyGetProcAddress((HMODULE)pMemoryAddress, "fmain");

	if (exfunc == 0)
	{
		VirtualFree(pMemoryAddress, 0, MEM_RELEASE);
		return NULL;
	}

	*(DWORD_PTR*)pMemoryAddress = exfunc;

	return (HMODULE)pMemoryAddress;
}

DWORD_PTR Plug::MyGetProcAddress(HMODULE hModule, const char* lpProcName)
{
	PIMAGE_DOS_HEADER lpDos = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS lpNtHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)hModule + (lpDos->e_lfanew));

	if (lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0 || lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size == 0)
	{
		return 0;
	}

	PIMAGE_EXPORT_DIRECTORY pImageExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR)hModule + lpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	DWORD* pAddressOfFunction = (DWORD*)(pImageExportDirectory->AddressOfFunctions + (DWORD_PTR)hModule);
	DWORD* pAddressOfNames = (DWORD*)(pImageExportDirectory->AddressOfNames + (DWORD_PTR)hModule);
	DWORD dwNumberOfNames = (DWORD)(pImageExportDirectory->NumberOfNames);

	WORD* pAddressOfNameOrdinals = (WORD*)(pImageExportDirectory->AddressOfNameOrdinals + (DWORD_PTR)hModule);

	for (int i = 0; i < (int)dwNumberOfNames; i++)
	{
		char* strFunction = (char*)(pAddressOfNames[i] + (DWORD_PTR)hModule);
		if (lstrcmpA(lpProcName, strFunction) == 0)
		{
			return (pAddressOfFunction[pAddressOfNameOrdinals[i]] + (DWORD_PTR)hModule);
		}
	}

	return 0;
}

int Plug::CallPlg(HMODULE h, int type)
{
	typedef int (*FMain)(HMODULE hModule, DWORD  ul_reason_for_call);

	DWORD_PTR callfun = *(DWORD_PTR*)h;

	FMain main = (FMain)callfun;

	return main(h, type);
}

void Plug::start()
{
	WCHAR name[32] = { 0 };

	wsprintfW(name, PLUG_MAP_NAME, GetCurrentProcessId());

	HANDLE hmap;

	if (NULL == (hmap = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(PLGFUNC), name)))
	{
		return;
	}

	PLGFUNC* pi = NULL;

	if (NULL == (pi = (PLGFUNC*)MapViewOfFile(hmap, FILE_MAP_WRITE, 0, 0, 0)))
	{
		return;
	}

	pi->PlgLoad = PlgLoad;
	pi->PlgSockName = PlgSockName;
	pi->PlgSendAll = PlgSendAll;
	pi->PlgRecvAll = PlgRecvAll;
	DWORD op;

	VirtualProtect(pi, sizeof(PLGFUNC), PAGE_READONLY, &op);

	CPlgOhter::GetInstance()->Load(HMODULE(-1));
}

Plug* Plug::GetInstance() {

	static Plug* lp = NULL;

	if (lp == NULL)
	{
		lp = new Plug;
	}

	return lp;
}

int Plug::OnRecv(HANDLE con, PACKET_HEADER* pkt)
{
	switch (pkt->cmd)
	{
	case CMD_PLUGIN_LOAD: return OnLoadPlug(con, pkt); break;
	default: break;
	}
	for (int i = 0; i < MAX_PLUG_COUNT; i++)
	{
		BOOL caller;

		m_cs.Enter();

		if (m_plug[i].h)
		{
			caller = TRUE; m_plug[i].ref++;
		}
		else
		{
			caller = FALSE;
		}

		m_cs.Leave();

		if (!caller)
		{
			continue;
		}

		int ercode = m_plug[i].OnRecv(con, pkt);

		m_cs.Enter();

		if (m_plug[i].h)
		{
			m_plug[i].ref--;
		}

		m_cs.Leave();

		if (ercode != (-1))
		{
			return (ercode);
		}
	}

	return 0;
}
