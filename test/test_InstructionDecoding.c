#include "unity.h"
#include "InstructionDecoding.h"
#include "getMask.h"

void setUp(void)
{
}

void tearDown(void)
{
}


/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *  ^ ^
 *  | |
 * 31 28
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_31_lowerRange_28_should_return_0x04()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 31, 28);
  TEST_ASSERT_EQUAL(0x04 , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *     ^         ^
 *     |         |
 *    27        21
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_27_lowerRange_21_should_return_0x37()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 27, 21);
  TEST_ASSERT_EQUAL(0x37 , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *	   ^        ^
 *    |         |
 *   27        22
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_27_lowerRange_22_should_return_0x1b()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 27, 22);
  TEST_ASSERT_EQUAL(0x1b , result);
}


/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *     ^     ^
 *    |      |
 *   27     23
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_27_lowerRange_23_should_return_0x0d()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 27, 23);
  TEST_ASSERT_EQUAL(0x0d , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *	                               ^       ^
 *                                |        |
 *                               10        4
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_10_lowerRange_4_should_return_0x6a()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 10, 4);
  TEST_ASSERT_EQUAL(0x6a , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *                                  ^      ^
 *                                  |      |
 *                                 9       4
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_9_lowerRange_4_should_return_0x2a()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 9, 4);
  TEST_ASSERT_EQUAL(0x2a , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *                                   ^     ^
 *                                   |     |
 *                                  8      4
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_9_lowerRange_4_should_return_0x0a()
{
    unsigned int dummy = 0x46E81EA7;

    unsigned int result = getBits(dummy, 8, 4);
    TEST_ASSERT_EQUAL(0x0a , result);
}



//boundary test
/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *                                              ^^
 *                                              ||
 *                                             1 0
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_1_lowerRange_0_should_return_0x03()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 1, 0);
  TEST_ASSERT_EQUAL(0x03 , result);
}


//boundary test, single bit
/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *                ^
 *                |
 *               21
 *
 */
void test_getBits_given_0x46E81EA7_higherRange_21_lowerRange_21_should_return_0x01()
{
  unsigned int dummy = 0x46E81EA7;

  unsigned int result = getBits(dummy, 21, 21);
  TEST_ASSERT_EQUAL(0x01 , result);
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