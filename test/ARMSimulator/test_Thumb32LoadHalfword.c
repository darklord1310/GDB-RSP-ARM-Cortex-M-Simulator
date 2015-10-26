#include "unity.h"
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
#include "BKPT.h"
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
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "ExceptionObject.h"
#include "VMOV.h"


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRHImmediate T2

// LDRH.W r0,[r1,#0]
void test_LDRHImmediateT2_given_0xf8b10000_should_get_R0_is_0xbeef()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0xde;
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0x08000060;
  writeInstructionToMemoryGivenByAddress(0xf8b10000, 0x08000040);  // LDRH.W r0,[r1,#0]
  coreReg[PC] = 0x08000040;

  //test
  armStep();

  TEST_ASSERT_EQUAL(0xbeef, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



// LDRH.W r0,[r1,#4095]
void test_LDRHImmediateT2_given_0xf8b10fff_should_get_R0_is_0xbeef()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0xde;
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0x7fff061;
  writeInstructionToMemoryGivenByAddress(0xf8b10fff, 0x08000040);  // LDRH.W r0,[r1,#4095]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xbeef, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRHImmediate T3
    
//test with maximum index, -255
//test ldrh r0, [r12,#-255]
/*  r0  = 0xffffffff
 *  r12 = 0x0800011a
 *  Expected:
 *              r0 = 0x77f0
 */
void test_LDRHImmediateT3_given_offindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800011a;
  coreReg[PC] = 0x0800003e;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x77;
  writeInstructionToMemoryGivenByAddress(0xf83c0cff, 0x0800003e);  //ldrh r0, [r12,#-255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x77f0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}



//test with maximum index, 255
//test ldrh r0, [r12,#-255]!
/*  r0  = 0xffffffff
 *  r12 = 0x0800011a
 *  Expected:
 *              r0  = 0x77f0
 *              r12 = 0x0800001b
 */
void test_LDRHImmediateT3_given_preindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800011a;
  coreReg[PC] = 0x0800003e;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x77;
  writeInstructionToMemoryGivenByAddress(0xf83c0dff, 0x0800003e);  //ldrh r0, [r12,#-255]!

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x77f0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x0800001b, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}


//test with maximum index, 255
//test ldrh r0, [r12] , #255
/*  r0  = 0xffffffff
 *  r12 = 0x0800001b
 *  Expected:
 *              r0  = 0x77f0
 *              r12 = 0x0800001b
 */
void test_LDRHImmediateT3_given_postindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800001b;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x77;
  writeInstructionToMemoryGivenByAddress(0xf83c0bff, 0x08000040);  //ldrh r0, [r12] , #255

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x77f0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x0800011a, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRHT
    
//test with maximum index, 255
//test ldrht r0, [r12, #255]
/*  r0  = 0xffffffff
 *  r12 = 0x7FFFF1C
 *  Expected:
 *              r0  = 0x77f0
 *              PC  = 0x08000044
 */
void test_LDRHT_given_maximum_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x7FFFF1C;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x77;
  writeInstructionToMemoryGivenByAddress(0xf83c0eff, 0x08000040);  //ldrht r0, [r12, #255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x77f0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}

  
//test with minimum index, 0
//test ldrht r0, [r12, #0]
/*  r0  = 0xffffffff
 *  r12 = 0x0800001c
 *  Expected:
 *              r0  = 0x3677
 *              PC  = 0x08000044
 */
void test_LDRHT_given_minimum_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x0800001c;
  coreReg[PC] = 0x08000040;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x77;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001d) ] = 0x36;
  writeInstructionToMemoryGivenByAddress(0xf83c0e00, 0x08000040);  //ldrht r0, [r12, #0]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x3677, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000044, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRHLiteral
    
//test with positive index
//test LDRH r0,[PC,#8]
/*  r0  = 0xffffffff
 *  Expected:
 *              r0  = 0x44fd
 *              PC  = 0x08000044
 */
void test_LDRHLiteral_given_positive_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[PC] = 0x0800003e;
  memoryBlock[ virtualMemToPhysicalMem(0x08000048) ] = 0xfd;
  memoryBlock[ virtualMemToPhysicalMem(0x08000049) ] = 0x44;
  writeInstructionToMemoryGivenByAddress(0xf8bf0008, 0x0800003e);  //LDRH r0,[PC,#8]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x44fd, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}



//test with negative index
//test LDRH r0,[PC,#-26]
/*  r0  = 0xffffffff
 *  Expected:
 *              r0  = 0x4f
 *              PC  = 0x08000044
 */
void test_LDRHLiteral_given_negative_index_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[PC] = 0x0800003e;
  memoryBlock[ virtualMemToPhysicalMem(0x08000026) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000027) ] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xf83f001a, 0x0800003e);  //LDRH r0,[PC,#-26]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0xf04f, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRH Register T2
    
    
