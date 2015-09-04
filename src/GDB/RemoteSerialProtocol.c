#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "RemoteSerialProtocol.h"
#include "Packet.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "ErrorSignal.h"
#include "ARMSimulator.h"
#include "CException.h"

/* ARM Cortex-M4 Target with FPU */
char *targetCortexM4_XML =
"l<?xml version=\"1.0\"?>"
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"
"<target>"
"  <xi:include href=\"arm-m-profile.xml\"/>"
"  <xi:include href=\"arm-vfpv2.xml\"/>"
"</target>";

/* ARM Cortex-M4 Core Register */
char *arm_m_profile =
"l<?xml version=\"1.0\"?>"
"<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"
"<feature name=\"org.gnu.gdb.arm.m-profile\">"
"   <reg name=\"r0\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r1\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r2\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r3\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r4\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r5\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r6\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r7\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r8\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r9\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r10\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r11\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"r12\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"sp\" bitsize=\"32\" type=\"data_ptr\"/>"
"   <reg name=\"lr\" bitsize=\"32\" type=\"uint32\"/>"
"   <reg name=\"pc\" bitsize=\"32\" type=\"code_ptr\"/>"
"   <reg name=\"xpsr\" bitsize=\"32\" type=\"uint32\" regnum=\"25\"/>"
"</feature>";

/* ARM Cortex-M4 FPU Register */
char *arm_vfpv2 =
"l<?xml version=\"1.0\"?>"
"<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"
"<feature name=\"org.gnu.gdb.arm.vfp\">"
"   <reg name=\"d0\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d1\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d2\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d3\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d4\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d5\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d6\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d7\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d8\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d9\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d10\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d11\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d12\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d13\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d14\" bitsize=\"64\" type=\"ieee_double\"/>"
"   <reg name=\"d15\" bitsize=\"64\" type=\"ieee_double\"/>"
"  <reg name=\"fpscr\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
"</feature>";

int watchpointIndex = 0;

/************************************************************
 * This function handle all the query packet receive from
 * gdb client and return the appropriate message back to it
 *
 * Input:
 *      data    packet receive from gdb client
 *
 * Return:
 *      packet  complete packet to reply to gdb client
 ************************************************************/
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
            packet = gdbCreateMsgPacket("PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-");    //PacketSize=3fff;qRelocInsn-;qXfer:memory-map:read-;qXfer:features:read+;
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

/******************************************************
 * ‘p n’ ==> Read the value of register n; n is in hex.
 *
 * Reply:
 *      XX…     The register's value for n
 *
 *      E NN    For an error
 *
 *      ‘’      Indicating an unrecognized query.
 ******************************************************/
char *readSingleRegister(char *data)
{
    char *packet = NULL;
    int regNum, byteToSent;
    unsigned long long int decodeVal;    //64-bits value
    char asciiString[20];

    sscanf(data, "$p%x", &regNum);
    // printf("Reg no: %d\n", regNum);

    if(regNum <= 16 && regNum >= 0)
    {
        byteToSent = 4;
        decodeVal = decodeFourByte(coreReg[regNum]);
        sprintf(asciiString, "%08x", decodeVal);
    }
    else if(regNum == 0x2a)     //fPSCR
    {
        byteToSent = 4;
        decodeVal = decodeFourByte(coreReg[fPSCR]);
        sprintf(asciiString, "%x", decodeVal);
    }
    else if(regNum >= 0x1a && regNum <= 0x29)
    {
        byteToSent = 8;
        decodeVal = decodeEightByte(fpuDoublePrecision[regNum - 0x1a]);
        sprintf(asciiString, "%016llx", decodeVal);
    }
    else
    {
        printf("Warning: Attempt to read unknown registers\n");
        Throw(GDB_SIGNAL_0);
    }

    // asciiString = createdHexToString(decodeVal, byteToSent);
    packet = gdbCreateMsgPacket(asciiString);
    // destroyHexToString(asciiString);

    return packet;
}

/********************************************************************************
 * ‘g’ ==> Read general registers.
 *
 * Reply:
 *      XX…     Each byte of register data is described by two hex digits.
 *              The bytes with the register are transmitted in target byte order.
 *
 *      E NN    For an error.
 ********************************************************************************/
