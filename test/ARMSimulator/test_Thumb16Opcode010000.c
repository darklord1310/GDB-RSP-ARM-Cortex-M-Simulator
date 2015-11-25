#include "unity.h"
#include "ExceptionObject.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
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
#include "VMOV.h"
#include "VMSR.h"
#include "VMRS.h"
#include "VMLAandVMLS.h"
#include "VMUL.h"
#include "VNMLAandVNMLSandVNMUL.h"
#include "VSTM.h"
#include "VSTR.h"
#include "VPUSH.h"
#include "VLDM.h"
#include "VLDR.h"
#include "VPOP.h"
#include "VNEG.h"
#include "VCMP.h"
#include "VABS.h"
#include "VCVT.h"
#include "VSQRT.h"
#include "MiscellaneousInstructions.h"
#include "VADD.h"
#include "VSUB.h"
#include "VDIV.h"
#include "VCVTBandVCVTT.h"
#include "VCVTandVCVTR.h"
#include "VDIV.h"


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //AND Register T1

// test ANDS R0, R1
void test_ANDRegisterT1_given_r0_0xf0_r1_0xff_should_get_r0_0x0f_xPSR_unchanged(void)
{
  uint32_t instruction = 0x40010000;
  
  coreReg[0] = 0x0f;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x0f, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



//testing zero flag changing
// test ANDS R0, R1
void test_ANDRegisterT1_given_r0_0x00_r1_0xff_should_get_r0_0x00_xPSR_0x41000000(void)
{
  uint32_t instruction = 0x40010000;
  
  coreReg[0] = 0x00;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}



//testing in IT block
/* Test case 1:  
 *            r0 = 0x00
 *            r1 = 0xff
 *            r2 = 0xff 
 *            r3 = 0x11
 *            r4 = 0x88 
 *            r5 = 0x44
 *            r6 = 0x77 
 *            r7 = 0x22
 *            ITETE CS
 *            ANDCS r1,r0
 *            ANDCC r2,r3
 *            ANDCS r4,r5
 *            ANDCC r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00
 *            r1 = 0x00
 *            r2 = 0xff
 *            r3 = 0x11
 *            r4 = 0x00
 *            r5 = 0x44
 *            r6 = 0x77
 *            r7 = 0x22
 * 
 */
void test_ANDRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{

  coreReg[0] = 0x00;
  coreReg[1] = 0xff;
  coreReg[2] = 0xff;
  coreReg[3] = 0x11;
  coreReg[4] = 0x88;
  coreReg[5] = 0x44;
  coreReg[6] = 0x77;
  coreReg[7] = 0x22;
  
  setCarryFlag();
  ARMSimulator(0xbf2b0000);   //ITETE CS
  ARMSimulator(0x40010000);   //ANDCS r1,r0
  ARMSimulator(0x401a0000);   //ANDCC r2,r3
  ARMSimulator(0x402c0000);   //ANDCS r4,r5
  ARMSimulator(0x40370000);   //ANDCC r7,r6
  
  TEST_ASSERT_EQUAL(0x00,coreReg[0]);
  TEST_ASSERT_EQUAL(0x00,coreReg[1]);
  TEST_ASSERT_EQUAL(0xff,coreReg[2]);
  TEST_ASSERT_EQUAL(0x11,coreReg[3]);
  TEST_ASSERT_EQUAL(0x00,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44,coreReg[5]);
  TEST_ASSERT_EQUAL(0x77,coreReg[6]);
  TEST_ASSERT_EQUAL(0x22,coreReg[7]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}



//testing in IT block
/* Test case 2:  
 *            r0 = 0x00
 *            r1 = 0xff
 *            r2 = 0xff 
 *            r3 = 0x11
 *            r4 = 0x88 
 *            r5 = 0x44
 *            r6 = 0x77 
 *            r7 = 0x22
 *            ITETE CC
 *            ANDCC r1,r0
 *            ANDCS r2,r3
 *            ANDCC r4,r5
 *            ANDCS r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00
 *            r1 = 0x00
 *            r2 = 0xff
 *            r3 = 0x11
 *            r4 = 0x00
 *            r5 = 0x44
 *            r6 = 0x77
 *            r7 = 0x22
 * 
 */
void test_ANDRegisterT1_given_test_case_2_should_get_the_expected_result(void)
{

  coreReg[0] = 0x00;
  coreReg[1] = 0xff;
  coreReg[2] = 0xff;
  coreReg[3] = 0x11;
  coreReg[4] = 0x88;
  coreReg[5] = 0x44;
  coreReg[6] = 0x77;
  coreReg[7] = 0x22;
  
  resetCarryFlag();
  ARMSimulator(0xbf350000);   //ITETE CC
  ARMSimulator(0x40010000);   //ANDCC r1,r0
  ARMSimulator(0x401a0000);   //ANDCS r2,r3
  ARMSimulator(0x402c0000);   //ANDCC r4,r5
  ARMSimulator(0x40370000);   //ANDCS r7,r6
  
  TEST_ASSERT_EQUAL(0x00,coreReg[0]);
  TEST_ASSERT_EQUAL(0x00,coreReg[1]);
  TEST_ASSERT_EQUAL(0xff,coreReg[2]);
  TEST_ASSERT_EQUAL(0x11,coreReg[3]);
  TEST_ASSERT_EQUAL(0x00,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44,coreReg[5]);
  TEST_ASSERT_EQUAL(0x77,coreReg[6]);
  TEST_ASSERT_EQUAL(0x22,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LSL Register T1


//test LSLS r2,r1 given r2 = 0xffffffff and r1 = 0x0000ff0f 
void test_LSLRegisterToRegisterT1_given_0x408A_should_shift_left_r1_15_times_and_write_to_R2(void)
{
  uint32_t instruction = 0x408A0000;
  
  coreReg[1] = 0x0000ff0f;                          //set R1 to be 0x0000ff0f
  coreReg[2] = 0xffffffff;                          //set R2 to be 0xffffffff
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffff8000, coreReg[2]);        //after shift 15 times, should get 0xffff8000
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
}


//test LSLS r2,r1 given r2 = 0xffffffff and r1 = 0x0000ffff 
void test_LSLRegisterToRegisterT1_given_0x408A_should_shift_left_r1_0xff_times_and_write_to_R2(void)
{
  uint32_t instruction = 0x408A0000;

  coreReg[1] = 0x0000ffff;                          //set R1 to be 0x0000ffff
  coreReg[2] = 0xffffffff;                          //set R2 to be 0xffffffff
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x00, coreReg[2]);             //after shift 0xff times, should get 0x00
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}

//testing carry flag change
//test LSLS r2,r1 given r2 = 0xffffffff and r1 = 0x0000ff1f
void test_LSLRegisterToRegisterT1_given_0x408A_should_shift_left_r1_0x20_times_and_write_to_R2(void)
{
  uint32_t instruction = 0x408A0000;

  coreReg[1] = 0x0000ff20;                          //set R1 to be 0x0000ff20
  coreReg[2] = 0xffffffff;                          //set R2 to be 0xffffffff
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x00, coreReg[2]);              //after shift 0xff times, should get 0x00
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
}



//testing in IT block
/* Test case 1:  
 *            r0 = 0x00010101
 *            r1 = 0xffffffff
 *            r2 = 0x10101010
 *            r3 = 0x88888888
 *            r4 = 0x44444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE CC
 *            LSLCC r1,r0
 *            LSLCS r2,r3
 *            LSLCC r4,r5
 *            LSLCS r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00010101
 *            r1 = 0xfffffffe
 *            r2 = 0x10101010
 *            r3 = 0x88888888
 *            r4 = 0x00000000
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 */
void test_LSLRegisterToRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{

  coreReg[0] = 0x00010101;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x88888888;
  coreReg[4] = 0x44444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;

  
  resetCarryFlag();
  ARMSimulator(0xbf350000);   //ITETE CC
  ARMSimulator(0x40810000);   //LSLCC r1,r0
  ARMSimulator(0x409a0000);   //LSLCS r2,r3
  ARMSimulator(0x40ac0000);   //LSLCC r4,r5
  ARMSimulator(0x40b70000);   //LSLCS r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0xfffffffe,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x88888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x00000000,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



//testing in IT block
/* Test case 2:  
 *            r0 = 0x00010101
 *            r1 = 0xffffffff
 *            r2 = 0x10101010
 *            r3 = 0x88888888
 *            r4 = 0x44444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE CC
 *            LSLCC r1,r0
 *            LSLCS r2,r3
 *            LSLCC r4,r5
 *            LSLCS r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00010101
 *            r1 = 0xfffffffe
 *            r2 = 0x10101010
 *            r3 = 0x88888888
 *            r4 = 0x00000000
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 */
void test_LSLRegisterToRegisterT1_given_test_case_2_should_get_the_expected_result(void)
{

  coreReg[0] = 0x00010101;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x88888888;
  coreReg[4] = 0x44444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;
  
  setCarryFlag();
  ARMSimulator(0xbf350000);   //ITETE CC
  ARMSimulator(0x40810000);   //LSLCC r1,r0
  ARMSimulator(0x409a0000);   //LSLCS r2,r3
  ARMSimulator(0x40ac0000);   //LSLCC r4,r5
  ARMSimulator(0x40b70000);   //LSLCS r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0xffffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x00000000,coreReg[2]);
  TEST_ASSERT_EQUAL(0x88888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x00000000,coreReg[7]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LSR Register T1
  

//test LSRS  R1, R2  given R1 = 0xffffffff and R2 = 0x00000113
void test_LSRRegisterToRegister16bitsT1_given_0x40d1_should_shift_right_r1_19_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x40d10000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000113;                          //set R2 to be 0x00000113
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000113, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x00001fff, coreReg[1]);        //after shift right 19 times, should get 0x00001fff
}


//testing flag changing
//test LSRS  R1, R2  given R1 = 0xffffffff and R2 = 0x00000120
void test_LSRRegisterToRegister16bitsT1_given_0x40d1_should_shift_right_r1_32_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x40d10000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000120;                          //set R2 to be 0x00000120
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000120, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x00000000, coreReg[1]);        //after shift right 32 times, should get 0x00
  TEST_ASSERT_EQUAL(1,isCarry());
}