//test with minimum shifting, 0
// ldrh.w r5, [r4, r1, lsl #0]
void test_LDRHRegisterT2_given_instruction_0xf8145001_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x60;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x08000060;
  writeInstructionToMemoryGivenByAddress(0xf8345001, 0x0800003e);  // ldrh.w r5, [r4, r1, lsl #0]
  coreReg[PC] = 0x0800003e;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x00000060, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000042, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test with maximum shifting, 3
// ldrh.w r5, [r4, r1, lsl #3]
void test_LDRHRegisterT2_given_instruction_0xf8145031_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x0c;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x100000c;
  writeInstructionToMemoryGivenByAddress(0xf8345031, 0x0800003c);  //ldrh.w r5, [r4, r1, lsl #3]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x0000000c, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRSH Immediate T1
 
//test maximum index, 4095
// LDRSH.W r1,[r0,#4095]
void test_LDRSHImmediateT1_given_instruction_0xf9901fff_should_load_0x08000007_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000068) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000069) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006a) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006b) ] = 0x20;
  coreReg[0] = 0x07fff069;
  writeInstructionToMemoryGivenByAddress(0xf9b01fff, 0x08000040);  // LDRSH.W r1,[r0,#4095]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x00001000, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
    
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRSH Immediate T2
    
    
//test offset addressing
// LDRSH.W r1,[r0,#-20]
void test_LDRSHImmediateT2_given_instruction_0xf9301c14_should_load_0x3eee_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000038) ] = 0xee;
  memoryBlock[ virtualMemToPhysicalMem(0x08000039) ] = 0x3e;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003a) ] = 0x0a;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003b) ] = 0x48;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf9301c14, 0x0800003c);  // LDRSH.W r1,[r0,#-20]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x3eee, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Pre-indexed addressing, negative index
// LDRSH.W r1,[r0,#-20]!
void test_LDRSHImmediateT2_given_instruction_0xf9301d14_should_load_0xffffccee_into_R1_and_R0_is_0x08000038()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000038) ] = 0xee;
  memoryBlock[ virtualMemToPhysicalMem(0x08000039) ] = 0xcc;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003a) ] = 0x0a;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003b) ] = 0x48;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf9301d14, 0x0800003c);  // LDRSH.W r1,[r0,#-20]!
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffccee, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000038, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Post-indexed addressing, positive index
// LDRSH.W r1,[r0], #20
void test_LDRSHImmediateT2_given_instruction_0xf9301b14_should_load_0x4414_into_R1_and_R0_is_0x08000060()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x0800004c) ] = 0x14;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004d) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004e) ] = 0xc8;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004f) ] = 0x2f;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf9301b14, 0x0800003c);  // LDRSH.W r1,[r0], #20
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x4414, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000060, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRSHT
    
//test maximum index, 255
// LDRSHT.W r1,[r0,#255]
void test_LDRSHT_given_instruction_0xf9301eff_should_load_0x11ef_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0xe1;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[0] = 0x7ffff61;
  writeInstructionToMemoryGivenByAddress(0xf9301eff, 0x08000040);  // LDRSHT.W r1,[r0,#255]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xffffe1ef, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRSH Literal
    
//test LDRSH r0,[PC,#8]
/*  r0  = 0xffffffff
 *  Expected:
 *              r0  = 0x44fd
 *              PC  = 0x08000044
 */
void test_LDRSHLiteral_given_instruction_0xf99f0008_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[PC] = 0x0800003e;
  memoryBlock[ virtualMemToPhysicalMem(0x08000048) ] = 0xfd;
  memoryBlock[ virtualMemToPhysicalMem(0x08000049) ] = 0x44;
  writeInstructionToMemoryGivenByAddress(0xf9bf0008, 0x0800003e);  //LDRSH r0,[PC,#8]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0x44fd, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //LDRSH Register T2

//test with minimum shifting, 0
// ldrsh.w r5, [r4, r1, lsl #0]
void test_LDRSHRegisterT2_given_instruction_0xf9345001_should_load_0xffffcfef_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0xcf;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x08000060;
  writeInstructionToMemoryGivenByAddress(0xf9345001, 0x08000040);  // ldrsh.w r5, [r4, r1, lsl #0]
  coreReg[PC] = 0x08000040;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0xffffcfef, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test with maximum shifting, 3
// ldrsh.w r5, [r4, r1, lsl #3]
void test_LDRSHRegisterT2_given_instruction_0xf9345031_should_load_0x00ef_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x100000c;
  writeInstructionToMemoryGivenByAddress(0xf9345031, 0x0800003c);  // ldrsh.w r5, [r4, r1, lsl #3]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x00ef, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}
