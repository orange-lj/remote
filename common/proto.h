#pragma once

#include <stdint.h>

#pragma pack(push)
#pragma pack(1)
typedef struct PacketHeder
{
    uint64_t id;
    uint32_t length;
    uint32_t error;
    uint32_t cmd;
} PACKET_HEADER, * PPACKET_HEADER;
#pragma pack(pop)


#define CMD_PULG_OTHER              0x00000001
#define CMD_MAIN_CONN               0x00000100
#define CMD_INFO                    0x00000101
#define CMD_SUB_CONN                0x0000010d