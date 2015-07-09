#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "RemoteSerialProtocol.h"
#include "Packet.h"
#include "ARMRegisters.h"
#include "ROM.h"

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

/*
 * This function read one of the 17 ARM registers and response
 * back the values of the request register
 *
 * Input:
 *      data    packet receive from gdb client
 *
 * Return:
 *      packet  complete packet with register values to reply to gdb client
 */
char *readSingleRegister(char *data)
{
    char *packet = NULL;
    int regNum;//, i = 0, bits = 32, maskBits = 0xf;
    unsigned int regValue, decodeVal;
    char *asciiString;

    sscanf(&data[2], "%2x", &regNum);
    assert(regNum <= 16);
    // printf("Reg no: %d\n", regNum);

    /* Testing
    if(regNum <= 12)        //R0 - R12 is GPR
        // regValue = 0x00000000;
        // regValue = coreReg->reg[regNum - 1].data;
    else if(regNum == 13)   //R13 is Stack Pointer
        regValue = 0x11111111;
    else if(regNum == 14)   //R14 is Link Register
        regValue = 0x22222222;
    else if(regNum == 15)   //R15 is Program Counter
        regValue = 0x33333333;
    else if(regNum == 16)   //R16 is Special-purpose Program Status Registers
        regValue = 0x44444444; */

    if(regNum <= 15)
        regValue = coreReg[regNum - 1];
    else
        regValue = coreReg[xPSR];

    // printf("Reg val: %x\n", regValue);

    /* Testing
    for(i = 0; i < 8; i++)
    {
        asciiString[i] = hex[regValue >> (bits - 4) & maskBits];
        bits -= 4;
    }
    asciiString[8] = '\0'; */

    decodeVal = decodeFourByte(regValue);
    asciiString = createdHexToString(decodeVal, 4);
    // printf("ASCII String: %s\n", asciiString);

    packet = gdbCreateMsgPacket(asciiString);
    destroyHexToString(asciiString);

    return packet;
}

/*
 * This function read all of the 17 ARM registers and response
 * back the value of all register
 *
 * Return:
 *      packet  complete packet with all registers values to reply to gdb client
 */
char *readAllRegister()
{
    char *packet = NULL, fullRegValue[140] = "";
    int i, j;
    unsigned int regValue[numberOfRegister], decodeVal;
    char *asciiString;

    for(i = 0; i < numberOfRegister; i++)
    {
        regValue[i] = coreReg[i];

        decodeVal = decodeFourByte(regValue[i]);
        asciiString = createdHexToString(decodeVal, 4);

        strcat(fullRegValue, asciiString);
        // printf("Full reg val: %s\n", fullRegValue);
        destroyHexToString(asciiString);
    }

    packet = gdbCreateMsgPacket(fullRegValue);

    return packet;
}

/*
 * This function write one of the 17 ARM registers
 *
 * Input:
 *      data    packet receive from gdb client
 */
void writeSingleRegister(char *data)
{
    int regNum, i, j = 0, bits = 32;
    char *addr = NULL;
    unsigned int regValue = 0x00000000, temp, decodeVal;

    sscanf(&data[2], "%2x", &regNum);
    assert(regNum <= 16);
    // printf("Reg no: %d\n", regNum);
    addr = strstr(data, "=") + 1;
    // printf("addr %s\n", addr);

    for(i = 0; i < 4 && addr[j] != '\0'; i++)
    {
        sscanf(&addr[j], "%2x", &temp);
        regValue = regValue | temp << (bits - 8);
        bits -= 8;
        j += 2;
    }

    // printf("Reg val: %x\n", regValue);
    decodeVal = decodeFourByte(regValue);
    coreReg[regNum] = decodeVal;
}

/*
 * This function write all of the 17 ARM registers
 *
 * Input:
 *      data    packet receive from gdb client
 */
void writeAllRegister(char *data)
{
    unsigned int regValue[numberOfRegister], decodeVal;
    int i, j = 2;

    for(i = 0; i < numberOfRegister; i++)
    {
        sscanf(&data[j], "%8x", &regValue[i]);
        // printf("Reg val %d: %x\n", i, regValue[i]);
        j += 8;
        decodeVal = decodeFourByte(regValue[i]);
        coreReg[i] = decodeVal;
    }
}

char *readMemory(char *data)
{
    char *packet = NULL, *comaAddr = NULL, *asciiString, fullMemContent[150] = "";
    unsigned int addr, memoryContent = 0, decodeVal;
    int i, byteLength;

    sscanf(&data[2], "%8x", &addr);
    // printf("addr: %x\n", addr);
    comaAddr = strstr(data, ",");
    sscanf(&comaAddr[1], "%2x", &byteLength);
    // printf("byteLength: %d\n", byteLength);

    for(i = 0; i < byteLength; i += 4)
    {
        memoryContent = rom->address[virtualMemToPhysicalMem(addr)].data;

        if(byteLength - i >= 4)
        {
            decodeVal = decodeFourByte(memoryContent);
            asciiString = createdHexToString(decodeVal, 4);
        }
        else
        {
            decodeVal = decodeTwoByte(memoryContent);
            asciiString = createdHexToString(decodeVal, 2);
        }

        strcat(fullMemContent, asciiString);
        destroyHexToString(asciiString);
        addr++;
    }

    packet = gdbCreateMsgPacket(fullMemContent);

    return packet;
}

void writeMemory(char *data)
{
    char *packet = NULL, *comaAddr = NULL, *semicolonAddr = NULL;
    unsigned int addr, memoryContent = 0, decodeVal;
    int i, byteLength, j = 1;

    sscanf(&data[2], "%8x", &addr);
    printf("addr: %x\n", addr);
    comaAddr = strstr(data, ",");
    sscanf(&comaAddr[1], "%2x", &byteLength);
    printf("byteLength: %d\n", byteLength);
    semicolonAddr = strstr(data, ":");

    for(i = 0; i < byteLength; i += 4)
    {
        // if(byteLength - i >= 4)
        // {
            // sscanf(&semicolonAddr[j], "%8x", &memoryContent);
            // decodeVal = decodeFourByte(memoryContent);
            // rom->address[virtualMemToPhysicalMem(addr)].data = decodeVal;
        // }
        // else
        // {
            sscanf(&semicolonAddr[j], "%4x", &memoryContent);
            // printf("memoryContent: %x\n", memoryContent);
            decodeVal = decodeTwoByte(memoryContent);
            // printf("decodeVal: %x\n", decodeVal);
            // rom->address[virtualMemToPhysicalMem(addr)].data = decodeVal;
        // }

        addr++;
    }
}

char *step(char *data)
{
    char *packet = NULL;
    char *trapSignal = "T05";
    char *pcReg = "0f";
    char *reg7 = "07";
    char *pcValue;
    char *r7Value;
    char msg[50] = "";
    unsigned int decodeVal;

    decodeVal = decodeFourByte(coreReg[PC]);
    pcValue = createdHexToString(decodeVal, 4);
    decodeVal = decodeFourByte(coreReg[7]);
    r7Value = createdHexToString(decodeVal, 4);

    strcat(msg, trapSignal);
    strcat(msg, pcReg);
    strcat(msg, ":");
    strcat(msg, pcValue);
    strcat(msg, ";");
    strcat(msg, reg7);
    strcat(msg, ":");
    strcat(msg, r7Value);

    // printf("msg: %s\n", msg);

    destroyHexToString(pcValue);
    destroyHexToString(r7Value);

    packet = gdbCreateMsgPacket(msg);

    return packet;
}