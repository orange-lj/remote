#pragma once
#include <memory>
#include "Listener.h"
#include "cotp.h"
class LisFacto {
public:
	static std::shared_ptr<Listener> CreateListener(int connType, int flag, int bindPort);
};
