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
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "CException.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"


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



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Push Registers T1
  
  
//push the maximum amount of allowed register for encoding T1
//test push {r0-r7}
void test_PUSHT1_given_SP_0x20001000_should_get_SP_0x20000FE0()
{
  coreReg[0] = 0x11111111;
  coreReg[1] = 0x22222222;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x55555555;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x88888888;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[SP] = 0x20001000;
  
  uint32_t instruction = 0xb4ff0000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(  0x20000FE0, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x11, memoryBlock[ virtualMemToPhysicalMem(0x20000fe0)]);
  TEST_ASSERT_EQUAL(  0x11, memoryBlock[ virtualMemToPhysicalMem(0x20000fe1)]);
  TEST_ASSERT_EQUAL(  0x11, memoryBlock[ virtualMemToPhysicalMem(0x20000fe2)]);
  TEST_ASSERT_EQUAL(  0x11, memoryBlock[ virtualMemToPhysicalMem(0x20000fe3)]);
  TEST_ASSERT_EQUAL(  0x22, memoryBlock[ virtualMemToPhysicalMem(0x20000fe4)]);
  TEST_ASSERT_EQUAL(  0x22, memoryBlock[ virtualMemToPhysicalMem(0x20000fe5)]);
  TEST_ASSERT_EQUAL(  0x22, memoryBlock[ virtualMemToPhysicalMem(0x20000fe6)]);
  TEST_ASSERT_EQUAL(  0x22, memoryBlock[ virtualMemToPhysicalMem(0x20000fe7)]);
  TEST_ASSERT_EQUAL(  0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000fe8)]);
  TEST_ASSERT_EQUAL(  0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000fe9)]);
  TEST_ASSERT_EQUAL(  0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000fea)]);
  TEST_ASSERT_EQUAL(  0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000feb)]);
  TEST_ASSERT_EQUAL(  0x44, memoryBlock[ virtualMemToPhysicalMem(0x20000fec)]);
  TEST_ASSERT_EQUAL(  0x44, memoryBlock[ virtualMemToPhysicalMem(0x20000fed)]);
  TEST_ASSERT_EQUAL(  0x44, memoryBlock[ virtualMemToPhysicalMem(0x20000fee)]);
  TEST_ASSERT_EQUAL(  0x44, memoryBlock[ virtualMemToPhysicalMem(0x20000fef)]);
  TEST_ASSERT_EQUAL(  0x55, memoryBlock[ virtualMemToPhysicalMem(0x20000ff0)]);
  TEST_ASSERT_EQUAL(  0x55, memoryBlock[ virtualMemToPhysicalMem(0x20000ff1)]);
  TEST_ASSERT_EQUAL(  0x55, memoryBlock[ virtualMemToPhysicalMem(0x20000ff2)]);
  TEST_ASSERT_EQUAL(  0x55, memoryBlock[ virtualMemToPhysicalMem(0x20000ff3)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff4)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff5)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff6)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff7)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ff8)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ff9)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ffa)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ffb)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000ffc)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000ffd)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000ffe)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000fff)]);

}


//push some of the amount of allowed registers for encoding T1
//test push {r5-r7}
void test_PUSHT1_given_SP_0x20001000_should_get_SP_0x20000FF4()
{
  coreReg[0] = 0x11111111;
  coreReg[1] = 0x22222222;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x55555555;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x88888888;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[SP] = 0x20001000;
  
  uint32_t instruction = 0xb4e00000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(  0x20000FF4, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff4)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff5)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff6)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ff7)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ff8)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ff9)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ffa)]);
  TEST_ASSERT_EQUAL(  0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000ffb)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000ffc)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000ffd)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000ffe)]);
  TEST_ASSERT_EQUAL(  0x88, memoryBlock[ virtualMemToPhysicalMem(0x20000fff)]);

}




//push only one register for encoding T1
//test push {r5}
void test_PUSHT1_given_SP_0x20001000_should_get_SP_0x20000FFC()
{
  coreReg[0] = 0x11111111;
  coreReg[1] = 0x22222222;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x55555555;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x88888888;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[SP] = 0x20001000;
  
  uint32_t instruction = 0xb4200000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(  0x20000FFC, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ffc)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ffd)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000ffe)]);
  TEST_ASSERT_EQUAL(  0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000fff)]);

}


