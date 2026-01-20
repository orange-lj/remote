#pragma once
#include<string>
#define CONN_TYPE_TCP	0x0001

int ConnTypeFromStr(const char* type);

const char* ConnTypeToStr(int connType);