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

void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


// test ANDS R0, R1
void test_ANDRegisterT1_given_r0_0xf0_r1_0xff_should_get_r0_0xf0(void)
{
  uint32_t instruction = 0x40080000;
  
  coreReg[0] = 0xf0;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xcb7, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}