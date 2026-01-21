#pragma once
#include <string>
#define NODE_TYPE_ITEM      "Item"
#define HOST_STATUS_ONLINE  "true"
#define HOST_STATUS_OFFLINE "false"
class HostInfo
{
public:
    enum
    {
        HOSTID,
        SESSIONID,
        LANIP,
        WANIP,
        HOSTNAME,
        PID,
        USERNAME,
        PROTOCOL,
        OS,
        OS_TYPE,
        OS_ARCH,
        TIME,
        ONLINE,
        NODE_TYPE,
        COUNT
    };
    HostInfo(std::string hostid, std::string sid, std::string lan, std::string wan, std::string hostname, std::string pid, std::string username, std::string os, std::string osType, std::string osArch, std::string lastTime, std::string online, std::string protocol);
    HostInfo();
    std::string getSid();
    std::string get(int col) const;
    void set(int col, std::string value);
    std::string toString();
private:
    std::string m_values[COUNT];
};

