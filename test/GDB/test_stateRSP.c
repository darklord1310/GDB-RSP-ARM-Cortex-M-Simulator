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

void test_rspState_given_ack_data_and_INITIAL_state_should_reply_ack(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char data[] = "+";

    sendBuffer_ExpectAndReturn(&rspData.sock, data, 1);

    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
}

void test_rspState_given_nack_data_and_INITIAL_state_reply_nack(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char data[] = "-";

    sendBuffer_ExpectAndReturn(&rspData.sock, data, 1);

    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
}

void test_rspState_given_ack_with_packet_data_and_INITIAL_state_should_serve_the_packet_data(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char data[] = "+$qSupported:multiprocess+;qRelocInsn+#2a";

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", strlen("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58"));

    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
}

void test_rspState_given_two_ack_and_INITIAL_state_should_reply_nack(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char data[] = "++";

    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);

    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
}

void test_rspState_given_k_data_packet_and_INITIAL_state_should_change_to_KILL_state(void)
{
    SOCKET sock;
    RspData rspData = { SERVE_RSP, sock };
    char data[] = "$k#6b";

    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(KILL, rspData.state);
}

void test_rspState_given_INITIAL_state_should_change_to_KILL_state_if_nack_data_recveive_more_than_five_time(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char data[] = "-";

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);

    rspState(&rspData, "+");            //to clear the nack value
    rspState(&rspData, data);
    rspState(&rspData, data);
    rspState(&rspData, data);
    rspState(&rspData, data);
    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(KILL, rspData.state);
}

void test_rspState_given_INITIAL_state_should_reply_nack_and_change_to_KILL_state_if_incorrect_packet_format_is_receive_five_time(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char data[] = "+$$qSupported:multiprocess+;qRelocInsn+#2a";

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "-", 1);

    rspState(&rspData, "+");        //to clear the nack value
    rspState(&rspData, data);
    rspState(&rspData, data);
    rspState(&rspData, data);
    rspState(&rspData, data);
    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(KILL, rspData.state);
}

void test_rspState_given_ack_and_data_and_INITIAL_state_should_reply_ack_and_appropriate_packet(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };
    char ack[] = "+";
    char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", strlen("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58"));

    rspState(&rspData, ack);
    rspState(&rspData, data);

    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
}

void test_rspState_to_do_a_regression_test(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    rspState(&rspData, "+");
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", strlen("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58"));
    rspState(&rspData, "$qSupported:multiprocess+;qRelocInsn+#2a");
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    rspState(&rspData, "+");
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "$#00", strlen("$#00"));
    rspState(&rspData, "$Hg0#df");
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    rspState(&rspData, "+");
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "$l<?xml version=\"1.0\"?><!DOCTYPE target SYSTEM \"gdb-target.dtd\"><target>  <xi:include href=\"arm-m-profile.xml\"/>  <xi:include href=\"arm-vfpv2.xml\"/></target>#dd", strlen("$l<?xml version=\"1.0\"?><!DOCTYPE target SYSTEM \"gdb-target.dtd\"><target>  <xi:include href=\"arm-m-profile.xml\"/>  <xi:include href=\"arm-vfpv2.xml\"/></target>#dd"));
    rspState(&rspData, "$qXfer:features:read:target.xml:0,fff#7d");
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    rspState(&rspData, "+");
    TEST_ASSERT_EQUAL(SERVE_RSP, rspData.state);
}

void test_rspState_to_do_a_regression_test2(void)
{
    SOCKET sock;
    RspData rspData = { INITIAL, sock };

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58", strlen("$PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-#58"));
    rspState(&rspData, "+$qSupported:multiprocess+;qRelocInsn+#2a");
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "$#00", strlen("$#00"));
    rspState(&rspData, "+$Hg0#df");
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);

    sendBuffer_ExpectAndReturn(&rspData.sock, "+", 1);
    sendBuffer_ExpectAndReturn(&rspData.sock, "$l<?xml version=\"1.0\"?><!DOCTYPE target SYSTEM \"gdb-target.dtd\"><target>  <xi:include href=\"arm-m-profile.xml\"/>  <xi:include href=\"arm-vfpv2.xml\"/></target>#dd", strlen("$l<?xml version=\"1.0\"?><!DOCTYPE target SYSTEM \"gdb-target.dtd\"><target>  <xi:include href=\"arm-m-profile.xml\"/>  <xi:include href=\"arm-vfpv2.xml\"/></target>#dd"));
    rspState(&rspData, "+$qXfer:features:read:target.xml:0,fff#7d");
    TEST_ASSERT_EQUAL(INITIAL, rspData.state);
}

// regression test
void test_rspState_given_ack_and_empty_data_and_NACK_state_should_change_to_KILL_state(void)
{
    SOCKET sock;
    RspData rspData = { NACK, sock };

    rspState(&rspData, "");
    rspState(&rspData, "");
    rspState(&rspData, "");
    rspState(&rspData, "");
    rspState(&rspData, "");

    TEST_ASSERT_EQUAL(KILL, rspData.state);
}
