#pragma once

#include <memory>
#include "conn.h"
#include "cotp.h"
class ConnFacto
{
public:
    //static std::shared_ptr<Conn> CreateConnect(int connType, int flag, char* server, int port);
    static Conn* CreateConnect2(int connType, int flag, char* server, int port);
};