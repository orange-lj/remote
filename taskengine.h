#ifndef TASKENGINE_H
#define TASKENGINE_H

#include <QObject>


class MainWindow;

class TaskEngine : public QObject
{
    Q_OBJECT
public:
    explicit TaskEngine(MainWindow* pMainWindow,QObject *parent = nullptr);

signals:
private:
    MainWindow* m_pMainWindow;
    std::atomic<uint64_t> m_tidCounter;
};

#endif // TASKENGINE_H
