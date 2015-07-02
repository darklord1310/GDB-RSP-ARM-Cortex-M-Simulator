#include "unity.h"
#include "ConditionalExecution.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"

void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}

//test case for EQ
void test_checkCondition_given_0000_and_Z_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b0000;
  setZeroFlag();
  
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for EQ
void test_checkCondition_given_0000_and_Z_flag_not_set_should_return_0(void)
{
  //create test case
  cond = 0b0000;
  resetZeroFlag();
  
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for NE
void test_checkCondition_given_0001_and_Z_flag_not_set_should_return_1(void)
{
  //create test case
  cond = 0b0001;
  resetZeroFlag();
  
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for NE
void test_checkCondition_given_0001_and_Z_flag_set_should_return_0(void)
{
  //create test case
  cond = 0b0001;
  setZeroFlag();
  
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for CS
void test_checkCondition_given_0010_and_C_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b0010;
  setCarryFlag();
  
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for CS
void test_checkCondition_given_0010_and_C_flag_not_set_should_return_0(void)
{
  //create test case
  cond = 0b0010;
  resetCarryFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for CC
void test_checkCondition_given_0011_and_C_flag_not_set_should_return_1(void)
{
  //create test case
  cond = 0b0011;
  resetCarryFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for CC
void test_checkCondition_given_0011_and_C_flag_set_should_return_0(void)
{
  //create test case
  cond = 0b0011;
  setCarryFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for MI
void test_checkCondition_given_0100_and_N_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b0100;
  setNegativeFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for MI
void test_checkCondition_given_0100_and_N_flag_not_set_should_return_0(void)
{
  //create test case
  cond = 0b0100;
  resetNegativeFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}

//test case for PL
void test_checkCondition_given_0101_and_N_flag_not_set_should_return_1(void)
{
  //create test case
  cond = 0b0101;
  resetNegativeFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}

//test case for PL
void test_checkCondition_given_0101_and_N_flag_set_should_return_0(void)
{
  //create test case
  cond = 0b0101;
  setNegativeFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for VS
void test_checkCondition_given_0110_and_OV_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b0110;
  setOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}

//test case for VS
void test_checkCondition_given_0110_and_OV_flag_reset_should_return_0(void)
{
  //create test case
  cond = 0b0110;
  resetOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}

//test case for VC
void test_checkCondition_given_0111_and_OV_flag_reset_should_return_1(void)
{
  //create test case
  cond = 0b0111;
  resetOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for VC
void test_checkCondition_given_0111_and_OV_flag_set_should_return_0(void)
{
  //create test case
  cond = 0b0111;
  setOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for HI
void test_checkCondition_given_1000_and_C_flag_set_and_Z_flag_reset_should_return_1(void)
{
  //create test case
  cond = 0b1000;
  setCarryFlag();
  resetZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for LS
void test_checkCondition_given_1001_and_C_flag_reset_and_Z_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b1001;
  resetCarryFlag();
  setZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for GE
void test_checkCondition_given_1010_if_N_flag_and_OV_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b1010;
  resetNegativeFlag();
  resetOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for GE
void test_checkCondition_given_1010_if_N_flag_and_OV_flag_reset_should_return_1(void)
{
  //create test case
  cond = 0b1010;
  setNegativeFlag();
  setOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for GE
void test_checkCondition_given_1010_if_N_flag_and_OV_flag_different_should_return_0(void)
{
  //create test case
  cond = 0b1010;
  resetNegativeFlag();
  setOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for LT
void test_checkCondition_given_1011_if_N_flag_reset_and_OV_flag_set_should_return_1(void)
{
  //create test case
  cond = 0b1011;
  resetNegativeFlag();
  setOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}

//test case for LT
void test_checkCondition_given_1011_if_N_flag_set_and_OV_flag_reset_should_return_1(void)
{
  //create test case
  cond = 0b1011;
  setNegativeFlag();
  resetOverflowFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for GT
// possibility 1: N is 0, OV is 0, Z is 0
void test_checkCondition_given_1100_and_possiblilty1_should_return_1(void)
{
  //create test case
  cond = 0b1100;
  resetNegativeFlag();
  resetOverflowFlag();
  resetZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for GT
// possibility 2: N is 1, OV is 1, Z is 0
void test_checkCondition_given_1100_and_possiblilty2_should_return_1(void)
{
  //create test case
  cond = 0b1100;
  setNegativeFlag();
  setOverflowFlag();
  resetZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}

//test case for GT
// possibility 3: N is 0, OV is 1, Z is 0
void test_checkCondition_given_1100_and_possiblilty3_should_return_0(void)
{
  //create test case
  cond = 0b1100;
  resetNegativeFlag();
  setOverflowFlag();
  resetZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for GT
// possibility 4: N is 1, OV is 1, Z is 1
void test_checkCondition_given_1100_and_possiblilty4_should_return_0(void)
{
  //create test case
  cond = 0b1100;
  setNegativeFlag();
  setOverflowFlag();
  setZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for LE
// possibility 1: N is 0, OV is 1, Z is 1
void test_checkCondition_given_1101_and_possiblilty1_should_return_1(void)
{
  //create test case
  cond = 0b1101;
  resetNegativeFlag();
  setOverflowFlag();
  setZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}


//test case for LE
// possibility 2: N is 1, OV is 0, Z is 1
void test_checkCondition_given_1101_and_possiblilty2_should_return_1(void)
{
  //create test case
  cond = 0b1101;
  setNegativeFlag();
  resetOverflowFlag();
  setZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(1,result);
}

//test case for LE
// possibility 3: N is 0, OV is 1, Z is 0
void test_checkCondition_given_1101_and_possiblilty3_should_return_0(void)
{
  //create test case
  cond = 0b1101;
  resetNegativeFlag();
  setOverflowFlag();
  resetZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


//test case for LE
// possibility 4: N is 1, OV is 1, Z is 0
void test_checkCondition_given_1101_and_possiblilty4_should_return_0(void)
{
  //create test case
  cond = 0b1101;
  setNegativeFlag();
  setOverflowFlag();
  resetZeroFlag();
 
	int result = checkCondition();
  TEST_ASSERT_EQUAL(0,result);
}


