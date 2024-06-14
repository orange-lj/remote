#ifndef LISTENER_H
#define LISTENER_H
#include <memory>
#include "conn.h"


class Listener
{
public:
    virtual int Start() = 0;
    virtual std::shared_ptr<Conn> Accept() = 0;
};

#endif // LISTENER_H
