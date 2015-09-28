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
#include "SUBSPRegister.h"
#include "CLZ.h"
#include "BL.h"
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
void test_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0xffffffff_xPSR_0x81000000()
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
void test_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0xf3333333_xPSR_0xa1000000()
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
void test_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0x3fffffff_xPSR_0x01000000()
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
void test_MVNRegisterT2_given_r0_0x11111111_r2_0x33333333_should_get_r0_0xcccccccc_xPSR_0xa1000000()
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

// without affecting status flag
// test AND.W R0, R1, R2
void test_ANDRegisterT2_given_r1_0xf0_r2_0xff_should_get_r0_0xf0_xPSR_unchanged(void)
{
  coreReg[1] = 0xf0;
  coreReg[2] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea010002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0, coreReg[0]);
}

// without affecting status flag
// test AND.W R0, R1
void test_ANDRegisterT2_given_r0_0xf0_r1_0xff_should_get_r0_0xf0_xPSR_unchanged(void)
{
  coreReg[0] = 0xf0;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea000001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0, coreReg[0]);
}

// without affecting status flag
// test AND.W R0, R1, LSL #16
void test_ANDRegisterT2_given_r0_0xf0_r1_0xff_should_get_r0_0x0_xPSR_unchanged(void)
{
  coreReg[0] = 0x0f;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea004001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0, coreReg[0]);
}

