#include "unity.h"
#include <malloc.h>
#include <string.h>
#include "Packet.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_gdbCreateMsgPacket_given_empty_string_should_return_a_complete_packet(void)
{
    char *packet;

    packet = gdbCreateMsgPacket("");

    TEST_ASSERT_EQUAL_STRING("$#00", packet);

    destroyPacket(packet);
}

void test_gdbCreateMsgPacket_given_string_of_data_should_return_a_complete_packet(void)
{
    char data[] = "OK";
    char *packet;

    packet = gdbCreateMsgPacket(data);

    TEST_ASSERT_EQUAL_STRING("$OK#9a", packet);

    destroyPacket(packet);
}

void test_createdHexToString_given_regVal_should_return_string_of_the_regVal(void)
{
    unsigned int regVal = 0x00000000;
    char *packet;

    packet = createdHexToString(regVal);

    TEST_ASSERT_EQUAL_STRING("00000000", packet);
    
    destroyHexToString(packet);
}