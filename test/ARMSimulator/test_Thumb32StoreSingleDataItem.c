#include "unity.h"
#include "ExceptionObject.h"
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
#include "VMOV.h"
#include "VMSR.h"
#include "VMRS.h"


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
void test_STRBImmediateT3_given_offindex_should_get_expected_result(void)
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
void test_STRBImmediateT3_given_preindex_should_get_expected_result(void)
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
void test_STRBImmediateT3_given_postindex_should_get_expected_result(void)
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


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRBRegister T2

//maximum shift index,3
//test STRB.W r1,[r2,r3,LSL #3]
/*  r1 = 0xffffffff
 *  r2 = 0x00
 *  r3 = 0x4000200
 */
void test_STRBRegisterT2_given_shiftIndex_is_3_should_0xff_at_memory_address_0x20001000(void)
{
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x0;
  coreReg[3] = 0x4000200;
  coreReg[PC] = 0x08000048;
  writeInstructionToMemoryGivenByAddress(0xf8021033, 0x08000048);  //STRB.W r1,[r2,r3,LSL #3]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0x0800004c, coreReg[PC]);
}



//maximum shift index,0
//test STRB.W r1,[r2,r3,LSL #0]
/*  r1 = 0xffffffff
 *  r2 = 0x00
 *  r3 = 0x20001000
 */
void test_STRBRegisterT2_given_shiftIndex_is_0_should_0xff_at_memory_address_0x20001000(void)
{
  coreReg[1] = 0xffffff31;
  coreReg[2] = 0x0;
  coreReg[3] = 0x20001000;
  coreReg[PC] = 0x08000048;
  writeInstructionToMemoryGivenByAddress(0xf8021003, 0x08000048);  //STRB.W r1,[r2,r3,LSL #0]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x31, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0x0800004c, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRHImmediate T2
  
  
//test STRH.W r1,[r2,#4095]
/*  r1 = 0xffffffff
 *  r2 = 0x00
 *  r3 = 0x4000200
 */
void test_STRHImmediateT2_should_get_0xff_at_memory_address_0x20001fff(void)
{
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;
  coreReg[PC] = 0x08000046;
  writeInstructionToMemoryGivenByAddress(0xf8a21fff, 0x08000046);  //STRH.W r1,[r2,#4095]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001fff) ]);
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20002000) ]);
  TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRHImmediate T3

//test with maximum index, -255
//test strh r0, [r12,#-255]
/*  r0  = 0xffffffff
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x2000100 = 0xff
 *              Memory address 0x2000101 = 0xff
 */
void test_STRHImmediateT3_given_offindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf82c0cff, 0x0800004a);  //strh r0, [r12,#-255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}



//test with maximum index, -255
//test strh r0, [r12,#-255]!
/*  r0  = 0xffffffff
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x2000100 = 0xff
 *              Memory address 0x2000101 = 0xff
 *              r12 = 0x20001000
 */
void test_STRHImmediateT3_given_preindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf82c0dff, 0x0800004a);  //strh r0, [r12,#-255]!

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0x20001000, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}



//test with maximum index, -255
//test strh r0, [r12] , #-255
/*  r0  = 0xffffffff
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x200010ff = 0xff
 */
void test_STRHImmediateT3_given_postindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xffffffff;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800004a;
  writeInstructionToMemoryGivenByAddress(0xf82c09ff, 0x0800004a);  //strh r0, [r12] , #-255

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x200010ff) ]);
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001100) ]);
  TEST_ASSERT_EQUAL( 0x20001000, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRHRegister T2
  

//maximum shift index,3
//test STRH.W r1,[r2,r3,LSL #3]
/*  r1 = 0xffffffff
 *  r2 = 0x00
 *  r3 = 0x4000200
 */
void test_STRHRegisterT2_given_shiftIndex_is_3_should_0xff_at_memory_address_0x20001000_and_0x20001001(void)
{
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x0;
  coreReg[3] = 0x4000200;
  coreReg[PC] = 0x08000048;
  writeInstructionToMemoryGivenByAddress(0xf8221033, 0x08000048);  //STRH.W r1,[r2,r3,LSL #3]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0x0800004c, coreReg[PC]);
}



//maximum shift index,0
//test STRH.W r1,[r2,r3,LSL #0]
/*  r1 = 0xffffffff
 *  r2 = 0x00
 *  r3 = 0x20001000
 */
void test_STRHRegisterT2_given_shiftIndex_is_0_should_0xff_at_memory_address_0x20001000(void)
{
  coreReg[1] = 0xffffff31;
  coreReg[2] = 0x0;
  coreReg[3] = 0x20001000;
  coreReg[PC] = 0x08000048;
  writeInstructionToMemoryGivenByAddress(0xf8221003, 0x08000048);  //STRH.W r1,[r2,r3,LSL #0]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0x31, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0x0800004c, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRRegister T2
  

//maximum shift index,3
//test STR.W r1,[r2,r3,LSL #3]
/*  r1 = 0xdeadbeef
 *  r2 = 0x00
 *  r3 = 0x4000200
 *
 *  Expected:
 *              0x20001000 = 0xef
 *              0x20001001 = 0xbe
 *              0x20001002 = 0xad
 *              0x20001003 = 0xde
 *      
 */
void test_STRRegisterT2_given_shiftIndex_is_3_should_get_the_expected_result(void)
{
  coreReg[1] = 0xdeadbeef;
  coreReg[2] = 0x0;
  coreReg[3] = 0x4000200;
  coreReg[PC] = 0x08000048;
  writeInstructionToMemoryGivenByAddress(0xf8421033, 0x08000048);  //STR.W r1,[r2,r3,LSL #3]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ]);
  TEST_ASSERT_EQUAL( 0x0800004c, coreReg[PC]);
}



//maximum shift index,0
//test STR.W r1,[r2,r3,LSL #0]
/*  r1 = 0xdeadbeef
 *  r2 = 0x00
 *  r3 = 0x20001000
 */
void test_STRRegisterT2_given_shiftIndex_is_0_should_0xff_at_memory_address_0x20001000(void)
{
  coreReg[1] = 0xdeadbeef;
  coreReg[2] = 0x0;
  coreReg[3] = 0x20001000;
  coreReg[PC] = 0x08000046;
  writeInstructionToMemoryGivenByAddress(0xf8421003, 0x08000046);  //STR.W r1,[r2,r3,LSL #0]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ]);
  TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRImmediate T3
  
//test STR.W r1,[r2,#4095]
/*  r1 = 0xdeadbeef
 *  r2 = 0x00
 *  r3 = 0x20001000
 */
void test_STRImmediateT2_should_get_0xff_at_memory_address_0x20001fff(void)
{
  coreReg[1] = 0xdeadbeef;
  coreReg[2] = 0x20001000;
  coreReg[PC] = 0x08000044;
  writeInstructionToMemoryGivenByAddress(0xf8c21fff, 0x08000044);  //STR.W r1,[r2,#4095]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20001fff) ]);
  TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20002000) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20002001) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20002002) ]);
  TEST_ASSERT_EQUAL( 0x08000048, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRImmediate T4
  
  
//test with maximum index, -255
//test str r0, [r12,#-255]
/*  r0  = 0xdeadbeef
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x2000100 = 0xef
 *              Memory address 0x2000101 = 0xbe
 *              Memory address 0x2000102 = 0xad
 *              Memory address 0x2000103 = 0xde
 */
void test_STRImmediateT4_given_offindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xdeadbeef;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800003e;
  writeInstructionToMemoryGivenByAddress(0xf84c0cff, 0x0800003e);  //str r0, [r12,#-255]

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}



