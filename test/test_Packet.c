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

void test_completePacket_given_empty_string_should_return_a_complete_packet(void)
{
    char *packet;

	packet = completePacket("");

    TEST_ASSERT_EQUAL_STRING("$#00", packet);

    free(packet);
}

void test_completePacket_given_string_of_data_should_return_a_complete_packet(void)
{
    char data[] = "asdfgh";
    char *packet;

	packet = completePacket(data);

    TEST_ASSERT_EQUAL_STRING("$asdfgh#6d", packet);

    free(packet);
}