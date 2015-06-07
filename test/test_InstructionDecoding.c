#include "unity.h"
#include "InstructionDecoding.h"
#include "getBits.h"
#include "getMask.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_is32or16instruction_given_32bits_instruction_should_return_bit32(void)
{
  unsigned int value = 0xF05F0B0F;      // an example of instruction taken from KEIL assembler
                                        // which is MOVS R11, #0xF
  unsigned int result;

  result = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION32bits, result);
}



void test_is32or16instruction_given_16bits_instruction_should_return_bit16()
{
  unsigned int value = 0x46E80000;      // an example of instruction taken from KEIL assembler
                                        // which is  MOV R8, SP

  value = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION16bits, value);

}