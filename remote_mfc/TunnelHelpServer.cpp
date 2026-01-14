#include "pch.h"
#include "TunnelHelpServer.h"
#include "common/net/LisFacto.h"

TunnelHelpServer::TunnelHelpServer(CremotemfcDlg* pMainWindow)
	: m_pMainWindow(pMainWindow),
	m_listenPort(6789),
	m_connId(1),
	m_bRunning(true)
{

}

TunnelHelpServer::~TunnelHelpServer()
{
}

int TunnelHelpServer::Start()
{
	m_listener = LisFacto::CreateListener(CONN_TYPE_TCP, 0, m_listenPort);
	return 0;
}
