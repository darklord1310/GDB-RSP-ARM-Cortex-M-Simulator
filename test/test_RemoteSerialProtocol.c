#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include <string.h>
#include "ARMRegisters.h"
#include "ROM.h"
#include "RemoteSerialProtocol.h"
#include "mock_Packet.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "CException.h"
#include "ErrorSignal.h"
#include "ARMSimulator.h"
#include "ConditionalExecution.h"
#include "StatusRegisters.h"
#include "Thumb16bitsTable.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "ModifiedImmediateConstant.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ITandHints.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"

extern char *targetCortexM4_XML;
extern char *arm_m_profile;
extern char *arm_vfpv2;

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

void test_readSingleRegister_given_data_with_p1a_packet_should_return_first_fpuDoublePrecision_value(void)
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
    coreReg[2] = 0x21436587;

    decodeFourByte_ExpectAndReturn(0x21436587, 0x87654321);
    createdHexToString_ExpectAndReturn(0x87654321, 4, "87654321");
    gdbCreateMsgPacket_ExpectAndReturn("87654321", "$87654321#a4");
    destroyHexToString_Expect("87654321");

    reply = readSingleRegister(data);

    TEST_ASSERT_EQUAL_STRING("$87654321#a4", reply);
}

void test_readSingleRegister_given_data_with_p12_packet_should_throw_GDB_SIGNAL_0(void)
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

void test_readSingleRegister_given_data_with_p_neg_1_packet_should_throw_GDB_SIGNAL_0(void)
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
        else
        {
            decodeFourByte_ExpectAndReturn(0x01000000, 0x00000001);
            createdHexToString_ExpectAndReturn(0x00000001, 4, "00000001");
            destroyHexToString_Expect("00000001");
        }
    }

    for(i = 0; i < 16; i++)
    {
        decodeEightByte_ExpectAndReturn(0x0000000000000000, 0x0000000000000000);
        createdHexToString_ExpectAndReturn(0x0000000000000000, 8, "0000000000000000");
        destroyHexToString_Expect("0000000000000000");
    }

    decodeFourByte_ExpectAndReturn(0x00000000, 0x00000000);
    createdHexToString_ExpectAndReturn(0x00000000, 4, "00000000");
    destroyHexToString_Expect("00000000");

    gdbCreateMsgPacket_ExpectAndReturn("0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                                       "$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000#25");

    reply = readAllRegister();

    TEST_ASSERT_EQUAL_STRING("$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000#25", reply);
}

void test_writeSingleRegister_given_data_with_P6_should_write_value_sixth_coreReg(void)
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

void test_writeSingleRegister_given_P1b_should_write_value_second_fpuDoublePrecision_and_update_the_fpuSinglePrecision(void)
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

void xtest_writeAllRegister_given_following_data_should_write_value_to_all_registers(void)
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
    decodeEightByte_ExpectAndReturn(0x0478000000000000, 0x0000000000007804);
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
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
}

void test_readMemory_given_m0_and_2_should_retrieve_memory_content_start_from_0x0(void)
{
    char data[] = "$m0,2#fb";
    char *reply = NULL;

    createROM();

    rom->address[0x0].data = 0x20;
    rom->address[0x1].data = 0x3f;

    createdHexToString_ExpectAndReturn(0x20, 1, "20");
    destroyHexToString_Expect("20");
    createdHexToString_ExpectAndReturn(0x3f, 1, "3f");
    destroyHexToString_Expect("3f");
    gdbCreateMsgPacket_ExpectAndReturn("3f20", "$3f20#fb");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$3f20#fb", reply);

    destroyROM();
}

void test_readMemory_given_m80009d6_and_4_should_retrieve_memory_content_start_from_0x080009d6(void)
{
    char data[] = "$m80009d6,4#68";
    char *reply = NULL;

    createROM();

    rom->address[virtualMemToPhysicalMem(0x80009d6)].data = 0xf6;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 1)].data = 0x43;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 2)].data = 0x70;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 3)].data = 0xff;

    createdHexToString_ExpectAndReturn(0xf6, 1, "f6");
    destroyHexToString_Expect("f6");
    createdHexToString_ExpectAndReturn(0x43, 1, "43");
    destroyHexToString_Expect("43");
    createdHexToString_ExpectAndReturn(0x70, 1, "70");
    destroyHexToString_Expect("70");
    createdHexToString_ExpectAndReturn(0xff, 1, "ff");
    destroyHexToString_Expect("ff");
    gdbCreateMsgPacket_ExpectAndReturn("43f6ff70", "$43f6ff70#36");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$43f6ff70#36", reply);

    destroyROM();
}

