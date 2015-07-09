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

/*
 * This function convert HEX value to ASCII string
 *
 * Input:
 *      regVal      register value in HEX form
 *      bytes       number of bytes to convert to ASCII form
 *
 * Return:
 *      asciiString     HEX value in string form
 */
char *createdHexToString(unsigned int regVal, int bytes)
{
    // char asciiString[9] = "";
    char *asciiString = malloc(9);
    int i, bits = 32, maskBits = 0xf;

    switch(bytes)
    {
        case 3:
            regVal = regVal << 8;
            break;
        case 2:
            regVal = regVal << 16;
            break;
        case 1:
            regVal = regVal << 24;
            break;
        default:
            break;
    }
    
    for(i = 0; i < bytes * 2; i++)
    {
        asciiString[i] = hex[regVal >> (bits - 4) & maskBits];
        bits -= 4;
    }
    asciiString[bytes * 2] = '\0';

    return asciiString;
}

void destroyHexToString(char *asciiString)
{
    if(asciiString != NULL)
        free(asciiString);
}

unsigned int decodeTwoByte(unsigned int byteData)
{
    unsigned int msb, lsb;
    
    msb = byteData >> 8;
    lsb = byteData & 0xff;
    
    return (msb | lsb << 8);
}

unsigned int decodeFourByte(unsigned int byteData)
{
    unsigned int msb, lsb;
    
    msb = decodeTwoByte(byteData >> 16);
    lsb = decodeTwoByte(byteData & 0xffff);
    
    return (msb | lsb << 16);
}