char *readAllRegister()
{
    char *packet = NULL, fullRegValue[405] = "";
    int i, j;
    unsigned long long int decodeVal;
    char *asciiString;

    //core register r0 - r12, SP, LR, PC, xPSR
    for(i = 0; i < NUM_OF_CORE_Register - 1; i++)
    {
        decodeVal = decodeFourByte(coreReg[i]);
        asciiString = createdHexToString(decodeVal, 4);
        strcat(fullRegValue, asciiString);
        destroyHexToString(asciiString);
    }

    //fpu register
    for(i = 0; i < NUM_OF_FPUD_Register; i++)
    {
        decodeVal = decodeEightByte(fpuDoublePrecision[i]);
        asciiString = createdHexToString(decodeVal, 8);
        strcat(fullRegValue, asciiString);
        destroyHexToString(asciiString);
    }

    //fpu status register
    decodeVal = decodeFourByte(coreReg[fPSCR]);
    asciiString = createdHexToString(decodeVal, 4);
    strcat(fullRegValue, asciiString);
    destroyHexToString(asciiString);

    packet = gdbCreateMsgPacket(fullRegValue);

    return packet;
}

/************************************************************************************************
 * ‘P n…=r…’ ==> Write register n… with value r…. The register number n is in hexadecimal,
 *               and r… contains two hex digits for each byte in the register (target byte order).
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘E NN’      For an error
 ************************************************************************************************/
char *writeSingleRegister(char *data)
{
    int regNum;
    unsigned long long int regValue, decodeVal;

    sscanf(data, "$P%x=%llx", &regNum, &regValue);
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
    {
        printf("Warning: Attempt to write unknown registers\n");
        Throw(GDB_SIGNAL_0);
    }

    return gdbCreateMsgPacket("OK");        //Write successfully
}

/****************************************
 * ‘G XX...’ ==> Write general registers.
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘E NN’      For an error
 ****************************************/
char *writeAllRegister(char *data)
{
    char *regHex = data + 2, *fpuRegHex = regHex + 8 * (NUM_OF_CORE_Register - 1),
         *fpuStatusHex = fpuRegHex + 16 * NUM_OF_FPUD_Register;
    unsigned long long int decodeVal, regValue, temp;
    int i;

    //core register r0 - r12, SP, LR, PC, xPSR
    for(i = 0; i < NUM_OF_CORE_Register - 1; i++)
    {
        sscanf(regHex, "%8x", &regValue);
        // printf("Reg val %d: %x\n", i, regValue);
        regHex += 8;
        decodeVal = decodeFourByte(regValue);
        coreReg[i] = decodeVal;
    }

    // printf("fpuRegHex: %s\n", fpuRegHex);

    //fpu register
    if(fpuRegHex[0] != '#')
    {
        for(i = 0; i < NUM_OF_FPUD_Register; i++)
        {
            regValue = 0;
            temp = 0;
            sscanf(fpuRegHex, "%8x", &temp);
            // printf("fpu val %d: %x\n", i, temp);
            fpuRegHex += 8;
            sscanf(fpuRegHex, "%8x", &regValue);
            // printf("fpu val %d: %x\n", i, regValue);
            fpuRegHex += 8;
            regValue |= (temp << 32);
            // printf("fpu val %d: %llx\n", i, regValue);
            decodeVal = decodeEightByte(regValue);
            writeDoublePrecision(i, decodeVal);
            writeSinglePrecision(i * 2, decodeVal & 0xffffffff);      //lower 32-bits
            writeSinglePrecision(i * 2 + 1, decodeVal >> 32);         //upper 32-bits
        }

        //fpu status register
        sscanf(fpuStatusHex, "%8x", &regValue);
        // printf("fpu val 16: %x\n", regValue);
        decodeVal = decodeFourByte(regValue);
        coreReg[fPSCR] = decodeVal;
    }

    return gdbCreateMsgPacket("OK");        //Write successfully
}

/**********************************************************************************************
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
 **********************************************************************************************/
