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

void setUp(void)
{
  initializeSimulator();

}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MOV Immediate T2

// mov r7, #0x2f00
void test_MOVImmediateT2_given_instruction_0xf45f573c_should_move_into_0x2f00_into_R7_and_update_the_flag()
{
  uint32_t instruction = 0xf45f573c;

  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x2f00, coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// mov r5, #-1 and not affecting the flag register
void test_MOVImmediateT2_given_instruction_0xf04f35ff_should_move_into_0xffffffff_into_R5_and_do_not_update_flag()
{
  uint32_t instruction = 0xf04f35ff;

  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[5]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

//test case modify control smaller than 0b00111
// movs r5, #-1 and affect flag register
void test_MOVImmediateT2_given_instruction_0xf05f35ff_should_move_into_0xffffffff_into_R5_and_set_negative_flag()
{
  uint32_t instruction = 0xf05f35ff;

  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[5]);
  TEST_ASSERT_EQUAL(0x81000000, coreReg[xPSR]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// movs.w  r0, #0x88000000
void test_MOVImmediateT2_given_instruction_0xf05f4008_should_move_into_0x88000000_into_R0_and_set_carry_and_negative_flag()
{
  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf05f4008, 0x0800000C);  // movs.w  r0, #0x88000000
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x88000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
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
  //AND Immediate T1

// AND r0 ,#0xab
void test_ANDImmediateT1_given_instruction_0xf00000ab_should_AND_0xab_with_R0_and_place_it_into_R0()
{
  uint32_t instruction = 0xf00000ab;
  coreReg[0] = 0xabababab;

  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// ANDS r0 ,#-1 and affecting the flag register
void test_ANDImmediateT1_given_instruction_0xf01030ff_should_AND_0xffffffff_with_R0_and_set_negative_flag()
{
  uint32_t instruction = 0xf01030ff;
  coreReg[0] = 0xabababab;

  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// ANDS r0 ,#0x0 and affecting the flag register
void test_ANDImmediateT1_given_instruction_0xf0100000_should_AND_0x0_with_R0_and_set_zero_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0100000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// ANDS r0 ,#0x80000000 and affecting the flag register
void test_ANDImmediateT1_given_instruction_0xf0104000_should_AND_0x80000000_with_R0_and_set_carry_and_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0104000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //TST Immediate T1

// TST r0 ,#0x0
void test_TSTImmediateT1_given_instruction_0xf0100f00_should_AND_0x0_with_R0_and_update_zero_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0100f00, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// TST r0 ,#-1 and affecting the flag register
void test_TSTImmediateT1_given_instruction_0xf01030ff_should_AND_0xffffffff_with_R0_and_set_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0103fff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// TST r0 ,#0xab and not affecting the flag register
void test_TSTImmediateT1_given_instruction_0xf0100fab_should_AND_0xab_with_R0_and_do_not_update_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0100fab, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// TST r0 ,#0x80000000 and affecting the flag register
void test_TSTImmediateT1_given_instruction_0xf0104f00_should_AND_0x80000000_with_R0_and_set_carry_and_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0104f00, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //BIC Immediate T1

// BIC r1, r0 ,#0x1
void test_BICImmediateT1_given_instruction_0xf0200101_should_AND_0xfe_with_R0_and_place_it_into_R1()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0200101, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0xabababaa, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// BICS r0 ,#-1 and affecting the flag register
void test_BICImmediateT1_given_instruction_0xf03030ff_should_AND_0x0_with_R0_and_set_zero_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf03030ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// BICS r0 ,#0xab and affecting the flag register
void test_BICImmediateT1_given_instruction_0xf03000ab_should_AND_0xffffff54_with_R0_and_update_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf03000ab, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xababab00, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// BICS r0 ,#0x80000000 and affecting the flag register
void test_BICImmediateT1_given_instruction_0xf0304000_should_AND_0x7fffffff_with_R0_and_set_carry_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0304000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2bababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}




/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ORR Immediate T1

// ORR r1 ,r0 ,#0x54
void test_ORRImmediateT1_given_instruction_0xf00000ab_should_OR_0x54_with_R0_and_place_it_into_R1()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0400154, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0xabababff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// ORRS r0 ,#-1 and affecting the flag register
void test_ORRImmediateT1_given_instruction_0xf05030ff_should_OR_0xffffffff_with_R0_and_set_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf05030ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// ORRS r0 ,#0x0 and affecting the flag register
void test_ORRImmediateT1_given_instruction_0xf0500000_should_AND_0x0_with_R0_and_set_zero_flag()
{
  coreReg[0] = 0x0;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0500000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// ORRS r0 ,#0x80000000 and affecting the flag register
void test_ORRImmediateT1_given_instruction_0xf0504000_should_AND_0x80000000_with_R0_and_set_carry_and_negative_flag()
{
  coreReg[0] = 0x0;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0504000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}