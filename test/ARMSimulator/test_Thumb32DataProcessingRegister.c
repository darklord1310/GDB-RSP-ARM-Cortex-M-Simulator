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
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
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
  //LSL Register T2

// without affecting status flag
// test LSL.W R0, R1, R2
void test_LSLRegisterT2_given_r1_0xff_r2_0x4_should_get_r0_0xff0_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  coreReg[2] = 0x4;
  writeInstructionToMemoryGivenByAddress(0xfa01f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xff0, coreReg[0]);
}

// without affecting status flag
// test LSL.W R0, R1, R2
void test_LSLRegisterT2_given_r1_0xff_r2_0x800000ff_should_get_r0_0x0_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  coreReg[2] = 0x800000ff;
  writeInstructionToMemoryGivenByAddress(0xfa01f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}

// affecting status flag
// test LSLS.W R0, R1
void test_LSLRegisterT2_given_r1_0x80000000_r1_0x1_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xfa10f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test LSLS.W R0, R1, #3
void test_LSLRegisterT2_given_r1_0x08_r1_28_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x8;
  coreReg[1] = 28;
  writeInstructionToMemoryGivenByAddress(0xfa10f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LSR Immediate T2

// without affecting status flag
// test LSR.W R0, R1, #4
void xtest_LSRImmediateT2_given_r1_0xff_should_get_r0_0xf_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea4f1011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// affecting status flag
// test LSRS.W R0, R1, #2
void xtest_LSRImmediateT2_given_r1_0x1_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xea5f1091, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test LSRS.W R0, R1, #31
void xtest_LSLImmediateT2_given_r1_0xc0000000_should_get_r0_0x1_and_set_carry_flag(void)
{
  coreReg[1] = 0xc0000000;
  writeInstructionToMemoryGivenByAddress(0xea5f70d1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x1, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ASR Immediate T2

// without affecting status flag
// test ASR.W R0, R1, #4
void xtest_ASRImmediateT2_given_r1_0xff_should_get_r0_0xf_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea4f1021, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// without affecting status flag
// test ASR.W R0, R1, #1
void xtest_ASRImmediateT2_given_r1_0x80000000_should_get_r0_0xc0000000_xPSR_unchanged(void)
{
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xea4f0061, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xc0000000, coreReg[0]);
}
 
// affecting status flag
// test ASRS.W R0, R1, #2
void xtest_ASRImmediateT2_given_r1_0x1_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xea5f10a1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ASRS.W R0, R1, #3
void xtest_ASRImmediateT2_given_r1_0xf0000000_should_get_r0_0xfe000000_and_set_neg_flag(void)
{
  coreReg[1] = 0xf0000000;
  writeInstructionToMemoryGivenByAddress(0xea5f00e1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xfe000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ASRS.W R0, R1, #31
void xtest_ASRImmediateT2_given_r1_0xc0000000_should_get_r0_0xffffffff_and_set_carry_flag(void)
{
  coreReg[1] = 0xc0000000;
  writeInstructionToMemoryGivenByAddress(0xea5f70e1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(-1, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ROR Immediate T1

// without affecting status flag
// test ROR.W R0, R1, #2
void xtest_RORImmediateT1_given_r1_is_0xf_should_get_r0_0xc0000003_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea4f00b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xc0000003, coreReg[0]);
}

// without affecting status flag
// test ROR.W R0, R1, #4
void xtest_RORImmediateT1_given_and_r1_is_0xf_should_get_r0_0xf0000000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea4f1031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
}

// affecting status flag
// test RORS.W R0, R1, #1
void xtest_RORImmediateT1_given_and_r1_is_0x1_should_get_r0_0x80000000_and_set_neg_and_carry_flag(void)
{
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xea5f0071, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
}

// affecting status flag
// test RORS.W R0, R1, #32
void xtest_RORImmediateT1_given_and_r1_is_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea5f70f1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x41000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}




