#include "unity.h"
#include "LSR_16bitsInstruction.h"
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

//test LSRS  R2 , #32 given R2 = 0xffffffff, maximum shift
void test_LSRImmediate16bitsT1_given_0x0812_should_shift_right_r2_32_times_and_write_to_R2(void)
{
  uint32_t instruction = 0x08120000;
  
  coreReg->reg[2].data = 0xffffffff;                    //set R2 to be 0xffffffff
  LSRImmediate16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0x00, coreReg->reg[2].data);        //after shift right 32 times, should get 0x00
  
  destroyCoreRegister(coreReg);
}


//test LSRS  R1, R2 , #15 given R2 = 0xffffffff expect R1 = 0x0001ffff
void test_LSRImmediate16bitsT1_given_0x0bd1_should_shift_right_r2_15_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x0bd10000;
  
  coreReg->reg[2].data = 0xffffffff;                          //set R2 to be 0xffffffff
  LSRImmediate16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg->reg[2].data);    
  TEST_ASSERT_EQUAL(0x0001ffff, coreReg->reg[1].data);        //after shift right 15 times, should get 0x0001ffff
    
  
  destroyCoreRegister(coreReg);
}


//test LSRS  R1, R2 , #1 given R2 = 0xffffffff expect R1 = 0x0001ffff
void test_LSRImmediate16bitsT1_given_0x0851_should_shift_right_r2_1_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x08510000;
  
  coreReg->reg[2].data = 0xffffffff;                          //set R2 to be 0xffffffff
  LSRImmediate16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg->reg[2].data);    
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg->reg[1].data);        //after shift right 1 times, should get 0x7fffffff
    
  
  destroyCoreRegister(coreReg);
}