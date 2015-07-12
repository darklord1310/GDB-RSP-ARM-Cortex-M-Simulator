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
void test_BX_given_r0_0x80000000_should_get_PC_is_0x80000000_xPSR_unchanged(void)
{
  uint32_t instruction = 0x47000000;
  
  coreReg[0] = 0x80000000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x80000000, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Branch with Link and Exchange

// test BLX r0
void test_BLXRegister_given_r0_0x80000000_should_get_PC_is_0x80000000_LR_is_0x80000013_xPSR_unchanged(void)
{
  uint32_t instruction = 0x47800000;
  
  coreReg[0] = 0x80000000;
  coreReg[PC] = 0x08000010;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x80000000, coreReg[PC]);
  printf("LR: %x\n", coreReg[LR]);
  TEST_ASSERT_EQUAL(0x80000013, coreReg[LR]);  
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
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

