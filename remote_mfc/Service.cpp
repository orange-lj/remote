#include "pch.h"
#include "Service.h"
#include "Manager.h"
#include "../common/packetresolve.h"
Service::Service(CremotemfcDlg* pMainWindow) :m_pMainWindow(pMainWindow)
{

}

void Service::Run(std::shared_ptr<Conn> pConn)
{
    int error = 0;
    PACKET_HEADER header;
    std::string data;

    error = ReadPacket(pConn, &header, data);
    if (error)
    {
        return;
    }

    if (header.cmd == CMD_MAIN_CONN)
    {
        HandleMainConn(pConn);
    }
    else
    {
        //Invalid connection
        pConn->Close();
        return;
    }
}

void Service::HandleMainConn(std::shared_ptr<Conn> pConn)
{
    std::shared_ptr<Manager> pServer = std::make_shared<Manager>(m_pMainWindow, pConn);

    pServer->Run();
}
