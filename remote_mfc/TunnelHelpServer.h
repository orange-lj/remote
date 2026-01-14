#pragma once
#include <atomic>
#include "common/net/Listener.h"
class CremotemfcDlg;
class TunnelHelpServer
{
public:
    TunnelHelpServer(CremotemfcDlg* pMainWindow);
	~TunnelHelpServer();
	int Start();
private:
	CremotemfcDlg* m_pMainWindow;
	std::shared_ptr<Listener> m_listener;
	int m_listenPort;
	std::atomic<int> m_connId;
	bool m_bRunning;
};

