#include "unity.h"
#include "CMPImmediate.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include <stdint.h>

void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}

// test CMP r7, #200 given R7 = 200
void test_CMPImmediateT1_given_0x2fc8_should_compare_immediate_200_with_R7_and_set_carry_flag_and_zero_flag(void)
{
	uint32_t instruction = 0x2fc80000;
  
  coreReg[7] = 200;                          //set R7 to be 200
  CMPImmediateT1(instruction);
  
  TEST_ASSERT_EQUAL(1, isZero() );
  TEST_ASSERT_EQUAL(1, isCarry() );

}

// test CMP r7, #20 given R7 = 0x200
void test_CMPImmediateT1_given_0x2f14_should_compare_immediate_20_with_R7_and_set_carry_flag(void)
{
	uint32_t instruction = 0x2f140000;
  coreReg[7] = 200;                          //set R7 to be 200
  CMPImmediateT1(instruction);
  
  TEST_ASSERT_EQUAL(1, isCarry() );
}


// test CMP r7, #200 given R7 = 0x20
void test_CMPImmediateT1_given_0x2fc8_should_compare_immediate_20_with_R7_and_set_negative_flag(void)
{
	uint32_t instruction = 0x2fc80000;
  coreReg[7] = 20;                          //set R7 to be 20
  CMPImmediateT1(instruction);
  
  TEST_ASSERT_EQUAL(1, isNegative() );
}
