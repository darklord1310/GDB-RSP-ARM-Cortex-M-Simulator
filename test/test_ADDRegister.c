#include "unity.h"
#include "ADDRegister.h"
#include "ARMRegisters.h"
#include "ADDSPRegister.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
  coreReg = initCoreRegister();
  initStatusRegister();
}

void tearDown(void)
{
}


//test ADDS R2, R3, R4 given R3 = 3000 and R4 = 2000
void test_ADDRegisterToRegisterT1_given_0x191a_and_r3_is_3000_r4_is_2000_should_get_0x1388_at_r2_statusRegister_unchanged(void)
{
  uint32_t instruction = 0x191a0000;
  
  coreReg->reg[3].data = 3000;
  coreReg->reg[4].data = 2000;
  ADDRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x1388, coreReg->reg[2].data);
  TEST_ASSERT_EQUAL(0,StatusRegisters);
  destroyCoreRegister(coreReg);
}

//testing flag change
//test ADDS R2, R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_ADDRegisterToRegisterT1_given_0x191a_and_r3_is_0xffffffff_r4_is_0xffffffff_should_get_0x1388_at_r2_OV_flag_set_C_flag_set(void)
{
  uint32_t instruction = 0x191a0000;
  
  coreReg->reg[3].data = 0xffffffff;
  coreReg->reg[4].data = 0x80000000;
  ADDRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg->reg[2].data);
  TEST_ASSERT_EQUAL(1, isOverflow() );
  TEST_ASSERT_EQUAL(1, isCarry() );
  destroyCoreRegister(coreReg);
}



//test ADD R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_ADDRegisterToRegisterT2_given_0x4423_and_r3_is_0xffffffff_r4_is_0xffffffff_should_get_0x7fffffff_at_r3_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44230000;
  
  coreReg->reg[3].data = 0xffffffff;
  coreReg->reg[4].data = 0x80000000;
  ADDRegisterToRegisterT2(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg->reg[3].data);
  TEST_ASSERT_EQUAL(0,StatusRegisters);
  destroyCoreRegister(coreReg);
}


//test ADD R10, R8 given R8 = 0xf and R10 = 0x80
void test_ADDRegisterToRegisterT2_given_0x44c2_and_r8_is_0xf_r10_is_0x80_should_get_0x8f_at_r10_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44c20000;
  
  coreReg->reg[8].data = 0xf;
  coreReg->reg[10].data = 0x80;
  ADDRegisterToRegisterT2(instruction);
  
  TEST_ASSERT_EQUAL(0x8f, coreReg->reg[10].data);
  TEST_ASSERT_EQUAL(0,StatusRegisters);
  destroyCoreRegister(coreReg);
}