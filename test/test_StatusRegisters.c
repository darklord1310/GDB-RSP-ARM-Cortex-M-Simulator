#include "unity.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initStatusRegister_should_set_StatusRegisters_to_be_0(void)
{
	initStatusRegister();
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
}


void test_setFlag_when_set_NEGATIVE_negative_flag_should_be_1_and_checkFlag_should_return_1(void)
{
	initStatusRegister();                             //initialize all to 0
  int flag;
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setFlag(NEGATIVE);                                //set NEGATIVE flag
  flag = checkFlag(NEGATIVE);                       //check flag
  
  TEST_ASSERT_EQUAL( 0x80000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , flag);

}



void test_setFlag_when_set_CARRY_carry_flag_should_be_1_and_checkFlag_should_return_1(void)
{
	initStatusRegister();                             //initialize all to 0
  int flag;
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setFlag(CARRY);                                //set CARRY flag
  flag = checkFlag(CARRY);                       //check flag
  
  TEST_ASSERT_EQUAL( 0x20000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , flag);

}



void test_setFlag_when_set_OVERFLOW_overflow_flag_should_be_1_and_checkFlag_should_return_1(void)
{
	initStatusRegister();                             //initialize all to 0
  int flag;
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setFlag(OVERFLOW);                                //set OVERFLOW flag
  flag = checkFlag(OVERFLOW);                       //check flag
  
  TEST_ASSERT_EQUAL( 0x10000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , flag);

}



void test_setFlag_when_set_ZERO_zero_flag_should_be_1_and_checkFlag_should_return_1(void)
{
	initStatusRegister();                             //initialize all to 0
  int flag;
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setFlag(ZERO);                                //set ZERO flag
  flag = checkFlag(ZERO);                       //check flag
  
  TEST_ASSERT_EQUAL( 0x40000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , flag);

}