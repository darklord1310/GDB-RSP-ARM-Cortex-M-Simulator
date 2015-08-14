#include <string.h>
#include <malloc.h>
#include "unity.h"
#include "stateRSP.h"
#include "ServeRSP.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "CException.h"
#include "ErrorSignal.h"
#include "State.h"
#include "mock_ARMSimulator.h"
#include "mock_gdbserver.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_rsp_state_given_ack_data_and_INITIAL_state_should_change_to_ACK_state(void)
{
    RspData rspData = { INITIAL, NULL };
    char data[] = "+";
    char *packet = NULL;

    sendReply_Expect(rspData.sock, data);
    
    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(ACK, rspData.state);
}

void test_rsp_state_given_nack_data_and_INITIAL_state_should_change_to_NACK_state(void)
{
    RspData rspData = { INITIAL, NULL };
    char data[] = "-";
    char *packet = NULL;

    sendReply_Expect(rspData.sock, data);
    
    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(NACK, rspData.state);

    free(packet);
}

void test_rsp_state_given_k_data_packet_and_INITIAL_state_should_change_to_KILL_state(void)
{
    RspData rspData = { SERVE_RSP, NULL };
    char data[] = "$k#6b";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(KILL, rspData.state);

    free(packet);
}

void xtest_rsp_state_twice_given_ack_data_and_INITIAL_state_should_return_ack_packet(void)
{
    RspData rspData = { INITIAL, NULL };
    char data[] = "+";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING("+", packet);
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);

    free(packet);
}

void xtest_rsp_state_twice_given_nack_data_and_INITIAL_state_should_return_nack_packet(void)
{
    RspData rspData = { INITIAL, NULL };
    char data[] = "-";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING("-", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    free(packet);
}

void xtest_rsp_state_given_NACK_state_should_change_to_KILL_state_if_nack_data_recveive_more_than_five_time(void)
{
    RspData rspData = { ACK, NULL };      //to clear the nack
    char data[] = "-";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);

    rspData.state = NACK;
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING("-", packet);
    TEST_ASSERT_EQUAL(KILL, rspData.state);

    free(packet);
}

void xtest_rsp_state_twice_given_k_data_packet_and_INITIAL_state_should_return_k_packet(void)
{
    RspData rspData = { SERVE_RSP, NULL };
    char data[] = "$k#6b";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);
    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING("k", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    free(packet);
}

void xtest_rsp_state_given_data_and_SERVE_RSP_state_should_return_appropriate_packet(void)
{
    RspData rspData = { SERVE_RSP, NULL };
    char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", packet);
    // TEST_ASSERT_EQUAL_STRING("$qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#88", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    free(packet);
}

void xtest_rsp_state_given_data_with_wrong_chksum_and_SERVE_RSP_state_should_return_nack_packet(void)
{
    RspData rspData = { SERVE_RSP, NULL };
    char data[] = "$qSupported:multiprocess+;qRelocInsn+#4a";
    char *packet = NULL;

    packet = rsp_state(&rspData, data);

    TEST_ASSERT_EQUAL_STRING("-", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    free(packet);
}

void xtest_rsp_state_given_data_and_INITIAL_state_should_return_appropriate_packet(void)
{
    RspData rspData = { INITIAL, NULL };
    char data1[] = "+";
    char *packet = NULL;

    packet = rsp_state(&rspData, data1);
    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(ACK, rspData.state);

    packet = rsp_state(&rspData, data1);
    TEST_ASSERT_EQUAL_STRING("+", packet);
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
    free(packet);

    char data2[] = "$qSupported:multiprocess+;qRelocInsn+#2a";

    packet = rsp_state(&rspData, data2);
    TEST_ASSERT_EQUAL_STRING("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
    free(packet);
}

void xtest_rsp_state_to_do_a_regression_test(void)
{
    RspData rspData = { INITIAL, NULL };
    char *packet = NULL;

    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(ACK, rspData.state);

    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING("+", packet);
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
    free(packet);

    packet = rsp_state(&rspData, "$qSupported:multiprocess+;qRelocInsn+#2a");
    TEST_ASSERT_EQUAL_STRING("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
    free(packet);

    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(ACK, rspData.state);

    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING("+", packet);
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
    free(packet);
    
    packet = rsp_state(&rspData, "$Hg0#df");
    TEST_ASSERT_EQUAL_STRING("$#00", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
    free(packet);
    
    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(ACK, rspData.state);

    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING("+", packet);
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
    free(packet);
    
    packet = rsp_state(&rspData, "$qXfer:features:read:target.xml:0,fff#7d");
    TEST_ASSERT_EQUAL_STRING("$l<?xml version=\"1.0\"?><!DOCTYPE target SYSTEM \"gdb-target.dtd\"><target>  <xi:include href=\"arm-m-profile.xml\"/>  <xi:include href=\"arm-vfpv2.xml\"/></target>#dd", packet);
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
    free(packet);
    
    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING(NULL, packet);
    TEST_ASSERT_EQUAL(ACK, rspData.state);

    packet = rsp_state(&rspData, "+");
    TEST_ASSERT_EQUAL_STRING("+", packet);
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
    free(packet);
}