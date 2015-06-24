#include "unity.h"
#include "SUBRegister.h"
#include "ARMRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
  coreReg = initCoreRegister();
  initStatusRegister();
}

void tearDown(void)
{
}

//test SUBS R2, R3, R4 given R3 = 3000 and R4 = 2000
void test_SUBRegisterToRegisterT1_given_0x1b1a_and_r3_is_3000_r4_is_2000_should_get_0x3e8_at_r2_C_flag_set(void)
{
  uint32_t instruction = 0x1b1a0000;
  
  coreReg->reg[3].data = 3000;
  coreReg->reg[4].data = 2000;
  SUBRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x3e8, coreReg->reg[2].data);
  TEST_ASSERT_EQUAL(1,isCarry());
  destroyCoreRegister(coreReg);
}


//testing flag change
//test SUBS R2, R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_SUBRegisterToRegisterT1_given_0x1b1a_and_r3_is_0xffffffff_r4_is_0x80000000_should_get_0x1388_at_r2_OV_flag_set_C_flag_set(void)
{
  uint32_t instruction = 0x1b1a0000;
  
  coreReg->reg[3].data = 0xffffffff;
  coreReg->reg[4].data = 0x80000000;
  SUBRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg->reg[2].data);
  TEST_ASSERT_EQUAL(1, isCarry() );
  destroyCoreRegister(coreReg);
}
