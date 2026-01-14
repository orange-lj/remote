#include "taskengine.h"

TaskEngine::TaskEngine(MainWindow* pMainWindow,QObject *parent)
    : QObject(parent),
      m_pMainWindow(pMainWindow),
      m_tidCounter(10)
{
    //connect()
}
