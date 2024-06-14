#include "tunnelhelpserver.h"
#include "common/net/listenerfactory.h"
TunnelHelpServer::TunnelHelpServer(MainWindow *pMainWindow)
    :m_pMainWindow(pMainWindow),
      m_listenPort(6789),
      m_connId(1),
      m_bRunning(true)
{

}

int TunnelHelpServer::Start()
{
    m_listener = ListenerFactory::CreateListener(CONN_TYPE_TCP,0,m_listenPort);
    if(!m_listener)
    {
        return 1;
    }
    //创建，绑定，监听
    int error = m_listener->Start();
    if (error)
    {
        return error;
    }
    m_listenThread = std::thread(ListenThread, shared_from_this());
    return 0;
}

void TunnelHelpServer::ListenThread(std::shared_ptr<TunnelHelpServer> pSelf)
{
    pSelf->ListenWorker();
}

void TunnelHelpServer::ListenWorker()
{
    while(true)
    {
        //accept等待，如果有连接，返回一个Conn智能指针对象
        std::shared_ptr<Conn> pConn = m_listener->Accept();
        if (!pConn)
        {
            break;
        }
        std::thread t(ServiceThread,shared_from_this(),pConn);
        t.detach();
    }
}

void TunnelHelpServer::ServiceThread(std::shared_ptr<TunnelHelpServer> pSelf, std::shared_ptr<Conn> pConn)
{
    pself->ServiceWorker(pConn);
}

void TunnelHelpServer::ServiceWorker(std::shared_ptr<Conn> pConn)
{
    int error = 0;
    char sidLength;
    error = pConn->RecvAll()

}
