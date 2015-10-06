#include <malloc.h>
#include <string.h>
#include <math.h>
#include "unity.h"
#include "ServeRSP.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
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
#include "LDRImmediate.h"
#include "LDRLiteral.h"
#include "SVC.h"
#include "ADR.h"
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "CLZ.h"
#include "SUBSPRegister.h"
#include "BL.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "ExceptionObject.h"
#include "BKPT.h"


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

void test_serveRSP_given_qSupported_query_packet_should_return_appropriate_response(void)
{
	char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", reply);
    // TEST_ASSERT_EQUAL_STRING("$qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#88", reply);

    free(reply);
}

void test_serveRSP_given_qXfer_read_target_should_return_target_xml_description(void)
{
    char data[] = "$qXfer:features:read:target.xml:0,fff#7d";
    char *reply = NULL, dollarSign[] = "$", hashSign[] = "#dd", packet[1024] = "";

    strcat(packet, dollarSign);
    strcat(packet, targetCortexM4_XML);
    strcat(packet, hashSign);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING(packet, reply);

    free(reply);
}

void test_handleQueryPacket_given_qXfer_read_arm_m_profile_should_return_arm_m_profile_xml_description(void)
{
    char data[] = "$qXfer:features:read:arm-m-profile.xml:0,fff#ee";
    char *reply = NULL, dollarSign[] = "$", hashSign[] = "#47", packet[1024] = "";

    strcat(packet, dollarSign);
    strcat(packet, arm_m_profile);
    strcat(packet, hashSign);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING(packet, reply);

    free(reply);
}

void test_handleQueryPacket_given_qXfer_read_arm_vfpv2_should_arm_vfpv2_xml_description(void)
{
    char data[] = "$qXfer:features:read:arm-vfpv2.xml:0,fff#57";
    char *reply = NULL, dollarSign[] = "$", hashSign[] = "#89", packet[1024] = "";

    strcat(packet, dollarSign);
    strcat(packet, arm_vfpv2);
    strcat(packet, hashSign);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING(packet, reply);

    free(reply);
}

