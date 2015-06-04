#include "unity.h"
#include "InstructionDecoding.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_getFirst3BitsFromInstruction_given_0xE0101110_should_return_0x07()
{
	unsigned int dummy = 0xE0101110;
	unsigned int return_value = getFirst3BitsFromInstruction(dummy);
	
	TEST_ASSERT_EQUAL(return_value , 0x07);
	
	
}


void test_getFirst4BitsFromInstruction_given_0xF1110011_should_return_0x0F()
{
	unsigned int dummy = 0xF1110011;
	unsigned int return_value = getFirst4BitsFromInstruction(dummy);
	
	TEST_ASSERT_EQUAL(return_value , 0x0f);
	
}


void test_getFirst5BitsFromInstruction_given_0xF8101011_should_return_0x1F()
{
	unsigned int dummy = 0xF8101011;
	unsigned int return_value = getFirst5BitsFromInstruction(dummy);
	
	TEST_ASSERT_EQUAL(return_value , 0x1F);
	
}


void test_getFirst6BitsFromInstruction_given_0xFC001011_should_return_0x3F()
{
	unsigned int dummy = 0xFC001011;
	unsigned int return_value = getFirst6BitsFromInstruction(dummy);
	
	TEST_ASSERT_EQUAL(return_value , 0x3F);
	
}


void test_is32or16instruction_given_32bits_instruction_should_return_bit32(void)
{
	unsigned int value = 0xF05F0B0F;			// an example of instruction taken from KEIL assembler
												// which is MOVS R11, #0xF
	unsigned int result;
	
	result = is32or16instruction(value);
	
	TEST_ASSERT_EQUAL( bit_32, result);
}


void test_is32or16instruction_given_16bits_instruction_should_return_bit16()
{
	unsigned int value = 0x46E80000;			// an example of instruction taken from KEIL assembler
												// which is  MOV R8, SP
	
	value = is32or16instruction(value);
	
	TEST_ASSERT_EQUAL( bit_16, value);
	
}

void test_InstructionDecoding_32bits()
{
	
	
}