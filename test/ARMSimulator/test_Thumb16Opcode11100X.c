#include "unity.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
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
#include "ADR.h"
#include "ADDSPRegister.h"
#include "ADDSPImmediate.h"
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


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Unconditional branch

  
//branch backward
// test B label
void test_unconditionalBranch_given_PC_0x0800001a_should_get_PC_is_0x0800000e_xPSR_unchanged(void)
{
  uint32_t instruction = 0xE7F80000;
  
  coreReg[PC] = 0x0800001a;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x0800000e, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



//branch forward
// test B label
void test_unconditionalBranch_given_PC_0x0800000e_should_get_PC_is_0x0800001c_xPSR_unchanged(void)
{
  uint32_t instruction = 0xE0050000;
  
  coreReg[PC] = 0x0800000e;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x0800001c, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test last in IT block
void test_unconditionalBranch_given_last_in_IT_block_should_not_throw_error()
{
  CEXCEPTION_T err;
  uint32_t instruction = 0xe0010000;
  
  coreReg[PC] = 0x08000008;

  Try
  {
    ARMSimulator(0xbf340000);       // ITE CC
    ARMSimulator(0x45880000);       // CMPCC r8,r1
    ARMSimulator(instruction);
    TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
    TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test if not last instruction in IT block
void test_unconditionalBranch_given_not_last_in_IT_block_should_throw_error()
{
  CEXCEPTION_T err;
  uint32_t instruction = 0xe0010000;
  
  coreReg[PC] = 0x0800000c;

  Try
  {
    ARMSimulator(0xbf340000);       // ITE CC
    ARMSimulator(instruction);
    ARMSimulator(0x45880000);       // CMPCS r8,r1
    TEST_FAIL_MESSAGE("Expect error to be throw\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT,coreReg[PC]);
    TEST_ASSERT_EQUAL(UsageFault,err);
  }
}



void test_unconditionalBranch_should_branch_to_itself()
{
  coreReg[PC] = 0x080001b0;
  uint32_t instruction = 0xe7fe0000;
  
  ARMSimulator(instruction);
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL( 0x080001b0, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Conditional branch

  
//branch forward
// test BCC label
void test_ConditionalBranch_given_PC_0x0800000c_should_get_PC_is_0x08000012_xPSR_unchanged(void)
{
  uint32_t instruction = 0xd3010000;
  
  resetCarryFlag();
  coreReg[PC] = 0x0800000c;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



//branch backward
// test BCS label
void test_ConditionalBranch_given_PC_0x0800001e_should_get_PC_is_0x08000008_xPSR_0x21000000(void)
{
  uint32_t instruction = 0xd2f30000;
  
  setCarryFlag();
  coreReg[PC] = 0x0800001e;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x08000008, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}


// test if inside IT block
void test_ConditionalBranch_given_inside_IT_block_should_throw_error(void)
{
  uint32_t instruction = 0xd2f30000;
  CEXCEPTION_T err;
  setCarryFlag();
  coreReg[PC] = 0x0800001e;

  Try
  {
    ARMSimulator(0xbf340000);       // ITE CC
    ARMSimulator(0x45880000);       // CMPCC r8,r1
    ARMSimulator(instruction);      // BCS label
    TEST_FAIL_MESSAGE("Expect error to be throw\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT,coreReg[PC]);
    TEST_ASSERT_EQUAL(UsageFault,err);
  }
}


