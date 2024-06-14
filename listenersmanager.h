#ifndef LISTENERSMANAGER_H
#define LISTENERSMANAGER_H
#include <memory>

class MainWindow;

class ListenersManager : public std::enable_shared_from_this<ListenersManager>
{
public:
    ListenersManager(MainWindow* pMainWindow);
private:
    MainWindow* m_pMainWindow;
};

#endif // LISTENERSMANAGER_H
