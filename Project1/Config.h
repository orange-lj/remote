#pragma once


#pragma pack(push)
#pragma pack(1)
typedef struct sHostProxy
{
	unsigned short  wPort;
	char  cHost[64];
	char  cUser[64];
	char  cPass[64];
}HostProxy, * PHostProxy;

typedef struct sHost
{
	unsigned short  wFlag;
	unsigned short  wType;
	unsigned short  wPort;
	char  szIp[64];
}HOST, * PHOST;

typedef struct sConnConfig
{
	HOST hs[3];
	HostProxy hp;
	unsigned char cbSleep[4];
}CONNCONFIG, * PCONNCONFIG;

typedef struct sListenConfig
{
	unsigned short  wFlag;
	unsigned short  wType;
	unsigned short  wPort;
}LISTENCONFIG;

typedef struct sConfig
{
	unsigned long  key;
	int type;
	union
	{
		CONNCONFIG cconfig;
		LISTENCONFIG lconfig;
	};
}CONFIG, * PCONFIG;
#pragma pack(pop)



void ResetConfigReg();
int GetHost(PHOST hs);