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
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
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
  //MVN Register T2

//test mvns.w r0, r2, ASR #31
//test carry flag not set
void xtest_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0xffffffff_xPSR_0x81000000()
{
  //create test fixture
  setCarryFlag();
  coreReg[0] = 0x11111111;
  coreReg[2] = 0x33333333;
  coreReg[PC] = 0x08000014;
  writeInstructionToMemoryGivenByAddress(0xEA7F70E2, 0x08000014); //mvns.w r0, r2, ASR #31

  //execute
  armStep();

  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000018,coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffffffff,coreReg[0]);
}


//test mvns.w r0, r2, ASR #2
//test carry flag is set
void xtest_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0xf3333333_xPSR_0xa1000000()
{
  coreReg[0] = 0x11111111;
  coreReg[2] = 0x33333333;
  coreReg[PC] = 0x08000014;
  uint32_t instruction = 0xEA7F00A2;
  writeInstructionToMemoryGivenByAddress(instruction, 0x08000014); //mvns.w r0, r2, ASR #2

  armStep();

  TEST_ASSERT_EQUAL(0xA1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000018,coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf3333333,coreReg[0]);
}



//test mvns.w r0, r2, LSL #30
//test carry flag is not set
void xtest_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0x3fffffff_xPSR_0x01000000()
{
  setCarryFlag();
  coreReg[0] = 0x11111111;
  coreReg[2] = 0x33333333;
  coreReg[PC] = 0x08000040;
  uint32_t instruction = 0xEA7F7082;
  writeInstructionToMemoryGivenByAddress(instruction, 0x08000040); //mvns.w r0, r2, LSL #30

  armStep();

  TEST_ASSERT_EQUAL(0x3fffffff,coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044,coreReg[PC]);
}


//test mvns.w r0, r2
//test carry flag is set after execute still set
void xtest_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0xcccccccc_xPSR_0xa1000000()
{
  setCarryFlag();
  coreReg[0] = 0x11111111;
  coreReg[2] = 0x33333333;
  coreReg[PC] = 0x08000040;
  uint32_t instruction = 0xEA7F0002;
  writeInstructionToMemoryGivenByAddress(instruction, coreReg[PC]); //mvns.w r0, r2

  armStep();

  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044,coreReg[PC]);
  TEST_ASSERT_EQUAL(0xcccccccc,coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //AND Register T2

// test ANDS R0, R1
void test_ANDRegisterT2_given_r0_0xf0_r1_0xff_should_get_r0_0x0f_xPSR_unchanged(void)
{
  uint32_t instruction = 0x40010000;

  coreReg[0] = 0x0f;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x0f, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

//testing zero flag changing
// test ANDS R0, R1
void test_ANDRegisterT2_given_r0_0x00_r1_0xff_should_get_r0_0x00_xPSR_0x41000000(void)
{
  uint32_t instruction = 0x40010000;

  coreReg[0] = 0x00;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //RRX T1

// without affecting status flag
// test RRX R0, R1 with carry = 1
void test_RRXT1_given_0xea4f0031_and_r1_is_0xf_should_get_r0_0x80000007_and_xPSR_unchanged(void)
{
  setCarryFlag();
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea4f0031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x21000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x80000007, coreReg[0]);
}

// without affecting status flag
// test RRX R0, R1 with carry = 0
void test_RRXT1_given_0xea4f0031_and_r1_is_0xf_should_get_r0_0x7_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea4f0031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x7, coreReg[0]);
}

// affecting status flag
// test RRX R0, R1 with carry = 1
void test_RRXT1_given_0xea4f0031_and_r1_is_0xf_should_get_r0_0x80000007_and_set_neg_and_carry_flag(void)
{
  setCarryFlag();
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea5f0031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x80000007, coreReg[0]);
}

// affecting status flag
// test RRX R0, R1 with carry = 0
void test_RRXT1_given_0xea4f0031_and_r1_is_0x1_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xea5f0031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x61000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}
