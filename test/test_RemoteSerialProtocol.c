#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "RemoteSerialProtocol.h"
#include "mock_Packet.h"

void setUp(void)
{
}

void tearDown(void)
{
}
/*
void test_handleQueryPacket_given_data_with_qL_should_return_empty_data(void)
{
	char data[] = "$qL1160000000000000000#55";
    char *reply;

    completePacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}

void test_handleQueryPacket_given_data_with_qC_should_return_empty_data(void)
{
	char data[] = "$qC#b4";
    char *reply = NULL;

    completePacket_ExpectAndReturn("", "$#00");

    reply = handleQueryPacket(data);
    printf("reply: %p\n", reply);

    TEST_ASSERT_EQUAL_STRING("$#00", reply);
}
*/
void test_handleQueryPacket_given_qSupported_should_return_appropriate_response(void)
{
	char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *reply = NULL;

    completePacket_ExpectAndReturn("qRelocInsn-", "$qRelocInsn-#2b");

    reply = handleQueryPacket(data);

    TEST_ASSERT_EQUAL_STRING("$qRelocInsn-#2b", reply);
}
