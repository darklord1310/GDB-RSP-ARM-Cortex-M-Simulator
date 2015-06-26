#include "unity.h"
#include "gdbserver.h"
#include "mock_RemoteSerialProtocol.h"
#include "mock_Packet.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_serveRSP_given_qSupported_query_packet_should_call_handleQueryPacket_function(void)
{
    char data[] = "$qSupported:multiprocess+;qRelocInsn+#2a";
    char *reply = NULL;

    handleQueryPacket_ExpectAndReturn(data, "$qRelocInsn-#2b");

    reply = serveRSP(data);

    TEST_ASSERT_EQUAL_STRING("$qRelocInsn-#2b", reply);
}
