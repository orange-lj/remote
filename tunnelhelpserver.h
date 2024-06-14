#ifndef TUNNELHELPSERVER_H
#define TUNNELHELPSERVER_H
#include<memory>
#include<atomic>
#include <thread>
#include "common/net/listener.h"
#include "common/net/conn.h"

class MainWindow;

class TunnelHelpServer : public std::enable_shared_from_this<TunnelHelpServer>
{
public:
    TunnelHelpServer(MainWindow *pMainWindow);
    int Start();
private:
    static void ListenThread(std::shared_ptr<TunnelHelpServer> pSelf);
    void ListenWorker();
    static void ServiceThread(std::shared_ptr<TunnelHelpServer> pSelf,std::shared_ptr<Conn> pConn);
    void ServiceWorker(std::shared_ptr<Conn> pConn);
private:
    MainWindow *m_pMainWindow;
    std::shared_ptr<Listener> m_listener;
    std::thread m_listenThread;
    std::thread m_timeoutCheckerThread;
    int m_listenPort;
    std::atomic<int> m_connId;
    bool m_bRunning;
};

#endif // TUNNELHELPSERVER_H
