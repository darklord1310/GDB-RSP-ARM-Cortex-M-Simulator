#include "unity.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "CException.h"
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
  //Branch Exchange

// test BX r0
void test_BX_given_r0_0x80000001_should_get_PC_is_0x80000001_xPSR_unchanged(void)
{
  CEXCEPTION_T err;
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x80000001;
  
  Try
  {
    ARMSimulator(instruction);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
  
  
  TEST_ASSERT_EQUAL(0x80000000, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// test BX r0
void test_BX_given_r0_0x0800013_should_get_PC_is_0x08000012_xPSR_unchanged(void)
{
  CEXCEPTION_T err;
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x08000013;
  
  Try
  {
    ARMSimulator(instruction);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }

  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test if inside IT block
void test_BX_if_inside_IT_block_should_throw_err(void)
{
  CEXCEPTION_T err;
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x80000003;
  
  Try
  {
    ARMSimulator(0xbf010000);      //ITTTT EQ 
    ARMSimulator(instruction);
    TEST_FAIL_MESSAGE("Not expect to be pass\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT, coreReg[PC]);
  }
}



//test if bit 0 is not 1
void test_BX_if_the_branch_register_bit_0_is_not_1_should_throw_err(void)
{
  CEXCEPTION_T err;
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x80000000;
  
  Try
  {
    ARMSimulator(instruction);
    TEST_FAIL_MESSAGE("Not expect to be pass\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT, coreReg[PC]);
  }
  
}


// test last instruction in IT block
void test_BX_when_it_is_last_in_IT_block_given_r0_0x0800013_should_get_PC_is_0x08000012_xPSR_unchanged(void)
{
  CEXCEPTION_T err;
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x08000013;
  
  Try
  {
    ARMSimulator(0xbfe40000);                   //ITT AL
    ARMSimulator(0x07c90000);                   //LSLAL r1,#31
    ARMSimulator(instruction);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }

  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Branch with Link and Exchange

// test BLX r0
void test_BLXRegister_given_r0_0x080004a5_should_get_PC_is_0x080004a4_LR_is_0x08000331_xPSR_unchanged(void)
{
  uint32_t instruction = 0x47800000;
  
  coreReg[0] = 0x080004a5;
  coreReg[PC] = 0x0800032e;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x080004a4, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x08000331, coreReg[LR]);  
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test if Rm is PC
void test_BLXRegister_if_the_Rm_is_PC_should_throw_err(void)
{
  CEXCEPTION_T err;
  uint32_t instruction = 0x47f80000;
  
  Try
  {
    ARMSimulator(instruction);
    TEST_FAIL_MESSAGE("Not expect to be pass\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT, coreReg[PC]);
  }
  
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Move Register to Register Encoding T1 

//test MOV R8, R3, case D is 1
void test_MOVRegisterToRegisterT1_given_instruction_0x46980000_should_move_R3_to_R8(void)
{
  uint32_t instruction = 0x46980000;
  
  coreReg[3] = 0xff101c00;                        //set R3 to be 0xff101c00
  ARMSimulator(instruction);                      //move r3 to r8
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg[8]);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg[3]);
}


//test MOV R4, R3, case D is 0
void test_MOVRegisterToRegisterT1_given_instruction_0x461c0000_should_move_R3_to_R4(void)
{
  uint32_t instruction = 0x461c0000;
    
  coreReg[3] = 0xff101c00;                        //set R3 to be 0xff101c00
  ARMSimulator(instruction);                      //move r3 to r4
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg[4]);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg[3]);
}


//testing status flag should not change
//test MOV R4, R3, move negative number
void test_MOVRegisterToRegisterT1_given_instruction_0x461c0000_should_move_R3_to_R4_0xffffffff_xPSR_unchanged(void)
{
  uint32_t instruction = 0x461c0000;
    
  coreReg[3] = 0xffffffff;                        //set R3 to be 0xffffffff
  ARMSimulator(instruction);                      //move r3 to r4
  
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[4]);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Add Register Encoding T2
  
//test ADD R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_ADDRegisterToRegisterT2_given_0x4423_and_r3_is_0xffffffff_r4_is_0x80000000_should_get_0x7fffffff_at_r3_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44230000;
  
  coreReg[3] = 0xffffffff;
  coreReg[4] = 0x80000000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test ADD R10, R8 given R8 = 0xf and R10 = 0x80
void test_ADDRegisterToRegisterT2_given_0x44c2_and_r8_is_0xf_r10_is_0x80_should_get_0x8f_at_r10_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44c20000;
  
  coreReg[8] = 0xf;
  coreReg[10] = 0x80;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x8f, coreReg[10]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test ADD R4, R2 given R2 = 0x77 and R4 = 0x88
void test_ADDRegisterToRegisterT2_given_0x4414_and_r2_is_0x77_r4_is_0x88_should_get_0xff_at_r4_status_flag_unchanged(void)
{
  uint32_t instruction = 0x44140000;
  
  coreReg[2] = 0x77;
  coreReg[4] = 0x88;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg[4]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Compare Registers Encoding T2
  
//test CMP R7, R10 given R3 = 0xffffffff and R4 = 0x80000000
void test_CMPRegisterT2_given_0x4557_and_r7_is_0xffffffff_r10_is_0x80000000_should_get_xPSR_0x21000000(void)
{
  uint32_t instruction = 0x45570000;
  
  coreReg[7] = 0xffffffff;
  coreReg[10] = 0x80000000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}


//testing in IT block
/* 
 *            r8 = 0x00010101
 *            r1 = 0x0fffffff
 *            r9 = 0x10101010
 *            r3 = 0x18888888
 *            r10 = 0x34444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r11 = 0x01010101
 *            ITETE EQ
 *            CMPEQ r8,r1
 *            CMPNE r9,r3
 *            CMPEQ r10,r5
 *            CMPNE r11,r6
 * 
 * Expected Result:    
 *                  coreReg[xPSR] = 0x05001400
 *                  coreReg[xPSR] = 0x81000C00
 *                  coreReg[xPSR] = 0x81001800
 *                  coreReg[xPSR] = 0x21000000
 *
 */
void test_CMPRegisterT2_given_test_case_above_should_get_the_expected_result(void)
{
  coreReg[8] = 0x00010101;
  coreReg[1] = 0x0fffffff;
  coreReg[9] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[10] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[11] = 0x01010101;
  
  ARMSimulator(0xbf0B0000);   //ITETE EQ
  ARMSimulator(0x45880000);   //CMPEQ r8,r1
  TEST_ASSERT_EQUAL(0x05001400,coreReg[xPSR]);
  ARMSimulator(0x45990000);   //CMPNE r9,r3
  TEST_ASSERT_EQUAL(0x81000C00,coreReg[xPSR]);
  ARMSimulator(0x45AA0000);   //CMPEQ r10,r5
  TEST_ASSERT_EQUAL(0x81001800,coreReg[xPSR]);
  ARMSimulator(0x45B30000);   //CMPNE r11,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[8]);
  TEST_ASSERT_EQUAL(0x0fffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[9]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x34444444,coreReg[10]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[11]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}

