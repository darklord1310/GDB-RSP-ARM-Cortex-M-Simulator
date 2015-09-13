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
  //STRB T2

//test with index is 0
//test strb r0, [r12,#0]
/*  r0  = 0xffffffff
 *  r12 = 0x20001000
 *  Expected:
 *              Memory address 0x20001000 = 0xff
 */
void test_STRBImmediateT2_given_offset_0_r0_0xffffffff_and_r12_0x20001000_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x20001000;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf88c0000, 0x0800004a);  //strb r0, [r12,#0]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}


//test with maximum index, 4095
//test strb r0, [r12,#4095]
/*  r0  = 0xffffffff
 *  r12 = 0x20001000
 *  Expected:
 *              Memory address 0x20001FFF = 0xff
 */
void test_STRBImmediateT2_given_offset_4095_r0_0xffffffff_and_r12_0x20001000_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x20001000;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf88c0fff, 0x0800004a);  //strb r0, [r12,#4095]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001FFF) ]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}


//test strb r0, [pc,#4095], expect error to be thrown
void test_STRBImmediateT2_given_Rn_is_pc_should_throw(void)
{
  CEXCEPTION_T err;
  writeInstructionToMemoryGivenByAddress(0xf88f0fff, 0x0800004a);  //strb r0, [pc,#4095]
  coreReg[PC] = 0x0800004a;
  
  Try
  {
    armStep();
    TEST_FAIL_MESSAGE("Expect error to be throw\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
  }
}



//test strb pc, [r0,#4095], expect error to be thrown
void test_STRBImmediateT2_given_Rt_is_pc_should_throw(void)
{
  CEXCEPTION_T err;
  writeInstructionToMemoryGivenByAddress(0xf880ffff, 0x0800004a);  //strb pc, [r0,#4095]
  coreReg[PC] = 0x0800004a;
  
  Try
  {
    armStep();
    TEST_FAIL_MESSAGE("Expect error to be throw\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
  }
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRB T3


//test with maximum index, -255
//test strb r0, [r12,#-255]
/*  r0  = 0xffffffff
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x2000100 = 0xff
 */
void test_STRBImmediateT2_given_offindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf80c0cff, 0x0800004a);  //strb r0, [r12,#-255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}



//test with maximum index, -255
//test strb r0, [r12,#-255]!
/*  r0  = 0xffffffff
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x2000100 = 0xff
 *              r12 = 0x20001000
 */
void test_STRBImmediateT2_given_preindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf80c0dff, 0x0800004a);  //strb r0, [r12,#-255]!

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0x20001000, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}



//test with maximum index, -255
//test strb r0, [r12] , #255
/*  r0  = 0xffffffff
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x200010ff = 0xff
 */
void test_STRBImmediateT2_given_postindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf80c09ff, 0x0800004a);  //strb r0, [r12] , #255

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x200010ff) ]);
  TEST_ASSERT_EQUAL( 0x20001000, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}