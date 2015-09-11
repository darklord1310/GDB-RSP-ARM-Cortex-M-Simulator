#include "unity.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
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
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "LDRImmediate.h"
#include "MemoryBlock.h"
#include "LDRLiteral.h"
#include "ErrorSignal.h"
#include "CException.h"
#include "SVC.h"
#include "ADDSPRegister.h"
#include "ADDSPImmediate.h"
#include "ADR.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MLA T1

//test MLA  r2,r3,r1,r0
void test_instruction_given_0xfb030201_should_get_R2_is_0xc19999cf()
{
  //create test fixture
  coreReg[0] = 0x0800004f;
  coreReg[1] = 0x08000060;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfb030201, 0x0800003e);  // MLA  r2,r3,r1,r0
  coreReg[PC] = 0x0800003e;
  
  //test
  armStep();
  TEST_ASSERT_EQUAL(0xc19999cf, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000042, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MUL T2

//test MUL  r3,r1,r0
void test_instruction_given_0xfb01f300_should_get_R3_is_0x78001da0()
{
  //create test fixture
  coreReg[0] = 0x0800004f;
  coreReg[1] = 0x08000060;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfb01f300, 0x0800003e);  // MUL  r3,r1,r0
  coreReg[PC] = 0x0800003e;
  
  //test
  armStep();
  TEST_ASSERT_EQUAL(0x78001da0, coreReg[3]);
  TEST_ASSERT_EQUAL(0x08000042, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MLS T1

//test MLS  r2,r3,r1,r0
void test_instruction_given_0xfb030211_should_get_R2_is_0x4e6666cf()
{
  //create test fixture
  coreReg[0] = 0x0800004f;
  coreReg[1] = 0x08000060;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfb030211, 0x0800003e);  // MLS  r2,r3,r1,r0
  coreReg[PC] = 0x0800003e;
  
  //test
  armStep();
  TEST_ASSERT_EQUAL(0x4e6666cf, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000042, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