// without affecting status flag
// test AND.W R0, R1, LSR #4
void test_ANDRegisterT2_given_r0_0x0a_r1_0xff_should_get_r0_0xa_xPSR_unchanged(void)
{
  coreReg[0] = 0x0a;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea001011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xa, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// without affecting status flag
// test AND.W R0, R1, ASR #4
void test_ANDRegisterT2_given_r0_0x08000000_r1_0x8000000f_should_get_r0_0x08000000_xPSR_unchanged(void)
{
  coreReg[0] = 0x08000000;
  coreReg[1] = 0x8000000f;
  writeInstructionToMemoryGivenByAddress(0xea001021, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x08000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// without affecting status flag
// test AND.W R0, R1, RRX
void test_ANDRegisterT2_given_r0_0xf000000f_r1_0x8000000f_should_get_r0_0xc0000007_xPSR_unchanged(void)
{
  setCarryFlag();
  coreReg[0] = 0xf000000f;
  coreReg[1] = 0x8000000f;
  writeInstructionToMemoryGivenByAddress(0xea000031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xc0000007, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// without affecting status flag
// test AND.W R0, R1, ROR #16
void test_ANDRegisterT2_given_r0_0xffffffff_r1_0x8000000f_should_get_r0_0x000f8000_xPSR_unchanged(void)
{
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0x8000000f;
  writeInstructionToMemoryGivenByAddress(0xea004031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x000f8000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ANDS.W R0, R1
void test_ANDRegisterT2_given_r0_0xf_r1_0xf0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xea100001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ANDS.W R0, R1, RRX
void test_ANDRegisterT2_given_r0_0x80000000_r1_0x0_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea100031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ANDS.W R0, R1, LSL #4
void test_ANDRegisterT2_given_r0_0x10_r1_0x10000001_should_get_r0_0x10_and_set_carry_flag(void)
{
  coreReg[0] = 0x10;
  coreReg[1] = 0x10000001;
  writeInstructionToMemoryGivenByAddress(0xea101001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //TST Register T2

// affecting status flag
// test TST.W R0, R1
void test_TSTRegisterT2_given_r0_0xf_r1_0xf0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xea100f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test TST.W R0, R1, RRX
void test_TSTRegisterT2_given_r0_0x80000000_r1_0x0_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea100f31, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test TST.W R0, R1, LSL #4
void test_TSTRegisterT2_given_r0_0x10_r1_0x10000001_should_get_r0_0x10_and_set_carry_flag(void)
{
  coreReg[0] = 0x10;
  coreReg[1] = 0x10000001;
  writeInstructionToMemoryGivenByAddress(0xea101f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //BIC Register T2

// without affecting status flag
// test BIC.W R0, R1, R2
void test_BICRegisterT2_given_r1_0x800_r2_0xff_should_get_r0_0x800_xPSR_unchanged(void)
{
  coreReg[1] = 0x800;
  coreReg[2] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea210002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x800, coreReg[0]);
}

// without affecting status flag
// test BIC.W R0, R1
void test_BICRegisterT2_given_r0_0xf00_r1_0xff_should_get_r0_0xf00_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea200001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf00, coreReg[0]);
}

// affecting status flag
// test BICS.W R0, R1
void test_BICRegisterT2_given_r0_0xf0_r1_0xf0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0xf0;
  coreReg[1] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xea300001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test BICS.W R0, R1, RRX
void test_BICRegisterT2_given_r0_0xf_r1_0xf_should_get_r0_0x8_and_set_carry_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea300031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x8, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test BICS.W R0, R1, LSL #4
void test_BICRegisterT2_given_r0_0x80000000_r1_0x07000000_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x07000000;
  writeInstructionToMemoryGivenByAddress(0xea301001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ORR Register T2

// without affecting status flag
// test ORR.W R0, R1, R2
void test_ORRRegisterT2_given_r1_0x800_r2_0xff_should_get_r0_0x8ff_xPSR_unchanged(void)
{
  coreReg[1] = 0x800;
  coreReg[2] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea410002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x8ff, coreReg[0]);
}

// without affecting status flag
// test ORR.W R0, R1, LSR #4
void test_ORRRegisterT2_given_r0_0xf00_r1_0xff_should_get_r0_0xf0f_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea401011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0f, coreReg[0]);
}

// affecting status flag
// test ORRS.W R0, R1
void test_ORRRegisterT2_given_r0_0x0_r1_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x0;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea500001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ORRS.W R0, R1, RRX
void test_ORRRegisterT2_given_r0_0xf_r1_0xf_should_get_r0_0xf_and_set_carry_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0xf;
  writeInstructionToMemoryGivenByAddress(0xea500031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ORRS.W R0, R1, LSL #4
void test_ORRRegisterT2_given_r0_0x80000000_r1_0x07000000_should_get_r0_0xf0000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x07000000;
  writeInstructionToMemoryGivenByAddress(0xea501001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MOV Register T3

// without affecting status flag
// test MOV.W R0, R1
void test_MOVRegisterT3_given_r0_0x800_r1_0xff_should_get_r0_0xff_xPSR_unchanged(void)
{
  coreReg[0] = 0x800;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea4f0001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xff, coreReg[0]);
}

// affecting status flag
// test MOVS.W R0, R1
void test_MOVRegisterT3_given_r0_0x1_r1_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x01;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea5f0001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test MOVS.W R0, R1
void test_MOVRegisterT3_given_r1_0x80000000_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xea5f0001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LSL Immediate T2

// without affecting status flag
// test LSL.W R0, R1, #4
void test_LSLImmediateT2_given_r1_0xff_should_get_r0_0xff0_xPSR_unchanged(void)
{
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea4f1001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xff0, coreReg[0]);
}

// affecting status flag
// test LSLS.W R0, R1, #2
void test_LSLImmediateT2_given_r1_0x80000000_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xea5f1081, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test LSLS.W R0, R1, #3
void test_LSLImmediateT2_given_r1_0x10000000_should_get_r0_0x80000000_and_set_neg_flag(void)
{
  coreReg[1] = 0x10000000;
  writeInstructionToMemoryGivenByAddress(0xea5f00c1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test LSLS.W R0, R1, #31
void test_LSLImmediateT2_given_r1_0x3_should_get_r0_0x80000000_and_set_carry_flag(void)
{
  coreReg[1] = 0x3;
  writeInstructionToMemoryGivenByAddress(0xea5f70c1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LSR Immediate T2

// without affecting status flag
// test LSR.W R0, R1, #4
void test_LSRImmediateT2_given_r1_0xff_should_get_r0_0xf_xPSR_unchanged(void)
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
void test_LSRImmediateT2_given_r1_0x1_should_get_r0_0x0_and_set_zero_flag(void)
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
void test_LSLImmediateT2_given_r1_0xc0000000_should_get_r0_0x1_and_set_carry_flag(void)
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
void test_ASRImmediateT2_given_r1_0xff_should_get_r0_0xf_xPSR_unchanged(void)
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
void test_ASRImmediateT2_given_r1_0x80000000_should_get_r0_0xc0000000_xPSR_unchanged(void)
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
void test_ASRImmediateT2_given_r1_0x1_should_get_r0_0x0_and_set_zero_flag(void)
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
void test_ASRImmediateT2_given_r1_0xf0000000_should_get_r0_0xfe000000_and_set_neg_flag(void)
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
void test_ASRImmediateT2_given_r1_0xc0000000_should_get_r0_0xffffffff_and_set_carry_flag(void)
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



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ROR Immediate T1

// without affecting status flag
// test ROR.W R0, R1, #2
void test_RORImmediateT1_given_r1_is_0xf_should_get_r0_0xc0000003_and_xPSR_unchanged(void)
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
void test_RORImmediateT1_given_r1_is_0xf_should_get_r0_0xf0000000_and_xPSR_unchanged(void)
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
void test_RORImmediateT1_given_r1_is_0x1_should_get_r0_0x80000000_and_set_neg_and_carry_flag(void)
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
void test_RORImmediateT1_given_r1_is_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea5f70f1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x41000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ORN Register T1

// without affecting status flag
// test ORN.W R0, R1, R2
void test_ORNRegisterT1_given_r1_0x800_r2_0xff_should_get_r0_0xffffff00_xPSR_unchanged(void)
{
  coreReg[1] = 0x800;
  coreReg[2] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea610002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xffffff00, coreReg[0]);
}

// without affecting status flag
// test ORN.W R0, R1, #LSR #4
void test_ORNRegisterT1_given_r0_0xf00_r1_0xff_should_get_r0_0xfffffff0_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea601011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfffffff0, coreReg[0]);
}

// affecting status flag
// test ORNS.W R0, R1
void test_ORNRegisterT1_given_r0_0x0_r1_0xffffffff_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x0;
  coreReg[1] = 0xffffffff;
  writeInstructionToMemoryGivenByAddress(0xea700001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ORNS.W R0, R1, RRX
void test_ORNRegisterT1_given_r0_0xf_r1_0xfffffff1_should_get_r0_0x8000000f_and_set_carry_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0xfffffff1;
  writeInstructionToMemoryGivenByAddress(0xea700031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x8000000f, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ORNS.W R0, R1, LSL #4
void test_ORNRegisterT1_given_r0_0x80000000_r1_0x07000000_should_get_r0_0x8fffffff_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x07000000;
  writeInstructionToMemoryGivenByAddress(0xea701001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x8fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //EOR Register T2

// without affecting status flag
// test EOR.W R0, R1, R2
void test_EORRegisterT2_given_r1_0x800_r2_0xff_should_get_r0_0x8ff_xPSR_unchanged(void)
{
  coreReg[1] = 0x800;
  coreReg[2] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea810002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x8ff, coreReg[0]);
}
 
// without affecting status flag
// test EOR.W R0, R1, #LSR #4
void test_EORRegisterT2_given_r0_0xf00_r1_0xff_should_get_r0_0xf0f_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xea801011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0f, coreReg[0]);
}

// affecting status flag
// test EORS.W R0, R1
void test_EORRegisterT2_given_r0_0x0_r1_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x0;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea900001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test EORS.W R0, R1, RRX
void test_EORRegisterT2_given_r0_0xf_r1_0x1_should_get_r0_0xf_and_set_carry_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xea900031, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test EORS.W R0, R1, LSL #4
void test_EORRegisterT2_given_r0_0x80000000_r1_0x07000000_should_get_r0_0xf0000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x07000000;
  writeInstructionToMemoryGivenByAddress(0xea901001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //TEQ Register T1

// affecting status flag
// test TEQ R0, R1
void test_TEQRegisterT1_given_r0_0x0_r1_0x0_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x0;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xea900f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test TEQ R0, R1, RRX
void test_TEQRegisterT1_given_r0_0xf_r1_0x1_should_get_r0_0xf_and_set_carry_flag(void)
{
  coreReg[0] = 0xf;
  coreReg[1] = 0x1;
  writeInstructionToMemoryGivenByAddress(0xea900f31, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test TEQ R0, R1, LSL #4
void test_TEQRegisterT1_given_r0_0x80000000_r1_0x07000000_should_get_r0_0xf0000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x07000000;
  writeInstructionToMemoryGivenByAddress(0xea901f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD Register T3

// without affecting status flag
// test ADD.W R0, R1, R2
void test_ADDRegisterT3_given_r1_0xfe000000_r2_0xff000000_should_get_r0_0xfd000000_xPSR_unchanged(void)
{
  coreReg[1] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xeb010002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfd000000, coreReg[0]);
}
 
// without affecting status flag
// test ADD.W R0, R1, #LSR #4
void test_ADDRegisterT3_given_r0_0xf00_r1_0xff_should_get_r0_0xf0f_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xeb001011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0f, coreReg[0]);
}

// affecting status flag
// test ADDS.W R0, R1
void test_ADDRegisterT3_given_r0_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb100001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x71000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ADDS.W R0, R1, LSL #4
void test_ADDRegisterT3_given_r0_0x80000000_r1_0x700000_should_get_r0_0x87000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x700000;
  writeInstructionToMemoryGivenByAddress(0xeb101001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x87000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ADDS.W R0, R1, LSL #4
void test_ADDRegisterT3_given_r0_0x70000000_r1_0x06000000_should_get_r0_0xd0000000_and_set_overflow_flag(void)
{
  coreReg[0] = 0x70000000;
  coreReg[1] = 0x06000000;
  writeInstructionToMemoryGivenByAddress(0xeb101001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xd0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test ADDS.W R0, R1, LSL #1
void test_ADDRegisterT3_given_r0_0x10000000_r1_0x80000000_should_get_r0_0x10000000(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb100041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //CMN Register T2

// affecting status flag
// test CMN.W R0, R1
void test_CMNRegisterT2_given_r0_0x80000000_r1_0x80000000_should_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb100f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x71000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test CMN.W R0, R1, LSL #4
void test_CMNRegisterT2_given_r0_0x80000000_r1_0x700000_should_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x700000;
  writeInstructionToMemoryGivenByAddress(0xeb101f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test CMN.W R0, R1, LSL #4
void test_CMNRegisterT2_given_r0_0x70000000_r1_0x06000000_should_set_overflow_flag(void)
{
  coreReg[0] = 0x70000000;
  coreReg[1] = 0x06000000;
  writeInstructionToMemoryGivenByAddress(0xeb101f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x70000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test CMN.W R0, R1, LSL #1
void test_CMNRegisterT2_given_r0_0x10000000_r1_0x80000000_should_not_set_carry_flag(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb100f41, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADC Register T2

// carry = 0
// without affecting status flag
// test ADC.W R0, R1, R2
void test_ADCRegisterT2_given_r1_0xfe000000_r2_0xff000000_should_get_r0_0xfd000000_xPSR_unchanged(void)
{
  coreReg[1] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xeb410002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfd000000, coreReg[0]);
}

// carry = 1
// without affecting status flag
// test ADC.W R0, R1, #LSR #4
void test_ADCRegisterT2_given_r0_0xf00_r1_0xff_should_get_r0_0xf10_xPSR_unchanged(void)
{
  setCarryFlag();
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xeb401011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x21000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf10, coreReg[0]);
}

// carry = 1
// affecting status flag
// test ADCS.W R0, R1
void test_ADCRegisterT2_given_r0_0x10000000_r1_0x10000000_should_get_r0_0x1_and_unset_carry_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x10000000;
  writeInstructionToMemoryGivenByAddress(0xeb500001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x20000001, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status flag
// test ADCS.W R0, R1
void test_ADCRegisterT2_given_r0_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb500001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x71000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status flag
// test ADCS.W R0, R1, LSL #4
void test_ADCRegisterT2_given_r0_0x80000000_r1_0x700000_should_get_r0_0x87000000_and_set_neg_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x700000;
  writeInstructionToMemoryGivenByAddress(0xeb501001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x87000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 1
// affecting status flag
// test ADCS.W R0, R1, LSL #4
void test_ADCRegisterT2_given_r0_0x70000000_r1_0x06000000_should_get_r0_0xd0000001_and_set_overflow_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x70000000;
  coreReg[1] = 0x06000000;
  writeInstructionToMemoryGivenByAddress(0xeb501001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xd0000001, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 1
// affecting status(overflow) flag after add carry
// test ADCS.W R0, R1, LSL #4
void test_ADCRegisterT2_given_r0_0x7fffffff_r1_0x0_should_get_r0_0x80000000_and_set_overflow_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x7fffffff;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xeb501001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 1
// affecting status(carry) flag after add carry
// test ADCS.W R0, R1, LSL #4
void test_ADCRegisterT2_given_r0_0x7fffffff_r1_0x08000000_should_get_r0_0x0_and_set_carry_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x7fffffff;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xeb501001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status flag (shift will not affect carry flag)
// test ADCS.W R0, R1, LSL #1
void test_ADCRegisterT2_given_r0_0x10000000_r1_0x80000000_should_get_r0_0x10000000(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb500041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SBC Register T2

// carry = 0
// without affecting status flag
// test SBC.W R0, R1, R2
void test_SBCRegisterT2_given_r1_0xfe000000_r2_0xff000000_should_get_r0_0xfeffffff_xPSR_unchanged(void)
{
  coreReg[1] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xeb610002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfeffffff, coreReg[0]);
}

// carry = 1
// without affecting status flag
// test SBC.W R0, R1, #LSR #4
void test_SBCRegisterT2_given_r0_0xf00_r1_0xff_should_get_r0_0xef1_xPSR_unchanged(void)
{
  setCarryFlag();
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xeb601011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x21000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xef1, coreReg[0]);
}

// carry = 1
// affecting status flag
// test SBCS.W R0, R1
void test_SBCRegisterT2_given_r0_0x01000000_r1_0x10000000_should_get_r0_0xf1000000_and_unset_carry_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x01000000;
  coreReg[1] = 0x10000000;
  writeInstructionToMemoryGivenByAddress(0xeb700001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf1000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 1
// affecting status flag
// test SBCS.W R0, R1
void test_SBCRegisterT2_given_r0_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb700001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status flag
// test SBCS.W R0, R1, LSL #4
void test_SBCRegisterT2_given_r0_0x700000_r1_0x08000000_should_get_r0_0x806fffff_and_set_neg_flag(void)
{
  coreReg[0] = 0x700000;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xeb701001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x806fffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 1
// affecting status flag
// test SBCS.W R0, R1, LSL #4
void test_SBCRegisterT2_given_r0_0x80000000_r1_0x06000000_should_get_r0_0x20000000_and_set_overflow_flag(void)
{
  setCarryFlag();
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x06000000;
  writeInstructionToMemoryGivenByAddress(0xeb701001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x20000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x31000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status(overflow) flag after minus carry
// test SBCS.W R0, R1, LSL #4
void test_SBCRegisterT2_given_r0_0x80000000_r1_0x0_should_get_r0_0x7fffffff_and_set_overflow_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x0;
  writeInstructionToMemoryGivenByAddress(0xeb701001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x31000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status(carry) flag after minus carry
// test SBCS.W R0, R1, LSL #4
void test_SBCRegisterT2_given_r0_0x80000000_r1_0x08000000_should_get_r0_0xffffffff_and_set_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xeb701001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// carry = 0
// affecting status flag (shift will not affect carry flag)
// test SBCS.W R0, R1, LSL #1
void test_SBCRegisterT2_given_r0_0x10000000_r1_0x90000000_should_get_r0_0xefffffff(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x90000000;
  writeInstructionToMemoryGivenByAddress(0xeb700041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xefffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SUB Register T2

// without affecting status flag
// test SUB.W R0, R1, R2
void test_SUBRegisterT2_given_r1_0xfe000000_r2_0xff000000_should_get_r0_0xff000000_xPSR_unchanged(void)
{
  coreReg[1] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xeba10002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xff000000, coreReg[0]);
}
 
// without affecting status flag
// test SUB.W R0, R1, #LSR #4
void test_SUBRegisterT2_given_r0_0xf00_r1_0xff_should_get_r0_0xef1_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xeba01011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xef1, coreReg[0]);
}

// affecting status flag
// test SUBS.W R0, R1
void test_SUBRegisterT2_given_r0_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xebb00001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test SUBS.W R0, R1, LSL #4
void test_SUBRegisterT2_given_r0_0x700000_r1_0x08000000_should_get_r0_0x80700000_and_set_neg_flag(void)
{
  coreReg[0] = 0x700000;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xebb01001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80700000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test SUBS.W R0, R1, LSL #4
void test_SUBRegisterT2_given_r0_0xf0000000_r1_0x02000000_should_get_r0_0xd0000000_and_set_overflow_flag(void)
{
  coreReg[0] = 0xf0000000;
  coreReg[1] = 0x02000000;
  writeInstructionToMemoryGivenByAddress(0xebb01001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xd0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test SUBS.W R0, R1, LSL #1
void test_SUBRegisterT2_given_r0_0x10000000_r1_0x90000000_should_get_r0_0xf0000000(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x90000000;
  writeInstructionToMemoryGivenByAddress(0xebb00041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //CMP Register T3

// affecting status flag
// test CMP.W R0, R1
void test_CMPRegisterT3_given_r0_0x80000000_r1_0x80000000_should_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xebb00f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test CMP.W R0, R1, LSL #4
void test_CMPRegisterT3_given_r0_0x700000_r1_0x08000000_should_set_neg_flag(void)
{
  coreReg[0] = 0x700000;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xebb01f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x700000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test CMP.W R0, R1, LSL #4
void test_CMPRegisterT3_given_r0_0x70000000_r1_0x08000000_should_set_overflow_flag(void)
{
  coreReg[0] = 0x70000000;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xebb01f01, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x70000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test CMP.W R0, R1, LSL #1
void test_CMPRegisterT3_given_r0_0x10000000_r1_0x90000000_should_set_carry_flag(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x90000000;
  writeInstructionToMemoryGivenByAddress(0xebb00f41, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //RSB Register T1

// without affecting status flag
// test RSB.W R0, R1, R2
void test_RSBRegisterT1_given_r1_0xfe000000_r2_0xff000000_should_get_r0_0x01000000_xPSR_unchanged(void)
{
  coreReg[1] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xebc10002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[0]);
}
 
// without affecting status flag
// test RSB.W R0, R1, #LSR #4
void test_RSBRegisterT1_given_r0_0xf00_r1_0xff_should_get_r0_0xfffff10f_xPSR_unchanged(void)
{
  coreReg[0] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xebc01011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfffff10f, coreReg[0]);
}

// affecting status flag
// test RSBS.W R0, R1
void test_RSBRegisterT1_given_r0_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xebd00001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test RSBS.W R0, R1, LSL #4
void test_RSBRegisterT1_given_r0_0x700000_r1_0x09000000_should_get_r0_0x8f900000_and_set_neg_flag(void)
{
  coreReg[0] = 0x700000;
  coreReg[1] = 0x09000000;
  writeInstructionToMemoryGivenByAddress(0xebd01001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x8f900000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test RSBS.W R0, R1, LSL #4
void test_RSBRegisterT1_given_r0_0xffffffff_r1_0x02000000_should_get_r0_0x20000001_and_set_overflow_flag(void)
{
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0x02000000;
  writeInstructionToMemoryGivenByAddress(0xebd01001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x20000001, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test RSBS.W R0, R1, LSL #1
void test_RSBRegisterT1_given_r0_0x10000000_r1_0x80000000_should_get_r0_0xf0000000(void)
{
  coreReg[0] = 0x10000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xebd00041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD SP Register T3

// without affecting status flag
// test ADD.W R0, SP, R2
void test_ADDSPRegisterT3_given_SP_0xfe000000_r2_0xff000000_should_get_r0_0xfd000000_xPSR_unchanged(void)
{
  coreReg[SP] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xeb0d0002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xfd000000, coreReg[0]);
}
 
// without affecting status flag
// test ADD.W R0, SP, R1, #LSR #4
void test_ADDSPRegisterT3_given_SP_0xf00_r1_0xff_should_get_r0_0xf0f_xPSR_unchanged(void)
{
  coreReg[SP] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xeb0d1011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xf0f, coreReg[0]);
}

// affecting status flag
// test ADDS.W R0, SP, R1
void test_ADDSPRegisterT3_given_SP_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[SP] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb1d0001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x71000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ADDS.W R0, SP, R1, LSL #4
void test_ADDSPRegisterT3_given_SP_0x80000000_r1_0x700000_should_get_r0_0x87000000_and_set_neg_flag(void)
{
  coreReg[SP] = 0x80000000;
  coreReg[1] = 0x700000;
  writeInstructionToMemoryGivenByAddress(0xeb1d1001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x87000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test ADDS.W R0, SP, R1, LSL #4
void test_ADDSPRegisterT3_given_SP_0x70000000_r1_0x06000000_should_get_r0_0xd0000000_and_set_overflow_flag(void)
{
  coreReg[SP] = 0x70000000;
  coreReg[1] = 0x06000000;
  writeInstructionToMemoryGivenByAddress(0xeb1d1001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xd0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test ADDS.W R0, SP, R1, LSL #1
void test_ADDSPRegisterT3_given_SP_0x10000000_r1_0x80000000_should_get_r0_0x10000000(void)
{
  coreReg[SP] = 0x10000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xeb1d0041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x10000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// if Rd is SP, shift is allowed to be LSL #1-3
// test ADDS.W SP, R1, LSL #3
void test_ADDSPRegisterT3_given_r1_0x80000000_should_get_r0_0x90000000(void)
{
  coreReg[1] = 0x10000000;
  writeInstructionToMemoryGivenByAddress(0xeb1d0dc1, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xa001fffc, coreReg[SP]);
  TEST_ASSERT_EQUAL(0x81000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SUB SP Register T1

// without affecting status flag
// test SUB.W R0, SP, R2
void test_SUBSPRegisterT1_given_SP_0xfe000000_r2_0xff000000_should_get_r0_0xff000000_xPSR_unchanged(void)
{
  coreReg[SP] = 0xfe000000;
  coreReg[2] = 0xff000000;
  writeInstructionToMemoryGivenByAddress(0xebad0002, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xff000000, coreReg[0]);
}
 
// without affecting status flag
// test SUB.W R0, SP, R1, #LSR #4
void test_SUBSPRegisterT1_given_SP_0xf00_r1_0xff_should_get_r0_0xef1_xPSR_unchanged(void)
{
  coreReg[SP] = 0xf00;
  coreReg[1] = 0xff;
  writeInstructionToMemoryGivenByAddress(0xebad1011, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xef1, coreReg[0]);
}

// affecting status flag
// test SUBS.W R0, SP, R1
void test_SUBSPRegisterT1_given_SP_0x80000000_r1_0x80000000_should_get_r0_0x0_and_set_zero_and_carry_flag(void)
{
  coreReg[SP] = 0x80000000;
  coreReg[1] = 0x80000000;
  writeInstructionToMemoryGivenByAddress(0xebbd0001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test SUBS.W R0, SP, R1, LSL #4
void test_SUBSPRegisterT1_given_SP_0x700000_r1_0x08000000_should_get_r0_0x80700000_and_set_neg_flag(void)
{
  coreReg[SP] = 0x700000;
  coreReg[1] = 0x08000000;
  writeInstructionToMemoryGivenByAddress(0xebbd1001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0x80700000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag
// test SUBS.W R0, SP, R1, LSL #4
void test_SUBSPRegisterT1_given_SP_0xf0000000_r1_0x02000000_should_get_r0_0xd0000000_and_set_overflow_flag(void)
{
  coreReg[SP] = 0xf0000000;
  coreReg[1] = 0x02000000;
  writeInstructionToMemoryGivenByAddress(0xebbd1001, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xd0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}

// affecting status flag (shift will not affect carry flag)
// test SUBS.W R0, SP, R1, LSL #1
void test_SUBSPRegisterT1_given_SP_0x10000000_r1_0x90000000_should_get_r0_0xf0000000(void)
{
  coreReg[SP] = 0x10000000;
  coreReg[1] = 0x90000000;
  writeInstructionToMemoryGivenByAddress(0xebbd0041, 0x08000040);
  coreReg[PC] = 0x08000040;

  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
}
