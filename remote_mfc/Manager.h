#pragma once
#include "../common/net/conn.h"

class CremotemfcDlg;
class Manager : public std::enable_shared_from_this<Manager>
{
public:
	Manager(CremotemfcDlg* pMainWindow, std::shared_ptr<Conn> pConn);
	~Manager();

	void Run();
private:
	int RequestHostinfo();
private:
	CremotemfcDlg* m_pMainWindow;
	std::shared_ptr<Conn> m_pConn;
};