//testing shift zero should not update carry flag
//boundary case, minimum shift 
//test LSRS  R1, R2  given R1 = 0xffffffff and R2 = 0x00000100
void test_LSRRegisterToRegister16bitsT1_given_0x40d1_should_shift_right_r1_0_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x40d10000;
  
  setCarryFlag();
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000100;                          //set R2 to be 0x00000100
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000100, coreReg[2]);    
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);        //after shift right 0 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);     //carry flag is still set, and right now N flag is set too because
                                                    //of -1
}


//boundary case, maximum shift 
//test LSRS  R1, R2  given R1 = 0xffffffff and R2 = 0x000001ff
void test_LSRRegisterToRegister16bitsT1_given_0x40d1_should_shift_right_r1_0xff_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x40d10000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x000001ff;                          //set R2 to be 0x000001ff
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x000001ff, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);              //after shift right 0 times, should get 0xffffffff
}



//testing in IT block
/* Test case 1:  
 *            r0 = 0x00010101
 *            r1 = 0xffffffff
 *            r2 = 0x10101010
 *            r3 = 0x88888888
 *            r4 = 0x44444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE CC
 *            LSRCC r1,r0
 *            LSRCS r2,r3
 *            LSLRC r4,r5
 *            LSLRS r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00010101
 *            r1 = 0xfffffffe
 *            r2 = 0x10101010
 *            r3 = 0x88888888
 *            r4 = 0x00000000
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 */
void test_LSRRegisterToRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{

  coreReg[0] = 0x00010101;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x88888888;
  coreReg[4] = 0x44444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;
  
  resetCarryFlag();
  ARMSimulator(0xbf350000);   //ITETE CC
  ARMSimulator(0x40C10000);   //LSRCC r1,r0
  ARMSimulator(0x40DA0000);   //LSRCS r2,r3
  ARMSimulator(0x40EC0000);   //LSRCC r4,r5
  ARMSimulator(0x40F70000);   //LSRCS r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0x7fffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x88888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x00000000,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ASR Register T1
  
  
//test ASRS  R1, R2  given R2, #0xffffffff and R1 = 0x00000113
void test_ASRRegisterToRegisterT1_given_0x4111_should_arithmetic_shift_right_r1_19_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x41110000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000113;                          //set R2 to be 0x00000113
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000113, coreReg[2]);    
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);                 //after shift right 19 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
}

