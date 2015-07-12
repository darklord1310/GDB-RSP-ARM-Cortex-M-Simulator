#include "unity.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "Thumb16bitsTable.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMSimulator.h"
#include "ITandHints.h"
#include "ADDImmediate.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MOVRegister.h"
#include "CMPRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


// test ITTTT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf010000_should_change_coreReg_to_0x03000000(void)
{
  uint32_t instruction = 0xbf010000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x03000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test ITTT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf020000_should_change_coreReg_to_0x05000000(void)
{
  uint32_t instruction = 0xbf020000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x05000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test ITT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf040000_should_change_coreReg_to_0x01000400(void)
{
  uint32_t instruction = 0xbf040000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01000400, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test IT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf080000_should_change_coreReg_to_0x01000800(void)
{
  uint32_t instruction = 0xbf080000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01000800, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test IT MI 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf480000_should_change_coreReg_to_0x01004800(void)
{
  uint32_t instruction = 0xbf480000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01004800, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( MI ,cond);
}