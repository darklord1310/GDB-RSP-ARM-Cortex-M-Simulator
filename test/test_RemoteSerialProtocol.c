#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "ARMRegisters.h"
#include "ROM.h"
#include "RemoteSerialProtocol.h"
#include "mock_Packet.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * qL<startflag><thread count><next thread> -- obtain thread info
 *
 * startflag (one hex digit) is one to indicate the first query
 * and zero to indicate a subsequent query
 *
 * thread count (two hex digits) is the maximum number of threads
 * the response packet can contain
 *
 * next thread (eight hex digits), for subsequent queries (startflag is zero),
 * is returned in the response as argthread
 */
void test_handleQueryPacket_given_data_with_qL_should_return_empty_response(void)
{
    char data[] = "$qL1160000000000000000#55";
    char *reply;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

/*
 * qC -- current thread
 *
 * Reply:
 *      QCpid       Where pid is a HEX encoded 16 bit process id
 *      *           Any other reply implies the old pid
 *
 */
void test_handleQueryPacket_given_data_with_qC_should_return_empty_response(void)
{
    char data[] = "$qC#b4";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

/*
 * qCRC:addr,length -- Compute the CRC checksum of a block of memory
 *
 * Reply:
 *      E NN        An error (such as memory fault)
 *      C crc32     The specified memory region's checksum is crc32
 *
 */
void test_handleQueryPacket_given_data_with_qCRC_should_return_E01_response(void)
{
    char data[] = "$qCRC#49";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("E01", "$E01#a6");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$E01#a6", reply);
}

void test_handleQueryPacket_given_qSupported_should_return_appropriate_response(void)
{
    char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("qRelocInsn-", "$qRelocInsn-#2b");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$qRelocInsn-#2b", reply);
}

/*
 * qAttached:pid -- Indication of whether the remote server attached to an
 *                  existing process or created a new process
 *
 * Reply:
 *      1       The remote server attached to an existing process
 *      0       The remote server created a new process
 *      E NN    An error occurred, nn are hex digits
 */
void test_handleQueryPacket_given_data_with_qAttached_should_return_empty_response(void)
{
    char data[] = "$qAttached#8f";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

/*
 * qTStatus -- Ask the stub if there is a trace experiment running right now
 *
 * Reply:
 *      T0       There is no trace experiment running
 *      T1       There is a trace experiment running
 */
void test_handleQueryPacket_given_data_with_qTStatus_should_return_empty_response(void)
{
    char data[] = "$qTStatus#49";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

/*
 * qfThreadInfo -- Ask the stub if there is a trace experiment running right now
 *
 * Reply:
 *      T0       There is no trace experiment running
 *      T1       There is a trace experiment running
 */
void test_handleQueryPacket_given_data_with_qfThreadInfo_should_return_empty_response(void)
{
    char data[] = "$qfThreadInfo#bb";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

/*
 * qOffsets -- Get section offsets that the target used when relocating the downloaded image
 *
 * Reply:
 *      Text=xxx;Data=yyy[;Bss=zzz]
 *      TextSeg=xxx[;DataSeg=yyy]
 */
void test_handleQueryPacket_given_data_with_qOffsets_should_return_empty_response(void)
{
    char data[] = "$qOffsets#4b";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

/*
 * qSymbol:: -- Notify the target that No value for GDBN is prepared to serve symbol lookup requests.
 *              Accept requests from the target for the values of symbols
 *
 * Reply:
 *      OK                  The target does not need to look up any (more) symbols
 *      qSymbol:sym_name
 */
void test_handleQueryPacket_given_data_with_qSymbol_should_return_empty_response(void)
{
    char data[] = "$qSymbol::#5b";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

void test_handleQueryPacket_given_data_with_unrecognized_RSP_query_should_return_empty_response(void)
{
    char data[] = "$qB#b3";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

void test_readSingleRegister_given_data_with_p10_packet_should_return_appropriate_response(void)
{
    char data[] = "$p10#d1";
    char *reply = NULL;

    initCoreRegister();

    decodeFourByte_ExpectAndReturn(0x01000000, 0x00000001);
    createdHexToString_ExpectAndReturn(0x00000001, 4, "00000001");
    gdbCreateMsgPacket_ExpectAndReturn("00000001", "$00000001#81");
    destroyHexToString_Expect("00000001");

    reply = readSingleRegister(data);

    TEST_ASSERT_EQUAL_STRING("$00000001#81", reply);
}

void test_readAllRegister_should_return_appropriate_response_with_all_reg_val(void)
{
    char *reply = NULL;
    int i;

    initCoreRegister();
    coreReg[2] = 0x12345678;

    for(i = 0; i < 17; i++)
    {
        if(i < 16)
        {
            if(i == 2)
            {
                decodeFourByte_ExpectAndReturn(0x12345678, 0x78563412);
                createdHexToString_ExpectAndReturn(0x78563412, 4, "78563412");
                destroyHexToString_Expect("78563412");
            }
            else
            {
                decodeFourByte_ExpectAndReturn(0x00000000, 0x00000000);
                createdHexToString_ExpectAndReturn(0x00000000, 4, "00000000");
                destroyHexToString_Expect("00000000");
            }
        }
        else
        {
            decodeFourByte_ExpectAndReturn(0x01000000, 0x00000001);
            createdHexToString_ExpectAndReturn(0x00000001, 4, "00000001");
            destroyHexToString_Expect("00000001");
        }
    }

    gdbCreateMsgPacket_ExpectAndReturn("0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",  \
                                       "$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001#81");

    reply = readAllRegister();

    TEST_ASSERT_EQUAL_STRING("$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001#81", reply);
}

void test_writeSingleRegister_given_following_data_should_write_value_to_a_register(void)
{
    char data[] = "$P6=fe090008#23";

    initCoreRegister();

    decodeFourByte_ExpectAndReturn(0xfe090008, 0x080009ef);

    writeSingleRegister(data);

    TEST_ASSERT_EQUAL(0x080009ef, coreReg[6]);
}

void test_writeAllRegister_given_following_data_should_write_value_to_all_register(void)
{
    char data[] = "$G00000000111111118cff0120333333334444444455555555666666667777777788888888500b0008aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffff00000001#c8";
    initCoreRegister();

    decodeFourByte_ExpectAndReturn(0x00000000, 0x00000000);
    decodeFourByte_ExpectAndReturn(0x11111111, 0x11111111);
    decodeFourByte_ExpectAndReturn(0x8cff0120, 0x2001ff8c);
    decodeFourByte_ExpectAndReturn(0x33333333, 0x33333333);
    decodeFourByte_ExpectAndReturn(0x44444444, 0x44444444);
    decodeFourByte_ExpectAndReturn(0x55555555, 0x55555555);
    decodeFourByte_ExpectAndReturn(0x66666666, 0x66666666);
    decodeFourByte_ExpectAndReturn(0x77777777, 0x77777777);
    decodeFourByte_ExpectAndReturn(0x88888888, 0x88888888);
    decodeFourByte_ExpectAndReturn(0x500b0008, 0x08000b50);
    decodeFourByte_ExpectAndReturn(0xaaaaaaaa, 0xaaaaaaaa);
    decodeFourByte_ExpectAndReturn(0xbbbbbbbb, 0xbbbbbbbb);
    decodeFourByte_ExpectAndReturn(0xcccccccc, 0xcccccccc);
    decodeFourByte_ExpectAndReturn(0xdddddddd, 0xdddddddd);
    decodeFourByte_ExpectAndReturn(0xeeeeeeee, 0xeeeeeeee);
    decodeFourByte_ExpectAndReturn(0xffffffff, 0xffffffff);
    decodeFourByte_ExpectAndReturn(0x00000001, 0x01000000);

    writeAllRegister(data);

    TEST_ASSERT_EQUAL(0x00000000, coreReg[0]);
    TEST_ASSERT_EQUAL(0x11111111, coreReg[1]);
    TEST_ASSERT_EQUAL(0x2001ff8c, coreReg[2]);
    TEST_ASSERT_EQUAL(0x33333333, coreReg[3]);
    TEST_ASSERT_EQUAL(0x44444444, coreReg[4]);
    TEST_ASSERT_EQUAL(0x55555555, coreReg[5]);
    TEST_ASSERT_EQUAL(0x66666666, coreReg[6]);
    TEST_ASSERT_EQUAL(0x77777777, coreReg[7]);
    TEST_ASSERT_EQUAL(0x88888888, coreReg[8]);
    TEST_ASSERT_EQUAL(0x08000b50, coreReg[9]);
    TEST_ASSERT_EQUAL(0xaaaaaaaa, coreReg[10]);
    TEST_ASSERT_EQUAL(0xbbbbbbbb, coreReg[11]);
    TEST_ASSERT_EQUAL(0xcccccccc, coreReg[12]);
    TEST_ASSERT_EQUAL(0xdddddddd, coreReg[SP]);
    TEST_ASSERT_EQUAL(0xeeeeeeee, coreReg[LR]);
    TEST_ASSERT_EQUAL(0xffffffff, coreReg[PC]);
    TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

void test_step_given_following_data_should_return_signal_value_pc_reg_value_and_r7_value(void)
{
    char data[] = "$s#73";
    char *reply = NULL;

    initCoreRegister();
    coreReg[PC] = 0x08000d08;
    coreReg[7] = 0x2001ff7c;

    decodeFourByte_ExpectAndReturn(0x08000d08, 0x080d0008);
    createdHexToString_ExpectAndReturn(0x080d0008, 4, "080d0008");
    decodeFourByte_ExpectAndReturn(0x2001ff7c, 0x7cff0120);
    createdHexToString_ExpectAndReturn(0x7cff0120, 4, "7cff0120");
    destroyHexToString_Expect("080d0008");
    destroyHexToString_Expect("7cff0120");
    gdbCreateMsgPacket_ExpectAndReturn("T050f:080d0008;07:7cff0120", "$T050f:080d0008;07:7cff0120#52");

    reply = step(data);

    TEST_ASSERT_EQUAL_STRING("$T050f:080d0008;07:7cff0120#52", reply);
}

void test_readMemory_given_0x0_mem_addr_should_return_4_byte_value_in_memory_addr_given_by_data(void)
{
    char data[] = "$m0,4#64";
    char *reply = NULL;

    createROM();

    rom->address[0x0].data = 0xd034f8df;

    decodeFourByte_ExpectAndReturn(0xd034f8df, 0xdff834d0);
    createdHexToString_ExpectAndReturn(0xdff834d0, 4, "dff834d0");
    destroyHexToString_Expect("dff834d0");
    gdbCreateMsgPacket_ExpectAndReturn("dff834d0", "$dff834d0#63");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$dff834d0#63", reply);

    destroyROM();
}

void test_readMemory_given_0x8000d06_mem_addr_should_return_2_byte_value_in_memory_addr_given_by_data(void)
{
    char data[] = "$m8000d06,2#5d";
    char *reply = NULL;

    createROM();

    rom->address[virtualMemToPhysicalMem(0x8000d06)].data = 0x4a4d;

    decodeTwoByte_ExpectAndReturn(0x4a4d, 0x4d4a);
    createdHexToString_ExpectAndReturn(0x4d4a, 2, "4d4a");
    destroyHexToString_Expect("4d4a");
    gdbCreateMsgPacket_ExpectAndReturn("4d4a", "$4d4a#2d");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$4d4a#2d", reply);

    destroyROM();
}

void test_readMemory_given_0x8000ab0_mem_addr_should_return_20_byte_value_in_memory_addr_given_by_data(void)
{
    char data[] = "$m8000ab0,14#5d";
    char *reply = NULL;

    createROM();

    rom->address[virtualMemToPhysicalMem(0x8000ab0)].data = 0x08004a4d;
    rom->address[virtualMemToPhysicalMem(0x8000ab1)].data = 0x08005a5d;
    rom->address[virtualMemToPhysicalMem(0x8000ab2)].data = 0x08006a6d;
    rom->address[virtualMemToPhysicalMem(0x8000ab3)].data = 0x08007a7d;
    rom->address[virtualMemToPhysicalMem(0x8000ab4)].data = 0x08008a8d;

    decodeFourByte_ExpectAndReturn(0x08004a4d, 0x4d4a0008);
    createdHexToString_ExpectAndReturn(0x4d4a0008, 4, "4d4a0008");
    destroyHexToString_Expect("4d4a0008");

    decodeFourByte_ExpectAndReturn(0x08005a5d, 0x5d5a0008);
    createdHexToString_ExpectAndReturn(0x5d5a0008, 4, "5d5a0008");
    destroyHexToString_Expect("5d5a0008");

    decodeFourByte_ExpectAndReturn(0x08006a6d, 0x6d6a0008);
    createdHexToString_ExpectAndReturn(0x6d6a0008, 4, "6d6a0008");
    destroyHexToString_Expect("6d6a0008");

    decodeFourByte_ExpectAndReturn(0x08007a7d, 0x7d7a0008);
    createdHexToString_ExpectAndReturn(0x7d7a0008, 4, "7d7a0008");
    destroyHexToString_Expect("7d7a0008");

    decodeFourByte_ExpectAndReturn(0x08008a8d, 0x8d8a0008);
    createdHexToString_ExpectAndReturn(0x8d8a0008, 4, "8d8a0008");
    destroyHexToString_Expect("8d8a0008");

    gdbCreateMsgPacket_ExpectAndReturn("4d4a00085d5a00086d6a00087d7a00088d8a0008", "$4d4a00085d5a00086d6a00087d7a00088d8a0008#60");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$4d4a00085d5a00086d6a00087d7a00088d8a0008#60", reply);

    destroyROM();
}

void test_writeMemory_given_0x8000d06_mem_addr_should_write_2_byte_data_in_the_memory_addr(void)
{
    char data[] = "$m8000d00,2:4a4d#5d";

    createROM();

    // rom->address[0x10d06].data = 0x4d4a;
    decodeTwoByte_ExpectAndReturn(0x4a4d, 0x4d4a);

    writeMemory(data);

    // TEST_ASSERT_EQUAL_STRING("$4d4a#2d", rom->address[virtualMemToPhysicalMem(0x8000d06)].data);

    destroyROM();
}
