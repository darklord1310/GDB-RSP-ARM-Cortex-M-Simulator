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
  //STM Register T2

//test case 1
//test STM.W  r0, {r1-r10}
/*  r2 = 0x20000000
 *  r3 = 0x0b19face
 *  r4 = 0x12345678
 *  r5 = 0xdeadbeef
 *  r6 = 0x20000000
 *  r7 = 0xabcdef00
 * 
 * Expected:
 *  Memory address 0x20000000 = 0xce
 *  Memory address 0x20000001 = 0xfa
 *  Memory address 0x20000002 = 0x19
 *  Memory address 0x20000003 = 0x0b
 *  Memory address 0x20000004 = 0x78
 *  Memory address 0x20000005 = 0x56
 *  Memory address 0x20000006 = 0x34
 *  Memory address 0x20000007 = 0x12
 *  Memory address 0x20000008 = 0xef
 *  Memory address 0x20000009 = 0xbe
 *  Memory address 0x2000000a = 0xad
 *  Memory address 0x2000000b = 0xde
 *  Memory address 0x2000000c = 0x00
 *  Memory address 0x2000000d = 0x00
 *  Memory address 0x2000000e = 0x00
 *  Memory address 0x2000000f = 0x20
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0xef
 *  Memory address 0x20000012 = 0xcd
 *  Memory address 0x20000013 = 0xab
 */
void test_STMRegisterT1_given_test_case_1_and_the_writeback_register_is_not_in_the_register_list_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[2] = 0x20000000;
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x12345678;
  coreReg[5] = 0xdeadbeef;
  coreReg[6] = 0x20000000;
  coreReg[7] = 0xabcdef00;
    coreReg[0] = 0x0800004F;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  writeInstructionToMemoryGivenByAddress(0xfbe12300, 0x08000040);  // UMLAL  r2,r3,r1,r0
  coreReg[PC] = 0x08000040;
  uint32_t instruction = 0xc2f80000;
  
  Try
  {
    armStep();
    TEST_ASSERT_EQUAL( 0x20000014, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]);
    TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]);
    TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]);
    TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]);
    TEST_ASSERT_EQUAL( 0x78, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0x56, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0x34, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0x12, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]);
    TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]);
    TEST_ASSERT_EQUAL( 0xcd, memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]);
    TEST_ASSERT_EQUAL( 0xab, memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}