void test_handleQueryPacket_given_qXfer_read_arm_fpa_should_return_empty_response(void)
{
    char data[] = "$qXfer:features:read:arm-fpa.xml:0,fff#9a";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qL_should_return_empty_response(void)
{
    char data[] = "$qL1160000000000000000#55";
    char *reply;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qC_should_return_empty_response(void)
{
    char data[] = "$qC#b4";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qCRC_should_return_E01_response(void)
{
    char data[] = "$qCRC#49";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qAttached_should_return_empty_response(void)
{
    char data[] = "$qAttached#8f";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qTStatus_should_return_empty_response(void)
{
    char data[] = "$qTStatus#49";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qfThreadInfo_should_return_empty_response(void)
{
    char data[] = "$qfThreadInfo#bb";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qOffsets_should_return_empty_response(void)
{
    char data[] = "$qOffsets#4b";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_qSymbol_should_return_empty_response(void)
{
    char data[] = "$qSymbol::#5b";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_unrecognized_RSP_query_should_return_empty_response(void)
{
    char data[] = "$qB#b3";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}

void test_serveRSP_given_data_with_p1a_packet_should_return_first_fpuDoublePrecision_value(void)
{
    char data[] = "$p1a#d1";
    char *reply = NULL;

    initCoreRegister();
    // fpuDoublePrecision[0] = 0x2143658778563412;
    fpuDoublePrecision[0] = 0x2143650000000000;

    reply = serveRSP(data);

    // TEST_ASSERT_EQUAL_STRING("$1234567887654321#48", reply);
    TEST_ASSERT_EQUAL_STRING("$0000000000654321#15", reply);

    free(reply);
}

void test_serveRSP_given_data_with_p2_packet_should_return_second_coreReg_value(void)
{
    char data[] = "$p2#a2";
    char *reply = NULL;

    initCoreRegister();
    // coreReg[2] = 0x21436587;
    coreReg[2] = 0x21430000;

    reply = serveRSP(data);

    // TEST_ASSERT_EQUAL_STRING("$87654321#a4", reply);
    TEST_ASSERT_EQUAL_STRING("$00004321#8a", reply);

    free(reply);
}

void test_serveRSP_given_data_with_p12_packet_should_return_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$p12#d3";
    char *reply = NULL;

    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$E00#a5", reply);

    free(reply);
}

void test_serveRSP_given_data_with_p_neg_1_packet_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$p-1#ce";
    char *reply = NULL;

    initCoreRegister();

    Try
	  {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
	  {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_0, errorSignal);
        printf("Error signal: %x\n", errorSignal);
	  }

    TEST_ASSERT_EQUAL_STRING("$E00#a5", reply);
}

void xtest_serveRSP_given_data_with_g_packet_should_return_all_reg_val(void)
{
    char data[] = "$g#67";
    char *reply = NULL;
    initCoreRegister();

    coreReg[2] = 0x12345678;
    coreReg[fPSCR] = 0xaddeadde;
    fpuDoublePrecision[0] = 0x2143658778563412;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$0000000000000000785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001#a5", reply);

    free(reply);
}

void test_serveRSP_should_return_all_reg_val_including_fpu_reg(void)
{
    char data[] = "$g#67";
    char *reply = NULL;
    int i;

    initCoreRegister();
    coreReg[2] = 0x12345678;
    fpuDoublePrecision[1] = 0x1234567887654321;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$00000000000000007856341200000000000000000000000000000000000000000000000000000000000000000000000000000000fcff0120ffffffff0000000000000001000000000000000021436587785634120000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000#f5", reply);

    free(reply);
}

void test_serveRSP_given_data_with_P6_should_update_sixth_coreReg_value(void)
{
    char data[] = "$P6=fe090008#23";
    char *reply = NULL;

    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL(0x080009fe, coreReg[6]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    free(reply);
}

void test_serveRSP_given_P1b_packet_should_update_the_second_fpuDoublePrecision_and_fpuSinglePrecision(void)
{
    char data[] = "$P1b=1234567887654321#68";
    char *reply = NULL;

    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL(0x2143658778563412, fpuDoublePrecision[1]);
    TEST_ASSERT_EQUAL(0x78563412, fpuSinglePrecision[2]);
    TEST_ASSERT_EQUAL(0x21436587, fpuSinglePrecision[3]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    free(reply);
}

void test_serveRSP_given_data_with_P30_packet_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$P30=1234567887654321#38";
    char *reply = NULL;

    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$E00#a5", reply);

    free(reply);
}

void test_serveRSP_given_data_with_P_neg_5_should_throw_GDB_SIGNAL_0(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$P-5=12345678#93";
    char *reply = NULL;

    initCoreRegister();

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_0, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E00#a5", reply);
}

void test_serveRSP_given_data_with_G_packet_should_should_write_value_to_all_registers(void)
{
    char data[] = "$G00000000111111118cff0120333333334444444455555555666666667777777788888888500b0008aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffff00000001#69";
    char *reply = NULL;

    initCoreRegister();

    reply = serveRSP(data);

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

    free(reply);
}

void test_serveRSP_given_following_data_should_write_value_to_all_registers_including_fpu_reg(void)
{
    char data[] = "$G00000000111111118cff0120333333334444444455555555666666667777777788888888500b0008aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffff0000000100000000000000000101010101010101020202020202020203030303030303030404040404040404050505050505050506060606060606060707070707070707080808080808080809090909090909090a0a0a0a0a0a0a0a0b0b0b0b0b0b0b0b0c0c0c0c0c0c0c0c0d0d0d0d0d0d0d0d0e0e0e0e0e0e0e0e0f0f0f0f0f0f0f0fabababab#85";
    char *reply = NULL;

    initCoreRegister();

    reply = serveRSP(data);

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

    free(reply);
}

void test_serveRSP_given_m0_and_2_should_retrieve_memory_content_start_from_0x0(void)
{
    char data[] = "$m0,2#fb";
    char *reply = NULL;

    memoryBlock[0x0] = 0x20;
    memoryBlock[0x1] = 0x3f;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$203f#fb", reply);

    free(reply);
}

void test_serveRSP_given_m80009d6_and_4_should_retrieve_memory_content_start_from_0x080009d6(void)
{
    char data[] = "$m80009d6,4#68";
    char *reply = NULL;

    memoryBlock[virtualMemToPhysicalMem(0x80009d6)] = 0xf6;
    memoryBlock[virtualMemToPhysicalMem(0x80009d6 + 1)] = 0x43;
    memoryBlock[virtualMemToPhysicalMem(0x80009d6 + 2)] = 0x70;
    memoryBlock[virtualMemToPhysicalMem(0x80009d6 + 3)] = 0xff;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$f64370ff#36", reply);

    free(reply);
}

void test_serveRSP_given_m0_and_neg_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$m0,-2#28";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);

    free(reply);
}

void test_serveRSP_given_m7ffffff_and_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$m7ffffff,2#28";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
}

void test_serveRSP_given_M8000d06_and_2_should_write_2_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,2:0010#38";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL(0x00, memoryBlock[virtualMemToPhysicalMem(0x8000d06)]);
    TEST_ASSERT_EQUAL(0x10, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 1)]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    free(reply);
}

void test_serveRSP_given_M8000d06_and_4_should_write_4_byte_data_in_the_memory_addr(void)
{
    char data[] = "$M8000d06,4:00100020#fc";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL(0x00, memoryBlock[virtualMemToPhysicalMem(0x8000d06)]);
    TEST_ASSERT_EQUAL(0x10, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 1)]);
    TEST_ASSERT_EQUAL(0x00, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 2)]);
    TEST_ASSERT_EQUAL(0x20, memoryBlock[virtualMemToPhysicalMem(0x8000d06 + 3)]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    free(reply);
}

void test_serveRSP_given_M8000d06_and_neg_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,-2:4ff0#d4";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);

    free(reply);
}

