#include "pch.h"
#include "Manager.h"
#include "../common/proto.h"
#include "../common/net/Tcpconn.h"
#include "../common/packetresolve.h"
#include <sstream>
#include <afx.h>

Manager::Manager(CremotemfcDlg* pMainWindow, std::shared_ptr<Conn> pConn)
    : m_pConn(pConn),
    m_pMainWindow(pMainWindow)
{

}

Manager::~Manager()
{
}

void Manager::Run()
{
    int error;

    error = RequestHostinfo();
    if (error)
    {
        return;
    }

    auto pPrev = m_pMainWindow->RegistManageServer(m_hostinfo.get(HostInfo::SESSIONID), shared_from_this());
    if (pPrev)
    {
        pPrev->Disconnect();
    }
    m_pMainWindow->UpdateHostInfo(m_hostinfo);

    m_writeThread = std::thread(WriteThread, shared_from_this());

    while (true)
    {
        PACKET_HEADER header;
        std::string data;

        error = ReadPacket(m_pConn, &header, data);
        if (error)
        {
            break;
        }

        error = ProcessPacket(&header, data);
        if (error)
        {
            break;
        }
    }
}

void Manager::Disconnect()
{
    m_pConn->CloseNotify();
    m_pConn->Close();
}

void Manager::Write(std::string& packet)
{
    std::lock_guard<std::mutex> guard(m_lock);

    if (m_writeQueue.size() > 1000)
    {
        //remove old packet
        m_writeQueue.pop();
    }

    m_writeQueue.push(packet);
}

int Manager::RequestHostinfo()
{
    int error = 0;

    PACKET_HEADER header = { 0 };

    header.cmd = CMD_INFO;

    error = m_pConn->SendAll((char*)&header, sizeof(PACKET_HEADER));

    if (error)
    {
        return error;
    }
    std::string data;
    error = ReadPacket(m_pConn, &header, data);
    if (error)
    {
        return error;
    }

    //按照\t对data进行分割
    std::vector<std::string> vecStrTemp;
    std::string strTemp;
    std::istringstream iss(data);
    while (std::getline(iss, strTemp, '\t'))
    {
        //将分割出来的数据添加到HostInfo对象中
        vecStrTemp.push_back(strTemp);
    }
    std::string id = vecStrTemp[0];
    std::string sid = vecStrTemp[1];
    std::string hostname = vecStrTemp[2];
    std::string lan = vecStrTemp[3];
    std::string username = vecStrTemp[4];
    std::string pid = vecStrTemp[5];
    std::string os = vecStrTemp[6];
    std::string osType = vecStrTemp[7];
    std::string osArch = vecStrTemp[8];
    std::string protocol = ConnTypeToStr(m_pConn->GetConnType());
    std::string wan = m_pConn->PeerIp().c_str();
    std::string currentTime = CT2A(CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")).GetString());
    HostInfo hostinfo(id, sid, lan, wan, hostname, pid, username, os, osType, osArch, currentTime, HOST_STATUS_ONLINE, protocol);

    m_hostinfo = hostinfo;
    return 0;
}

void Manager::WriteThread(std::shared_ptr<Manager> pSelf)
{
    pSelf->WriterWorker();
}

void Manager::WriterWorker()
{
    int error = 0;

    while (!m_bStopWrite) {
    
        m_lock.lock();
        if (m_writeQueue.size() == 0)
        {
            m_lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }
        std::string packet = m_writeQueue.front();
        m_writeQueue.pop();
        m_lock.unlock();

        error = m_pConn->SendAll((char*)packet.c_str(), packet.length());
        if (error)
        {
            break;
        }
    }
}

int Manager::ProcessPacket(PACKET_HEADER* pHeader, std::string& data)
{
    return 0;
}
