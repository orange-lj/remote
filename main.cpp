#include "mainwindow.h"
#include"svgiconengine.h"
#include<WinSock2.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    QApplication a(argc, argv);
    QApplication::setWindowIcon(SVGIconEngine::instance()->icon(":/icons/icons/app2.svg",QSize(32,32)));
    MainWindow w;
    w.show();
    return a.exec();
}