char *readMemory(char *data)
{
    char *packet = NULL, fullMemContent[0x3fff] = "", *asciiString = NULL;
    unsigned int addr, memoryContent = 0;
    int i, length;

    sscanf(data, "$m%x,%x", &addr, &length);
    // printf("addr: %x\n", addr);
    // printf("length: %d\n", length);

    if(virtualMemToPhysicalMem(addr) == 0xffffffff || virtualMemToPhysicalMem(addr + length) == 0xffffffff)
    {
        printf("Warning: Memory exceeded\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    if(length <= 0)
    {
        printf("Warning: Unknown byte's length\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    for(i = 1; i < length + 1; i++)
    {
        memoryContent = memoryBlock[virtualMemToPhysicalMem(addr)];
        asciiString = createdHexToString(memoryContent, 1);
        strcat(fullMemContent, asciiString);
        destroyHexToString(asciiString);

        addr++;
    }

    packet = gdbCreateMsgPacket(fullMemContent);

    return packet;
}

/******************************************************************************************************
 * ‘M addr,length:XX…’ ==> Write length bytes of memory starting at address addr.
 *                         XX… is the data; each byte is transmitted as a two-digit hexadecimal number.
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘E NN’      For an error (this includes the case where only part of the data was written).
 ******************************************************************************************************/
char *writeMemory(char *data)
{
    char *packet = NULL, memCont[0x3fff] = {0};
    char *memContentAddr;        //memContentAddr ==> addr starting from the first data
    unsigned int addr, memoryContent = 0;
    int i, length;

    sscanf(data, "$M%x,%x:%s", &addr, &length, memCont);
    // printf("addr: %x\n", addr);
    // printf("length: %d\n", length);
    // printf("memCont: %s\n", memCont);
    memContentAddr = strstr(data, ":") + 1;

    if(virtualMemToPhysicalMem(addr) == 0xffffffff || virtualMemToPhysicalMem(addr + length) == 0xffffffff)
    {
        printf("Warning: Memory exceeded\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    if(length <= 0)
    {
        printf("Warning: Unknown byte's length\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    if(memCont[length * 2] != '#')
    {
        printf("Warning: Data length and byte's length not match\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    for(i = 1; i < length + 1; i++)
    {
        sscanf(memContentAddr, "%2x", &memoryContent);
        memoryBlock[virtualMemToPhysicalMem(addr)] = memoryContent;
        addr++;
        memContentAddr += 2;
    }

    return gdbCreateMsgPacket("OK");
}

/*************************************************************************************************
 * ‘s [addr]’       ==> Single step, resuming at addr. If addr is omitted, resume at same address.
 * ‘S sig[;addr]’   ==> Step with signal. This is analogous to the ‘C’ packet, but requests a
 *                      single-step, rather than a normal resumption of execution.
 *
 * Reply:
 *      ‘S05’       Signal trap
 *
 *      ‘E NN’      For an error.
 *************************************************************************************************/
char *step(char *data)
{
    CEXCEPTION_T armException;
    char *packet = NULL, *asciiString = NULL;
    char *signal = "S", *error = "E";
    char msg[4] = "";

    Try
    {
        armStep();
    }
    Catch(armException)
    {
        if(armException == UsageFault)
        {
            asciiString = createdHexToString(GDB_SIGNAL_ILL, 1);
            strcat(msg, error);     //error msg
        }
    }

    if(asciiString == NULL)
    {
        asciiString = createdHexToString(GDB_SIGNAL_TRAP, 1);
        strcat(msg, signal);        //signal trap
    }

    strcat(msg, asciiString);
    destroyHexToString(asciiString);
    packet = gdbCreateMsgPacket(msg);

    return packet;
}

/*****************************************************************************************
 * ‘C sig[;addr]’ ==> Continue with signal sig (hex signal number). If ‘;addr’ is omitted,
 *                    resume at same address.
 *
 * Reply:
 *      ‘S05’       Signal trap
 *
 *      ‘E NN’      For an error.
 *****************************************************************************************/
char *cont(char *data)
{
    CEXCEPTION_T armException;
    char *packet = NULL, *asciiString = NULL;
    char *signal = "S", *error = "E";
    char msg[4] = "";

    while(!findBreakpoint(bp))
    {
        Try
        {
            armStep();
        }
        Catch(armException)
        {
            if(armException == UsageFault)
            {
                asciiString = createdHexToString(GDB_SIGNAL_ILL, 1);
                strcat(msg, error);     //error msg
            }

            break;
        }

        if(virtualMemToPhysicalMem(coreReg[PC]) == RAM_BASE_ADDR)   // stop if reach the end of code addr
            break;
    }

    if(asciiString == NULL)
    {
        asciiString = createdHexToString(GDB_SIGNAL_TRAP, 1);
        strcat(msg, signal);        //signal trap
    }

    strcat(msg, asciiString);
    destroyHexToString(asciiString);
    packet = gdbCreateMsgPacket(msg);

    return packet;
}

/********************************************************************
 * To search the breakpoint available and compare to the PC register
 *
 * Input:
 *      breakpoint
 *
 * Return:
 *      0           if breakpoint do not match with PC register
 *      1           if breakpoint match with PC register
 ********************************************************************/
int findBreakpoint(Breakpoint *breakpoint)
{
    if(breakpoint != NULL)
    {
        if(coreReg[PC] == breakpoint->addr)
            return 1;
        else
        {
            if(breakpoint->next != NULL)
            {
                if(coreReg[PC] > breakpoint->addr)
                    findBreakpoint(breakpoint->next);
            }
        }
    }

    return 0;
}

/*****************************************************************************************************
 * Insert
 * ‘Z0,addr,kind’ ==> A memory breakpoint at address addr of type kind. A memory breakpoint is
 *                    implemented by replacing the instruction at addr with a software breakpoint
 *                    or trap instruction. The kind is target-specific and typically indicates the
 *                    size of the breakpoint in bytes that should be inserted. E.g.,the arm and mips
 *                    can insert either a 2 or 4 byte breakpoint.
 * ‘Z1,addr,kind’ ==> A hardware breakpoint at address addr. A hardware breakpoint is implemented
 *                    using a mechanism that is not dependant on being able to modify the target’s
 *                    memory.
 *
 * These breakpoint kinds are defined for the ‘Z0’ and ‘Z1’ packets.
 *      2 16-bit Thumb mode breakpoint.
 *      3 32-bit Thumb mode (Thumb-2) breakpoint.
 *      4 32-bit ARM mode breakpoint.
 *
 * ‘Z2,addr,kind’ ==> A write watchpoint at addr. The number of bytes to watch is specified by kind.
 * ‘Z3,addr,kind’ ==> A read watchpoint at addr. The number of bytes to watch is specified by kind.
 * ‘Z4,addr,kind’ ==> An access watchpoint at addr. The number of bytes to watch is specified by kind.
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘’          Not supported
 *
 *      ‘E NN’      For an error (this includes the case where only part of the data was written).
 *****************************************************************************************************/
char *insertBreakpointOrWatchpoint(char *data)
{
    BP_Type type;           //Sort of breakpoint
    unsigned int addr;      //Address specified
	int kind;                //Breakpoint kinds

    sscanf(data, "$Z%1d,%x,%1d", (int *)&type, &addr, &kind);
    // printf("type: %d\n", type);
    // printf("addr: %x\n", addr);
    // printf("kind: %d\n", kind);

    if(virtualMemToPhysicalMem(addr) == 0xffffffff)
    {
        printf("Warning: Memory exceeded\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    switch (type)
    {
        case BP_MEMORY:
        case BP_HARDWARE:
            addBreakpoint(&bp, addr);
            break;
        case WP_WRITE:
            // break;
        case WP_READ:
            // break;
        case WP_ACCESS:
            addWatchpoint(addr, kind, type);
            break;
        default:
            printf("Warning: breakpoint type not recognized\n");
            Throw(GDB_SIGNAL_HUP);
            break;
    }

    return gdbCreateMsgPacket("OK");
}

/******************************************************************************************************
 * Remove
 * ‘z0,addr,kind’ ==> A memory breakpoint at address addr of type kind. A memory breakpoint is
 *                    implemented by replacing the instruction at addr with a software breakpoint
 *                    or trap instruction. The kind is target-specific and typically indicates the
 *                    size of the breakpoint in bytes that should be inserted. E.g.,the arm and mips
 *                    can insert either a 2 or 4 byte breakpoint.
 * ‘z1,addr,kind’ ==> A hardware breakpoint at address addr. A hardware breakpoint is implemented
 *                    using a mechanism that is not dependant on being able to modify the target’s
 *                    memory.
 *
 * These breakpoint kinds are defined for the ‘Z0’ and ‘Z1’ packets.
 *      2 16-bit Thumb mode breakpoint.
 *      3 32-bit Thumb mode (Thumb-2) breakpoint.
 *      4 32-bit ARM mode breakpoint.
 *
 * ‘z2,addr,kind’ ==> A write watchpoint at addr. The number of bytes to watch is specified by kind.
 * ‘z3,addr,kind’ ==> A read watchpoint at addr. The number of bytes to watch is specified by kind.
 * ‘z4,addr,kind’ ==> An access watchpoint at addr. The number of bytes to watch is specified by kind.
 *
 * Reply:
 *      ‘OK’        For success
 *
 *      ‘’          Not supported
 *
 *      ‘E NN’      For an error (this includes the case where only part of the data was written).
 ******************************************************************************************************/
char *removeBreakpointOrWatchpoint(char *data)
{
    BP_Type type;           //Sort of breakpoint
    unsigned int addr;      //Address specified
	int kind;                //Breakpoint kinds

    sscanf(data, "$z%1d,%x,%1d", (int *)&type, &addr, &kind);
    // printf("type: %d\n", type);
    // printf("addr: %x\n", addr);
    // printf("kind: %d\n", kind);

    if(virtualMemToPhysicalMem(addr) == 0xffffffff)
    {
        printf("Warning: Memory exceeded\n");
        Throw(GDB_SIGNAL_ABRT);
    }

    switch (type)
    {
        case BP_MEMORY:
        case BP_HARDWARE:
            removeBreakpoint(&bp, addr);
            break;
        case WP_WRITE:
            // break;
        case WP_READ:
            // break;
        case WP_ACCESS:
            removeWatchpoint(addr, kind, type);
            break;
        default:
            printf("Warning: breakpoint type not recognized\n");
            Throw(GDB_SIGNAL_HUP);
            break;
    }

    return gdbCreateMsgPacket("OK");
}

/*********************************************************
 * This function create breakpoint contain address info
 *
 * Input:
 *      addr            address of the breakpoint
 *
 * Return:
 *      breakpoint      pointer to breakpoint object
 **********************************************************/
Breakpoint *createBreakpoint(unsigned int addr)
{
    Breakpoint *breakpoint;
    breakpoint = malloc(sizeof(Breakpoint));
    breakpoint->addr = addr;
    breakpoint->next = NULL;

    return breakpoint;
}

void deleteBreakpoint(Breakpoint **breakpoint)
{
    if(*breakpoint != NULL)
    {
        free(*breakpoint);
        *breakpoint = NULL;
    }
}

void deleteAllBreakpoint(Breakpoint **breakpoint)
{
    Breakpoint *temp_bp = *breakpoint;

    if(temp_bp != NULL)
    {
        if(temp_bp->next != NULL)
            deleteAllBreakpoint(&(*breakpoint)->next);

        deleteBreakpoint(&(*breakpoint));
    }
}

/****************************************************
 * This function add breakpoint to the list
 *
 * Input:
 *      addr            address of the breakpoint
 *      breakpoint      pointer to breakpoint object
 ****************************************************/
void addBreakpoint(Breakpoint **breakpoint, unsigned int addr)
{
    Breakpoint *temp_bp = *breakpoint;

    if(temp_bp == NULL)
        *breakpoint = createBreakpoint(addr);
    else
    {
        if(addr > temp_bp->addr)
        {
            if(temp_bp->next != NULL)
                addBreakpoint(&(*breakpoint)->next, addr);
            else
                (*breakpoint)->next = createBreakpoint(addr);
        }
        else
        {
            temp_bp = NULL;
            addBreakpoint(&temp_bp, addr);
            temp_bp->next = *breakpoint;
            *breakpoint = temp_bp;
        }
    }
}

/****************************************************
 * This function remove breakpoint from the list
 *
 * Input:
 *      addr            address of the breakpoint
 *      breakpoint      pointer to breakpoint object
 ****************************************************/
void removeBreakpoint(Breakpoint **breakpoint, unsigned int addr)
{
    Breakpoint *temp_bp = *breakpoint;

    if(temp_bp->addr == addr)
    {
        temp_bp = (*breakpoint)->next;
        deleteBreakpoint(&(*breakpoint));
        *breakpoint = temp_bp;
    }
    else
        removeBreakpoint(&(*breakpoint)->next, addr);
}

void initializeWatchpoint()
{
    int i;

    for(i = 0; i < MAX_HW_WATCHPOINT; i++)
    {
        wp[i].type = NONE;
        wp[i].addr = 0;
        wp[i].size = 0;
    }
}

void addWatchpoint(unsigned int addr, unsigned int size, BP_Type type)
{
    wp[watchpointIndex].type = type;
    wp[watchpointIndex].addr = addr;
    wp[watchpointIndex].size = size;
    watchpointIndex++;
}

void removeWatchpoint(unsigned int addr, unsigned int size, BP_Type type)
{
    int i;

    for(i = 0; i < MAX_HW_WATCHPOINT; i++)
    {
        if(wp[i].addr == addr && wp[i].type == type && wp[i].size == size)
        {
            wp[i].type = NONE;
            wp[i].addr = 0;
            wp[i].size = 0;
            watchpointIndex--;
            break;
        }
    }

    for(; i < MAX_HW_WATCHPOINT - 1; i++)
    {
        wp[i] = wp[i + 1];
    }
}
