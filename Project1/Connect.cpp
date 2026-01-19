#include "Connect.h"
#include <windows.h>

Connect::Connect()
{
	m_conntype = 1;
	memset((char*)&m_ncfg, 0, sizeof(NetCfg));
}

Connect::~Connect()
{
}

Connect* Connect::GetInstance()
{
	static Connect* lp = NULL;

	if (lp == NULL)
	{
		lp = new Connect;
	}

	return lp;
}

void Connect::ResetConnect()
{
	ResetConfigReg();
}

Conn* Connect::NewConnect()
{
	while (1)
	{
		memset(&m_ncfg, 0, sizeof(NetCfg));

		if (GetHost(&m_ncfg.ConnCfg.hs))
		{
			break;
		}

		if (strlen(m_ncfg.ConnCfg.hs.szIp) == 0 || m_ncfg.ConnCfg.hs.wPort == 0)
		{
			continue;
		}

		Conn* conn = ConnFacto::CreateConnect2(m_ncfg.ConnCfg.hs.wType, m_ncfg.ConnCfg.hs.wFlag, m_ncfg.ConnCfg.hs.szIp, m_ncfg.ConnCfg.hs.wPort);
		if (conn)
		{
			m_conntype = 1;
			return conn;
		}
	}
	return NULL;
}
