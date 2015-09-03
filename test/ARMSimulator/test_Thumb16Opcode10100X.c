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



void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}

//test adr r3, bla
void test_ADRT1_given_PC_0x08000044_should_get_r3_0x0800004C(void)
{
  uint32_t instruction = 0xa3010000;
  
  coreReg[PC] = 0x08000044;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x0800004C, coreReg[3]);
  TEST_ASSERT_EQUAL(0x08000046, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}


// test for the conditional cases
/* Test case 1
 *            ITETE EQ
 *            adrne.n r2, bla
 *            adreq.n r3, bla
 *            CMPNE r7, #200
 * 
 * Expected Result:
 *            r2 = 0x08000054
 *            r7 = 0x0ddddddd
 *            PC = 0x0800004c
 *            xPSR = 0x21000000
 *  
 */
void test_ADRT1_conditional_cases_should_get_the_expected_result()
{
  coreReg[PC] = 0x08000044;
  
  resetZeroFlag();
  ARMSimulator(0xbf160000);   //ITETE NE
  ARMSimulator(0xa2030000);   //adrne.n r2, bla
  ARMSimulator(0xa3020000);   //adreq.n r3, bla
  ARMSimulator(0x2fc80000);   //CMPNE r7, #200
  
  TEST_ASSERT_EQUAL(0x08000054,coreReg[2]);
  TEST_ASSERT_EQUAL(0x0800004c,coreReg[PC]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}