void test_serveRSP_given_M7ffffff_and_2_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M7ffffff,2:4ff0#d4";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_M8000d06_and_2_with_more_data_supply_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,2:4ff0fff0#d4";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_M8000d06_and_2_with_no_data_supply_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,2:#d4";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_M8000d06_and_2_with_less_data_supply_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$M8000d06,2:4f#d4";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
      TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
      printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_following_data_and_PC_0x2_should_step_through_the_instruction(void)
{
    char data[] = "$s#73";
    char *reply = NULL;

    initializeSimulator();
    coreReg[PC] = 0x2;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_EQUAL(0x4, coreReg[PC]);
    free(reply);
}

void test_serveRSP_given_following_data_should_generate_an_GDB_SIGNAL_ILL_error_msg(void)
{
    char data[] = "$s#73";
    char *reply = NULL;

    initializeSimulator();
    memoryBlock[0] = 0x34;
    memoryBlock[1] = 0xbf;      //ITE CC
    memoryBlock[2] = 0x01;
    memoryBlock[3] = 0xe0;      //expect an error after stepping this

    reply = serveRSP(data);
    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$E04#a9", reply);
    free(reply);
}

void test_serveRSP_given_following_data_should_response_S05(void)
{
    char data[] = "$?#3f";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    free(reply);
}

