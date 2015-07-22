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
            packet = gdbCreateMsgPacket("qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-");    //PacketSize=3fff;qRelocInsn-;qXfer:memory-map:read-;PacketSize=3fff;
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
    char *packet = NULL, *dummy;    //dummy ==> sscanf the "$p" from data
    int regNum, byteToSent;
    unsigned long long int decodeVal;    //64-bits value
    char *asciiString;
    // float f = 123.56789;
    // double d = 123.567890123456789;

    sscanf(data, "%2c%x", &dummy, &regNum);
    // printf("Reg no: %d\n", regNum);

    if(regNum <= 16 && regNum >= 0)
    {
        byteToSent = 4;
        decodeVal = decodeFourByte(coreReg[regNum]);
    }
    else if(regNum == 0x2a)
    {
        byteToSent = 4;
        decodeVal = decodeFourByte(coreReg[fPSCR]);
    }
    else if(regNum >= 0x1a && regNum <= 0x29)
    {
        byteToSent = 8;
        decodeVal = decodeEightByte(fpuDoublePrecision[regNum - 0x1a]);
    }
    else
        Throw(GDB_SIGNAL_0);

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
    unsigned long long int decodeVal;
    char *asciiString;

    for(i = 0; i < NUM_OF_CORE_Register - 1; i++)
    {
        decodeVal = decodeFourByte(coreReg[i]);
        asciiString = createdHexToString(decodeVal, 4);
        strcat(fullRegValue, asciiString);
        destroyHexToString(asciiString);
    }

    packet = gdbCreateMsgPacket(fullRegValue);

    return packet;
}

/*
 * ‘P n…=r…’ ==> Write register n… with value r…. The register number n is in hexadecimal,
 *               and r… contains two hex digits for each byte in the register (target byte order).
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘E NN’      For an error
 */
char *writeSingleRegister(char *data)
{
    int regNum;
    char *equal, *dummy;      //dummy ==> sscanf the "$P" from data
                              //equal ==> sscanf the '=' from data
    unsigned long long int regValue, decodeVal;

    sscanf(data, "%2c%x%c%llx", &dummy, &regNum, &equal, &regValue);
    // printf("Reg no: %d\n", regNum);
    // printf("Reg Value: %llx\n", regValue);

    if(regNum <= 16 && regNum >= 0)
    {
        decodeVal = decodeFourByte(regValue);
        coreReg[regNum] = decodeVal;
    }
    else if(regNum == 0x2a)
    {
        decodeVal = decodeFourByte(regValue);
        coreReg[fPSCR] = decodeVal;
    }
    else if(regNum >= 0x1a && regNum <= 0x29)
    {
        decodeVal = decodeEightByte(regValue);
        writeDoublePrecision(regNum - 0x1a, decodeVal);
        writeSinglePrecision((regNum - 0x1a) * 2, decodeVal & 0xffffffff);      //lower 32-bits
        writeSinglePrecision((regNum - 0x1a) * 2 + 1, decodeVal >> 32);         //upper 32-bits
    }
    else
        Throw(GDB_SIGNAL_0);

    return gdbCreateMsgPacket("OK");        //Write successfully
}

/*
 * ‘G XX...’ ==> Write general registers.
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘E NN’      For an error
 */
char *writeAllRegister(char *data)
{
    unsigned int regValue, decodeVal;
    int i, j = 2;

    for(i = 0; i < NUM_OF_CORE_Register - 1; i++)
    {
        sscanf(&data[j], "%8x", &regValue);
        // printf("Reg val %d: %x\n", i, regValue[i]);
        j += 8;
        decodeVal = decodeFourByte(regValue);
        coreReg[i] = decodeVal;
    }

    return gdbCreateMsgPacket("OK");        //Write successfully
}

/*
 * ‘m addr,length’ ==> Read length bytes of memory starting at address addr.
 *                     Note that addr may not be aligned to any particular boundary.
 *                     The stub need not use any particular size or alignment when
 *                     gathering data from memory for the response; even if addr is
 *                     word-aligned and length is a multiple of the word size,
 *                     the stub is free to use byte accesses, or not. For this reason,
 *                     this packet may not be suitable for accessing memory-mapped I/O devices.
 *
 * Reply:
 *      ‘XX…’       Memory contents; each byte is transmitted as a two-digit hexadecimal number.
 *                  The reply may contain fewer bytes than requested if the server was able to
 *                  read only part of the region of memory.
 *
 *      ‘E NN’      NN is errno
 */