//test with maximum index, -255
//test str r0, [r12,#-255]!
/*  r0  = 0xdeadbeef
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x2000100 = 0xef
 *              Memory address 0x2000101 = 0xbe
 *              Memory address 0x2000102 = 0xad
 *              Memory address 0x2000103 = 0xde
 *              r12                      = 0x20001000
 */
void test_STRImmediateT4_given_preindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xdeadbeef;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800003e;
  writeInstructionToMemoryGivenByAddress(0xf84c0dff, 0x0800003e);  //str r0, [r12,#-255]!

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
  TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ]);
  TEST_ASSERT_EQUAL( 0x20001000, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}



//test with maximum index, -255
//test str r0, [r12] , #-255
/*  r0  = 0xdeadbeef
 *  r12 = 0x200010ff
 *  Expected:
 *              Memory address 0x200010ff = 0xef
 *              Memory address 0x20001100 = 0xbe  
 *              Memory address 0x20001101 = 0xad
 *              Memory address 0x20001102 = 0xde
 */
void test_STRImmediateT4_given_postindex_should_get_expected_result(void)
{
  coreReg[0]  = 0xdeadbeef;
  coreReg[12] = 0x200010ff;
  coreReg[PC] = 0x0800003e;
  writeInstructionToMemoryGivenByAddress(0xf84c09ff, 0x0800003e);  //str r0, [r12] , #-255

  //execute
  armStep();
 
  TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x200010ff) ]);
  TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20001100) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20001101) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20001102) ]);
  TEST_ASSERT_EQUAL( 0x20001000, coreReg[12]);
  TEST_ASSERT_EQUAL( 0x08000042, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRBT

//test STRBT.W r1,[r2,#255]
/*  r1 = 0x0f
 *  r2 = 0x200010ff
 */
void test_STRBT_should_get_0x0f_at_memory_address_0x20001fff(void)
{
  coreReg[1] = 0x0f;
  coreReg[2] = 0x200010ff;
  coreReg[PC] = 0x08000046;
  writeInstructionToMemoryGivenByAddress(0xf8021eff, 0x08000046);  //STRBT.W r1,[r2,#255]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0x0f, memoryBlock[ virtualMemToPhysicalMem(0x200011fe) ]);
  TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRHT
  
//test STRHT.W r1,[r2,#255]
/*  r1 = 0xde0f
 *  r2 = 0x200010ff
 */
void test_STRHT_should_get_expected_result_at_memory_address(void)
{
  coreReg[1] = 0xde0f;
  coreReg[2] = 0x200010ff;
  coreReg[PC] = 0x08000046;
  writeInstructionToMemoryGivenByAddress(0xf8221eff, 0x08000046);  //STRHT.W r1,[r2,#255]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0x0f, memoryBlock[ virtualMemToPhysicalMem(0x200011fe) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x200011ff) ]);
  TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRHT
  
//test STRT.W r1,[r2,#255]
/*  r1 = 0xdeadde0f
 *  r2 = 0x200010ff
 */
void test_STRT_should_get_expected_result_at_memory_address(void)
{
  coreReg[1] = 0xdeadde0f;
  coreReg[2] = 0x200010ff;
  coreReg[PC] = 0x08000046;
  writeInstructionToMemoryGivenByAddress(0xf8421eff, 0x08000046);  //STRT.W r1,[r2,#255]

  //execute
  armStep();

  TEST_ASSERT_EQUAL( 0x0f, memoryBlock[ virtualMemToPhysicalMem(0x200011fe) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x200011ff) ]);
  TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x20001200) ]);
  TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x20001201) ]);
  TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
}