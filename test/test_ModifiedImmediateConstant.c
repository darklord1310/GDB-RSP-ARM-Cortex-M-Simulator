#include "unity.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//upper boundary case
void test_SetFirstBitAndShiftRight_given_0x12_and_modifyControl_0b11111_should_return_0x00000124()
{
  unsigned int input_value = 0x12;
  unsigned int modifyControl = 0b11111;
  unsigned int result = SetFirstBitAndShiftRight(input_value, modifyControl);
  
  TEST_ASSERT_EQUAL(0x00000124, result);
  
}

//lower boundary case
void test_SetFirstBitAndShiftRight_given_0x12_and_modifyControl_0b01000_should_return_0x92000000()
{
  unsigned int input_value = 0x12;
  unsigned int modifyControl = 0b01000;
  unsigned int result = SetFirstBitAndShiftRight(input_value, modifyControl);
  
  TEST_ASSERT_EQUAL(0x92000000, result);
}



void test_ModifyControlLessThan8_given_0x12_should_return_0x12121212()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlLessThan8(input_value);
  
  TEST_ASSERT_EQUAL(0x12121212, result);
  
}


void test_ModifyControlLessThan6_given_0x12_should_return_0x12001200()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlLessThan6(input_value);
  
  TEST_ASSERT_EQUAL(0x12001200, result);
  
}


void test_ModifyControlLessThan4_given_0x12_should_return_0x00120012()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlLessThan4(input_value);
  
  TEST_ASSERT_EQUAL(0x00120012, result);
  
}


void test_ModifyImmediateConstant_given_modifyControl_is_00000_input_is_0x1234_should_return_0x1234(void)
{
  unsigned int input_value = 0x1234;
  unsigned int result = ModifyImmediateConstant(0b0000, input_value);
  
  TEST_ASSERT_EQUAL(0x1234, result);
}
