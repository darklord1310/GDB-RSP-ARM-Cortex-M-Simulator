#include "unity.h"
#include "CMP_16bitsInstruction.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>

void setUp(void)
{
  coreReg = initCoreRegister();
  initStatusRegister();
}

void tearDown(void)
{
}

// test CMP r7, #200 given R7 = 200
void test_CMPImmediate16bitsT1_given_0x2fc8_should_compare_immediate_with_R7_and_set_carry_flag_and_zero_flag(void)
{
	uint32_t instruction = 0x2fc80000;
  
  coreReg->reg[7].data = 200;                          //set R7 to be 200
  CMPImmediate16bitsT1(instruction);
  
  TEST_ASSERT_EQUAL(1, isZero() );
  TEST_ASSERT_EQUAL(1, isCarry() );
  
  destroyCoreRegister(coreReg);

}

// test CMP r7, #200 given R7 = 0x2f00
void test_CMPImmediate16bitsT1_given_0x2fc8_should_compare_immediate_with_R7_and_set_carry_flag(void)
{
	uint32_t instruction = 0x2fc80000;
  
  coreReg->reg[7].data = 200;                          //set R7 to be 200
  CMPImmediate16bitsT1(instruction);
  
  TEST_ASSERT_EQUAL(1, isCarry() );
  destroyCoreRegister(coreReg);

}