QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/head

SOURCES += \
    checklist.cpp \
    common/net/conn.cpp \
    common/net/listenerfactory.cpp \
    common/net/pevents.cpp \
    common/net/socketapi.cpp \
    common/net/tcpconn.cpp \
    common/net/tcplistener.cpp \
    listenersmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    svgiconengine.cpp \
    taskengine.cpp \
    tunnelhelpserver.cpp

HEADERS += \
    checklist.h \
    common/net/conn.h \
    common/net/conntype.h \
    common/net/listener.h \
    common/net/listenerfactory.h \
    common/net/pevents.h \
    common/net/socketapi.h \
    common/net/tcpconn.h \
    common/net/tcplistener.h \
    listenersmanager.h \
    mainwindow.h \
    svgiconengine.h \
    taskengine.h \
    tunnelhelpserver.h

FORMS += \
    mainwindow.ui

LIBS += -lws2_32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