char *readMemory(char *data)
{
    char *packet = NULL, fullMemContent[1024] = "", temp[1024] = "", temp2[1024] = "", *asciiString;
    char *comma, *dummy;      //dummy ==> sscanf the "$m" from data
                              //comma ==> sscanf the ',' from data
    unsigned int addr, memoryContent = 0;
    int i, length;

    sscanf(data, "%2c%x%c%x", &dummy, &addr, &comma, &length);
    // printf("addr: %x\n", addr);
    // printf("length: %d\n", length);

    if(length <= 0)
        Throw(GDB_SIGNAL_ABRT);

    for(i = 1; i < length + 1; i++)
    {
        memoryContent = rom->address[virtualMemToPhysicalMem(addr)].data;
        // printf("PhysicalMem: %x\n", virtualMemToPhysicalMem(addr));
        // printf("memoryContent: %x\n", memoryContent);
        asciiString = createdHexToString(memoryContent, 1);
        strcpy(temp, asciiString);
        strcat(temp, temp2);
        strcpy(temp2, temp);
        destroyHexToString(asciiString);

        if(i < 5)
            strcpy(fullMemContent, temp2);

        if(i % 4 == 0)
        {
            if(i % 8 == 0)
                strcat(fullMemContent, temp2);

            strcpy(temp2, "");
        }

        addr++;
    }

    if(length > 5 && length % 4 != 0)
        strcat(fullMemContent, temp2);

    packet = gdbCreateMsgPacket(fullMemContent);

    return packet;
}

/*
 * ‘M addr,length:XX…’ ==> Write length bytes of memory starting at address addr.
 *                         XX… is the data; each byte is transmitted as a two-digit hexadecimal number.
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘E NN’      For an error (this includes the case where only part of the data was written).
 */
char *writeMemory(char *data)
{
    char *packet = NULL;
    char *comma, *semicolonAddr, *dummy;    //dummy ==> sscanf the "$M" from data
                                            //comma ==> sscanf the ',' from data
                                            //semicolonAddr ==> addr starting from the semicolon in the data
    unsigned int addr, memoryContent = 0, temp = 0, temp2 = 0;
    int i, length;

    sscanf(data, "%2c%x%c%x", &dummy, &addr, &comma, &length);
    // printf("addr: %x\n", addr);
    // printf("length: %d\n", length);
    semicolonAddr = strstr(data, ":") + 1;
    
    if(length <= 0)
        Throw(GDB_SIGNAL_ABRT);

    for(i = 1; i < length + 1; i++)
    {
        sscanf(semicolonAddr, "%2x", &memoryContent);
        // printf("memoryContent: %x\n", memoryContent);

        if(i % 4 == 0)
        {
            temp = temp | (memoryContent << 24);
            rom->address[virtualMemToPhysicalMem(addr)].data = temp >> 24;
            rom->address[virtualMemToPhysicalMem(addr + 1)].data = (temp >> 16) & 0xff;
            rom->address[virtualMemToPhysicalMem(addr + 2)].data = (temp >> 8) & 0xff;
            rom->address[virtualMemToPhysicalMem(addr + 3)].data = temp & 0xff;
            addr += 4;
            temp = 0;
        }
        else
        {
            if(i % 4 == 1)
            {
                temp = memoryContent;
                rom->address[virtualMemToPhysicalMem(addr)].data = temp;
            }
            else if(i % 4 == 2)
            {
                temp = temp | (memoryContent << 8);
                rom->address[virtualMemToPhysicalMem(addr)].data = temp >> 8;
                rom->address[virtualMemToPhysicalMem(addr + 1)].data = temp & 0xff;
            }
            else
            {
                temp = temp | (memoryContent << 16);
                rom->address[virtualMemToPhysicalMem(addr)].data = temp >> 16;
                rom->address[virtualMemToPhysicalMem(addr + 1)].data = (temp >> 8) & 0xff;
                rom->address[virtualMemToPhysicalMem(addr + 2)].data = temp & 0xff;
            }
        }

        semicolonAddr += 2;
    }

    return gdbCreateMsgPacket("OK");
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