void test_writeMemory_given_M8000d06_and_2_should_write_2_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,2:0010#38";
    char *reply = NULL;

    createROM();

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x10, rom->address[virtualMemToPhysicalMem(0x8000d06)].data);
    TEST_ASSERT_EQUAL(0x00, rom->address[virtualMemToPhysicalMem(0x8000d06 + 1)].data);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    destroyROM();
}

void test_writeMemory_given_M8000d06_and_4_should_write_4_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,4:00100020#fc";
    char *reply = NULL;

    createROM();

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x10, rom->address[virtualMemToPhysicalMem(0x8000d06)].data);
    TEST_ASSERT_EQUAL(0x00, rom->address[virtualMemToPhysicalMem(0x8000d06 + 1)].data);
    TEST_ASSERT_EQUAL(0x20, rom->address[virtualMemToPhysicalMem(0x8000d06 + 2)].data);
    TEST_ASSERT_EQUAL(0x00, rom->address[virtualMemToPhysicalMem(0x8000d06 + 3)].data);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    destroyROM();
}
/*
void test_readMemory_given_m0_and_2_should_retrieve_memory_content_start_from_0x0(void)
{
    char data[] = "$m0,2#fb";
    char *reply = NULL;

    createROM();

    rom->address[0x0].data = 0xf0;
    rom->address[0x1].data = 0x4f;

    createdHexToString_ExpectAndReturn(0xf0, 1, "f0");
    destroyHexToString_Expect("f0");
    createdHexToString_ExpectAndReturn(0x4f, 1, "4f");
    destroyHexToString_Expect("4f");
    gdbCreateMsgPacket_ExpectAndReturn("4ff0", "$4ff0#30");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$4ff0#30", reply);

    destroyROM();
}

void test_readMemory_given_m80009d6_and_4_should_retrieve_memory_content_start_from_0x080009d6(void)
{
    char data[] = "$m80009d6,4#68";
    char *reply = NULL;

    createROM();

    rom->address[virtualMemToPhysicalMem(0x80009d6)].data = 0x02;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 1)].data = 0x00;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 2)].data = 0xf0;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 3)].data = 0x4f;

    createdHexToString_ExpectAndReturn(0x02, 1, "02");
    destroyHexToString_Expect("02");
    createdHexToString_ExpectAndReturn(0x00, 1, "00");
    destroyHexToString_Expect("00");
    createdHexToString_ExpectAndReturn(0xf0, 1, "f0");
    destroyHexToString_Expect("f0");
    createdHexToString_ExpectAndReturn(0x4f, 1, "4f");
    destroyHexToString_Expect("4f");
    gdbCreateMsgPacket_ExpectAndReturn("4ff00002", "$4ff00002#f2");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$4ff00002#f2", reply);

    destroyROM();
}

void test_readMemory_given_m80009d6_and_10_should_retrieve_memory_content_start_from_0x080009d6(void)
{
    char data[] = "$m80009d6,a#95";
    char *reply = NULL;

    createROM();

    rom->address[virtualMemToPhysicalMem(0x80009d6)].data = 0x02;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 1)].data = 0x00;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 2)].data = 0xf0;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 3)].data = 0x4f;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 4)].data = 0x08;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 5)].data = 0x00;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 6)].data = 0x10;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 7)].data = 0x24;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 8)].data = 0xad;
    rom->address[virtualMemToPhysicalMem(0x80009d6 + 9)].data = 0xde;

    createdHexToString_ExpectAndReturn(0x02, 1, "02");
    destroyHexToString_Expect("02");
    createdHexToString_ExpectAndReturn(0x00, 1, "00");
    destroyHexToString_Expect("00");
    createdHexToString_ExpectAndReturn(0xf0, 1, "f0");
    destroyHexToString_Expect("f0");
    createdHexToString_ExpectAndReturn(0x4f, 1, "4f");
    destroyHexToString_Expect("4f");
    createdHexToString_ExpectAndReturn(0x08, 1, "08");
    destroyHexToString_Expect("08");
    createdHexToString_ExpectAndReturn(0x00, 1, "00");
    destroyHexToString_Expect("00");
    createdHexToString_ExpectAndReturn(0x10, 1, "10");
    destroyHexToString_Expect("10");
    createdHexToString_ExpectAndReturn(0x24, 1, "24");
    destroyHexToString_Expect("24");
    createdHexToString_ExpectAndReturn(0xad, 1, "ad");
    destroyHexToString_Expect("ad");
    createdHexToString_ExpectAndReturn(0xde, 1, "de");
    destroyHexToString_Expect("de");
    gdbCreateMsgPacket_ExpectAndReturn("4ff0000224100008dead", "$4ff0000224100008dead#0f");

    reply = readMemory(data);

    TEST_ASSERT_EQUAL_STRING("$4ff0000224100008dead#0f", reply);

    destroyROM();
}

void test_readMemory_given_m0_and_neg_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$m0,-2#28";
    char *reply = NULL;

    createROM();

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

    destroyROM();
}

void test_writeMemory_given_M8000d06_and_2_should_write_2_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,2:4a4d#a4";
    char *reply = NULL;

    createROM();

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x4d, rom->address[virtualMemToPhysicalMem(0x8000d06)].data);
    TEST_ASSERT_EQUAL(0x4a, rom->address[virtualMemToPhysicalMem(0x8000d06 + 1)].data);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    destroyROM();
}

void test_writeMemory_given_M8000d06_and_4_should_write_4_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,4:4ff00008#71";
    char *reply = NULL;

    createROM();

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x08, rom->address[virtualMemToPhysicalMem(0x8000d06)].data);
    TEST_ASSERT_EQUAL(0x00, rom->address[virtualMemToPhysicalMem(0x8000d06 + 1)].data);
    TEST_ASSERT_EQUAL(0xf0, rom->address[virtualMemToPhysicalMem(0x8000d06 + 2)].data);
    TEST_ASSERT_EQUAL(0x4f, rom->address[virtualMemToPhysicalMem(0x8000d06 + 3)].data);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    destroyROM();
}

void test_writeMemory_given_M8000d06_and_10_should_write_10_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,a:4ff00008094b9a424a4d#ca";
    char *reply = NULL;

    createROM();

    gdbCreateMsgPacket_ExpectAndReturn("OK", "$OK#9a");

    reply = writeMemory(data);

    TEST_ASSERT_EQUAL(0x08, rom->address[virtualMemToPhysicalMem(0x8000d06)].data);
    TEST_ASSERT_EQUAL(0x00, rom->address[virtualMemToPhysicalMem(0x8000d06 + 1)].data);
    TEST_ASSERT_EQUAL(0xf0, rom->address[virtualMemToPhysicalMem(0x8000d06 + 2)].data);
    TEST_ASSERT_EQUAL(0x4f, rom->address[virtualMemToPhysicalMem(0x8000d06 + 3)].data);

    TEST_ASSERT_EQUAL(0x42, rom->address[virtualMemToPhysicalMem(0x8000d06 + 4)].data);
    TEST_ASSERT_EQUAL(0x9a, rom->address[virtualMemToPhysicalMem(0x8000d06 + 5)].data);
    TEST_ASSERT_EQUAL(0x4b, rom->address[virtualMemToPhysicalMem(0x8000d06 + 6)].data);
    TEST_ASSERT_EQUAL(0x09, rom->address[virtualMemToPhysicalMem(0x8000d06 + 7)].data);

    TEST_ASSERT_EQUAL(0x4d, rom->address[virtualMemToPhysicalMem(0x8000d06 + 8)].data);
    TEST_ASSERT_EQUAL(0x4a, rom->address[virtualMemToPhysicalMem(0x8000d06 + 9)].data);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    destroyROM();
}

void test_writeMemory_given_M8000d06_and_neg_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,-2:4ff0#d4";
    char *reply = NULL;

    createROM();

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

    destroyROM();
} */
/*
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
} */