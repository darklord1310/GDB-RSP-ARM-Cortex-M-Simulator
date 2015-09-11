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
void test_ORRImmediateT1_given_instruction_0xf0400154_should_OR_0x54_with_R0_and_place_it_into_R1()
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
void test_ORRImmediateT1_given_instruction_0xf0500000_should_OR_0x0_with_R0_and_set_zero_flag()
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
void test_ORRImmediateT1_given_instruction_0xf0504000_should_OR_0x80000000_with_R0_and_set_carry_and_negative_flag()
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



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ORN Immediate T1

// ORN r1 ,r0 ,#0x54
void test_ORNImmediateT1_given_instruction_0xf0600154_should_OR_0xffffffab_with_R0_and_place_it_into_R1()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0600154, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0xffffffab, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// ORNS r0 ,#-1 and affecting the flag register
void test_ORNImmediateT1_given_instruction_0xf07030ff_should_OR_0x0_with_R0_and_set_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf07030ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// ORNS r0 ,#-1 and affecting the flag register
void test_ORNImmediateT1_given_instruction_0xf07030ff_should_OR_0x0_with_R0_and_set_zero_flag()
{
  coreReg[0] = 0x0;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf07030ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// ORNS r0 ,#0x80000000 and affecting the flag register
void test_ORNImmediateT1_given_instruction_0xf0704000_should_OR_0x7fffffff_with_R0_and_set_carry_and_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0704000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //MVN Immediate T2

// MVN r7, #0xabababab
void test_MVNImmediateT2_given_instruction_0xf06f07ab_should_move_0xffffff54_into_R7()
{
  coreReg[7] = 0xcdcdcdcd;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf06f07ab, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffff54, coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// MVNS r5, #-1 and not affecting the flag register
void test_MVNImmediateT2_given_instruction_0xf07f35ff_should_move_0x0_into_R5_and_update_zero_flag()
{
  coreReg[5] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf07f35ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[5]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test case modify control smaller than 0b00111
// MVNS r5, #0x0 and affect flag register
void test_MVNImmediateT2_given_instruction_0xf07f0500_should_move_0xffffffff_into_R5_and_set_negative_flag()
{
  coreReg[5] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf07f0500, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[5]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// MVNS  r0, #0x80000000
void test_MVNImmediateT2_given_instruction_0xf07f4000_should_move_0x7ffffff_into_R0_and_set_carry_flag()
{
  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf07f4000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x21000000, coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //EOR Immediate T1

// EOR r1 ,r0 ,#0x54
void test_EORImmediateT1_given_instruction_0xf0800154_should_XOR_0x54_with_R0_and_place_it_into_R1()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0800154, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0xabababff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// EORS r0 ,#-1 and affecting the flag register
void test_EORImmediateT1_given_instruction_0xf09030ff_should_XOR_0xffffffff_with_R0_and_update_zero_flag()
{
  coreReg[0] = 0xffffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf09030ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// EORS r0 ,#0x0 and affecting the flag register
void test_EORImmediateT1_given_instruction_0xf0900000_should_XOR_0x0_with_R0_and_set_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0900000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// EORS r0 ,#0x80000000 and affecting the flag register
void test_EORImmediateT1_given_instruction_0xf0904000_should_XOR_0x80000000_with_R0_and_set_carry_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0904000, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2bababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //TEQ Immediate T1

// TEQ r0 ,#0x54
void test_TEQImmediateT1_given_instruction_0xf0900f54_should_XOR_0x54_with_R0_and_update_negative_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0900f54, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


// TEQ r0 ,#-1 and affecting the flag register
void test_TEQImmediateT1_given_instruction_0xf0903fff_should_XOR_0xffffffff_with_R0_and_set_zero_flag()
{
  coreReg[0] = 0xffffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0903fff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control smaller than 0b00111
//modifyControl = 0b00111
// TEQ r0 ,#0xab and not affecting the flag register
void test_TEQImmediateT1_given_instruction_0xf0900fab_should_XOR_0xab_with_R0_and_do_not_update_flag()
{
  coreReg[0] = 0xabab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0900fab, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}


//test case modify control larger than 0b00111
//modifyControl = 0b01000
// TEQ r0 ,#0x80000000 and affecting the flag register
void test_TEQImmediateT1_given_instruction_0xf0904f00_should_XOR_0x80000000_with_R0_and_set_carry_flag()
{
  coreReg[0] = 0xabababab;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf0904f00, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xabababab, coreReg[0]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD Immediate T3

//without affect status flag
//boundary test, maximum immediate number allowed which is 0xffffffff
//test ADD.w R2, R3, #0xffffffff given R3 = 0xffffffff
void test_ADDImmediateT3_given_0xf10332ff_and_r3_is_0xffffffff_should_get_0xfffffffe_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 0xffffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf10332ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xfffffffe, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//boundary test, minimum immediate number allowed which is 0
//test ADD.w R2, R3, #0x0 given R3 = 3000
void test_ADDImmediateT3_given_0xf1030200_and_r3_is_3000_should_get_3000_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 3000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1030200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(3000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (negative)
//test ADDS.w R2, R3, #0x80000000 given R3 = 0x2fffffff
void test_ADDImmediateT3_given_0xf1134200_and_r3_is_0x2fffffff_should_get_0xafffffff_at_r2_and_set_neg_flag(void)
{
  coreReg[3] = 0x2fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1134200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xafffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (zero and carry)
//test ADDS.w R2, R3, #0x10000000 given R3 = 0xf0000000
void test_ADDImmediateT3_given_0xf1135280_and_r3_is_0xf0000000_should_get_0x0_at_r2_and_set_zero_and_carry_flag(void)
{
  coreReg[3] = 0xf0000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1135280, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[2]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (overflow)
//test ADDS.w R2, R3, #0x80000000 given R3 = 0x7fffffff
void test_ADDImmediateT3_given_0xf1136200_and_r3_is_0x7fffffff_should_get_0x87ffffff_at_r2_and_set_neg_and_overflow_flag(void)
{
  coreReg[3] = 0x7fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1136200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x87ffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //CMN Immediate T1

//affect status flag (negative)
//test CMN R0, #0x80000000 given R0 = 0x2fffffff
void test_CMNImmediateT1_given_0xf1104f00_and_r0_is_0x2fffffff_should_set_neg_flag(void)
{
  coreReg[0] = 0x2fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1104f00, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (zero and carry)
//test CMN R0, #0x10000000 given R0 = 0xf0000000
void test_CMNImmediateT1_given_0xf1105f80_and_r0_is_0xf0000000_should_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0xf0000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1105f80, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (overflow)
//test CMN R0, #0x80000000 given R0 = 0x7fffffff
void test_CMNImmediateT1_given_0xf1106f00_and_r0_is_0x7fffffff_should_set_neg_and_overflow_flag(void)
{
  coreReg[0] = 0x7fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1106f00, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADC Immediate T1

//without affect status flag
//boundary test, maximum immediate number allowed which is 0xffffffff
//test ADC R2, R3, #0xffffffff given R3 = 0xffffffff
void test_ADCImmediateT1_given_0xf14332ff_and_r3_is_0xffffffff_should_get_0xffffffff_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 0xffffffff;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf14332ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//boundary test, minimum immediate number allowed which is 0
//test ADC R2, R3, #0x0 given R3 = 3000
void test_ADCImmediateT1_given_0xf1430200_and_r3_is_3000_should_get_3001_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 3000;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1430200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(3001, coreReg[2]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 1, after addition of r3 and 0x80000000 no carry
//affect status flag (carry)
//test ADCS R2, R3, #0x80000000 given R3 = 0x0fffffff
void test_ADCImmediateT1_given_0xf1534200_and_r3_is_0x0fffffff_should_get_0x90000000_at_r2_and_unset_carry_flag(void)
{
  coreReg[3] = 0x0fffffff;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1534200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x90000000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 0, after addition of r3 and 0x80000000 no carry
//affect status flag (negative)
//test ADCS R2, R3, #0x80000000 given R3 = 0x2fffffff
void test_ADCImmediateT1_given_0xf1534200_and_r3_is_0x2fffffff_should_get_0xafffffff_at_r2_and_set_neg_flag(void)
{
  coreReg[3] = 0x2fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1534200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xafffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 1, after addition of r3 and 0x0 got carry
//affect status flag (zero)
//test ADCS R2, R3, #0x0 given R3 = 0xffffffff
void test_ADCImmediateT1_given_0xf1530200_and_r3_is_0xffffffff_should_get_0x0_at_r2_and_set_zero_and_carry_flag(void)
{
  coreReg[3] = 0xffffffff;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1530200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[2]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test overflow flag behavior, after R3 + 0x80000000 + c(1) got overflow
//affect status flag (overflow)
//test ADCS R2, R3, #0x80000000 given R3 = 0x80000000
void test_ADCImmediateT1_given_0xf1534200_and_r3_is_0x80000000_should_get_0x1_at_r2_and_set_overflow_flag(void)
{
  coreReg[3] = 0x80000000;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1534200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x1, coreReg[2]);
  TEST_ASSERT_EQUAL(0x31000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test overflow flag behavior, after R3 + 0x40000000 before adding with c(1) got overflow
//affect status flag (overflow)
//test ADCS R2, R3, #0x40000000 given R3 = 0x40000000
void test_ADCImmediateT1_given_0xf1534280_and_r3_is_0x40000000_should_get_0x80000001_at_r2_and_set_overflow_flag(void)
{
  coreReg[3] = 0x40000000;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1534280, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x80000001, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SBC Immediate T1

//without affect status flag
//boundary test, maximum immediate number allowed which is 0xffffffff
//test SBC R2, R3, #0xeeeeeeee given R3 = 0xffffffff
void test_SBCImmediateT1_given_0xf16332ee_and_r3_is_0xffffffff_should_get_0x11111110_at_r2_xPSR_unchanged(void)
{
  // carry flag == 0
  coreReg[3] = 0xffffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf16332ee, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x11111110, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//boundary test, minimum immediate number allowed which is 0
//test SBC R2, R3, #0x0 given R3 = 3000
void test_SBCImmediateT1_given_0xf1630200_and_r3_is_3000_should_get_3000_at_r2_xPSR_unchanged(void)
{
  // carry flag == 1
  coreReg[3] = 3000;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1630200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(3000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 0, after subtraction of r3 and 0x80000000 no carry
//affect status flag (negative)
//test SBCS R2, R3, #0x80000000 given R3 = 0x20000000;
void test_SBCImmediateT1_given_0xf1734200_and_r3_is_0x20000000_should_get_0x9fffffff_at_r2_and_set_neg_flag(void)
{
  coreReg[3] = 0x20000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1734200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x9fffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 0, after subtraction of r3 and 0x20000000 got carry
//affect status flag (carry)
//test SBCS R2, R3, #0x20000000 given R3 = 0x80000000;
void test_SBCImmediateT1_given_0xf1735200_and_r3_is_0x80000000_should_get_0x5FFFFFFF_at_r2_and_set_carry_flag(void)
{
  coreReg[3] = 0x80000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1735200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x5FFFFFFF, coreReg[2]);
  TEST_ASSERT_EQUAL(0x31000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 1, after subtraction of r3 and 0x80000000 no carry
//affect status flag (negative)
//test SBCS R2, R3, #0x80000000 given R3 = 0x20000000
void test_SBCImmediateT1_given_0xf1734200_and_r3_is_0x20000000_should_get_0xa0000000_at_r2_set_neg_flag(void)
{
  coreReg[3] = 0x20000000;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1734200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xa0000000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//test with carry is 1, after subtraction of r3 and 0x80000000 got carry
//affect status flag (carry)
//test SBCS R2, R3, #0x80000000 given R3 = 0x80000000
void test_SBCImmediateT1_given_0xf1734200_and_r3_is_0x80000000_should_get_0x0_at_r2_and_set_zero_and_carry_flag(void)
{
  coreReg[3] = 0x80000000;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1734200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[2]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (overflow)
//test SBCS R2, R3, #0x80000000 given R3 = 0x7fffffff
void test_SBCImmediateT1_given_0xf1734200_and_r3_is_0x7fffffff_should_get_0xffffffff_at_r2_and_set_overflow_flag(void)
{
  coreReg[3] = 0x7fffffff;
  setCarryFlag();

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1734200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SUB Immediate T3

//without affect status flag
//boundary test, maximum immediate number allowed which is 0xffffffff
//test SUB.w R2, R3, #0xeeeeeeee given R3 = 0xffffffff
void test_SUBImmediateT3_given_0xf1a332ee_and_r3_is_0xffffffff_should_get_0x11111111_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 0xffffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1a332ee, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x11111111, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//boundary test, minimum immediate number allowed which is 0
//test SUB.w R2, R3, #0x0 given R3 = 3000
void test_SUBImmediateT3_given_0xf1a30200_and_r3_is_3000_should_get_3000_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 3000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1030200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(3000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (negative)
//test SUBS.w R2, R3, #0x5 given R3 = 0xffffffff
void test_SUBImmediateT3_given_0xf1b30205_and_r3_is_0xffffffff_should_get_0xfffffffa_at_r2_and_set_neg_and_carry_flag(void)
{
  coreReg[3] = 0xffffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1b30205, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xfffffffa, coreReg[2]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (zero and carry)
//test SUBS.w R2, R3, #0xf0000000 given R3 = 0xf0000000
void test_SUBImmediateT3_given_0xf1b34270_and_r3_is_0xf0000000_should_get_0x0_at_r2_and_set_zero_and_carry_flag(void)
{
  coreReg[3] = 0xf0000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1b34270, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[2]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (overflow)
//test SUBS.w R2, R3, #0x80000000 given R3 = 0x7fffffff
void test_SUBImmediateT3_given_0xf1b34200_and_r3_is_0x7fffffff_should_get_0xffffffff_at_r2_and_set_neg_and_overflow_flag(void)
{
  coreReg[3] = 0x7fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1b34200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //CMP Immediate T2

//affect status flag (negative)
//test CMP.W R0, #0x30000000 given R0 = 0x2fffffff
void test_CMPImmediateT2_given_0xf1b05f40_and_r0_is_0x2fffffff_should_set_neg_flag(void)
{
  coreReg[0] = 0x2fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1b05f40, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (zero and carry)
//test CMP.W R0, #0xf0000000 given R0 = 0xf0000000
void test_CMPImmediateT2_given_0xf1b04f70_and_r0_is_0xf0000000_should_set_zero_and_carry_flag(void)
{
  coreReg[0] = 0xf0000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1b04f70, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (overflow)
//test CMP.W R0, #0x80000000 given R0 = 0x7fffffff
void test_CMPImmediateT2_given_0xf1106f00_and_r0_is_0x7fffffff_should_set_neg_and_overflow_flag(void)
{
  coreReg[0] = 0x7fffffff;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1b04f00, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //RSB Immediate T2

//without affect status flag
//boundary test, maximum immediate number allowed which is 0xffffffff
//test RSB.w R2, R3, #0xffffffff given R3 = 0xeeeeeeee
void test_RSBImmediateT2_given_0xf1c332ff_and_r3_is_0xeeeeeeee_should_get_0x11111111_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 0xeeeeeeee;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1c332ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x11111111, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//boundary test, minimum immediate number allowed which is 0
//test RSB.w R2, R3, #0x0 given R3 = 3000
void test_RSBImmediateT2_given_0xf1c30200_and_r3_is_3000_should_get_0xfffff448_at_r2_xPSR_unchanged(void)
{
  coreReg[3] = 3000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1c30200, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(-3000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (negative)
//test RSBS.w R2, R3, #0xffffffff given R3 = 0x5
void test_RSBImmediateT2_given_0xf1d332ff_and_r3_is_0x5_should_get_0xfffffffa_at_r2_and_set_neg_and_carry_flag(void)
{
  coreReg[3] = 0x5;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1d332ff, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xfffffffa, coreReg[2]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (zero and carry)
//test RSBS.w R2, R3, #0xf0000000 given R3 = 0xf0000000
void xtest_RSBImmediateT2_given_0xf1d34270_and_r3_is_0xf0000000_should_get_0x0_at_r2_and_set_zero_and_carry_flag(void)
{
  coreReg[3] = 0xf0000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1d34270, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0x0, coreReg[2]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}

//affect status flag (overflow)
//test RSBS.w R2, R3, #0x70000000 given R3 = 0x80000000
void test_RSBImmediateT2_given_0xf1d342e0_and_r3_is_0x70000000_should_get_0xf0000000_at_r2_and_set_neg_and_overflow_flag(void)
{
  coreReg[3] = 0x80000000;

  //create test fixture
  writeInstructionToMemoryGivenByAddress(0xf1d342e0, 0x0800000C);
  coreReg[PC] = 0x0800000C;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xf0000000, coreReg[2]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000010, coreReg[PC]);
}
