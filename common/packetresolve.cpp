#include "packetresolve.h"

int ReadPacket(std::shared_ptr<Conn> pConn, PACKET_HEADER* pPacketHeader, std::string& data)
{
    int error = 0;

    error = pConn->RecvAll((char*)pPacketHeader, sizeof(PACKET_HEADER));

    if (error)
    {
        return error;
    }

    if (pPacketHeader->length > 100 * 1024 * 1024)
    {
        return 1;
    }

    if (pPacketHeader->length == 0)
    {
        data.clear();
        return 0;
    }

    data.clear();
    data.resize(pPacketHeader->length);

    error = pConn->RecvAll((char*)data.c_str(), pPacketHeader->length);
    return error;
}
