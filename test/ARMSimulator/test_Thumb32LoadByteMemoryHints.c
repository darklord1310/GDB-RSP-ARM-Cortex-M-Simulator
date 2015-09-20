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
#include "CLZ.h"
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
  //LDRBImmediate T2

//minimum index, 0
//test LDRB.W r0,[r1,#0]
void test_LDRBImmediateT2_given_0xf8910000_should_get_R0_is_0x000000f0()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0x0800001b;
  writeInstructionToMemoryGivenByAddress(0xf8910000, 0x08000046);  // LDRB.W r0,[r1,#0]
  coreReg[PC] = 0x08000046;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x000000f0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//maximum index, 4095
//test LDRB.W r0,[r1,#4095]
void test_LDRBImmediateT2_given_0xf8910fff_should_get_R0_is_0x000000f0()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0x7fff01c;
  writeInstructionToMemoryGivenByAddress(0xf8910fff, 0x08000046);  // LDRB.W r0,[r1,#4095]
  coreReg[PC] = 0x08000046;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x000000f0, coreReg[0]);
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRBImmediate T3
  
  
//test with maximum index, -255
//test ldrb r0, [r12,#-255]
/*  r0  = 0xffffffff
 *  r12 = 0x0800011a
 *  Expected:
 *              r0 = 0xf0
 */
void test_LDRBImmediateT3_given_offindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800011a;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xf81c0cff, 0x08000040);  //strb r0, [r12,#-255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xf0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}



//test with maximum index, -255
//test ldrb r0, [r12,#-255]!
/*  r0  = 0xffffffff
 *  r12 = 0x0800011a
 *  Expected:
 *              r0  = 0xf0
 *              r12 = 0x0800001b
 */
void test_LDRBImmediateT3_given_preindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800011a;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xf81c0dff, 0x08000040);  //ldrb r0, [r12,#-255]!

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xf0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x0800001b, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}


//test with maximum index, -255
//test ldrb r0, [r12] , #255
/*  r0  = 0xffffffff
 *  r12 = 0x0800001b
 *  Expected:
 *              r0  = 0xf0
 *              r12 = 0x0800001b
 */
void test_LDRBImmediateT3_given_postindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800001b;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xf81c0bff, 0x08000040);  //ldrb r0, [r12] , #255

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xf0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x0800011a, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}




  

  

