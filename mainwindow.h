#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class ListenersManager;
class TaskEngine;
class CheckList;
class TunnelHelpServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<ListenersManager> m_pListenersManager;
    TaskEngine *m_pTaskEngine;
    CheckList* m_pCheckList;
    std::shared_ptr<TunnelHelpServer> m_pTunnelHelpServer;
};
#endif // MAINWINDOW_H
