#include "unity.h"
#include "LSLImmediate.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "MOVRegister.h"
#include <stdint.h>
#include "Thumb16bitsTable.h"
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


//test LSLS r2,r1,#2 given r1 = 0x01
void test_LSLImmediateT1_given_0x008A_should_shift_left_r1_2_times_and_write_to_R2_no_flag_set(void)
{
  uint32_t instruction = 0x008A0000;
  
  coreReg[1] = 1;                             //set R1 to be 1
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x01, coreReg[1]);        
  TEST_ASSERT_EQUAL(0x04, coreReg[2]);        //after shift 2 times, should get 0x04
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

//boundary test, minimum shift
//test LSLS r1,#0 given r1 = 0x01
void test_LSLImmediateT1_given_0x0009_should_shift_left_r1_2_times_and_write_to_R1_no_flag_set(void)
{
  uint32_t instruction = 0x00090000;
  
  coreReg[1] = 1;                             //set R1 to be 1
  ARMSimulator(instruction);
         
  TEST_ASSERT_EQUAL(0x01, coreReg[1]);        //will execute MOVRegisterT2
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//boundary test, maximum shift
//test LSLS r1,#31 given r1 = 0x01
void test_LSLImmediateT1_given_0x07C9_should_shift_left_r1_31_times_and_write_to_R1_negative_flag_set(void)
{
  uint32_t instruction = 0x07C90000;
  
  coreReg[1] = 1;                                   //set R1 to be 1
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x80000000, coreReg[1]);        //after shift 31 times, should get 0x80000000
  TEST_ASSERT_EQUAL(1, isNegative() );
}