//boundary case, if registerList < 1
void test_PUSHT1_should_throw_error_when_registerlist_less_than_1()
{
  CEXCEPTION_T err;
  uint32_t instruction = 0xb4000000;
  
  Try
  {
    ARMSimulator(instruction);
    TEST_FAIL_MESSAGE("Expect error to be throw\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT,coreReg[PC]);
    TEST_ASSERT_EQUAL(UsageFault,err);
  }

}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Pop Registers T1
  
//pop the maximum amount of allowed register for encoding T1
//test pop {r0-r7}
void test_POPT1_given_SP_0x20001000_and_pop_the_maximum_number_of_allowed_register_should_get_SP_0x20001000()
{
  coreReg[0] = 0x11111111;
  coreReg[1] = 0x22222222;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x55555555;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x88888888;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[SP] = 0x20001000;
  coreReg[PC] = 0x08000040;
  
  uint32_t instruction = 0xbcff0000;      //pop {r0-r7}
  
  ARMSimulator(0xb4ff0000);               //push {r0-r7}
  
  //clear all register to 0 to check whether really pop the correct values or not
  coreReg[0] = 0x00;
  coreReg[1] = 0x00;
  coreReg[2] = 0x00;
  coreReg[3] = 0x00;
  coreReg[4] = 0x00;
  coreReg[5] = 0x00;
  coreReg[6] = 0x00;
  coreReg[7] = 0x00;
  coreReg[8] = 0x00;
  coreReg[9] = 0x00;
  coreReg[10] = 0x00;
  coreReg[11] = 0x00;
  coreReg[12] = 0x00;
  ARMSimulator(instruction);              //pop {r0-r7}
  
  TEST_ASSERT_EQUAL(  0x20001000, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(  0x11111111, coreReg[0]);
  TEST_ASSERT_EQUAL(  0x22222222, coreReg[1]);
  TEST_ASSERT_EQUAL(  0x33333333, coreReg[2]);
  TEST_ASSERT_EQUAL(  0x44444444, coreReg[3]);
  TEST_ASSERT_EQUAL(  0x55555555, coreReg[4]);
  TEST_ASSERT_EQUAL(  0x66666666, coreReg[5]);
  TEST_ASSERT_EQUAL(  0x77777777, coreReg[6]);
  TEST_ASSERT_EQUAL(  0x88888888, coreReg[7]);
}



//pop some of the amount of allowed registers for encoding T1
//test pop {r0-r5}
void test_POPT1_given_SP_0x20001000_and_pop_some_of_the_allowed_register_should_get_SP_0x20000ff8()
{
  coreReg[0] = 0x11111111;
  coreReg[1] = 0x22222222;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x55555555;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x88888888;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[SP] = 0x20001000;
  coreReg[PC] = 0x08000040;
  
  uint32_t instruction = 0xbc3f0000;      //pop {r0-r7}
  
  ARMSimulator(0xb4ff0000);               //push {r0-r7}
  
  //clear all register to 0 to check whether really pop the correct values or not
  coreReg[0] = 0x00;
  coreReg[1] = 0x00;
  coreReg[2] = 0x00;
  coreReg[3] = 0x00;
  coreReg[4] = 0x00;
  coreReg[5] = 0x00;
  coreReg[6] = 0x00;
  coreReg[7] = 0x00;
  coreReg[8] = 0x00;
  coreReg[9] = 0x00;
  coreReg[10] = 0x00;
  coreReg[11] = 0x00;
  coreReg[12] = 0x00;
  ARMSimulator(instruction);              //pop {r0-r5}
  
  TEST_ASSERT_EQUAL(  0x20000ff8, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(  0x11111111, coreReg[0]);
  TEST_ASSERT_EQUAL(  0x22222222, coreReg[1]);
  TEST_ASSERT_EQUAL(  0x33333333, coreReg[2]);
  TEST_ASSERT_EQUAL(  0x44444444, coreReg[3]);
  TEST_ASSERT_EQUAL(  0x55555555, coreReg[4]);
  TEST_ASSERT_EQUAL(  0x66666666, coreReg[5]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[6]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[7]);
}



//push only one register for encoding T1
//test pop {r5}
void test_POPT1_given_SP_0x20001000_should_get_SP_0x20000FE4()
{
  coreReg[0] = 0x11111111;
  coreReg[1] = 0x22222222;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x55555555;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x88888888;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[SP] = 0x20001000;
  coreReg[PC] = 0x08000040;
    
  uint32_t instruction = 0xbc200000;
  
  ARMSimulator(0xb4ff0000);               //push {r0-r7}
  
  //clear all register to 0 to check whether really pop the correct values or not
  coreReg[0] = 0x00;
  coreReg[1] = 0x00;
  coreReg[2] = 0x00;
  coreReg[3] = 0x00;
  coreReg[4] = 0x00;
  coreReg[5] = 0x00;
  coreReg[6] = 0x00;
  coreReg[7] = 0x00;
  coreReg[8] = 0x00;
  coreReg[9] = 0x00;
  coreReg[10] = 0x00;
  coreReg[11] = 0x00;
  coreReg[12] = 0x00;
  ARMSimulator(instruction);              //pop {r5}
  
  TEST_ASSERT_EQUAL(  0x20000FE4, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x08000044, coreReg[PC]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[0]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[2]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[3]);
  TEST_ASSERT_EQUAL(  0x00, coreReg[4]);
  TEST_ASSERT_EQUAL(  0x11111111, coreReg[5]);

}




//boundary case, if registerList < 1
void test_POPT1_should_throw_error_when_registerlist_less_than_1()
{
  CEXCEPTION_T err;
  uint32_t instruction = 0xbc000000;
  
  Try
  {
    ARMSimulator(instruction);
    TEST_FAIL_MESSAGE("Expect error to be throw\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT,coreReg[PC]);
    TEST_ASSERT_EQUAL(UsageFault,err);
  }

}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //SP minus immediate T1

//test carry is 0
void test_SUBSPImmediateT1_given_SP_0x20000FE4_and_carry_is_0_should_get_SP_0x20000FDC()
{
  coreReg[PC] = 0x08000054;
  coreReg[SP] = 0x20000FE4;
  
  resetCarryFlag();
  uint32_t instruction = 0xb0820000;
  
  ARMSimulator(instruction);               //SUB SP,SP,#8
  
  
  TEST_ASSERT_EQUAL(  0x20000FDC, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x08000056, coreReg[PC]);
  
}


//test carry is 1
void test_SUBSPImmediateT1_given_SP_0x20000FE4_and_carry_is_1_should_get_SP_0x20000FDC()
{
  coreReg[PC] = 0x08000054;
  coreReg[SP] = 0x20000FE4;
  
  setCarryFlag();
  uint32_t instruction = 0xb0820000;
  
  ARMSimulator(instruction);               //SUB SP,SP,#8
  
  
  TEST_ASSERT_EQUAL(  0x20000FDC, coreReg[SP]);
  TEST_ASSERT_EQUAL(  0x08000056, coreReg[PC]);
  
}