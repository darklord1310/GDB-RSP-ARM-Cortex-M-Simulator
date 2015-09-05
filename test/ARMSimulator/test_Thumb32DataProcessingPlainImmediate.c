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
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"

void setUp(void)
{
  initializeSimulator();

}


void tearDown(void)
{
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MOV Immediate T3

/* case 1: i = 0
           imm4 = 0
           imm3 = 0
           imm8 = 0x42
   MOVW R5, #0x42
*/
void test_MOVImmediateT3_given_instruction_0xf2400542_should_move_into_0x42_into_R5()
{
  uint32_t instruction = 0xf2400542;

  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x42, coreReg[5]);

}


/* case 2: i = 0
           imm4 = 0
           imm3 = 0x5
           imm8 = 0x42
   MOVW R12, #0x542
*/
void test_MOVImmediateT3_given_instruction_0xf2405c42_should_move_into_0x542_into_R12()
{
  uint32_t instruction = 0xf2405c42;

  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x542, coreReg[12]);
}



/* case 3: i = 1
           imm4 = 0x00
           imm3 = 0x5
           imm8 = 0x42
   MOVW R12, #0xd42
*/
void test_MOVImmediateT3_given_instruction_0xf6405c42_should_move_into_0xd42_into_R12()
{
  uint32_t instruction = 0xf6405c42;

  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xd42, coreReg[12]);
}



/* case 4: i = 1
           imm4 = 0x3
           imm3 = 0x5
           imm8 = 0x42
   MOVW R3, #0xd42
*/
void test_MOVImmediateT3_given_instruction_0xf6435342_should_move_into_0x3d42_into_R3()
{
  uint32_t instruction = 0xf6435342;

  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x3d42, coreReg[3]);
}


// MOVW r5, 0xF360
void test_MOVImmediateT3_given_instruction_0xf24f3560_should_move_into_0xf360_into_R5()
{
  uint32_t instruction = 0xf24f3560;

  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xf360, coreReg[5]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD Immediate T4

/*
  case 1: i = 0
          imm3 = 0
          imm8 = 0x42
  ADDW R2, R3, #0x42
*/
void test_ADDImmediateT4_given_0xf2030242_and_r3_is_0xabababab_should_get_0xabababed_at_r2()
{
  coreReg[3] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf2030242, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababed, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

/*
  case 2: i = 0
          imm3 = 0x7
          imm8 = 0x42
  ADDW R1, R3, #0x0
*/
void test_ADDImmediateT4_given_0xf2037142_and_r3_is_0xabababab_should_get_0xababb2ed_at_r1()
{
  coreReg[3] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf2037142, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xababb2ed, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

/*
  case 3: i = 1
          imm3 = 7
          imm8 = 0x42
  ADDW R0, R3, #0xf42
*/
void test_ADDImmediateT4_given_0xf6037042_and_r3_is_0xabababab_should_get_0xababbaed_at_r0()
{
  coreReg[3] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf6037042, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xababbaed, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



