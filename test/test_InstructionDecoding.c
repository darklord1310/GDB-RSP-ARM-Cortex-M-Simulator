#include "unity.h"
#include "InstructionDecoding.h"

void setUp(void)
{
}

void tearDown(void)
{
}



/*
 *  Eg. if bitPosition is 16
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                       ^      
 *                       |      
 *                      16  
 *
 */ 
void test_setMask_given_bitPosition_16_should_return_0x0001ffff()
{
  unsigned int mask;
  mask = setMask(16);
    
  TEST_ASSERT_EQUAL(0x0001ffff,mask);
}



/*
 *  Eg. if bitPosition is 17
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                      ^      
 *                      |      
 *                     17  
 *
 */ 
void test_setMask_given_bitPosition_17_should_return_0x0003ffff()
{
  unsigned int mask;
  mask = setMask(17);
    
  TEST_ASSERT_EQUAL(0x0003ffff,mask);
}


/*
 *  Eg. if bitPosition is 18
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                     ^      
 *                     |      
 *                    18  
 *
 */ 
void test_setMask_given_bitPosition_18_should_return_0x0007ffff()
{
  unsigned int mask;
  mask = setMask(18);
    
  TEST_ASSERT_EQUAL(0x0007ffff,mask);
}



/*
 *  Eg. if bitPosition is 19
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                    ^      
 *                    |      
 *                   19  
 *
 */ 
void test_setMask_given_bitPosition_19_should_return_0x000fffff()
{
	unsigned int mask;
  mask = setMask(19);
    
  TEST_ASSERT_EQUAL(0x000fffff,mask);
}



//boundary test
/*
 *  Eg. if bitPosition is 31
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *  ^      
 *  |      
 * 31  
 *
 */ 
void test_setMask_given_bitPosition_31_should_return_0xffffffff()
{
	unsigned int mask;
	mask = setMask(31);
    
  TEST_ASSERT_EQUAL(0xffffffff,mask);
}



//boundary test
/*
 *  Eg. if bitPosition is 3
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                                            ^      
 *                                            |      
 *                                           31  
 *
 */  
void test_setMask_given_bitPosition_3_should_return_0x0000000f()
{
	unsigned int mask;
	mask = setMask(3);
    
  TEST_ASSERT_EQUAL(0x0000000f,mask);
}


//boundary test
/*
 *  Eg. if bitPosition is 0
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                                               ^      
 *                                               |      
 *                                               0  
 *
 */  
void test_setMask_given_bitPosition_0_should_return_0x00000001()
{
	unsigned int mask;
	mask = setMask(0);
    
  TEST_ASSERT_EQUAL(0x00000001,mask);
}




/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *  ^ ^      
 *  | |      
 * 31 28 
 *
 */   
void test_getStreamOfBits_given_0x46E81EA7_higherRange_31_lowerRange_28_should_return_0x04()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 31, 28);
    TEST_ASSERT_EQUAL(0x04 , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *     ^         ^      
 *     |         |      
 *    27        21 
 *
 */   
void test_getStreamOfBits_given_0x46E81EA7_higherRange_27_lowerRange_21_should_return_0x37()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 27, 21);
    TEST_ASSERT_EQUAL(0x37 , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *	   ^        ^    
 *    |         |    
 *   27        22
 *
 */ 
void test_getStreamOfBits_given_0x46E81EA7_higherRange_27_lowerRange_22_should_return_0x1b()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 27, 22);
    TEST_ASSERT_EQUAL(0x1b , result);
}


/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *     ^     ^    
 *    |      |    
 *   27     23
 *
 */ 
void test_getStreamOfBits_given_0x46E81EA7_higherRange_27_lowerRange_23_should_return_0x0d()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 27, 23);
    TEST_ASSERT_EQUAL(0x0d , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *	                               ^       ^    
 *                                |        |    
 *                               10        4
 *
 */ 
void test_getStreamOfBits_given_0x46E81EA7_higherRange_10_lowerRange_4_should_return_0x6a()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 10, 4);
    TEST_ASSERT_EQUAL(0x6a , result);
}



/* 
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *                                  ^      ^    
 *                                  |      |    
 *                                 9       4
 *
 */ 
void test_getStreamOfBits_given_0x46E81EA7_higherRange_9_lowerRange_4_should_return_0x2a()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 9, 4);
    TEST_ASSERT_EQUAL(0x2a , result);
}



/*
 *  0100  0110  1110  1000  0001  1110  1010  0111  --> this is a 32 bits integer
 *                                   ^     ^    
 *                                   |     |    
 *                                  8      4
 *
 */ 
void test_getStreamOfBits_given_0x46E81EA7_higherRange_9_lowerRange_4_should_return_0x0a()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 8, 4);
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
void test_getStreamOfBits_given_0x46E81EA7_higherRange_1_lowerRange_0_should_return_0x03()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 1, 0);
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
void test_getStreamOfBits_given_0x46E81EA7_higherRange_21_lowerRange_21_should_return_0x01()
{
    unsigned int dummy = 0x46E81EA7;
    
    unsigned int result = getStreamOfBits(dummy, 21, 21);
    TEST_ASSERT_EQUAL(0x01 , result);
}



void test_is32or16instruction_given_32bits_instruction_should_return_bit32(void)
{
	unsigned int value = 0xF05F0B0F;      // an example of instruction taken from KEIL assembler
                                        // which is MOVS R11, #0xF
	unsigned int result;
	
	result = is32or16instruction(value);
	
	TEST_ASSERT_EQUAL( bit_32, result);
}



void test_is32or16instruction_given_16bits_instruction_should_return_bit16()
{
	unsigned int value = 0x46E80000;      // an example of instruction taken from KEIL assembler
                                        // which is  MOV R8, SP

	value = is32or16instruction(value);
	
	TEST_ASSERT_EQUAL( bit_16, value);
	
}