void test_serveRSP_given_Z0_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$Z0,80009d6,2#af";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NOT_NULL(breakpointList);
    TEST_ASSERT_NULL(breakpointList->next);
    TEST_ASSERT_EQUAL(0x80009d6, breakpointList->addr);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_Z0_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$Z0,7ffffff,2#af";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
        printf("Error signal: %x\n", errorSignal);
    }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_Z1_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$Z1,80009d6,2#b0";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NOT_NULL(breakpointList);
    TEST_ASSERT_NULL(breakpointList->next);
    TEST_ASSERT_EQUAL(0x80009d6, breakpointList->addr);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_Z1_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$Z1,7ffffff,2#b0";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		    printf("Error signal: %x\n", errorSignal);
	  }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_Z3_and_Z2_should_insert_read_and_write_watchpoint_at_0x20000000_and_0x20000010_respectively(void)
{
    char data[] = "$Z3,20000000,2#99";
    char *reply = NULL;

    watchpointIndex = 0;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_READ, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(2, wp[0].size);

    char data2[] = "$Z2,20000010,4#9c";

    reply = serveRSP(data2);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_WRITE, wp[1].type);
    TEST_ASSERT_EQUAL(0x20000010, wp[1].addr);
    TEST_ASSERT_EQUAL(4, wp[1].size);
    free(reply);
}

void test_serveRSP_given_z0_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$z0,80009d6,2#cf";
    char *reply = NULL;

    addBreakpoint(&breakpointList, 0x80009d6);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NULL(breakpointList);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_z0_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$z0,7ffffff,2#cf";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		    printf("Error signal: %x\n", errorSignal);
	  }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_z1_should_insert_breakpoint_at_0x080009d6(void)
{
    char data[] = "$z1,80009d6,2#d0";
    char *reply = NULL;

    addBreakpoint(&breakpointList, 0x80009d6);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_NULL(breakpointList);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_z1_should_should_throw_GDB_SIGNAL_ABRT(void)
{
    CEXCEPTION_T errorSignal;
    char data[] = "$z1,7ffffff,2#d0";
    char *reply = NULL;

    Try
    {
        reply = serveRSP(data);
    }
    Catch(errorSignal)
    {
        TEST_ASSERT_EQUAL(GDB_SIGNAL_ABRT, errorSignal);
		    printf("Error signal: %x\n", errorSignal);
	  }

    TEST_ASSERT_EQUAL_STRING("$E06#ab", reply);
    free(reply);
}

void test_serveRSP_given_z3_and_z2_should_insert_read_and_write_watchpoint_at_0x20000000_and_0x20000010_respectively(void)
{
    char data[] = "$Z3,20000000,2#99";
    char data2[] = "$Z2,20000010,4#9c";
    char *reply = NULL;

    watchpointIndex = 0;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    reply = serveRSP(data2);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_READ, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(2, wp[0].size);
    TEST_ASSERT_EQUAL(WP_WRITE, wp[1].type);
    TEST_ASSERT_EQUAL(0x20000010, wp[1].addr);
    TEST_ASSERT_EQUAL(4, wp[1].size);

    char data3[] = "$z3,20000000,2#b9";
    char data4[] = "$z2,20000010,4#bc";

    reply = serveRSP(data3);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_WRITE, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000010, wp[0].addr);
    TEST_ASSERT_EQUAL(4, wp[0].size);
    TEST_ASSERT_EQUAL(NONE, wp[1].type);
    TEST_ASSERT_EQUAL(0, wp[1].addr);
    TEST_ASSERT_EQUAL(0, wp[1].size);

    reply = serveRSP(data4);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(NONE, wp[0].type);
    TEST_ASSERT_EQUAL(0, wp[0].addr);
    TEST_ASSERT_EQUAL(0, wp[0].size);
    free(reply);
}