//corner case, carry flag change to 1
//test ASRS  R1, R2  given R2, #0x80000000 and R1 = 0x00000120
void test_ASRRegisterToRegisterT1_given_0x4111_should_arithmetic_shift_right_r1_32_times_and_write_to_R1_carry_flag_1(void)
{
  uint32_t instruction = 0x41110000;
  
  coreReg[1] = 0x80000000;                          //set R1 to be 0x80000000
  coreReg[2] = 0x00000120;                          //set R2 to be 0x00000120
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000120, coreReg[2]);    
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);                 //after shift right 32 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
}


//corner case, carry flag change to 0
//test ASRS  R1, R2  given R2, #0x00000000 and R1 = 0x00000120
void test_ASRRegisterToRegisterT1_given_0x4111_should_arithmetic_shift_right_r1_32_times_and_write_to_R1_carry_flag_0(void)
{
  uint32_t instruction = 0x41110000;
  
  setCarryFlag();
  coreReg[1] = 0x00000000;                          //set R1 to be 0x00000000
  coreReg[2] = 0x00000120;                          //set R2 to be 0x00000120
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000120, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);                 //after shift right 32 times, should get 0x00
  TEST_ASSERT_EQUAL(0x41000000, coreReg[xPSR]);
}


//maximum shift
//test ASRS  R1, R2  given R2, #0xffffffff and R1 = 0x000001ff
void test_ASRRegisterToRegisterT1_given_0x4111_should_arithmetic_shift_right_r1_0xff_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x41110000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x000001ff;                          //set R2 to be 0x000001ff
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x000001ff, coreReg[2]);    
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);                 //after shift right 255 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
}


//minimum shift, carry flag is not affected
//test ASRS  R1, R2  given R2, #0xffffffff and R1 = 0x00000100
void test_ASRRegisterToRegisterT1_given_0x4111_should_arithmetic_shift_right_r1_0_times_and_write_to_R1(void)
{
  uint32_t instruction = 0x41110000;
  
  setCarryFlag();
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[2] = 0x00000100;                          //set R2 to be 0x00000100
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00000100, coreReg[2]);    
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);                 //after shift right 0 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(1, isCarry());                           //after ASR instruction , the carry flag is still set
}


//testing in IT block
/* Test case 1:  
 *            r0 = 0x00010101
 *            r1 = 0x0fffffff
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE CC
 *            ASRCC r1,r0
 *            ASRCS r2,r3
 *            ASRCC r4,r5
 *            ASRCS r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00010101
 *            r1 = 0x07ffffff
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x00000000
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 */
void test_ASRRegisterToRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{

  coreReg[0] = 0x00010101;
  coreReg[1] = 0x0fffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;
  
  resetCarryFlag();
  ARMSimulator(0xbf350000);   //ITETE CC
  ARMSimulator(0x41010000);   //ASRCC r1,r0
  ARMSimulator(0x411a0000);   //ASRCS r2,r3
  ARMSimulator(0x412c0000);   //ASRCC r4,r5
  ARMSimulator(0x41370000);   //ASRCS r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0x07ffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x00000000,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Compare Register T1

  
//test CMP  R1, R0  given R1, #0xffffffff and R0 = 0x00010100
void test_CMPRegisterT1_given_0x4281_should_minus_r1_with_r0_and_update_N_flag_and_C_flag(void)
{
  uint32_t instruction = 0x42810000;
  
  coreReg[1] = 0xffffffff;                          //set R1 to be 0xffffffff
  coreReg[0] = 0x00010100;                          //set R0 to be 0x00010100
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00010100, coreReg[0]);    
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);  
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(1, isCarry());
  TEST_ASSERT_EQUAL(1, isNegative());
}


