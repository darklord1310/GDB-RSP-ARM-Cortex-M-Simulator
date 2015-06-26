#include <malloc.h>
#include "unity.h"
#include "gdbserver.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"

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

void test_serveRSP_given_data_with_p3_packet_should_return_appropriate_response(void)
{
    char data[] = "$p3#a3";
    char *reply = NULL;
    coreReg = initCoreRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$00000000#80", reply);

    free(reply);
}

void test_serveRSP_given_data_with_pd_packet_should_return_appropriate_response(void)
{
    char data[] = "$pd#d4";
    char *reply = NULL;
    coreReg = initCoreRegister();

    coreReg->reg[13-1].data = 0x11111111;

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$11111111#88", reply);

    free(reply);
}

void test_serveRSP_given_data_with_p10_packet_should_return_appropriate_response(void)
{
    char data[] = "$p10#d1";
    char *reply = NULL;
    initStatusRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$01000000#81", reply);

    free(reply);
}

void test_serveRSP_given_data_with_g_packet_should_return_appropriate_response(void)
{
    char data[] = "$g#67";
    char *reply = NULL;
    coreReg = initCoreRegister();
    initStatusRegister();

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000#81", reply);

    free(reply);
}