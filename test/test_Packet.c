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

void test_createdHexToString_given_regVal_should_return_4_byte_of_string_of_the_regVal(void)
{
    unsigned int regVal = 0xabababab;
    char *packet;

    packet = createdHexToString(regVal, 4);

    TEST_ASSERT_EQUAL_STRING("abababab", packet);

    destroyHexToString(packet);
}

void test_createdHexToString_given_regVal_should_return_3_byte_of_string_of_the_regVal(void)
{
    unsigned int regVal = 0x0011adad;
    char *packet;

    packet = createdHexToString(regVal, 3);

    TEST_ASSERT_EQUAL_STRING("11adad", packet);

    destroyHexToString(packet);
}

void test_createdHexToString_given_regVal_should_return_2_byte_of_string_of_the_regVal(void)
{
    unsigned int regVal = 0x0000adad;
    char *packet;

    packet = createdHexToString(regVal, 2);

    TEST_ASSERT_EQUAL_STRING("adad", packet);

    destroyHexToString(packet);
}

void test_createdHexToString_given_regVal_should_return_1_byte_of_string_of_the_regVal(void)
{
    unsigned int regVal = 0x000000ad;
    char *packet;

    packet = createdHexToString(regVal, 1);

    TEST_ASSERT_EQUAL_STRING("ad", packet);

    destroyHexToString(packet);
}

void test_decodeTwoByte_given_byte_of_0x7856_should_return_0x5678(void)
{
    unsigned int byteData = 0x7856, result;

    result = decodeTwoByte(byteData);

    TEST_ASSERT_EQUAL(0x5678, result);
}

void test_decodeFourByte_given_byte_of_0x78563412_should_return_0x12345678(void)
{
    unsigned int byteData = 0x78563412, result;

    result = decodeFourByte(byteData);

    TEST_ASSERT_EQUAL(0x12345678, result);
}
