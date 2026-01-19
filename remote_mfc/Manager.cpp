#include "pch.h"
#include "Manager.h"
#include "../common/proto.h"

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
}

int Manager::RequestHostinfo()
{
    int error = 0;

    PACKET_HEADER header = { 0 };

    header.cmd = CMD_INFO;

    error = m_pConn->SendAll((char*)&header, sizeof(PACKET_HEADER));
    MessageBoxA(0, 0, 0, 0);
    if (error)
    {
        return error;
    }


    return 0;
}
