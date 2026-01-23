#pragma once
#include "../common/net/conn.h"
#include "../common/proto.h"
#include "HostInfo.h"
#include "remote_mfcDlg.h"
#include<thread>
#include <queue>
class CremotemfcDlg;
class Manager : public std::enable_shared_from_this<Manager>
{
public:
	Manager(CremotemfcDlg* pMainWindow, std::shared_ptr<Conn> pConn);
	~Manager();

	void Run();
	void Disconnect();
	void Write(std::string& packet);
private:
	int RequestHostinfo();
	static void WriteThread(std::shared_ptr<Manager> pSelf);
	void WriterWorker();
	int ProcessPacket(PACKET_HEADER* pHeader, std::string& data);
	int ProcessPluginFileDisk(PACKET_HEADER* pHeader, std::string& data);
private:
	CremotemfcDlg* m_pMainWindow;
	std::shared_ptr<Conn> m_pConn;
	HostInfo m_hostinfo;
	std::thread m_writeThread;
	bool m_bStopWrite;
	std::mutex m_lock;
	std::queue<std::string> m_writeQueue;
};

