#include "unity.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ModifyControlIs14_given_0x12_should_return_0x00000124()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs14(input_value);
  
  TEST_ASSERT_EQUAL(0x00000124, result);
  
}

void test_ModifyControlIs13_given_0x12_should_return_0x00000248()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs13(input_value);
  
  TEST_ASSERT_EQUAL(0x00000248, result);
  
}

void test_ModifyControlIs12_given_0x12_should_return_0x00000490()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs12(input_value);
  
  TEST_ASSERT_EQUAL(0x00000490, result);
  
}

void test_ModifyControlIs11_given_0x12_should_return_0x12400000()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs11(input_value);
  
  TEST_ASSERT_EQUAL(0x12400000, result);
  
}

void test_ModifyControlIs10_given_0x12_should_return_0x24800000()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs10(input_value);
  
  TEST_ASSERT_EQUAL(0x24800000, result);
  
}

void test_ModifyControlIs9_given_0x12_should_return_0x49000000()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs9(input_value);
  
  TEST_ASSERT_EQUAL(0x49000000, result);
  
}


void test_ModifyControlIs8_given_0x12_should_return_0x92000000()
{
  unsigned int input_value = 0x12;
  unsigned int result = ModifyControlIs8(input_value);
  
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




void test_ModifyImmediateConstant_given_modifyControl_is_0000_input_is_0x1234_should_return_0x1234(void)
{
  
}
