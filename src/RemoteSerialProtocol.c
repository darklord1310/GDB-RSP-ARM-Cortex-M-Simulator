#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "RemoteSerialProtocol.h"
#include "Packet.h"

const char hex[] = "0123456789abcdef";

/*
 * This function handle all the query packet receive from
 * gdb client and return the appropriate message back to it
 *
 * Input:
 *      data    packet receive from gdb client
 *
 * Return:
 *      packet  complete packet to reply to gdb client
 */
char *handleQueryPacket(char *data)
{
    char *packet = NULL;

    if(data[2] == 'P' || data[2] == 'C' || data[2] == 'L')
    {
        if(strncmp("CRC", &data[2], strlen("CRC")) == 0)
            packet = gdbCreateMsgPacket("E01");     // error "E01" => CRC query not supported
        else
            packet = gdbCreateMsgPacket("");
    }
    else
    {
        if(strncmp("Supported", &data[2], strlen("Supported")) == 0)
            packet = gdbCreateMsgPacket("qRelocInsn-");
        else if(strncmp("Attached", &data[2], strlen("Attached")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("TStatus", &data[2], strlen("TStatus")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("fThreadInfo", &data[2], strlen("fThreadInfo")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("Offsets", &data[2], strlen("Offsets")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("Symbol::", &data[2], strlen("Symbol::")) == 0)
            packet = gdbCreateMsgPacket("");
        else
        {
            packet = gdbCreateMsgPacket("");
            printf("Unrecognized RSP query");
        }
    }

    return packet;
}

char *readSingleRegister(char *data)
{
    char *packet = NULL;
    int regNum, regValue, i = 0, bits = 32, maskBits = 0xf;
    char asciiString[9] = "";

    sscanf(&data[2], "%2x", &regNum);
    printf("Reg no: %d\n", regNum);

    if(regNum <= 12)        //R0 - R12 is GPR
        regValue = 0x00000000;
    else if(regNum == 13)   //R13 is Stack Pointer
        regValue = 0x11111111;
    else if(regNum == 14)   //R14 is Link Register
        regValue = 0x22222222;
    else if(regNum == 15)   //R15 is Program Counter
        regValue = 0x33333333;
    else if(regNum == 16)   //R16 is Special-purpose Program Status Registers
        regValue = 0x44444444;

    printf("Reg val: %x\n", regValue);

    for(i = 0; i < 8; i++)
    {
        asciiString[i] = hex[regValue >> (bits - 4) & maskBits];
        bits -= 4;
    }
    asciiString[8] = '\0';
    
    printf("ASCII String: %s\n", asciiString);

    packet = gdbCreateMsgPacket(asciiString);  //simply reply to test

    return packet;
}

char *readRegister()
{

}