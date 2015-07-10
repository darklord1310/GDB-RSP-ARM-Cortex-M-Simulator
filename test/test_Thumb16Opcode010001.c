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

void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Branch Exchange

// test BX r0
void test_BX_given_r0_0x80000000_should_get_PC_is_0x80000000_xPSR_unchanged(void)
{
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x80000000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x80000000, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Branch with Link and Exchange

// test BLX r0
void test_BLXRegister_given_r0_0x80000000_should_get_PC_is_0x80000000_LR_is_0x80000013_xPSR_unchanged(void)
{
  uint32_t instruction = 0x47800000;
  
  coreReg[0] = 0x80000000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x80000000, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x80000013, coreReg[LR]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

