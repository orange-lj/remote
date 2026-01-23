#pragma once
#include "plg.h"
#include "../common/utils.h"
#include "../common/net/conn.h"
#pragma pack(push)
#pragma pack(1)
typedef struct _PlgInfo
{
	int ref;
	HMODULE h;
	FPlgRecvPkt OnRecv;
	char name[32];
}PLGINFO, * PPLGINFO;
#pragma pack(pop)

class Plug
{
private:
	Plug();
	~Plug();
	int PlugLoad(HMODULE hmodule, int id, FPlgRecvPkt OnPacket,const char* name);
	int OnLoadPlug(HANDLE con, PACKET_HEADER* pkt);
	int LoadPlg(char* buf, int nlen);
	HMODULE LoadModule(char* buf);
	DWORD_PTR MyGetProcAddress(HMODULE hModule,const char* lpProcName);
	int CallPlg(HMODULE h, int type);
	static int WINAPI PlgLoad(HMODULE hmodule, int id, FPlgRecvPkt OnPacket,const char* name)
	{
		return Plug::GetInstance()->PlugLoad(hmodule, id, OnPacket, name);
	}
	static int WINAPI PlgSockName(HANDLE con, struct sockaddr* name, int* namelen)
	{
		return ((Conn*)con)->SockName(name, namelen);
	}
	static int WINAPI PlgSendAll(HANDLE con, char* buf, int bytesToSend)
	{
		return ((Conn*)con)->SendAll(buf, bytesToSend);
	}
	static int WINAPI PlgRecvAll(HANDLE con, char* buf, int bytesToRecv, uint64_t times)
	{
		return ((Conn*)con)->RecvAll(buf, bytesToRecv, times);
	}
public:
	void start();
	static Plug* GetInstance();
	int OnRecv(HANDLE con, PACKET_HEADER* pkt);
private:
	CLock m_cs;
	PLGINFO m_plug[MAX_PLUG_COUNT];
};

