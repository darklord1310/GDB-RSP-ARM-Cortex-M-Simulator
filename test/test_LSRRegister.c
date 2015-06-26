#include "unity.h"
#include "LSRRegister.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>


void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}

//test LSRS  R1, R2  given R1 = 0xffffffff and R2 = 0x00000113
void test_LSRRegisterToRegister16bitsT1_given_0x40d1_should_shift_right_r1_19_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x40d10000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000113;                          //set R2 to be 0x00000113
  LSRRegisterToRegisterT1(instruction);
          
  TEST_ASSERT_EQUAL(0x00000113, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x00001fff, coreReg[1]);        //after shift right 19 times, should get 0x00001fff
 
}
