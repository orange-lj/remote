#include "pch.h"
#include "HostInfo.h"
#include<sstream>
HostInfo::HostInfo()
{

}

std::string HostInfo::get(int col) const
{
    if (col < 0 || col >= COUNT)
    {
        return "";
    }
    else
    {
        return m_values[col];
    }
}

void HostInfo::set(int col, std::string value)
{
    m_values[col] = value;
}

std::string HostInfo::toString()
{
    std::ostringstream oss;

    for (int i = 0; i < HostInfo::COUNT; i++)
    {
        oss << m_values[i];
        if (i < HostInfo::COUNT - 1)  // 不是最后一个，添加制表符
        {
            oss << "\t";
        }
    }

    return oss.str();
}

HostInfo::HostInfo(std::string hostid, std::string sid, std::string lan, std::string wan, std::string hostname, std::string pid, std::string username, std::string os, std::string osType, std::string osArch, std::string lastTime, std::string online, std::string protocol)
{
    m_values[HOSTID] = hostid;
    m_values[SESSIONID] = sid;
    m_values[LANIP] = lan;
    m_values[WANIP] = wan;
    m_values[HOSTNAME] = hostname;
    m_values[PID] = pid;
    m_values[USERNAME] = username;
    m_values[OS] = os;
    m_values[OS_TYPE] = osType;
    m_values[OS_ARCH] = osArch;
    m_values[TIME] = lastTime;
    m_values[NODE_TYPE] = NODE_TYPE_ITEM;
    m_values[ONLINE] = online;
    m_values[PROTOCOL] = protocol;
}
