#include "unity.h"
#include "ASRRegister.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include "ITandHints.h"

void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}

//test ASRS  R1, R2  given R2, #0xf0f0f0f0 and R1 = 0x00000113
void test_ASRRegisterToRegister16bitsT1_given_0x4111_should_arithmetic_shift_right_r2_240_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x41110000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000113;                          //set R2 to be 0x00000113
  ASRRegisterToRegister16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0x00000113, coreReg[2]);    
  TEST_ASSERT_EQUAL(0, coreReg[1]);                 //after shift right 240 times, should get 0
}