#include "unity.h"
#include "ExceptionObject.h"
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
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "CLZ.h"
#include "BL.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "BKPT.h"
#include "VMOVBetweenCoreRegAndDoubleFpuReg.h"
#include "VMOVBetweenCoreRegAndfpuSReg.h"


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SMULL T1

//test SMULL  r2,r3,r1,r0
void test_instruction_given_0xfb812300_should_get_R2_is_0x00000001_R3_0x00000000()
{
  //create test fixture
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0xffffffff;
  writeInstructionToMemoryGivenByAddress(0xfb812300, 0x08000040);  // SMULL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x00000000, coreReg[3]);
  TEST_ASSERT_EQUAL(0x00000001, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test SMULL  r2,r3,r1,r0
void test_instruction_given_0xfb812300_should_get_R2_is_0xf7ffffb1_R3_0x00000000()
{
  //create test fixture
  coreReg[0] = 0x0800004f;
  coreReg[1] = 0xffffffff;
  writeInstructionToMemoryGivenByAddress(0xfb812300, 0x08000040);  // SMULL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[3]);
  TEST_ASSERT_EQUAL(0xf7ffffb1, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}




/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //UMULL T1


//test UMULL  r2,r3,r1,r0
void test_instruction_given_0xfba12300_should_get_R2_is_0x00000001_R3_0xfffffffe()
{
  //create test fixture
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0xffffffff;
  writeInstructionToMemoryGivenByAddress(0xfba12300, 0x0800003e);  // UMULL  r2,r3,r1,r0
  coreReg[PC] = 0x0800003e;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x00000001, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000042, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0xfffffffe, coreReg[3]);
}


//test UMULL  r2,r3,r1,r0
void test_instruction_given_0xfba12300_should_get_R2_is_0xf7ffffb1_R3_0x0800004e()
{
  //create test fixture
  coreReg[0] = 0x0800004F;
  coreReg[1] = 0xffffffff;
  writeInstructionToMemoryGivenByAddress(0xfba12300, 0x0800003e);  // UMULL  r2,r3,r1,r0
  coreReg[PC] = 0x0800003e;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xf7ffffb1, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000042, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x0800004e, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SMLAL T1

//test SMLAL  r2,r3,r1,r0
void test_instruction_given_0xfbc12300_should_get_R2_is_0x2b3332e4_R3_0x44444444()
{
  //create test fixture
  coreReg[0] = 0x0800004F;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfbc12300, 0x08000040);  // SMLAL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2b3332e4, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x44444444, coreReg[3]);
}


//test SMLAL  r2,r3,r1,r0
void test_instruction_given_0xfbc12300_should_get_R2_is_0x33333334_R3_0x44444444()
{
  //create test fixture
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfbc12300, 0x08000040);  // SMLAL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x33333334, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x44444444, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //UMLAL T1

//test UMLAL  r2,r3,r1,r0
void test_instruction_given_0xfbe12300_should_get_R2_is_0x33333334_R3_0x44444442()
{
  //create test fixture
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfbe12300, 0x08000040);  // UMLAL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x33333334, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x44444442, coreReg[3]);
}



//test UMLAL  r2,r3,r1,r0
void test_instruction_given_0xfbe12300_should_get_R2_is_0x2b3332e4_R3_0x4c444493()
{
  //create test fixture
  coreReg[0] = 0x0800004F;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfbe12300, 0x08000040);  // UMLAL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2b3332e4, coreReg[2]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x4c444493, coreReg[3]);
}




