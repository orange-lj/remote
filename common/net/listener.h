#pragma once
#include "conn.h"

class Listener {
public:
	virtual int Start() = 0;
	virtual std::shared_ptr<Conn> Accept() = 0;
};