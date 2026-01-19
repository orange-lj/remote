#include "utils.h"

std::string UtGetOnlineInfo(std::string lanip)
{
    return UtGetId() + "\t" + UtGetSid() + "\t" + UtGetHostName() + "\t" + lanip + "\t" + UtGetUserName() + "\t" + UtGetPid() + "\t" + UtGetOs() + "\t" + UtOsType() + "\t" + UtOsBits();
}
