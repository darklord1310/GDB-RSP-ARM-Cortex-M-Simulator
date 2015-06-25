#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include "Packet.h"

const char hex[] = "0123456789abcdef";

/*
 * This function make the msg to become complete packet
 * of data before send it back to gdb
 *
 * Input:
 *      msg         string of data that required to response to gdb
 *                  (data without '$', '#' and checksum)
 *
 * Return:
 *      packet      complete string of data ( $<data>#<XS> in hex )
 */
char *gdbCreateMsgPacket(char *msg)
{
    int length = strlen(msg) + 5, i;
    char *packet = malloc(length);
    uint8_t chksum = 0;

    packet[0] = '$';

    for(i = 0; i < strlen(msg); i++)
    {
        packet[i + 1] = msg[i];
        chksum += msg[i];
    }

    packet[strlen(msg) + 1] = '#';
    packet[strlen(msg) + 2] = hex[chksum >> 4];
    packet[strlen(msg) + 3] = hex[chksum & 0x0f];
    packet[strlen(msg) + 4] = '\0';

    return  packet;
}

void destroyPacket(char *packet)
{
    if(packet != NULL)
        free(packet);
}