//test CMP  R1, R0  given R1, #0x80000000 and R0 = 0x40000000
void test_CMPRegisterT1_given_0x4281_should_minus_r1_with_r0_and_update_V_flag_and_C_flag(void)
{
  uint32_t instruction = 0x42810000;
  
  coreReg[1] = 0x80000000;                          //set R1 to be 0x80000000
  coreReg[0] = 0x40000000;                          //set R0 to be 0x40000000
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x40000000, coreReg[0]);    
  TEST_ASSERT_EQUAL(0x80000000, coreReg[1]);  
  TEST_ASSERT_EQUAL(0x31000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL(1, isOverflow());
  TEST_ASSERT_EQUAL(1, isCarry());
}


//testing in IT block
/* 
 *            r0 = 0x00010101
 *            r1 = 0x0fffffff
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE CC
 *            CMPCC r0,r1
 *            CMPCS r2,r3
 *            CMPCC r4,r5
 *            CMPCS r7,r6
 * 
 * Expected Result:    
 *                  coreReg[xPSR] = 0x85002800
 *                  coreReg[xPSR] = 0x81003400
 *                  coreReg[xPSR] = 0x81002800
 *                  coreReg[xPSR] = 0x81000000
 *
 */
void test_CMPRegisterT1_given_test_case_above_should_get_the_expected_result(void)
{
  coreReg[0] = 0x00010101;
  coreReg[1] = 0x0fffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;
  
  ARMSimulator(0xbf350000);   //ITETE CC
  ARMSimulator(0x42880000);   //CMPCC r0,r1
  TEST_ASSERT_EQUAL(0x85002800,coreReg[xPSR]);
  ARMSimulator(0x429A0000);   //CMPCS r2,r3
  TEST_ASSERT_EQUAL(0x81003400,coreReg[xPSR]);
  ARMSimulator(0x42AC0000);   //CMPCC r4,r5
  TEST_ASSERT_EQUAL(0x81002800,coreReg[xPSR]);
  ARMSimulator(0x42B70000);   //CMPCS r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0x0fffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x34444444,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Compare Negative Register T1

  
//test CMN  R1, R0  given R1, #0x80000000 and R0 = 0x40000000
void test_CMNRegisterT1_given_0x42c1_should_minus_r1_with_r0_and_update_N_flag(void)
{
  uint32_t instruction = 0x42c10000;
  
  coreReg[1] = 0x80000000;                          //set R1 to be 0x80000000
  coreReg[0] = 0x40000000;                          //set R0 to be 0x40000000
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x40000000, coreReg[0]);    
  TEST_ASSERT_EQUAL(0x80000000, coreReg[1]);  
  TEST_ASSERT_EQUAL(1, isNegative());
}


//testing in IT block
/* 
 *            r0 = 0x00010101
 *            r1 = 0x0fffffff
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE EQ
 *            CMNEQ r0,r1
 *            CMNNE r2,r3
 *            CMNEQ r4,r5
 *            CMNNE r7,r6
 * 
 * Expected Result:    
 *                  coreReg[xPSR] = 0x05001400
 *                  coreReg[xPSR] = 0x01000c00
 *                  coreReg[xPSR] = 0x01001800
 *                  coreReg[xPSR] = 0x01000000
 */
