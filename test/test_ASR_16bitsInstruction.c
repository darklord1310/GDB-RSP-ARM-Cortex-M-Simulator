#include "unity.h"
#include "ASR_16bitsInstruction.h"
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



// test ASRS  R1, R2, #2 given R2, #0xf0f0f0f0
void test_ASRImmediate16bitsT1_given_0x1091_should_arithmetic_shift_right_r2_2_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10910000;
  
  coreReg->reg[2].data = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ASRImmediate16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0xfc3c3c3c, coreReg->reg[1].data);        //after arithmetic shift right 5 times, should get 0xfc3c3c3c
  TEST_ASSERT_EQUAL(0xf0f0f0f0, coreReg->reg[2].data);
  destroyCoreRegister(coreReg);

}


//boundary test , maximum shift
// test ASRS  R1, R2, #32 given R2, #0xf0f0f0f0
void test_ASRImmediate16bitsT1_given_0x1011_should_arithmetic_shift_right_r2_32_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10110000;
  
  coreReg->reg[2].data = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ASRImmediate16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg->reg[1].data);        //after arithmetic shift right 32 times, should get 0xffffffff
  destroyCoreRegister(coreReg);

}



//boundary test , minimum shift
// test ASRS  R1, R2, #1 given R2, #0xf0f0f0f0
void test_ASRImmediate16bitsT1_given_0x1051_should_arithmetic_shift_right_r2_1_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10510000;
  
  coreReg->reg[2].data = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ASRImmediate16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0xf8787878, coreReg->reg[1].data);        //after arithmetic shift right 1 times, should get 0xf8787878
  destroyCoreRegister(coreReg);

}


//test ASRS  R1, R2  given R2, #0xf0f0f0f0 and R1 = 0x00000113
void test_ASRRegisterToRegister16bitsT1_given_0x4111_should_arithmetic_shift_right_r2_240_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x41110000;
  
  coreReg->reg[1].data = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg->reg[2].data = 0x00000113;                          //set R2 to be 0x00000113
  ASRRegisterToRegister16bitsT1(instruction);
          
  TEST_ASSERT_EQUAL(0x00000113, coreReg->reg[2].data);    
  TEST_ASSERT_EQUAL(0, coreReg->reg[1].data);                //after shift right 240 times, should get 0
 
  destroyCoreRegister(coreReg);
}