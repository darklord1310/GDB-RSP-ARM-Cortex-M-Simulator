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
#include "MOVRegister.h"
#include "CMPRegister.h"
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


void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //IT block
  
// test ITTTT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf010000_should_change_coreReg_to_0x03000000(void)
{
  uint32_t instruction = 0xbf010000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x03000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test ITTT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf020000_should_change_coreReg_to_0x05000000(void)
{
  uint32_t instruction = 0xbf020000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x05000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test ITT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf040000_should_change_coreReg_to_0x01000400(void)
{
  uint32_t instruction = 0xbf040000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01000400, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test IT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf080000_should_change_coreReg_to_0x01000800(void)
{
  uint32_t instruction = 0xbf080000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01000800, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test IT MI 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf480000_should_change_coreReg_to_0x01004800(void)
{
  uint32_t instruction = 0xbf480000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01004800, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( MI ,cond);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD SP Immediate T1
  
//test case when carry is 1
//test add SP,SP,#0x14
void test_ADDSPImmediateT2_given_carry_is_1_SP_0x20001000_and_offset_20_should_get_SP_0x20001014()
{
  setCarryFlag();
  coreReg[SP] = 0x20001000;
  uint32_t instruction = 0xb0050000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x20001014, coreReg[SP]);

}



//test case when carry is 0
//test add SP,SP,#0x14
void test_ADDSPImmediateT2_given_carry_is_0_SP_0x20001000_and_offset_20_should_get_SP_0x20001014()
{
  resetCarryFlag();
  coreReg[SP] = 0x20001000;
  uint32_t instruction = 0xb0050000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x20001014, coreReg[SP]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REV T1
  
//test REV r2,r3
void test_REVT1_given_r3_0xdeadbeef_should_get_r2_0xefbeadde()
{
  coreReg[3] = 0xdeadbeef;
  uint32_t instruction = 0xba1a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xefbeadde, coreReg[2]);
}



//test REV r2,r7
void test_REVT1_given_r7_0x10101010_should_get_r2_0x10101010()
{
  coreReg[7] = 0x10101010;
  uint32_t instruction = 0xba3a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x10101010, coreReg[2]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REV16 T1
  
//test REV16 r2,r3
void test_REV16T1_given_r3_0xdeadbeef_should_get_r2_0xaddeefbe()
{
  coreReg[3] = 0xdeadbeef;
  uint32_t instruction = 0xba5a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xaddeefbe, coreReg[2]);
}


//test REV16 r2,r7
void test_REV16T1_given_r7_0x10101010_should_get_r2_0x10101010()
{
  coreReg[7] = 0x10101010;
  uint32_t instruction = 0xba7a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x10101010, coreReg[2]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REVSH T1
  
//test REVSH r2,r3
void test_REVSHT1_given_r3_0xdeadbeef_should_get_r2_0xffffefbe()
{
  coreReg[3] = 0xdeadbeef;
  uint32_t instruction = 0xbada0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffffefbe, coreReg[2]);
}


//test REVSH r2,r7
void test_REVSHT1_given_r7_0x10101010_should_get_r2_0x00001010()
{
  coreReg[7] = 0x10101010;
  uint32_t instruction = 0xbafa0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x00001010, coreReg[2]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Signed Extend Halfword T1

//sign bit is 1
//test SXTH r2,r5
void test_SXTHT1_given_r5_0x88888888_should_get_r2_0xffff8888()
{
  coreReg[5] = 0x88888888;
  uint32_t instruction = 0xb22a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffff8888, coreReg[2]);
  
}


//sign bit is 0
//test SXTH r2,r5
void test_SXTHT1_given_r5_0x00004888_should_get_r2_0x00004888()
{
  coreReg[5] = 0x00004888;
  uint32_t instruction = 0xb22a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x00004888, coreReg[2]);
  
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Signed Extend Byte T1
  
//sign bit is 1
//test SXTB r2,r5
void test_SXTBT1_given_r5_0x88888888_should_get_r2_0xffffff88()
{
  coreReg[5] = 0x88888888;
  uint32_t instruction = 0xb26a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffffff88, coreReg[2]);
  
}



//sign bit is 0
//test SXTB r2,r5
void test_SXTBT1_given_r5_0x00004848_should_get_r2_0x00000048()
{
  coreReg[5] = 0x00004848;
  uint32_t instruction = 0xb26a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x00000048, coreReg[2]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Unsigned Extend Byte T1
  
//test UXTH r2,r5
void test_UXTHT1_given_r5_0x88888888_should_get_r2_0x00008888()
{
  coreReg[5] = 0x88888888;
  uint32_t instruction = 0xb2aa0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x00008888, coreReg[2]);
  
}


//test UXTH r2,r5
void test_UXTHT1_given_r5_0xdeadbeef_should_get_r2_0x0000beef()
{
  coreReg[5] = 0xdeadbeef;
  uint32_t instruction = 0xb2aa0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x0000beef, coreReg[2]);
  
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Unsigned Extend Byte T1
  
//test UXTB r2,r5
void test_UXTBT1_given_r5_0x88888888_should_get_r2_0x00000088()
{
  coreReg[5] = 0x88888888;
  uint32_t instruction = 0xb2ea0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x00000088, coreReg[2]);
  
}


//test UXTB r2,r5
void test_UXTBT1_given_r5_0xdeadbeef_should_get_r2_0x000000ef()
{
  coreReg[5] = 0xdeadbeef;
  uint32_t instruction = 0xb2ea0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x000000ef, coreReg[2]);
  
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Compare and Branch on Not Zero T1

//test case where r0 is not 0, should jump
//test CBNZ r0 , bla  (the bla label is at address 0x08000036)
void test_CBNZ_given_r0_0x10_should_get_PC_0x08000036()
{
  coreReg[0] = 0x10;
  coreReg[PC] = 0x0800002a;
  uint32_t instruction = 0xb9200000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x08000036, coreReg[PC]);
  
}


//test case where r0 is 0, should not jump
//test CBNZ r0 , bla  (the bla label is at address 0x08000036)
void test_CBNZ_given_r0_0x00_should_not_get_PC_0x08000036()
{
  coreReg[0] = 0x00;
  coreReg[PC] = 0x0800002a;
  uint32_t instruction = 0xb9200000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_NOT_EQUAL(0x08000036, coreReg[PC]);
  
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Compare and Branch on Zero T1
  

//test case where r0 is not 0, should not jump
//test CBZ r0 , bla  (the bla label is at address 0x08000036)
void test_CBZ_given_r0_0x10_should_not_get_PC_0x08000036()
{
  coreReg[0] = 0x10;
  coreReg[PC] = 0x0800002a;
  uint32_t instruction = 0xb1200000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_NOT_EQUAL(0x08000036, coreReg[PC]);
}


//test case where r0 is 0, should jump
//test CBZ r0 , bla  (the bla label is at address 0x08000030)
void test_CBZ_given_r0_0x10_should_get_PC_0x08000030()
{
  coreReg[0] = 0x00;
  coreReg[PC] = 0x08000024;
  uint32_t instruction = 0xb1200000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x08000030, coreReg[PC]);
}