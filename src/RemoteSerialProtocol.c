#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "RemoteSerialProtocol.h"
#include "Packet.h"
#include "ARMRegisters.h"
#include "ROM.h"
#include "ErrorSignal.h"

char *targetCortexM4_XML =
"l<?xml version=\"1.0\"?>"
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"
"<target>"
"  <xi:include href=\"arm-m-profile.xml\"/>"
"  <xi:include href=\"arm-vfpv2.xml\"/>"
"</target>";

char *arm_m_profile =
"l<?xml version=\"1.0\"?>"
"<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"
"<feature name=\"org.gnu.gdb.arm.m-profile\">"
"  <reg name=\"r0\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r1\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r2\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r3\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r4\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r5\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r6\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r7\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r8\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r9\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r10\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r11\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"r12\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"sp\" bitsize=\"32\" type=\"data_ptr\"/>"
"  <reg name=\"lr\" bitsize=\"32\" type=\"uint32\"/>"
"  <reg name=\"pc\" bitsize=\"32\" type=\"code_ptr\"/>"
"  <reg name=\"xpsr\" bitsize=\"32\" type=\"uint32\" regnum=\"25\"/>"
"</feature>";

char *arm_vfpv2 =
"l<?xml version=\"1.0\"?>"
"<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"
"<feature name=\"org.gnu.gdb.arm.vfp\">"
"  <reg name=\"d0\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d1\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d2\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d3\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d4\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d5\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d6\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d7\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d8\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d9\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d10\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d11\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d12\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d13\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d14\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"d15\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"fpscr\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
"</feature>";

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

    /* if(data[2] == 'P' || data[2] == 'C' || data[2] == 'L')
    {
        if(strncmp("CRC", &data[2], strlen("CRC")) == 0)
            packet = gdbCreateMsgPacket("E01");     // error "E01" => CRC query not supported
        else
            packet = gdbCreateMsgPacket("");
    }
    else
    { */
        if(strncmp("Supported", &data[2], strlen("Supported")) == 0)
            packet = gdbCreateMsgPacket("PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-");    //;qRelocInsn-;qXfer:memory-map:read-;PacketSize=3fff;
        /* else if(strncmp("Attached", &data[2], strlen("Attached")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("TStatus", &data[2], strlen("TStatus")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("fThreadInfo", &data[2], strlen("fThreadInfo")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("Offsets", &data[2], strlen("Offsets")) == 0)
            packet = gdbCreateMsgPacket("");
        else if(strncmp("Symbol::", &data[2], strlen("Symbol::")) == 0)
            packet = gdbCreateMsgPacket(""); */
        else if(strncmp("Xfer", &data[2], strlen("Xfer")) == 0)
        {
            if(strncmp("features", &data[7], strlen("features")) == 0 && strncmp("read", &data[16], strlen("read")) == 0)
            {
                if(strncmp("arm-m-profile.xml", &data[21], strlen("arm-m-profile.xml")) == 0)
                    packet = gdbCreateMsgPacket(arm_m_profile);
                else if(strncmp("arm-vfpv2.xml", &data[21], strlen("arm-vfpv2.xml")) == 0)
                    packet = gdbCreateMsgPacket(arm_vfpv2);
                else if(strncmp("target.xml", &data[21], strlen("target.xml")) == 0)
                    packet = gdbCreateMsgPacket(targetCortexM4_XML);
                else
                {
                    packet = gdbCreateMsgPacket("");
                    printf("Unsupported target XML\n");
                }
            }
        }
        else
        {
            packet = gdbCreateMsgPacket("");
            printf("Unsupported RSP query\n");
        }
    // }

    return packet;
}

/*
 * ‘p n’ ==> Read the value of register n; n is in hex.
 *
 * Reply:
 *      XX…     The register's value for n
 *
 *      E NN    For an error
 *
 *      ‘’      Indicating an unrecognized query.
 */
char *readSingleRegister(char *data)
{
    char *packet = NULL, *dummy;
    int regNum, byteToSent;
    unsigned int regValue;                          //32-bits value
    unsigned long long int fpuRegVal, decodeVal;    //64-bits value
    char *asciiString;
    // float f = 123.56789;
    // double d = 123.567890123456789;

    sscanf(data, "%2c%x", &dummy, &regNum);
    // printf("Reg no: %x\n", regNum);

    if(regNum <= 16)
    {
        regValue = coreReg[regNum];
        byteToSent = 4;
        decodeVal = decodeFourByte(regValue);
    }
    else if(regNum == 0x2a)
    {
        regValue = coreReg[fPSCR];
        byteToSent = 4;
        decodeVal = decodeFourByte(regValue);
    }
    else if(regNum >= 0x1a && regNum <= 0x29)
    {
        fpuRegVal = fpuDoublePrecision[regNum - 0x1a];
        byteToSent = 8;
        decodeVal = decodeEightByte(fpuRegVal);
    }
    // else
    // {
        // packet = gdbCreateMsgPacket("E06");
    // }

    asciiString = createdHexToString(decodeVal, byteToSent);
    packet = gdbCreateMsgPacket(asciiString);
    destroyHexToString(asciiString);

    return packet;
}

/*
 * ‘g’ ==> Read general registers.
 *
 * Reply:
 *      XX…     Each byte of register data is described by two hex digits.
 *              The bytes with the register are transmitted in target byte order.
 *
 *      E NN    For an error.
 */
char *readAllRegister()
{
    char *packet = NULL, fullRegValue[140] = "";
    int i, j;
    unsigned int regValue[NUM_OF_CORE_Register], decodeVal;
    char *asciiString;

    for(i = 0; i < NUM_OF_CORE_Register - 1; i++)
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
    unsigned int regValue[NUM_OF_CORE_Register], decodeVal;
    int i, j = 2;

    for(i = 0; i < NUM_OF_CORE_Register; i++)
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

        if(byteLength % 4 == 0)
        {
            decodeVal = decodeFourByte(memoryContent);
            asciiString = createdHexToString(decodeVal, 4);
        }
        else
        {
            decodeVal = decodeTwoByte(memoryContent >> 16);
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
    // printf("addr: %x\n", addr);
    comaAddr = strstr(data, ",");
    sscanf(&comaAddr[1], "%2x", &byteLength);
    // printf("byteLength: %d\n", byteLength);
    semicolonAddr = strstr(data, ":");

    for(i = 0; i < byteLength; i += 4)
    {
        if(byteLength % 4 == 0)
        {
            sscanf(&semicolonAddr[j], "%8x", &memoryContent);
            decodeVal = decodeFourByte(memoryContent);
            rom->address[virtualMemToPhysicalMem(addr)].data = decodeVal;
        }
        else
        {
            sscanf(&semicolonAddr[j], "%4x", &memoryContent);
            // printf("memoryContent: %x\n", memoryContent);
            decodeVal = decodeTwoByte(memoryContent);
            // printf("decodeVal: %x\n", decodeVal);
            rom->address[virtualMemToPhysicalMem(addr)].data = decodeVal << 16;
            // printf("rom->address.data: %x\n", rom->address[virtualMemToPhysicalMem(addr)].data);
        }

        addr++;
        j += 8;
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