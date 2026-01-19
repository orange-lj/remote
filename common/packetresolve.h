#pragma once

#include <memory>
#include "net/conn.h"
#include "proto.h"

int ReadPacket(std::shared_ptr<Conn> pConn, PACKET_HEADER* pPacketHeader, std::string& data);


