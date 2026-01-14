#ifndef LISTENERFACTORY_H
#define LISTENERFACTORY_H

#include<memory>
#include"listener.h"
#include"conntype.h"

class ListenerFactory
{
public:
    static std::shared_ptr<Listener> CreateListener(int connType,int flag,int bindPort);
};

#endif // LISTENERFACTORY_H
