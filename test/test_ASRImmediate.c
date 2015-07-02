#include "unity.h"
#include "ASRImmediate.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include "Thumb16bitsTable.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "ModifiedImmediateConstant.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ARMSimulator.h"
#include "ConditionalExecution.h"
#include "ITandHints.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


// test ASRS  R1, R2, #2 given R2, #0xf0f0f0f0
void test_ASRImmediateT1_given_0x1091_should_arithmetic_shift_right_r2_2_times_and_write_to_R1_N_flag_is_set(void)
{
	uint32_t instruction = 0x10910000;
  
  coreReg[2] = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xfc3c3c3c, coreReg[1]);        //after arithmetic shift right 5 times, should get 0xfc3c3c3c
  TEST_ASSERT_EQUAL(0xf0f0f0f0, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isNegative() );

}


//boundary test , maximum shift
// test ASRS  R1, R2, #32 given R2, #0xf0f0f0f0
void test_ASRImmediateT1_given_0x1011_should_arithmetic_shift_right_r2_32_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10110000;
  
  coreReg[2] = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);        //after arithmetic shift right 32 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(1, isCarry() );
  TEST_ASSERT_EQUAL(1, isNegative() );
}



//boundary test , minimum shift
// test ASRS  R1, R2, #1 given R2, #0xf0f0f0f0
void test_ASRImmediateT1_given_0x1051_should_arithmetic_shift_right_r2_1_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10510000;
  
  coreReg[2] = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xf8787878, coreReg[1]);        //after arithmetic shift right 1 times, should get 0xf8787878
  TEST_ASSERT_EQUAL(1, isNegative() );

}


