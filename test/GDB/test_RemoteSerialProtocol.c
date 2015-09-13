#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include <string.h>
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "RemoteSerialProtocol.h"
#include "mock_Packet.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "CException.h"
#include "ErrorSignal.h"
#include "mock_ARMSimulator.h"

extern char *targetCortexM4_XML;
extern char *arm_m_profile;
extern char *arm_vfpv2;
extern int watchpointIndex;

void setUp(void)
{
    initializeWatchpoint();
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

    // gdbCreateMsgPacket_ExpectAndReturn("E01", "$E01#a6");
    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

void test_handleQueryPacket_given_qSupported_should_return_appropriate_response(void)
{
    char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-",
                                       "$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58");
    // gdbCreateMsgPacket_ExpectAndReturn("qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-",
                                       // "$qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#88");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", reply);
    // TEST_ASSERT_EQUAL_STRING("$qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#88", reply);
}

void test_handleQueryPacket_given_qXfer_read_target_should_return_target_xml_description(void)
{
    char data[] = "$qXfer:features:read:target.xml:0,fff#7d";
    char *reply = NULL, dollarSign[] = "$", hashSign[] = "#dd", packet[1024] = "";

    strcat(packet, dollarSign);
    strcat(packet, targetCortexM4_XML);
    strcat(packet, hashSign);
    gdbCreateMsgPacket_ExpectAndReturn(targetCortexM4_XML, packet);

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING(packet, reply);
}

void test_handleQueryPacket_given_qXfer_read_arm_m_profile_should_arm_m_profile_xml_description(void)
{
    char data[] = "$qXfer:features:read:arm-m-profile.xml:0,fff#ee";
    char *reply = NULL, dollarSign[] = "$", hashSign[] = "#27", packet[1024] = "";

    strcat(packet, dollarSign);
    strcat(packet, arm_m_profile);
    strcat(packet, hashSign);
    gdbCreateMsgPacket_ExpectAndReturn(arm_m_profile, packet);

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING(packet, reply);
}

void test_handleQueryPacket_given_qXfer_read_arm_vfpv2_should_return_arm_vfpv2_xml_description(void)
{
    char data[] = "$qXfer:features:read:arm-vfpv2.xml:0,fff#57";
    char *reply = NULL, dollarSign[] = "$", hashSign[] = "#89", packet[1024] = "";

    strcat(packet, dollarSign);
    strcat(packet, arm_vfpv2);
    strcat(packet, hashSign);
    gdbCreateMsgPacket_ExpectAndReturn(arm_vfpv2, packet);

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING(packet, reply);
}

