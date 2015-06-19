#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include "Packet.h"

const char hex[] = "0123456789abcdef";

/*
 * This function make the data to become complete packet
 * of data before send it back to gdb
 *
 * Input:
 *      data        string of data (data without '$', '#' and checksum)
 *
 * Return:
 *      packet      complete string of data ( $<data>#<XS> in hex )
 */
char *completePacket(char *data)
{
    int length = strlen(data) + 5, i;
    char *packet = malloc(length);
    uint8_t chksum = 0;

    packet[0] = '$';

    for(i = 0; i < strlen(data); i++)
    {
        packet[i + 1] = data[i];
        chksum += data[i];
    }

    packet[strlen(data) + 1] = '#';
    packet[strlen(data) + 2] = hex[chksum >> 4];
    packet[strlen(data) + 3] = hex[chksum & 0x0f];

    if(packet[strlen(data) + 4] != '\0')
        packet[strlen(data) + 4] = '\0';

    return  packet;
}