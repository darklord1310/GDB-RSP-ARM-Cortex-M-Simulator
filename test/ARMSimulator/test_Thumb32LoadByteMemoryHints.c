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
#include "CLZ.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "BKPT.h"
#include "VMOV.h"

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
  writeInstructionToMemoryGivenByAddress(0xf81c0cff, 0x08000040);  //ldrb r0, [r12,#-255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xf0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}



//test with maximum index, 255
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


//test with maximum index, 255
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


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRBT 
  

//test with maximum index, 255
//test ldrbt r0, [r12, #255]
/*  r0  = 0xffffffff
 *  r12 = 0x7FFFF1C
 *  Expected:
 *              r0  = 0xf0
 *              PC  = 0x08000044
 */
void test_LDRBT_given_maximum_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x7FFFF1C;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xf81c0eff, 0x08000040);  //ldrbt r0, [r12, #255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xf0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}

  
//test with minimum index, 0
//test ldrbt r0, [r12, #0]
/*  r0  = 0xffffffff
 *  r12 = 0x0800001c
 *  Expected:
 *              r0  = 0xf0
 *              PC  = 0x08000044
 */
void test_LDRBT_given_minimum_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800001c;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x77;
  writeInstructionToMemoryGivenByAddress(0xf81c0e00, 0x08000040);  //ldrbt r0, [r12, #0]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x77, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}
  

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRBLiteral
  
//test with positive index
//test LDRB r0,[PC,#8]
/*  r0  = 0xffffffff
 *  Expected:
 *              r0  = 0xfd
 *              PC  = 0x08000044
 */
void test_LDRBLiteral_given_positive_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004c) ] = 0xfd;
  writeInstructionToMemoryGivenByAddress(0xf89f0008, 0x08000040);  //LDRB r0,[PC,#8]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xfd, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}



//test with negative index
//test LDRB r0,[PC,#-26]
/*  r0  = 0xffffffff
 *  Expected:
 *              r0  = 0x4f
 *              PC  = 0x08000044
 */
void test_LDRBLiteral_given_negative_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002a) ] = 0x4f;
  writeInstructionToMemoryGivenByAddress(0xf81f001a, 0x08000040);  //LDRB r0,[PC,#-26]

  //execute
  armStep();
  
  TEST_ASSERT_EQUAL( 0x4f, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRBRegister T2
  
//test with minimum shifting, 0
// ldrb.w r5, [r4, r1, lsl #0]
void test_LDRBRegisterT2_given_instruction_0xf8145001_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x08000060;
  writeInstructionToMemoryGivenByAddress(0xf8145001, 0x08000044);  // ldrb.w r5, [r4, r1, lsl #0]
  coreReg[PC] = 0x08000044;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x0000004f, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000048, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test with maximum shifting, 3
// ldrb.w r5, [r4, r1, lsl #3]
void test_LDRBRegisterT2_given_instruction_0xf8145031_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x100000c;
  writeInstructionToMemoryGivenByAddress(0xf8145031, 0x0800003c);  // ldrb.w r5, [r4, r1, lsl #3]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x0000004f, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
  

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSBImmediate T1
  
//test maximum index, 4095
// LDRSB.W r1,[r0,#4095]
void test_LDRSBImmediateT1_given_instruction_0xf9901fff_should_load_0x08000007_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000068) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000069) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006a) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006b) ] = 0x08;
  coreReg[0] = 0x07fff069;
  writeInstructionToMemoryGivenByAddress(0xf9901fff, 0x08000040);  // LDRSB.W r1,[r0,#4095]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

  
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSBImmediate T2
  
//test offset addressing
// LDRSB.W r1,[r0,#-20]
void test_LDRSBImmediateT2_given_instruction_0xf9101c14_should_load_0xffffffee_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000038) ] = 0xee;
  memoryBlock[ virtualMemToPhysicalMem(0x08000039) ] = 0x3c;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003a) ] = 0x0a;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003b) ] = 0x48;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf9101c14, 0x0800003c);  // LDRSB.W r1,[r0,#-20]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffee, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Pre-indexed addressing, negative index
// LDRSB.W r1,[r0,#-20]!
void test_LDRSBImmediateT2_given_instruction_0xf9101d14_should_load_0xffffffee_into_R1_and_R0_is_0x08000038()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000038) ] = 0xee;
  memoryBlock[ virtualMemToPhysicalMem(0x08000039) ] = 0x3c;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003a) ] = 0x0a;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003b) ] = 0x48;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf9101d14, 0x0800003c);  // LDRSB.W r1,[r0,#-20]!
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffee, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000038, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Pre-indexed addressing, positive index
// LDRSB.W r1,[r0,#20]!
void test_LDRSBImmediateT2_given_instruction_0xf9101f14_should_load_0xffffffef_into_R1_and_R0_is_0x08000060()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf9101f14, 0x0800003c);  // LDRSB.W r1,[r0,#20]!
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x08000060, coreReg[0]);
  TEST_ASSERT_EQUAL(0xffffffef, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
  
  
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSBT
  

//test maximum index, 255
// LDRSBT.W r1,[r0,#255]
void test_LDRSBT_given_instruction_0xf9101eff_should_load_0xffffffef_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x11;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[0] = 0x7ffff61;
  writeInstructionToMemoryGivenByAddress(0xf9101eff, 0x08000040);  // LDRSBT.W r1,[r0,#255]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffffef, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
  
  
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSBLiteral

//test LDRSB r0,[PC,#8]
/*  r0  = 0xffffffff
 *  Expected:
 *              r0  = 0xfd
 *              PC  = 0x08000044
 */
void test_LDRSBLiteral_given_instruction_0xf99f0008_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004c) ] = 0xfd;
  writeInstructionToMemoryGivenByAddress(0xf99f0008, 0x08000040);  //LDRSB r0,[PC,#8]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xfffffffd, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSBRegister T2
  
//test with minimum shifting, 0
// ldrsb.w r5, [r4, r1, lsl #0]
void test_LDRSBRegisterT2_given_instruction_0xf9145001_should_load_0xffffffef_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x08000060;
  writeInstructionToMemoryGivenByAddress(0xf9145001, 0x08000040);  // ldrsb.w r5, [r4, r1, lsl #0]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0xffffffef, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test with maximum shifting, 3
// ldrsb.w r5, [r4, r1, lsl #3]
void test_LDRSBRegisterT2_given_instruction_0xf9145031_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x100000c;
  writeInstructionToMemoryGivenByAddress(0xf9145031, 0x0800003c);  // ldrsb.w r5, [r4, r1, lsl #3]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0xffffffef, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
  
  
  
  
  