void test_handleQueryPacket_given_qXfer_read_arm_fpa_should_return_appropriate_response(void)
{
    char data[] = "$qXfer:features:read:arm-fpa.xml:0,fff#9a";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
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

void xtest_readSingleRegister_given_data_with_p1a_packet_should_return_first_fpuDoublePrecision_value(void)
{
    char data[] = "$p1a#d1";
    char *reply = NULL;

    initCoreRegister();
    fpuDoublePrecision[0] = 0x2143658778563412;

    decodeEightByte_ExpectAndReturn(0x2143658778563412, 0x1234567887654321);
    createdHexToString_ExpectAndReturn(0x1234567887654321, 8, "1234567887654321");
    gdbCreateMsgPacket_ExpectAndReturn("1234567887654321", "$1234567887654321#48");
    destroyHexToString_Expect("1234567887654321");

    reply = readSingleRegister(data);

    TEST_ASSERT_EQUAL_STRING("$1234567887654321#48", reply);
}

void test_readSingleRegister_given_data_with_p2_packet_should_return_second_coreReg_value(void)
{
    char data[] = "$p2#a2";
    char *reply = NULL;

    initCoreRegister();
    // coreReg[2] = 0x21436587;
    coreReg[2] = 0x21430000;

    // decodeFourByte_ExpectAndReturn(0x21436587, 0x87654321);
    decodeFourByte_ExpectAndReturn(0x21430000, 0x4321);
    // createdHexToString_ExpectAndReturn(0x87654321, 4, "87654321");
    // gdbCreateMsgPacket_ExpectAndReturn("87654321", "$87654321#a4");
    gdbCreateMsgPacket_ExpectAndReturn("00004321", "$00004321#8a");
    // destroyHexToString_Expect("87654321");

    reply = readSingleRegister(data);

    // TEST_ASSERT_EQUAL_STRING("$87654321#a4", reply);
    TEST_ASSERT_EQUAL_STRING("$00004321#8a", reply);
}

void xtest_readSingleRegister_given_data_with_p12_packet_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$p12#d3";
    char *reply = NULL;

    initCoreRegister();

    Try
	{
        reply = readSingleRegister(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_0, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void xtest_readSingleRegister_given_data_with_p_neg_1_packet_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$p-1#ce";
    char *reply = NULL;

    initCoreRegister();

    Try
	{
        reply = readSingleRegister(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_0, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void xtest_readAllRegister_should_return_all_reg_val(void)
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
        else    // PC
        {
            decodeFourByte_ExpectAndReturn(0x01000000, 0x00000001);
            createdHexToString_ExpectAndReturn(0x00000001, 4, "00000001");
            destroyHexToString_Expect("00000001");
        }
    }

    gdbCreateMsgPacket_ExpectAndReturn("0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
                                       "$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001#a5");

    reply = readAllRegister();

    TEST_ASSERT_EQUAL_STRING("$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001#a5", reply);
}

void test_readAllRegister_should_return_all_reg_val_including_fpu_reg(void)
{
    char *reply = NULL;
    int i;

    initCoreRegister();
    coreReg[2] = 0x12345678;
    fpuDoublePrecision[1] = 0x1234567887654321;

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
            else if(i == 13)    //SP
            {
                decodeFourByte_ExpectAndReturn(0x20001000, 0x00100020);
                createdHexToString_ExpectAndReturn(0x00100020, 4, "00100020");
                destroyHexToString_Expect("00100020");
            }
            else
            {
                decodeFourByte_ExpectAndReturn(0x00000000, 0x00000000);
                createdHexToString_ExpectAndReturn(0x00000000, 4, "00000000");
                destroyHexToString_Expect("00000000");
            }
        }
        else    // PC
        {
            decodeFourByte_ExpectAndReturn(0x01000000, 0x00000001);
            createdHexToString_ExpectAndReturn(0x00000001, 4, "00000001");
            destroyHexToString_Expect("00000001");
        }
    }

    for(i = 0; i < 16; i++)
    {
        if(i == 1)
        {
            decodeEightByte_ExpectAndReturn(0x1234567887654321, 0x2143658778563412);
            createdHexToString_ExpectAndReturn(0x2143658778563412, 8, "2143658778563412");
            destroyHexToString_Expect("2143658778563412");
        }
        else
        {
            decodeEightByte_ExpectAndReturn(0x0000000000000000, 0x0000000000000000);
            createdHexToString_ExpectAndReturn(0x0000000000000000, 8, "0000000000000000");
            destroyHexToString_Expect("0000000000000000");
        }
    }

    decodeFourByte_ExpectAndReturn(0x00000000, 0x00000000);
    createdHexToString_ExpectAndReturn(0x00000000, 4, "00000000");
    destroyHexToString_Expect("00000000");

    gdbCreateMsgPacket_ExpectAndReturn("0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000100020000000000000000000000001000000000000000021436587785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                                       "$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000100020000000000000000000000001000000000000000021436587785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000#70");

    reply = readAllRegister();

    TEST_ASSERT_EQUAL_STRING("$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000100020000000000000000000000001000000000000000021436587785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000#70", reply);
}

void test_writeSingleRegister_given_data_with_P6_should_update_sixth_coreReg_value(void)
{
    char data[] = "$P6=fe090008#23";
    char *reply = NULL;

    initCoreRegister();

    decodeFourByte_ExpectAndReturn(0xfe090008, 0x080009fe);
    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeSingleRegister(data);

    TEST_ASSERT_EQUAL(0x080009fe, coreReg[6]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void test_writeSingleRegister_given_P1b_should_update_the_second_fpuDoublePrecision_and_fpuSinglePrecision(void)
{
    char data[] = "$P1b=1234567887654321#68";
    char *reply = NULL;

    initCoreRegister();

    decodeEightByte_ExpectAndReturn(0x1234567887654321, 0x2143658778563412);
    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeSingleRegister(data);

    TEST_ASSERT_EQUAL(0x2143658778563412, fpuDoublePrecision[1]);
    TEST_ASSERT_EQUAL(0x78563412, fpuSinglePrecision[2]);
    TEST_ASSERT_EQUAL(0x21436587, fpuSinglePrecision[3]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void test_writeSingleRegister_given_data_with_P30_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$P30=1234567887654321#38";
    char *reply = NULL;

    initCoreRegister();

    Try
	{
        reply = writeSingleRegister(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_0, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeSingleRegister_given_data_with_P_neg_5_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$P-5=12345678#93";
    char *reply = NULL;

    initCoreRegister();

    Try
	{
        reply = writeSingleRegister(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_0, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeAllRegister_given_following_data_should_write_value_to_all_registers(void)
{
    char data[] = "$G00000000111111118cff0120333333334444444455555555666666667777777788888888500b0008aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffff00000001#69";
    char *reply = NULL;

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

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeAllRegister(data);

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

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void test_writeAllRegister_given_following_data_should_write_value_to_all_registers_including_fpu_reg(void)
{
    char data[] = "$G00000000111111118cff0120333333334444444455555555666666667777777788888888500b0008aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffff0000000100000000000000000101010101010101020202020202020203030303030303030404040404040404050505050505050506060606060606060707070707070707080808080808080809090909090909090a0a0a0a0a0a0a0a0b0b0b0b0b0b0b0b0c0c0c0c0c0c0c0c0d0d0d0d0d0d0d0d0e0e0e0e0e0e0e0e0f0f0f0f0f0f0f0fabababab#85";
    char *reply = NULL;

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
    decodeEightByte_ExpectAndReturn(0x0000000000000000, 0x0000000000000000);
    decodeEightByte_ExpectAndReturn(0x0101010101010101, 0x0101010101010101);
    decodeEightByte_ExpectAndReturn(0x0202020202020202, 0x0202020202020202);
    decodeEightByte_ExpectAndReturn(0x0303030303030303, 0x0303030303030303);
    decodeEightByte_ExpectAndReturn(0x0404040404040404, 0x0404040404040404);
    decodeEightByte_ExpectAndReturn(0x0505050505050505, 0x0505050505050505);
    decodeEightByte_ExpectAndReturn(0x0606060606060606, 0x0606060606060606);
    decodeEightByte_ExpectAndReturn(0x0707070707070707, 0x0707070707070707);
    decodeEightByte_ExpectAndReturn(0x0808080808080808, 0x0808080808080808);
    decodeEightByte_ExpectAndReturn(0x0909090909090909, 0x0909090909090909);
    decodeEightByte_ExpectAndReturn(0x0a0a0a0a0a0a0a0a, 0x0a0a0a0a0a0a0a0a);
    decodeEightByte_ExpectAndReturn(0x0b0b0b0b0b0b0b0b, 0x0b0b0b0b0b0b0b0b);
    decodeEightByte_ExpectAndReturn(0x0c0c0c0c0c0c0c0c, 0x0c0c0c0c0c0c0c0c);
    decodeEightByte_ExpectAndReturn(0x0d0d0d0d0d0d0d0d, 0x0d0d0d0d0d0d0d0d);
    decodeEightByte_ExpectAndReturn(0x0e0e0e0e0e0e0e0e, 0x0e0e0e0e0e0e0e0e);
    decodeEightByte_ExpectAndReturn(0x0f0f0f0f0f0f0f0f, 0x0f0f0f0f0f0f0f0f);
    decodeFourByte_ExpectAndReturn(0xabababab, 0xabababab);
    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeAllRegister(data);

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
    TEST_ASSERT_EQUAL(0xabababab, coreReg[fPSCR]);
    TEST_ASSERT_EQUAL(0x0000000000000000, fpuDoublePrecision[0]);
    TEST_ASSERT_EQUAL(0x0101010101010101, fpuDoublePrecision[1]);
    TEST_ASSERT_EQUAL(0x0202020202020202, fpuDoublePrecision[2]);
    TEST_ASSERT_EQUAL(0x0303030303030303, fpuDoublePrecision[3]);
    TEST_ASSERT_EQUAL(0x0404040404040404, fpuDoublePrecision[4]);
    TEST_ASSERT_EQUAL(0x0505050505050505, fpuDoublePrecision[5]);
    TEST_ASSERT_EQUAL(0x0606060606060606, fpuDoublePrecision[6]);
    TEST_ASSERT_EQUAL(0x0707070707070707, fpuDoublePrecision[7]);
    TEST_ASSERT_EQUAL(0x0808080808080808, fpuDoublePrecision[8]);
    TEST_ASSERT_EQUAL(0x0909090909090909, fpuDoublePrecision[9]);
    TEST_ASSERT_EQUAL(0x0a0a0a0a0a0a0a0a, fpuDoublePrecision[10]);
    TEST_ASSERT_EQUAL(0x0b0b0b0b0b0b0b0b, fpuDoublePrecision[11]);
    TEST_ASSERT_EQUAL(0x0c0c0c0c0c0c0c0c, fpuDoublePrecision[12]);
    TEST_ASSERT_EQUAL(0x0d0d0d0d0d0d0d0d, fpuDoublePrecision[13]);
    TEST_ASSERT_EQUAL(0x0e0e0e0e0e0e0e0e, fpuDoublePrecision[14]);
    TEST_ASSERT_EQUAL(0x0f0f0f0f0f0f0f0f, fpuDoublePrecision[15]);
    TEST_ASSERT_EQUAL(0, fpuSinglePrecision[0]);
    TEST_ASSERT_EQUAL(0, fpuSinglePrecision[1]);
    TEST_ASSERT_EQUAL(0x01010101, fpuSinglePrecision[2]);
    TEST_ASSERT_EQUAL(0x01010101, fpuSinglePrecision[3]);
    TEST_ASSERT_EQUAL(0x02020202, fpuSinglePrecision[4]);
    TEST_ASSERT_EQUAL(0x02020202, fpuSinglePrecision[5]);
    TEST_ASSERT_EQUAL(0x03030303, fpuSinglePrecision[6]);
    TEST_ASSERT_EQUAL(0x03030303, fpuSinglePrecision[7]);
    TEST_ASSERT_EQUAL(0x04040404, fpuSinglePrecision[8]);
    TEST_ASSERT_EQUAL(0x04040404, fpuSinglePrecision[9]);
    TEST_ASSERT_EQUAL(0x05050505, fpuSinglePrecision[10]);
    TEST_ASSERT_EQUAL(0x05050505, fpuSinglePrecision[11]);
    TEST_ASSERT_EQUAL(0x06060606, fpuSinglePrecision[12]);
    TEST_ASSERT_EQUAL(0x06060606, fpuSinglePrecision[13]);
    TEST_ASSERT_EQUAL(0x07070707, fpuSinglePrecision[14]);
    TEST_ASSERT_EQUAL(0x07070707, fpuSinglePrecision[15]);
    TEST_ASSERT_EQUAL(0x08080808, fpuSinglePrecision[16]);
    TEST_ASSERT_EQUAL(0x08080808, fpuSinglePrecision[17]);
    TEST_ASSERT_EQUAL(0x09090909, fpuSinglePrecision[18]);
    TEST_ASSERT_EQUAL(0x09090909, fpuSinglePrecision[19]);
    TEST_ASSERT_EQUAL(0x0a0a0a0a, fpuSinglePrecision[20]);
    TEST_ASSERT_EQUAL(0x0a0a0a0a, fpuSinglePrecision[21]);
    TEST_ASSERT_EQUAL(0x0b0b0b0b, fpuSinglePrecision[22]);
    TEST_ASSERT_EQUAL(0x0b0b0b0b, fpuSinglePrecision[23]);
    TEST_ASSERT_EQUAL(0x0c0c0c0c, fpuSinglePrecision[24]);
    TEST_ASSERT_EQUAL(0x0c0c0c0c, fpuSinglePrecision[25]);
    TEST_ASSERT_EQUAL(0x0d0d0d0d, fpuSinglePrecision[26]);
    TEST_ASSERT_EQUAL(0x0d0d0d0d, fpuSinglePrecision[27]);
    TEST_ASSERT_EQUAL(0x0e0e0e0e, fpuSinglePrecision[28]);
    TEST_ASSERT_EQUAL(0x0e0e0e0e, fpuSinglePrecision[29]);
    TEST_ASSERT_EQUAL(0x0f0f0f0f, fpuSinglePrecision[30]);
    TEST_ASSERT_EQUAL(0x0f0f0f0f, fpuSinglePrecision[31]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void xtest_readMemory_given_m0_and_2_should_retrieve_memory_content_start_from_0x0(void)
{
    char data[] = "$m0,2#fb";
    char *reply = NULL;

    memoryBlock[0] = 0x20;
    memoryBlock[1] = 0x3f;

    createdHexToString_ExpectAndReturn(0x20, 1, "20");
    destroyHexToString_Expect("20");
    createdHexToString_ExpectAndReturn(0x3f, 1, "3f");
    destroyHexToString_Expect("3f");
    gdbCreateMsgPacket_ExpectAndReturn("203f", "$203f#fb");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$203f#fb", reply);
}

void test_readMemory_given_m80009d6_and_4_should_retrieve_memory_content_start_from_0x080009d6(void)
{
    char data[] = "$m80009d6,4#68";
    char *reply = NULL;

    memoryBlock[virtualMemToPhysicalMem(0x80009d6)] = 0xf6;
    memoryBlock[virtualMemToPhysicalMem(0x80009d6 + 1)] = 0x43;
    memoryBlock[virtualMemToPhysicalMem(0x80009d6 + 2)] = 0x70;
    memoryBlock[virtualMemToPhysicalMem(0x80009d6 + 3)] = 0xff;

    createdHexToString_ExpectAndReturn(0xf6, 1, "f6");
    destroyHexToString_Expect("f6");
    createdHexToString_ExpectAndReturn(0x43, 1, "43");
    destroyHexToString_Expect("43");
    createdHexToString_ExpectAndReturn(0x70, 1, "70");
    destroyHexToString_Expect("70");
    createdHexToString_ExpectAndReturn(0xff, 1, "ff");
    destroyHexToString_Expect("ff");
    gdbCreateMsgPacket_ExpectAndReturn("f64370ff", "$f64370ff#36");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$f64370ff#36", reply);
}

void test_readMemory_given_m0_and_neg_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$m0,-2#28";
    char *reply = NULL;

    Try
	{
        reply = readMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_readMemory_given_m7ffffff_and_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$m7ffffff,2#28";
    char *reply = NULL;

    Try
	{
        reply = readMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeMemory_given_M8000d06_and_2_should_write_2_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,2:0010#38";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x00, memoryBlock[virtualMemToPhysicalMem(0x8000d06)]);
    TEST_ASSERT_EQUAL(0x10, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 1)]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void test_writeMemory_given_M8000d06_and_4_should_write_4_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,4:00100020#fc";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x00, memoryBlock[virtualMemToPhysicalMem(0x8000d06)]);
    TEST_ASSERT_EQUAL(0x10, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 1)]);
    TEST_ASSERT_EQUAL(0x00, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 2)]);
    TEST_ASSERT_EQUAL(0x20, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 3)]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void test_writeMemory_given_M8000d06_and_neg_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,-2:4ff0#d4";
    char *reply = NULL;

    Try
	{
        reply = writeMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeMemory_given_M7ffffff_and_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M7ffffff,2:4ff0#d4";
    char *reply = NULL;

    Try
	{
        reply = writeMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeMemory_given_M8000d06_and_2_with_more_data_supply_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,2:4ff0fff0#d4";
    char *reply = NULL;

    Try
	{
        reply = writeMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeMemory_given_M8000d06_and_2_with_no_data_supply_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,2:#d4";
    char *reply = NULL;

    Try
	{
        reply = writeMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_writeMemory_given_M8000d06_and_2_with_less_data_supply_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,2:4f#d4";
    char *reply = NULL;

    Try
	{
        reply = writeMemory(data);
    }
    Catch(errorSignal)
	{
		TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_step_given_following_data_should_step_through_the_instruction(void)
{
    char data[] = "$s#73";
    char *reply = NULL;

    armStep_Expect();
    createdHexToString_ExpectAndReturn(GDB_SIGNAL_TRAP, 1, "05");
    destroyHexToString_Expect("05");
    gdbCreateMsgPacket_ExpectAndReturn("S05", "$S05#b8");

    reply = step(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
}

void test_addBreakpoint_given_0x80009d6_should_add_0x80009d6_bp_addr_into_Breakpoint_list(void)
{
    addBreakpoint(&bp, 0x80009d6);

    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    deleteAllBreakpoint(&bp);
    TEST_ASSERT_NULL(bp);
}

void test_addBreakpoint_given_several_addr_should_add_all_bp_addr_into_Breakpoint_list(void)
{
    addBreakpoint(&bp, 0x80009d6);
    addBreakpoint(&bp, 0x8000ab6);
    addBreakpoint(&bp, 0x8000bc6);

    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NOT_NULL(bp->next);
    TEST_ASSERT_NOT_NULL(bp->next->next);
    TEST_ASSERT_NULL(bp->next->next->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);
    TEST_ASSERT_EQUAL(0x8000ab6, bp->next->addr);
    TEST_ASSERT_EQUAL(0x8000bc6, bp->next->next->addr);

    deleteAllBreakpoint(&bp);
}

void test_addBreakpoint_given_several_addr_should_add_all_bp_addr_into_Breakpoint_list_according_to_addr(void)
{
    addBreakpoint(&bp, 0x80009d6);
    addBreakpoint(&bp, 0x8000bc6);
    addBreakpoint(&bp, 0x8000ab6);

    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NOT_NULL(bp->next);
    TEST_ASSERT_NOT_NULL(bp->next->next);
    TEST_ASSERT_NULL(bp->next->next->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);
    TEST_ASSERT_EQUAL(0x8000ab6, bp->next->addr);
    TEST_ASSERT_EQUAL(0x8000bc6, bp->next->next->addr);

    deleteAllBreakpoint(&bp);
}

void test_removeBreakpoint_given_0x80009d6_should_remove_bp_from_Breakpoint_list(void)
{
    addBreakpoint(&bp, 0x80009d6);
    removeBreakpoint(&bp, 0x80009d6);

    TEST_ASSERT_NULL(bp);

    deleteAllBreakpoint(&bp);
}

void test_removeBreakpoint_given_several_addr_should_remove_0x8000ab6_bp_from_Breakpoint_list(void)
{
    addBreakpoint(&bp, 0x80009d6);
    addBreakpoint(&bp, 0x8000ab6);
    addBreakpoint(&bp, 0x8000bc6);
    removeBreakpoint(&bp, 0x8000ab6);

    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NOT_NULL(bp->next);
    TEST_ASSERT_NULL(bp->next->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);
    TEST_ASSERT_EQUAL(0x8000bc6, bp->next->addr);

    deleteAllBreakpoint(&bp);
}

void test_insertBreakpointOrWatchpoint_given_Z0_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$Z0,80009d6,2#af";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = insertBreakpointOrWatchpoint(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    deleteAllBreakpoint(&bp);
}

void test_insertBreakpointOrWatchpoint_given_Z0_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$Z0,7ffffff,2#af";
    char *reply = NULL;

    Try
    {
        reply = insertBreakpointOrWatchpoint(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_insertBreakpointOrWatchpoint_given_Z1_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$Z1,80009d6,2#b0";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = insertBreakpointOrWatchpoint(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    deleteAllBreakpoint(&bp);
}

void test_insertBreakpointOrWatchpoint_given_Z1_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$Z1,7ffffff,2#b0";
    char *reply = NULL;

    Try
    {
        reply = insertBreakpointOrWatchpoint(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_insertBreakpointOrWatchpoint_given_Z3_and_Z2_should_insert_read_and_write_watchpoint_at_0x20000000_and_0x20000010_respectively(void)
{
    char data[] = "$Z3,20000000,2#99";
    char *reply = NULL;

    watchpointIndex = 0;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = insertBreakpointOrWatchpoint(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_READ, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(2, wp[0].size);

    char data2[] = "$Z2,20000010,4#9c";

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = insertBreakpointOrWatchpoint(data2);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_WRITE, wp[1].type);
    TEST_ASSERT_EQUAL(0x20000010, wp[1].addr);
    TEST_ASSERT_EQUAL(4, wp[1].size);
}

void test_removeBreakpointOrWatchpoint_given_z0_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$Z0,80009d6,2#af";
    char *reply = NULL;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = insertBreakpointOrWatchpoint(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    char data2[] = "$z0,80009d6,2#cf";

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = removeBreakpointOrWatchpoint(data2);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NULL(bp);

    deleteAllBreakpoint(&bp);
}

void test_removeBreakpointOrWatchpoint_given_z0_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$z0,7ffffff,2#cf";
    char *reply = NULL;

    Try
    {
        reply = removeBreakpointOrWatchpoint(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_removeBreakpointOrWatchpoint_given_z1_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$z1,80009d6,2#d0";
    char *reply = NULL;

    addBreakpoint(&bp, 0x80009d6);
    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = removeBreakpointOrWatchpoint(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NULL(bp);

    deleteAllBreakpoint(&bp);
}

void test_removeBreakpointOrWatchpoint_given_z1_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$z1,7ffffff,2#d0";
    char *reply = NULL;

    Try
    {
        reply = removeBreakpointOrWatchpoint(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		printf("Error signal: %x\n", errorSignal);
	}

    TEST_ASSERT_EQUAL_STRING(NULL, reply);
}

void test_removeBreakpointOrWatchpoint_given_z3_and_z2_should_insert_read_and_write_watchpoint_at_0x20000000_and_0x20000010_respectively(void)
{
    char data[] = "$Z3,20000000,2#99";
    char data2[] = "$Z2,20000010,4#9c";
    char *reply = NULL;

    watchpointIndex = 0;

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = insertBreakpointOrWatchpoint(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = insertBreakpointOrWatchpoint(data2);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    char data3[] = "$z3,20000000,2#b9";
    char data4[] = "$z2,20000010,4#bc";

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = removeBreakpointOrWatchpoint(data3);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_WRITE, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000010, wp[0].addr);
    TEST_ASSERT_EQUAL(4, wp[0].size);
    TEST_ASSERT_EQUAL(NONE, wp[1].type);
    TEST_ASSERT_EQUAL(0, wp[1].addr);
    TEST_ASSERT_EQUAL(0, wp[1].size);

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");
    reply = removeBreakpointOrWatchpoint(data4);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(NONE, wp[0].type);
    TEST_ASSERT_EQUAL(0, wp[0].addr);
    TEST_ASSERT_EQUAL(0, wp[0].size);
}

void test_findBreakpoint_given_no_breakpoint_in_breakpoint_lits_should_return_0(void)
{
    resetMemoryBlock();
    coreReg[PC] = 0x80009d6;

    TEST_ASSERT_EQUAL(0, findBreakpoint(bp));
    TEST_ASSERT_NULL(bp);

    deleteAllBreakpoint(&bp);
}

void test_findBreakpoint_given_0x80009d6_in_breakpoint_lits_and_PC_is_0x80009d6_should_return_1(void)
{
    resetMemoryBlock();
    coreReg[PC] = 0x80009d6;
    addBreakpoint(&bp, 0x80009d6);

    TEST_ASSERT_EQUAL(1, findBreakpoint(bp));
    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    deleteAllBreakpoint(&bp);
}

void test_findBreakpoint_given_0x80009d6_in_breakpoint_lits_and_PC_is_0x80009d0_should_return_0(void)
{
    resetMemoryBlock();
    coreReg[PC] = 0x80009d0;
    addBreakpoint(&bp, 0x80009d6);

    TEST_ASSERT_EQUAL(0, findBreakpoint(bp));
    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    deleteAllBreakpoint(&bp);
}

void test_findBreakpoint_given_0x80009d6_in_breakpoint_lits_and_PC_is_0x80009d0_should_return_1_when_it_reach_during_while_loop(void)
{
    resetMemoryBlock();
    coreReg[PC] = 0x80009d0;
    addBreakpoint(&bp, 0x80009d6);

    while(!findBreakpoint(bp))
    {
        coreReg[PC] += 2;
    }

    TEST_ASSERT_EQUAL(1, findBreakpoint(bp));
    TEST_ASSERT_NOT_NULL(bp);
    TEST_ASSERT_NULL(bp->next);
    TEST_ASSERT_EQUAL(0x80009d6, bp->addr);

    deleteAllBreakpoint(&bp);
}

void test_initializeWatchpoint_should_initialize_all_4_watchpoint(void)
{
    int i;

    for(i = 0; i < MAX_HW_WATCHPOINT; i++)
    {
        TEST_ASSERT_EQUAL(NONE, wp[i].type);
        TEST_ASSERT_EQUAL(0, wp[i].addr);
        TEST_ASSERT_EQUAL(0, wp[i].size);
    }
}

void test_addWatchpoint_given_the_address_0x20000000_size_2_and_WP_WRITE_type_should_add_watchpoint(void)
{
    watchpointIndex = 0;
    addWatchpoint(0x20000000, 2, WP_WRITE);

    TEST_ASSERT_EQUAL(WP_WRITE, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(2, wp[0].size);
}

void test_addWatchpoint_given_several_address_size_type_should_add_all_watchpoint(void)
{
    watchpointIndex = 0;

    addWatchpoint(0x20000002, 2, WP_WRITE);
    addWatchpoint(0x20000004, 4, WP_WRITE);

    TEST_ASSERT_EQUAL(WP_WRITE, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000002, wp[0].addr);
    TEST_ASSERT_EQUAL(2, wp[0].size);

    TEST_ASSERT_EQUAL(WP_WRITE, wp[1].type);
    TEST_ASSERT_EQUAL(0x20000004, wp[1].addr);
    TEST_ASSERT_EQUAL(4, wp[1].size);
}

void test_removeWatchpoint_given_the_address_0x20000000_size_2_and_WP_WRITE_type_should_delete_watchpoint(void)
{
    watchpointIndex = 0;
    addWatchpoint(0x20000000, 2, WP_WRITE);
    removeWatchpoint(0x20000000, 2, WP_WRITE);

    TEST_ASSERT_EQUAL(NONE, wp[0].type);
    TEST_ASSERT_EQUAL(0, wp[0].addr);
    TEST_ASSERT_EQUAL(0, wp[0].size);
    TEST_ASSERT_EQUAL(0, watchpointIndex);
}

void test_removeWatchpoint_given_several_address_size_type_should_delete_watchpoint(void)
{
    watchpointIndex = 0;
    addWatchpoint(0x20000000, 2, WP_WRITE);
    addWatchpoint(0x20000010, 4, WP_WRITE);
    addWatchpoint(0x20000006, 4, WP_READ);
    removeWatchpoint(0x20000010, 4, WP_WRITE);

    TEST_ASSERT_EQUAL(WP_WRITE, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(2, wp[0].size);

    TEST_ASSERT_EQUAL(WP_READ, wp[1].type);
    TEST_ASSERT_EQUAL(0x20000006, wp[1].addr);
    TEST_ASSERT_EQUAL(4, wp[1].size);

    TEST_ASSERT_EQUAL(NONE, wp[2].type);
    TEST_ASSERT_EQUAL(0, wp[2].addr);
    TEST_ASSERT_EQUAL(0, wp[2].size);
    TEST_ASSERT_EQUAL(2, watchpointIndex);
}
