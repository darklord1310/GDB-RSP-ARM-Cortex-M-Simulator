#include "unity.h"
#include "ADDRegister.h"
#include "ARMRegisters.h"
#include "ADDSPRegister.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}


//test ADDS R2, R3, R4 given R3 = 3000 and R4 = 2000
void test_ADDRegisterToRegisterT1_given_0x191a_and_r3_is_3000_r4_is_2000_should_get_0x1388_at_r2_xPSR_unchanged(void)
{
  uint32_t instruction = 0x191a0000;
  
  coreReg[3] = 3000;
  coreReg[4] = 2000;
  ADDRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x1388, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

//testing flag change
//test ADDS R2, R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_ADDRegisterToRegisterT1_given_0x191a_and_r3_is_0xffffffff_r4_is_0x80000000_should_get_0x7fffffff_at_r2_OV_flag_set_C_flag_set(void)
{
  uint32_t instruction = 0x191a0000;
  
  coreReg[3] = 0xffffffff;
  coreReg[4] = 0x80000000;
  ADDRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isOverflow() );
  TEST_ASSERT_EQUAL(1, isCarry() );
}



//test ADD R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_ADDRegisterToRegisterT2_given_0x4423_and_r3_is_0xffffffff_r4_is_0x80000000_should_get_0x7fffffff_at_r3_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44230000;
  
  coreReg[3] = 0xffffffff;
  coreReg[4] = 0x80000000;
  ADDRegisterToRegisterT2(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test ADD R10, R8 given R8 = 0xf and R10 = 0x80
void test_ADDRegisterToRegisterT2_given_0x44c2_and_r8_is_0xf_r10_is_0x80_should_get_0x8f_at_r10_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44c20000;
  
  coreReg[8] = 0xf;
  coreReg[10] = 0x80;
  ADDRegisterToRegisterT2(instruction);
  
  TEST_ASSERT_EQUAL(0x8f, coreReg[10]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test ADD R4, R2 given R2 = 0x77 and R4 = 0x88
void test_ADDRegisterToRegisterT2_given_0x4414_and_r2_is_0x77_r4_is_0x88_should_get_0xff_at_r4_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44140000;
  
  coreReg[2] = 0x77;
  coreReg[4] = 0x88;
  ADDRegisterToRegisterT2(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg[4]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}