void test_CMNRegisterT1_given_test_case_above_should_get_the_expected_result(void)
{
  coreReg[0] = 0x00010101;
  coreReg[1] = 0x0fffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;
  
  ARMSimulator(0xbf0b0000);   //ITETE EQ
  ARMSimulator(0x42c80000);   //CMNEQ r0,r1
  TEST_ASSERT_EQUAL(0x05001400,coreReg[xPSR]);
  ARMSimulator(0x42da0000);   //CMNNE r2,r3
  TEST_ASSERT_EQUAL(0x01000c00,coreReg[xPSR]);
  ARMSimulator(0x42ec0000);   //CMNEQ r4,r5
  TEST_ASSERT_EQUAL(0x01001800,coreReg[xPSR]);
  ARMSimulator(0x42f70000);   //CMNNE r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0x0fffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x34444444,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Exclusive OR Register T1

  
// test EORS R1, R0
void test_EORRegisterT1_given_r0_0xf0_r1_0x0f_should_get_r0_0xff_xPSR_unchanged(void)
{
  uint32_t instruction = 0x40410000;
  
  coreReg[0] = 0xf0;
  coreReg[1] = 0x0f;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



// test EORS R1, R0
void test_EORRegisterT1_given_r0_0xff_r1_0xff_should_get_r0_0x00_Z_flag_set(void)
{
  uint32_t instruction = 0x40410000;
  
  coreReg[0] = 0xff;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}



//testing zero flag changing
// test EORS R1, R0
void test_EORRegisterT1_given_r0_0xff_r1_0xff_should_get_r0_0x00_xPSR_0x41000000(void)
{
  uint32_t instruction = 0x40410000;
  
  coreReg[0] = 0xff;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}



//testing in IT block
/* Test case 1:  
 *            r0 = 0x00
 *            r1 = 0xff
 *            r2 = 0xff 
 *            r3 = 0x11
 *            r4 = 0x88 
 *            r5 = 0x44
 *            r6 = 0x77 
 *            r7 = 0x22
 *            ITETE CS
 *            EORCS r1,r0
 *            EORCC r2,r3
 *            EORCS r4,r5
 *            EORCC r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00
 *            r1 = 0x00
 *            r2 = 0xee
 *            r3 = 0x11
 *            r4 = 0x88
 *            r5 = 0x44
 *            r6 = 0x77
 *            r7 = 0x55
 * 
 */
void test_EORRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{
  coreReg[0] = 0x00;
  coreReg[1] = 0xff;
  coreReg[2] = 0xff;
  coreReg[3] = 0x11;
  coreReg[4] = 0x88;
  coreReg[5] = 0x44;
  coreReg[6] = 0x77;
  coreReg[7] = 0x22;
  
  resetCarryFlag();
  ARMSimulator(0xbf2b0000);   //ITETE CS
  ARMSimulator(0x40410000);   //EORCS r1,r0
  ARMSimulator(0x405a0000);   //EORCC r2,r3
  ARMSimulator(0x406c0000);   //EORCS r4,r5
  ARMSimulator(0x40770000);   //EORCC r7,r6
  
  TEST_ASSERT_EQUAL(0x00,coreReg[0]);
  TEST_ASSERT_EQUAL(0xff,coreReg[1]);
  TEST_ASSERT_EQUAL(0xee,coreReg[2]);
  TEST_ASSERT_EQUAL(0x11,coreReg[3]);
  TEST_ASSERT_EQUAL(0x88,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44,coreReg[5]);
  TEST_ASSERT_EQUAL(0x77,coreReg[6]);
  TEST_ASSERT_EQUAL(0x55,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  // Logical OR Register T1
  
// test ORRS R1, R0
void test_ORRRegisterT1_given_r0_0xf0_r1_0xf0_should_get_r1_0xff_xPSR_unchanged(void)
{
  uint32_t instruction = 0x43010000;
  
  coreReg[0] = 0xf0;
  coreReg[1] = 0x0f;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// test ORRS R1, R0
void test_ORRRegisterT1_given_r0_0xff_r1_0x00_should_get_r1_0xff_xPSR_unchanged(void)
{
  uint32_t instruction = 0x43010000;
  
  coreReg[0] = 0xff;
  coreReg[1] = 0x00;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// test ORRS R1, R0
void test_ORRRegisterT1_given_r0_0x88888888_r1_0x44444444_should_get_r1_00xcccccccc_N_flag_set(void)
{
  uint32_t instruction = 0x43010000;
  
  coreReg[0] = 0x88888888;
  coreReg[1] = 0x44444444;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xcccccccc, coreReg[1]);
  TEST_ASSERT_EQUAL(1, isNegative());
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


//testing in IT block
/* Test case 1:  
 *            r0 = 0x00
 *            r1 = 0xff
 *            r2 = 0xff 
 *            r3 = 0x11
 *            r4 = 0x88 
 *            r5 = 0x44
 *            r6 = 0x77 
 *            r7 = 0x22
 *            ITETE CS
 *            ORRCS r1,r0
 *            ORRCC r2,r3
 *            ORRCS r4,r5
 *            ORRCC r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x00
 *            r1 = 0xff
 *            r2 = 0xff
 *            r3 = 0x11
 *            r4 = 0x88
 *            r5 = 0x44
 *            r6 = 0x77
 *            r7 = 0x77
 * 
 */
void test_ORRRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{
  coreReg[0] = 0x00;
  coreReg[1] = 0xff;
  coreReg[2] = 0xff;
  coreReg[3] = 0x11;
  coreReg[4] = 0x88;
  coreReg[5] = 0x44;
  coreReg[6] = 0x77;
  coreReg[7] = 0x22;
  
  resetCarryFlag();
  ARMSimulator(0xbf2b0000);   //ITETE CS
  ARMSimulator(0x43010000);   //ORRCS r1,r0
  ARMSimulator(0x431a0000);   //ORRCC r2,r3
  ARMSimulator(0x432c0000);   //ORRCS r4,r5
  ARMSimulator(0x43370000);   //ORRCC r7,r6
  
  TEST_ASSERT_EQUAL(0x00,coreReg[0]);
  TEST_ASSERT_EQUAL(0xff,coreReg[1]);
  TEST_ASSERT_EQUAL(0xff,coreReg[2]);
  TEST_ASSERT_EQUAL(0x11,coreReg[3]);
  TEST_ASSERT_EQUAL(0x88,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44,coreReg[5]);
  TEST_ASSERT_EQUAL(0x77,coreReg[6]);
  TEST_ASSERT_EQUAL(0x77,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  // Rotate Right Register T1
  
// test RORS R1, R0
void test_RORRegisterT1_given_r0_0x03_r1_0x07_should_get_r1_0xe0000000_xPSR_0xa1000000(void)
{
  uint32_t instruction = 0x41c10000;
  
  coreReg[0] = 0x03;
  coreReg[1] = 0x07;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xe0000000, coreReg[1]);
  TEST_ASSERT_EQUAL(0xa1000000,coreReg[xPSR]);
}


// test RORS R1, R0
void test_RORRegisterT1_given_r0_0x04_r1_0x06_should_get_r1_0x60000000_xPSR_0x01000000(void)
{
  uint32_t instruction = 0x41c10000;
  
  coreReg[0] = 0x04;
  coreReg[1] = 0x06;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x60000000, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

//boundary test, maximum shift , 0xff times
// test RORS R1, R0
void test_RORRegisterT1_given_r0_0xff_r1_0x88888888_should_get_r1_0x11111111_xPSR_0x01000000(void)
{
  uint32_t instruction = 0x41c10000;
  
  coreReg[0] = 0xff;
  coreReg[1] = 0x88888888;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x11111111, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//boundary test, minimum shift , 0x00 times
// test RORS R1, R0
void test_RORRegisterT1_given_r0_0x00_r1_0x88888888_should_get_r1_0x88888888_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x41c10000;
  
  coreReg[0] = 0x00;
  coreReg[1] = 0x88888888;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x88888888, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


//testing in IT block
/* Test case 1:  
 *            r0 = 0x40000044
 *            r1 = 0x80000000
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 *            ITETE CS
 *            RORCS r1,r0
 *            RORCC r2,r3
 *            RORCS r4,r5
 *            RORCC r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x40000044
 *            r1 = 0x08000000
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x43444444
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 * 
 */
void test_RORRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{
  coreReg[0] = 0x40000044;
  coreReg[1] = 0x80000000;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0x00000033;
  coreReg[7] = 0x01010101;
  
  setCarryFlag();
  ARMSimulator(0xbf2b0000);   //ITETE CS
  ARMSimulator(0x41C10000);   //RORCS r1,r0
  ARMSimulator(0x41DA0000);   //RORCC r2,r3
  ARMSimulator(0x41EC0000);   //RORCS r4,r5
  ARMSimulator(0x41F70000);   //RORCC r7,r6
  
  TEST_ASSERT_EQUAL(0x40000044,coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000000,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x43444444,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  // Move Not Register T1
  
// test MVNS R1, R0
void test_MVNRegisterT1_given_r0_0x00_r1_should_get_0xffffffff_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x43c10000;
  
  coreReg[0] = 0x00;
  coreReg[1] = 0x00;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


// test MVNS R1, R0
void test_MVNRegisterT1_given_r0_0x88888888_r1_should_get_0x77777777_xPSR_0x31000000(void)
{
  uint32_t instruction = 0x43c10000;
  
  coreReg[0] = 0x88888888;
  coreReg[1] = 0x00;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x77777777, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//testing in IT block
/* Test case 1:  
 *            r0 = 0x40000044
 *            r1 = 0x80000000
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 *            ITETE CS
 *            MVNCS r1,r0
 *            MVNCC r2,r3
 *            MVNCS r4,r5
 *            MVNCC r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x40000044
 *            r1 = 0xBFFFFFBB
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0xBBBBBBBB
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 * 
 */
void test_MVNRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{
  coreReg[0] = 0x40000044;
  coreReg[1] = 0x80000000;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0x00000033;
  coreReg[7] = 0x01010101;
  
  setCarryFlag();
  ARMSimulator(0xbf2b0000);   //ITETE CS
  ARMSimulator(0x43C10000);   //MVNCS r1,r0
  ARMSimulator(0x43DA0000);   //MVNCC r2,r3
  ARMSimulator(0x43EC0000);   //MVNCS r4,r5
  ARMSimulator(0x43F70000);   //MVNCC r7,r6
  
  TEST_ASSERT_EQUAL(0x40000044,coreReg[0]);
  TEST_ASSERT_EQUAL(0xBFFFFFBB,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0xBBBBBBBB,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Bit Clear Register T1
  
// test BICS R1, R0
void test_BICRegisterT1_given_r0_0xffffffff_r1_0xffffffff_should_get_r1_0x00_xPSR_0x41000000(void)
{
  uint32_t instruction = 0x43810000;
  
  coreReg[0] = 0xffffffff;
  coreReg[1] = 0xffffffff;                    //this will change to 0 after execution because AND with invert of R0
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}


// test BICS R1, R0
void test_BICRegisterT1_given_r0_0x44444444_r1_0xeeeeeeee_should_get_r1_0xaaaaaaaa_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x43810000;
  
  coreReg[0] = 0x44444444;
  coreReg[1] = 0xeeeeeeee;                
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xaaaaaaaa, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


//testing in IT block
/* Test case 1:  
 *            r0 = 0x40000044
 *            r1 = 0xBFFFFFBB
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 *            ITETE CS
 *            BICCS r1,r0
 *            BICCC r2,r3
 *            BICCS r4,r5
 *            BICCC r7,r6
 * 
 * Expected Result:    
 *            r0 = 0x40000044
 *            r1 = 0xBFFFFFBB
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x30000000
 *            r5 = 0x44444444
 *            r6 = 0x00000033
 *            r7 = 0x01010101
 * 
 */
void test_BICRegisterT1_given_test_case_1_should_get_the_expected_result(void)
{
  coreReg[0] = 0x40000044;
  coreReg[1] = 0xBFFFFFBB;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0x00000033;
  coreReg[7] = 0x01010101;
  
  setCarryFlag();
  ARMSimulator(0xbf2b0000);   //ITETE CS
  ARMSimulator(0x43810000);   //BICCS r1,r0
  ARMSimulator(0x439A0000);   //BICCC r2,r3
  ARMSimulator(0x43AC0000);   //BICCS r4,r5
  ARMSimulator(0x43BE0000);   //BICCC r7,r6
  
  TEST_ASSERT_EQUAL(0x40000044,coreReg[0]);
  TEST_ASSERT_EQUAL(0xBFFFFFBB,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x30000000,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  // Add with Carry Register T1

//test with carry is 0, after addition of r1 and r0  no carry
// test ADCS R1, R0
void test_ADCRegisterT1_given_r0_0x08_r1_0x02_and_carry_is_0_should_get_r1_0x0a_xPSR_0x01000000(void)
{
  uint32_t instruction = 0x41410000;
  
  resetCarryFlag();
  coreReg[0] = 0x08;
  coreReg[1] = 0x02;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xa, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



//test with carry is 1, after addition of r1 and r0 no carry
// test ADCS R1, R0
void test_ADCRegisterT1_given_r0_0x80000000_r1_0x7fffffff_and_carry_is_1_should_get_r1_0x00_xPSR_0x61000000(void)
{
  uint32_t instruction = 0x41410000;
  
  setCarryFlag();
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x7fffffff;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x00, coreReg[1]);
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
}


//test with carry is 1, after addition of r1 and r0 got carry
// test ADCS R1, R0
void test_ADCRegisterT1_given_r0_0x80000000_r1_0x80000000_and_carry_is_1_should_get_r1_0x10_xPSR_0x31000000(void)
{
  uint32_t instruction = 0x41410000;
  
  setCarryFlag();
  coreReg[0] = 0x80000000;
  coreReg[1] = 0x80000000;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x01, coreReg[1]);
  TEST_ASSERT_EQUAL(1, isCarry() );
  TEST_ASSERT_EQUAL(0x31000000,coreReg[xPSR]);
  
}



//test overflow flag behavior, after r1 + r0 + c(1) got overflow
// test ADCS R1, R0
void test_ADCRegisterT1_given_r0_0x40000000_r1_0x3fffffff_should_get_r1_0x80000000_xPSR_0x11000000(void)
{
  uint32_t instruction = 0x41410000;
  
  setCarryFlag();
  resetOverflowFlag();
  coreReg[0] = 0x40000000;
  coreReg[1] = 0x3fffffff;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x80000000, coreReg[1]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
}


//test overflow flag behavior, after r1 + r0 before adding with c(1) got overflow
// test ADCS R1, R0
void test_ADCRegisterT1_given_r0_0x40000000_r1_0x40000000_should_get_r1_0x80000001_xPSR_0x11000000(void)
{
  uint32_t instruction = 0x41410000;
  
  setCarryFlag();
  resetOverflowFlag();
  coreReg[0] = 0x40000000;
  coreReg[1] = 0x40000000;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x80000001, coreReg[1]);
  TEST_ASSERT_EQUAL(0x91000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  // Multiply Register T1
  
// test MULS R0, R1, R0
void test_MULRegisterT1_given_r0_0x44444444_r1_0x88888888_should_get_r0_0xeca86420_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x43480000;
  
  coreReg[0] = 0x44444444;
  coreReg[1] = 0x88888888;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xeca86420, coreReg[0]); 
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


// test MULS R1, R0, R1
void test_MULRegisterT1_given_r0_0x44444444_r1_0x88888888_should_get_r1_0xeca86420_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x43410000;

  coreReg[0] = 0x44444444;
  coreReg[1] = 0x88888888;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xeca86420, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


// test MULS R1, R1, R1
void test_MULRegisterT1_given_r1_0x88888888_should_get_r1_0xd950c840_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x43490000;

  coreReg[1] = 0x88888888;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xd950c840, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Test Register T1
  
// test TST  r0,r1 , update zero flag
void test_TSTRegisterT1_given_r0_0x44444444_r1_0x88888888_should_get_xPSR_0x41000000(void)
{
  uint32_t instruction = 0x42080000;
  
  coreReg[0] = 0x44444444;
  coreReg[1] = 0x88888888;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x44444444, coreReg[0]); 
  TEST_ASSERT_EQUAL(0x88888888, coreReg[1]); 
  TEST_ASSERT_EQUAL(0x41000000,coreReg[xPSR]);
}


// test TST  r0,r1 , update negative flag
void test_TSTRegisterT1_given_r0_0x84444444_r1_0x88888888_should_get_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x42080000;
  
  coreReg[0] = 0x84444444;
  coreReg[1] = 0x88888888;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x84444444, coreReg[0]); 
  TEST_ASSERT_EQUAL(0x88888888, coreReg[1]); 
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}



//testing in IT block
/* 
 *            r0 = 0x00010101
 *            r1 = 0x0fffffff
 *            r2 = 0x10101010
 *            r3 = 0x18888888
 *            r4 = 0x34444444
 *            r5 = 0x44444444
 *            R6 = 0X00000033
 *            r7 = 0x01010101
 *            ITETE EQ
 *            TSTEQ r0,r1
 *            TSTNE r2,r3
 *            TSTEQ r4,r5
 *            TSTNE r7,r6
 * 
 * Expected Result:    
 *                  coreReg[xPSR] = 0x05001400
 *                  coreReg[xPSR] = 0x01000C00
 *                  coreReg[xPSR] = 0x01001800
 *                  coreReg[xPSR] = 0x01000000
 */
void test_TSTRegisterT1_given_test_case_above_should_get_the_expected_result(void)
{
  coreReg[0] = 0x00010101;
  coreReg[1] = 0x0fffffff;
  coreReg[2] = 0x10101010;
  coreReg[3] = 0x18888888;
  coreReg[4] = 0x34444444;
  coreReg[5] = 0x44444444;
  coreReg[6] = 0X00000033;
  coreReg[7] = 0x01010101;
  
  ARMSimulator(0xbf0b0000);   //ITETE EQ
  ARMSimulator(0x42080000);   //TSTEQ r0,r1
  TEST_ASSERT_EQUAL(0x05001400,coreReg[xPSR]);
  ARMSimulator(0x421A0000);   //TSTNE r2,r3
  TEST_ASSERT_EQUAL(0x01000C00,coreReg[xPSR]);
  ARMSimulator(0x422C0000);   //TSTEQ r4,r5
  TEST_ASSERT_EQUAL(0x01001800,coreReg[xPSR]);
  ARMSimulator(0x42370000);   //TSTNE r7,r6
  
  TEST_ASSERT_EQUAL(0x00010101,coreReg[0]);
  TEST_ASSERT_EQUAL(0x0fffffff,coreReg[1]);
  TEST_ASSERT_EQUAL(0x10101010,coreReg[2]);
  TEST_ASSERT_EQUAL(0x18888888,coreReg[3]);
  TEST_ASSERT_EQUAL(0x34444444,coreReg[4]);
  TEST_ASSERT_EQUAL(0x44444444,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00000033,coreReg[6]);
  TEST_ASSERT_EQUAL(0x01010101,coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Reverse Subtract from Zero Immediate T1
  
// test RSBS  r0,r0 , update negative flag
void test_RSBImmediateT1_given_r0_0x44444444_should_get_r0_0xbbbbbbbc_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x42400000;
  
  coreReg[0] = 0x44444444;                 
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xbbbbbbbc, coreReg[0]); 
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


// test RSBS  r0,r0 , update carry and zero flag
void test_RSBImmediateT1_given_r0_0x00_should_get_r0_0x00_xPSR_0x61000000(void)
{
  uint32_t instruction = 0x42400000;
  
  coreReg[0] = 0x00;                 
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x00, coreReg[0]); 
  TEST_ASSERT_EQUAL(0x61000000,coreReg[xPSR]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Subtract with Carry Register T1

  
//test with carry is 0, after subtraction of r1 and r0 no carry
// test SBCS R1, R0
void test_SBCRegisterT1_given_r0_0x08_r1_0x02_and_carry_is_0_should_get_r1_0xfffffff9_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x41810000;
  
  resetCarryFlag();
  coreReg[0] = 0x08;
  coreReg[1] = 0x02;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0xfffffff9, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


//test with carry is 0, after subtraction of r1 and r0 got carry
// test SBCS R1, R0
void test_SBCRegisterT1_given_r0_0x02_r1_0x08_and_carry_is_0_should_get_r1_0x05_xPSR_0x21000000(void)
{
  uint32_t instruction = 0x41810000;
  
  resetCarryFlag();
  coreReg[0] = 0x02;
  coreReg[1] = 0x08;                    
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x05, coreReg[1]);
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
}

//test with carry is 1, after subtraction of r1 and r0 no carry
// test SBCS R1, R0
void test_SBCRegisterT1_given_r0_0x08_r1_0x02_and_carry_is_1_should_get_r1_0x00_xPSR_0x81000000(void)
{
  uint32_t instruction = 0x41810000;
  
  setCarryFlag();
  coreReg[0] = 0x08;
  coreReg[1] = 0x02;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xfffffffa, coreReg[1]);
  TEST_ASSERT_EQUAL(0x81000000,coreReg[xPSR]);
}


//test with carry is 1, after subtraction of r1 and r0 got carry
// test SBCS R1, R0
void test_SBCRegisterT1_given_r1_0x08_r0_0x02_and_carry_is_1_should_get_r1_0x10_xPSR_0x21000000(void)
{
  uint32_t instruction = 0x41810000;
  
  setCarryFlag();
  coreReg[0] = 0x02;
  coreReg[1] = 0x08;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x06, coreReg[1]);
  TEST_ASSERT_EQUAL(1, isCarry() );
  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  
}


//test overflow flag behavior, after r1 - r0 before subtract with c(0) got overflow
// test SBCS R1, R0
void test_SBCRegisterT1_given_r0_0x40000000_r1_0x80000000_should_get_r1_0x3fffffff_xPSR_0x31000000(void)
{
  uint32_t instruction = 0x41810000;
  
  resetCarryFlag();
  resetOverflowFlag();
  coreReg[0] = 0x40000000;
  coreReg[1] = 0x80000000;                    
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x3fffffff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x31000000,coreReg[xPSR]);
}