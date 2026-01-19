#pragma once
#include "../common/net/Conn.h"
#include "../common/proto.h"
class CremotemfcDlg;
class Service
{
public:
	Service(CremotemfcDlg* pMainWindow);
	void Run(std::shared_ptr<Conn> pConn);
private:
	void HandleMainConn(std::shared_ptr<Conn> pConn);
private:
	CremotemfcDlg* m_pMainWindow;
};