void test_serveRSP_given_c_packet_and_PC_is_0x0_should_stop_when_a_breakpoint_is_reach(void)
{
    char data[] = "$c#63";
    char *reply = NULL;

    resetMemoryBlock();
    coreReg[PC] = 0x0;
    memoryBlock[0] = 0x50;
    memoryBlock[1] = 0x20;  //movs  r0, #0x50
    memoryBlock[2] = 0x20;
    memoryBlock[3] = 0x21;  //movs  r1, #0x20
    memoryBlock[4] = 0x09;
    memoryBlock[5] = 0x06;  //lsls  r1, #24
    memoryBlock[6] = 0x08;
    memoryBlock[7] = 0x60;  //str   r0, [r1]
    memoryBlock[8] = 0xc0;
    memoryBlock[9] = 0x20;  //movs  r0, #0xc0
    memoryBlock[8] = 0xde;
    memoryBlock[9] = 0x21;  //movs  r1, #0xde
    // printf("PC: %x\n", coreReg[PC]);
    addBreakpoint(&breakpointList, 0xa);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_NOT_NULL(breakpointList);
    TEST_ASSERT_NULL(breakpointList->next);
    TEST_ASSERT_EQUAL(0xa, breakpointList->addr);
    TEST_ASSERT_EQUAL(0xa, coreReg[PC]);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_c_packet_and_PC_is_0x0_and_2_breakpoint_should_stop_whenever_a_breakpoint_is_reach(void)
{
    char data[] = "$c#63";
    char *reply = NULL;

    resetMemoryBlock();
    coreReg[PC] = 0x0;
    memoryBlock[0] = 0x50;
    memoryBlock[1] = 0x20;  //movs  r0, #0x50
    memoryBlock[2] = 0x20;
    memoryBlock[3] = 0x21;  //movs  r1, #0x20
    memoryBlock[4] = 0x09;
    memoryBlock[5] = 0x06;  //lsls  r1, #24
    memoryBlock[6] = 0x08;
    memoryBlock[7] = 0x60;  //str   r0, [r1]
    memoryBlock[8] = 0xc0;
    memoryBlock[9] = 0x20;  //movs  r0, #0xc0
    memoryBlock[10] = 0xde;
    memoryBlock[11] = 0x21; //movs  r1, #0xde
    memoryBlock[12] = 0x14;
    memoryBlock[13] = 0x22; //movs  r2, #20
    memoryBlock[14] = 0x28;
    memoryBlock[15] = 0x23; //movs  r3, #40
    memoryBlock[16] = 0x32;
    memoryBlock[17] = 0x24; //movs  r4, #50
    // printf("PC: %x\n", coreReg[PC]);
    addBreakpoint(&breakpointList, 0xa);
    addBreakpoint(&breakpointList, 0x10);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_NOT_NULL(breakpointList);
    TEST_ASSERT_NOT_NULL(breakpointList->next);
    TEST_ASSERT_NULL(breakpointList->next->next);
    TEST_ASSERT_EQUAL(0xa, breakpointList->addr);
    TEST_ASSERT_EQUAL(0x10, breakpointList->next->addr);
    TEST_ASSERT_EQUAL(0xa, coreReg[PC]);

    removeBreakpoint(&breakpointList, 0xa);
    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);

    TEST_ASSERT_EQUAL(0x10, coreReg[PC]);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_c_packet_and_PC_is_0x0_should_generate_an_GDB_SIGNAL_ILL_error_msg(void)
{
    char data[] = "$c#63";
    char *reply = NULL;

    resetMemoryBlock();
    coreReg[PC] = 0x0;
    memoryBlock[0] = 0x34;
    memoryBlock[1] = 0xbf;      //ITE CC
    memoryBlock[2] = 0x01;
    memoryBlock[3] = 0xe0;      //expect an error after execute this
    // printf("PC: %x\n", coreReg[PC]);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$E04#a9", reply);
    free(reply);
}

void test_serveRSP_given_c_packet_and_PC_is_0x807ff00_should_stop_when_reach_the_end_of_code_memory(void)
{
    char data[] = "$c#63";
    char *reply = NULL;

    resetMemoryBlock();
    coreReg[PC] = 0x806fff0;
    // printf("PC: %d\n", coreReg[PC]);

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_NULL(breakpointList);
    TEST_ASSERT_EQUAL(0x8070000, coreReg[PC]);

    deleteAllBreakpoint(&breakpointList);
    free(reply);
}

void test_serveRSP_given_c_packet_and_PC_is_0x0_and_read_watchpoint_should_stop_before_load_from_memory(void)
{
    char data[] = "$c#63";
    char data2[] = "$Z3,20000000,4#9b";
    char data3[] = "$M8000000,1ac:ffff0220ad010008c1010008c1010008c1010008c1010008c101000800000000000000000000000000000000c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008#61";
    char data4[] = "$M80001ac,18:0348052101600168013101602022fae700000020fee70000#64";
    char data5[] = "$M80001c4,4:04000000#fb";
    char *reply = NULL;

    watchpointIndex = 0;

    resetMemoryBlock();
    coreReg[PC] = 0x80001ac;

    reply = serveRSP(data3);        //write to memory first     /* ldr   r0, =mydata */     using this assembly
    reply = serveRSP(data4);                                    /* movs  r1, #5      */
    reply = serveRSP(data5);                                    /* str   r1, [r0]    */
                                                              /* again:              */
                                                                /* ldr   r1, [r0]    */     /* should stop over here */
                                                                /* adds  r1, #1      */
                                                                /* str   r1, [r0]    */
                                                                /* movs  r2, #0x20   */
                                                                /* b     again       */

    reply = serveRSP(data2);        //add watchpoint first

    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    TEST_ASSERT_EQUAL(WP_READ, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(4, wp[0].size);

    reply = serveRSP(data);         //continue

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_EQUAL(0x80001b2, coreReg[PC]);      //ldr   r1, [r0]

    free(reply);
}

void test_serveRSP_given_c_packet_and_PC_is_0x0_and_watch_read_watchpoint_should_stop_before_write_and_read_from_memory(void)
{
    char data[] = "$c#63";
    char dataWatchpoint[] = "$Z2,20000000,4#9a";
    char dataWatchpoint2[] = "$Z3,20000000,4#9b";
    char data3[] = "$M8000000,1ac:ffff0220ad010008c1010008c1010008c1010008c1010008c101000800000000000000000000000000000000c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008#61";
    char data4[] = "$M80001ac,18:0348052101600168013101602022fae700000020fee70000#64";
    char data5[] = "$M80001c4,4:04000000#fb";
    char *reply = NULL;

    watchpointIndex = 0;

    resetMemoryBlock();
    coreReg[PC] = 0x80001ac;

    reply = serveRSP(data3);        //write to memory first......same as previos test
    reply = serveRSP(data4);
    reply = serveRSP(data5);

    reply = serveRSP(dataWatchpoint);       //add write watchpoint first
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);
    reply = serveRSP(dataWatchpoint2);      //add read watchpoint first
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    TEST_ASSERT_EQUAL(WP_WRITE, wp[0].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[0].addr);
    TEST_ASSERT_EQUAL(4, wp[0].size);
    TEST_ASSERT_EQUAL(WP_READ, wp[1].type);
    TEST_ASSERT_EQUAL(0x20000000, wp[1].addr);
    TEST_ASSERT_EQUAL(4, wp[1].size);

    reply = serveRSP(data);         //continue

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_EQUAL(0x80001b0, coreReg[PC]);      //str   r1, [r0]

    coreReg[PC] = 0x80001b2;
    reply = serveRSP(data);         //continue

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_EQUAL(0x80001b2, coreReg[PC]);      //ldr   r1, [r0]

    coreReg[PC] = 0x80001b4;
    reply = serveRSP(data);         //continue

    TEST_ASSERT_EQUAL_STRING("$S05#b8", reply);
    TEST_ASSERT_EQUAL(0x80001b6, coreReg[PC]);      //str   r1, [r0]

    free(reply);
}
