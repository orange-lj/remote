#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listenersmanager.h"
#include "taskengine.h"
#include "checklist.h"
#include "tunnelhelpserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //make_shared一个智能指针对象m_pListenersManager，执行ListenersManager构造
    m_pListenersManager = std::make_shared<ListenersManager>(this);
    //new一个任务引擎对象，并传递MainWindow对象
    m_pTaskEngine = new TaskEngine(this);
    //new一个CheckList对象
    m_pCheckList = new CheckList();
    //make_shared一个智能指针对象m_pTunnelHelpServer
    m_pTunnelHelpServer=std::make_shared<TunnelHelpServer>(this);
    m_pTunnelHelpServer->Start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

