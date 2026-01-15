#include "cotp.h"

int ConnTypeFromStr(const char* type)
{
    std::string strType = type;

    if (strType == "tcp")
    {
        return CONN_TYPE_TCP;
    }
    return 0;
}
