#include "unity.h"
#include "SUBImmediate.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
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


//boundary test, maximum immediate number allowed which is 7
//test SUBS R2, R3, #0x07 given R3 = 0x01
void test_SUBImmediateT1_given_0x1fda_and_r3_is_0x01_should_get_0xfffffffa_at_r2_N_flag_set(void)
{
  uint32_t instruction = 0x1fda0000;
  
  coreReg[3] = 0x01;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xfffffffa, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01, coreReg[3]);
  TEST_ASSERT_EQUAL(1,isNegative());
}


//boundary test, minimum immediate number allowed which is 0
//test SUBS R2, R3, #0 given R3 = 3000
void test_SUBImmediateT1_given_0x1e1a_and_r3_is_3000_should_get_3000_at_r2_C_flag_set(void)
{
  uint32_t instruction = 0x1e1a0000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(3000, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}


//test SUBS R3, #0x08 given R3 = 3000
void test_SUBImmediateT2_given_0x3b08_and_r3_is_3000_should_get_0xbb0_at_r3_C_flag_set(void)
{
  uint32_t instruction = 0x3b080000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xbb0, coreReg[3]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}


//boundary test, minimum immediate number allowed which is 0
//test SUBS R3, #0 given R3 = 3000
void test_SUBImmediateT2_given_0x3b00_and_r3_is_3000_should_get_3000_at_r3_C_flag_set(void)
{
  uint32_t instruction = 0x3b000000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(3000, coreReg[3]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}



//boundary test, maximum immediate number allowed which is 0xff
//test SUBS R3, #0xff given R3 = 3000
void test_SUBImmediateT2_given_0x3bff_and_r3_is_3000_should_get_0xab9_at_r3_C_flag_set(void)
{
  uint32_t instruction = 0x3bff0000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xab9, coreReg[3]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}
