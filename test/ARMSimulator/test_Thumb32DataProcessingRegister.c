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
void test_LSLRegisterT2_given_r0_0x80000000_r1_0x1_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
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
void test_LSLRegisterT2_given_r0_0x08_r1_28_should_get_r0_0x80000000_and_set_neg_flag(void)
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
  //LSR Register T2

// without affecting status flag
// test LSR.W R0, R1, R2
void test_LSRRegisterT2_given_r1_0xff_r2_0x4_should_get_r0_0xf_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  coreReg[2] = 0x4;
  writeInstructionToMemoryGivenByAddress(0xfa21f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// without affecting status flag
// test LSR.W R0, R1, R2
void test_LSRRegisterT2_given_r1_0xff_r2_0x800000ff_should_get_r0_0x0_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  coreReg[2] = 0x800000ff;
  writeInstructionToMemoryGivenByAddress(0xfa21f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}

// affecting status flag
// test LSRS.W R0, R1
void test_LSRRegisterT2_given_r0_0xf0_r1_0x0fffffff_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x0fffffff;
  coreReg[1] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xfa30f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test LSRS.W R0, R1
void test_LSRRegisterT2_given_r0_0x80000000_r1_0x0_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xfa30f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test LSRS.W R0, R1
void test_LSRRegisterT2_given_r0_0xc0000000_r1_0xc0000000_should_get_r0_0x1_and_set_carry_flag(void)
{
  coreReg[0] = 0xc0000000;
  coreReg[1] = 0xc000001f;
  writeInstructionToMemoryGivenByAddress(0xfa30f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x1, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ASR Register T2

// without affecting status flag
// test ASR.W R0, R1, R2
void test_ASRRegisterT2_given_r1_0x88000000_r2_0x8_should_get_r0_0xff880000_xPSR_unchanged(void)
{
  coreReg[1] = 0x88000000;
  coreReg[2] = 0x8;
  writeInstructionToMemoryGivenByAddress(0xfa41f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xff880000, coreReg[0]);
}

// without affecting status flag
// test ASR.W R0, R1, R2
void test_ASRRegisterT2_given_r1_0xff000000_r2_0xa00000ff_should_get_r0_0xffffffff_xPSR_unchanged(void)
{
  coreReg[1] = 0xff000000;
  coreReg[2] = 0xa00000ff;
  writeInstructionToMemoryGivenByAddress(0xfa41f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[0]);
}
 
// affecting status flag
// test ASRS.W R0, R1
void test_ASRRegisterT2_given_r0_0x1_r1_0x2_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x1;
  coreReg[1] = 0x2;
  writeInstructionToMemoryGivenByAddress(0xfa50f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ASRS.W R0, R1
void test_ASRRegisterT2_given_r0_0x80000000_r1_0xf0000018_should_get_r0_0xfffffff8_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0xf000001c;
  writeInstructionToMemoryGivenByAddress(0xfa50f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xfffffff8, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ASRS.W R0, R1
void test_ASRRegisterT2_given_r0_0x3_r1_0xc0000001_should_get_r0_0x1_and_set_carry_flag(void)
{
  coreReg[0] = 0x3;
  coreReg[1] = 0xc0000001;
  writeInstructionToMemoryGivenByAddress(0xfa50f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x1, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ROR Register T2

// without affecting status flag
// test ROR.W R0, R1, R2
void test_RORRegisterT2_given_r1_is_0xf_r2_0x10_should_get_r0_0xf0000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  coreReg[2] = 0x10;
  writeInstructionToMemoryGivenByAddress(0xfa61f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0000, coreReg[0]);
}

// without affecting status flag
// test ROR.W R0, R1, R2
void test_RORRegisterT2_given_r1_is_0xf_r2_0xababab24_should_get_r0_0xf0000000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  coreReg[2] = 0xababab24;
  writeInstructionToMemoryGivenByAddress(0xfa61f002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
}

// affecting status flag
// test RORS.W R0, R1
void test_RORRegisterT2_given_r0_0x1_r1_is_0x1_should_get_r0_0x80000000_and_set_neg_and_carry_flag(void)
{
  coreReg[0] = 0x1;
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xfa70f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
}

// affecting status flag
// test RORS.W R0, R1
void test_RORRegisterT2_given_r0_0x3__r1_is_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x0;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xfa70f001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x41000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SXTH T2

// test SXTH  R0, R1, ROR #0
void test_SXTHT2_given_r1_is_0xf_should_get_r0_0xf_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xfa0ff081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// test SXTH  R0, R1, ROR #8
void test_SXTHT2_given_r1_is_0xabab_should_get_r0_0xab_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabab;
  writeInstructionToMemoryGivenByAddress(0xfa0ff091, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xab, coreReg[0]);
}

// test SXTH  R0, R1, ROR #16
void test_SXTHT2_given_r1_is_0xf00000f8_should_get_r0_0xfffff000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf00000f8;
  writeInstructionToMemoryGivenByAddress(0xfa0ff0a1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfffff000, coreReg[0]);
}

// test SXTH  R0, R1, ROR #24
void test_SXTHT2_given_r1_is_0x80_should_get_r0_0xffff8000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0x80;
  writeInstructionToMemoryGivenByAddress(0xfa0ff0b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffff8000, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //UXTH T2

// test UXTH  R0, R1, ROR #0
void test_UXTHT2_given_r1_is_0xf_should_get_r0_0xf_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xfa1ff081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// test UXTH  R0, R1, ROR #8
void test_UXTHT2_given_r1_is_0xabab_should_get_r0_0xab_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabab;
  writeInstructionToMemoryGivenByAddress(0xfa1ff091, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xab, coreReg[0]);
}

// test UXTH  R0, R1, ROR #16
void test_UXTHT2_given_r1_is_0xf00000f8_should_get_r0_0xf000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf00000f8;
  writeInstructionToMemoryGivenByAddress(0xfa1ff0a1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf000, coreReg[0]);
}

// test UXTH  R0, R1, ROR #24
void test_UXTHT2_given_r1_is_0x80_should_get_r0_0x8000_and_xPSR_unchanged(void)
{
  coreReg[1] = 0x80;
  writeInstructionToMemoryGivenByAddress(0xfa1ff0b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x8000, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SXTB T2

// test SXTB  R0, R1, ROR #0
void test_SXTBT2_given_r1_is_0xf_should_get_r0_0xf_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xfa4ff081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// test SXTB  R0, R1, ROR #8
void test_SXTBT2_given_r1_is_0xabab_should_get_r0_0xffffffab_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabab;
  writeInstructionToMemoryGivenByAddress(0xfa4ff091, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffffffab, coreReg[0]);
}

// test SXTB  R0, R1, ROR #16
void test_SXTBT2_given_r1_is_0xf00000f8_should_get_r0_0x0_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf00000f8;
  writeInstructionToMemoryGivenByAddress(0xfa4ff0a1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}

// test SXTB  R0, R1, ROR #24
void test_SXTBT2_given_r1_is_0x80000000_should_get_r0_0xffffff80_and_xPSR_unchanged(void)
{
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xfa4ff0b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffffff80, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //UXTB T2

// test UXTB  R0, R1, ROR #0
void test_UXTBT2_given_r1_is_0xf_should_get_r0_0xf_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xfa5ff081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
}

// test UXTB  R0, R1, ROR #8
void test_UXTBT2_given_r1_is_0xabab0_should_get_r0_0xba_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabab0;
  writeInstructionToMemoryGivenByAddress(0xfa5ff091, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xba, coreReg[0]);
}

// test UXTB  R0, R1, ROR #16
void test_UXTBT2_given_r1_is_0xf00000f8_should_get_r0_0x0_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xf00000f8;
  writeInstructionToMemoryGivenByAddress(0xfa5ff0a1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}

// test UXTB  R0, R1, ROR #24
void test_UXTBT2_given_r1_is_0x80000000_should_get_r0_0x80_and_xPSR_unchanged(void)
{
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xfa5ff0b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x80, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REV T2

// test REV  R0, R1
void test_REVT2_given_r1_is_0xabcd1234_should_get_r0_0x3412cdab_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabcd1234;
  writeInstructionToMemoryGivenByAddress(0xfa91f081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x3412cdab, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REV16 T2

// test REV16  R0, R1
void test_REV16T2_given_r1_is_0xabcd1234_should_get_r0_0xcdab3412_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabcd1234;
  writeInstructionToMemoryGivenByAddress(0xfa91f091, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xcdab3412, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //RBIT T1

// test RBIT  R0, R1
void test_RBITT1_given_r1_is_0xabcd1234_should_get_r0_0x2c48b3d5_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabcd1234;
  writeInstructionToMemoryGivenByAddress(0xfa91f0a1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x2c48b3d5, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REVSH T2

// test REVSH  R0, R1
void test_REVSHT2_given_r1_is_0xabcd1284_should_get_r0_0xffff8412_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabcd1284;
  writeInstructionToMemoryGivenByAddress(0xfa91f0b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffff8412, coreReg[0]);
}

// test REVSH  R0, R1
void test_REVSHT2_given_r1_is_0x1234_should_get_r0_0x3412_and_xPSR_unchanged(void)
{
  coreReg[1] = 0x1234;
  writeInstructionToMemoryGivenByAddress(0xfa91f0b1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x3412, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //CLZ T1

// test CLZ  R0, R1
void test_CLZT1_given_r1_is_0xabcd1284_should_get_r0_0x11_and_xPSR_unchanged(void)
{
  coreReg[1] = 0xabcd1284;
  writeInstructionToMemoryGivenByAddress(0xfab1f081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x11, coreReg[0]);
}

// test CLZ  R0, R1
void test_CLZT1_given_r1_is_0x0_should_get_r0_0x20_and_xPSR_unchanged(void)
{
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xfab1f081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x20, coreReg[0]);
}
