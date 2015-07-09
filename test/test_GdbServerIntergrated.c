#include <malloc.h>
#include "unity.h"
#include "ServeRSP.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"
#include "ARMRegisters.h"
#include "ROM.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_serveRSP_given_qSupported_query_packet_should_return_appropriate_response(void)
{
	char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$qRelocInsn-#2b", reply);

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

    TEST_ASSERT_EQUAL_STRING("$E01#a6", reply);

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

void test_serveRSP_given_data_with_Hc0_should_return_empty_response(void)
{
    char data[] = "$Hc0#db";
    char *reply = NULL;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);

    free(reply);
}
/*
void test_serveRSP_given_data_with_p10_packet_should_return_appropriate_response(void)
{
    char data[] = "$p10#d1";
    char *reply = NULL;
    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$01000000#81", reply);

    free(reply);
}

void test_serveRSP_given_data_with_g_packet_should_return_appropriate_response_with_all_reg_val(void)
{
    char data[] = "$g#67";
    char *reply = NULL;
    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000#81", reply);

    free(reply);
}
 
void test_serveRSP_given_data_with_P_packet_should_return_appropriate_response(void)
{
    char data[] = "$P6=1052ffff#23";
    char *reply = NULL;
    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL(0x1052ffff, coreReg[6]);
    TEST_ASSERT_EQUAL_STRING("$OK#9a", reply);

    free(reply);
}

void test_serveRSP_given_data_with_G_packet_should_return_appropriate_response(void)
{
    char data[] = "$G00000000111111112222222233333333444444445555555566666666777777778888888899999999aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffff01000000#c8";
    char *reply = NULL;
    initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL(0x00000000, coreReg[0]);
    TEST_ASSERT_EQUAL(0x11111111, coreReg[1]);
    TEST_ASSERT_EQUAL(0x22222222, coreReg[2]);
    TEST_ASSERT_EQUAL(0x33333333, coreReg[3]);
    TEST_ASSERT_EQUAL(0x44444444, coreReg[4]);
    TEST_ASSERT_EQUAL(0x55555555, coreReg[5]);
    TEST_ASSERT_EQUAL(0x66666666, coreReg[6]);
    TEST_ASSERT_EQUAL(0x77777777, coreReg[7]);
    TEST_ASSERT_EQUAL(0x88888888, coreReg[8]);
    TEST_ASSERT_EQUAL(0x99999999, coreReg[9]);
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

void test_serveRSP_given_data_with_s_packet_should_return_appropriate_response(void)
{
    char data[] = "$s#73";
    char *reply = NULL;

    initCoreRegister();
    coreReg[PC] = 0x080d0008;
    coreReg[7] = 0x7cff0120;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$T050f:080d0008;07:7cff0120#52", reply);
}

void test_serveRSP_given_data_with_m_packet_with_4_byte_length_should_return_appropriate_response(void)
{
    char data[] = "$m0,4#64";
    char *reply = NULL;

    createROM();

    rom->address[0x0].data = 0xdff834d0;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$dff834d0#63", reply);
}

void xtest_serveRSP_given_data_with_m_packet_with_2_byte_length_should_return_appropriate_response(void)
{
    char data[] = "$m8000d06,2#5d";
    char *reply = NULL;

    createROM();

    // address[0x8000d06].data = 0xdff84d4a;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$4d4a#2d", reply);
} */