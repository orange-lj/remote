#pragma once
#include "connect.h"
#include <windows.h>
class NetCore
{
public:
	NetCore();
	~NetCore();
public:
	void start();
private:
	void Work(Conn* con, int type, DWORD connid);
};

