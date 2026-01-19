#pragma once
#include "Config.h"
#include "../common/net/ConnFacto.h"
#include "../common/net/conn.h"
#include "../common/proto.h"
typedef struct sNetCfg
{
	union
	{
		struct
		{
			HOST hs;
			HostProxy hp;
		} ConnCfg;

		LISTENCONFIG lconfig;
	};
}NetCfg, * PNetCfg;


class Connect
{
private:
	Connect();
public:
	~Connect();
	static Connect* GetInstance();
	void ResetConnect();
	Conn* NewConnect();
private:
	NetCfg m_ncfg;
	int m_conntype;
};

