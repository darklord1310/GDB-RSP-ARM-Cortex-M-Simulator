#include "unity.h"
#include <stdint.h>
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

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Add Immediate T1, T2
  
//boundary test, maximum immediate number allowed which is 7
//test ADDS R2, R3, #0x07 given R3 = 0x01
void test_ADDImmediateT1_given_0x1dda_and_r3_is_0x01_should_get_0x08_at_r2_xPSR_unchanged(void)
{
  uint32_t instruction = 0x1dda0000;
  
  coreReg[3] = 0x01;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x08, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//boundary test, minimum immediate number allowed which is 0
//test ADDS R2, R3, #0x07 given R3 = 3000
void test_ADDImmediateT1_given_0x1dda_and_r3_is_3000_should_get_0x07_at_r2_xPSR_unchanged(void)
{
  uint32_t instruction = 0x1dda0000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xbbf, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//test ADDS R3, #0x08 given R3 = 3000
void test_ADDImmediateT2_given_0x3308_and_r3_is_3000_should_get_0xbc0_at_r3_xPSR_unchanged(void)
{
  uint32_t instruction = 0x33080000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xbc0, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//boundary test, minimum immediate number allowed which is 0
//test ADDS R3, #0 given R3 = 3000
void test_ADDImmediateT2_given_0x3300_and_r3_is_3000_should_get_3000_at_r3_xPSR_unchanged(void)
{
  uint32_t instruction = 0x33000000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(3000, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//boundary test, maximum immediate number allowed which is 0xff
//test ADDS R3, #0xff given R3 = 3000
void test_ADDImmediateT2_given_0x33ff_and_r3_is_3000_should_get_0xbc0_at_r3_xPSR_unchanged(void)
{
  uint32_t instruction = 0x33ff0000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xcb7, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

// test for the conditional cases
/* Expect
 *        r0   0x11
 *        r1   0x2f
 *        r2   0x33 
 *        r6   0x07
 *        xPSR 0x01000000
 * 
 */
void test_ADDImmediateT1_and_T2_should_get_the_expected_result()
{
  ARMSimulator(0x20110000);   //movs r0, #0x11
  ARMSimulator(0x21220000);   //movs r1, #0x22
  ARMSimulator(0x22330000);   //movs r2, #0x33
  ARMSimulator(0xbf0f0000);   //ITEEEE EQ
  ARMSimulator(0x1dda0000);   //addeq r2,r3,#7
  ARMSimulator(0x1dee0000);   //addne r6, r5, #0x07
  ARMSimulator(0x350c0000);   //addeq r5,#12 
  ARMSimulator(0x310d0000);   //addne r1,r1,#0x0D
  
  TEST_ASSERT_EQUAL( 0x11, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x2f, coreReg[1]);
  TEST_ASSERT_EQUAL( 0x33, coreReg[2]);
  TEST_ASSERT_EQUAL( 0x07, coreReg[6]);
  TEST_ASSERT_EQUAL(coreReg[xPSR], 0x01000000);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Add Register T1


//test ADDS R2, R3, R4 given R3 = 3000 and R4 = 2000
void test_ADDRegisterToRegisterT1_given_0x191a_and_r3_is_3000_r4_is_2000_should_get_0x1388_at_r2_xPSR_unchanged(void)
{
  uint32_t instruction = 0x191a0000;
  
  coreReg[3] = 3000;
  coreReg[4] = 2000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x1388, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//testing flag change
//test ADDS R2, R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_ADDRegisterToRegisterT1_given_0x191a_and_r3_is_0xffffffff_r4_is_0x80000000_should_get_0x7fffffff_at_r2_OV_flag_set_C_flag_set(void)
{
  uint32_t instruction = 0x191a0000;
  
  coreReg[3] = 0xffffffff;
  coreReg[4] = 0x80000000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isOverflow() );
  TEST_ASSERT_EQUAL(1, isCarry() );
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Arithmetic Shift Right T1

// test ASRS  R1, R2, #2 given R2, #0xf0f0f0f0
void test_ASRImmediateT1_given_0x1091_should_arithmetic_shift_right_r2_2_times_and_write_to_R1_N_flag_is_set(void)
{
	uint32_t instruction = 0x10910000;
  
  coreReg[2] = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xfc3c3c3c, coreReg[1]);        //after arithmetic shift right 5 times, should get 0xfc3c3c3c
  TEST_ASSERT_EQUAL(0xf0f0f0f0, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isNegative() );

}


//boundary test , maximum shift
// test ASRS  R1, R2, #32 given R2, #0xf0f0f0f0
void test_ASRImmediateT1_given_0x1011_should_arithmetic_shift_right_r2_32_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10110000;
  
  coreReg[2] = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[1]);        //after arithmetic shift right 32 times, should get 0xffffffff
  TEST_ASSERT_EQUAL(1, isCarry() );
  TEST_ASSERT_EQUAL(1, isNegative() );
}



//boundary test , minimum shift
// test ASRS  R1, R2, #1 given R2, #0xf0f0f0f0
void test_ASRImmediateT1_given_0x1051_should_arithmetic_shift_right_r2_1_times_and_write_to_R1(void)
{
	uint32_t instruction = 0x10510000;
  
  coreReg[2] = 0xf0f0f0f0;                          //set R2 to be 0xf0f0f0f0
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xf8787878, coreReg[1]);        //after arithmetic shift right 1 times, should get 0xf8787878
  TEST_ASSERT_EQUAL(1, isNegative() );

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Compare Immediate T1
  

// test CMP r7, #200 given R7 = 200
void test_CMPImmediateT1_given_0x2fc8_should_compare_immediate_200_with_R7_and_set_carry_flag_and_zero_flag(void)
{
	uint32_t instruction = 0x2fc80000;
  
  coreReg[7] = 200;                          //set R7 to be 200
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(1, isZero() );
  TEST_ASSERT_EQUAL(1, isCarry() );

}

// test CMP r7, #20 given R7 = 0x200
void test_CMPImmediateT1_given_0x2f14_should_compare_immediate_20_with_R7_and_set_carry_flag(void)
{
	uint32_t instruction = 0x2f140000;
  coreReg[7] = 200;                          //set R7 to be 200
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(1, isCarry() );
}


// test CMP r7, #200 given R7 = 0x20
void test_CMPImmediateT1_given_0x2fc8_should_compare_immediate_20_with_R7_and_set_negative_flag(void)
{
	uint32_t instruction = 0x2fc80000;
  coreReg[7] = 20;                          //set R7 to be 20
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(1, isNegative() );
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Logical Shift Left T1
  
//test LSLS r2,r1,#2 given r1 = 0x01
void test_LSLImmediateT1_given_0x008A_should_shift_left_r1_2_times_and_write_to_R2_no_flag_set(void)
{
  uint32_t instruction = 0x008A0000;
  
  coreReg[1] = 1;                             //set R1 to be 1
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x01, coreReg[1]);        
  TEST_ASSERT_EQUAL(0x04, coreReg[2]);        //after shift 2 times, should get 0x04
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

//boundary test, minimum shift
//test LSLS r1,#0 given r1 = 0x01
void test_LSLImmediateT1_given_0x0009_should_shift_left_r1_2_times_and_write_to_R1_no_flag_set(void)
{
  uint32_t instruction = 0x00090000;
  
  coreReg[1] = 1;                             //set R1 to be 1
  ARMSimulator(instruction);
         
  TEST_ASSERT_EQUAL(0x01, coreReg[1]);        //will execute MOVRegisterT2
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//boundary test, maximum shift
//test LSLS r1,#31 given r1 = 0x01
void test_LSLImmediateT1_given_0x07C9_should_shift_left_r1_31_times_and_write_to_R1_negative_flag_set(void)
{
  uint32_t instruction = 0x07C90000;
  
  coreReg[1] = 1;                                   //set R1 to be 1
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x80000000, coreReg[1]);        //after shift 31 times, should get 0x80000000
  TEST_ASSERT_EQUAL(1, isNegative() );
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Logical Shift Right T1
  
//maximum shift
//test LSRS  R2 , #32 given R2 = 0xffffffff, maximum shift
void test_LSRImmediateT1_given_0x0812_should_shift_right_r2_32_times_and_write_to_R2_carryflag_set_zeroFlag_set(void)
{
  uint32_t instruction = 0x08120000;
  
  coreReg[2] = 0xffffffff;                    //set R2 to be 0xffffffff
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0x00, coreReg[2]);        //after shift right 32 times, should get 0x00
  TEST_ASSERT_EQUAL(1, isCarry());
  TEST_ASSERT_EQUAL(1, isZero());
}


//test LSRS  R1, R2 , #15 given R2 = 0xffffffff expect R1 = 0x0001ffff
void test_LSRImmediateT1_given_0x0bd1_should_shift_right_r2_15_times_and_write_to_R1_carryFlag_set(void)
{
  uint32_t instruction = 0x0bd10000;
  
  coreReg[2] = 0xffffffff;                          //set R2 to be 0xffffffff
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x0001ffff, coreReg[1]);        //after shift right 15 times, should get 0x0001ffff
  TEST_ASSERT_EQUAL(1, isCarry());
}

//minimum shift
//test LSRS  R1, R2 , #1 given R2 = 0xffffffff expect R1 = 0x0001ffff
void test_LSRImmediateT1_given_0x0851_should_shift_right_r2_1_times_and_write_to_R1_carryFlag_set(void)
{
  uint32_t instruction = 0x08510000;
  
  coreReg[2] = 0xffffffff;                          //set R2 to be 0xffffffff
  ARMSimulator(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[1]);        //after shift right 1 times, should get 0x7fffffff
  TEST_ASSERT_EQUAL(1 , isCarry() );
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Move Immediate T1
  
  
  //test MOVS R1, #0xFF
void test_MOVImmediateT1_given_instruction_0x21FF0000_should_move_0xFF_into_R1_all_flag_not_set(void)
{
  uint32_t instruction = 0x21ff0000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg[1]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


//test MOVS R7, #0x13
void test_MOVImmediateT1_given_instruction_0x27130000_should_move_0x13_into_R7_all_flag_not_set(void)
{
  uint32_t instruction = 0x27130000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x13, coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Subtract Immediate T1, T2

  
//boundary test, maximum immediate number allowed which is 7
//test SUBS R2, R3, #0x07 given R3 = 0x01
void test_SUBImmediateT1_given_0x1fda_and_r3_is_0x01_should_get_0xfffffffa_at_r2_N_flag_set(void)
{
  uint32_t instruction = 0x1fda0000;
  
  coreReg[3] = 0x01;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xfffffffa, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01, coreReg[3]);
  TEST_ASSERT_EQUAL(1,isNegative());
}


//boundary test, minimum immediate number allowed which is 0
//test SUBS R2, R3, #0 given R3 = 3000
void test_SUBImmediateT1_given_0x1e1a_and_r3_is_3000_should_get_3000_at_r2_C_flag_set(void)
{
  uint32_t instruction = 0x1e1a0000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(3000, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}


//test SUBS R3, #0x08 given R3 = 3000
void test_SUBImmediateT2_given_0x3b08_and_r3_is_3000_should_get_0xbb0_at_r3_C_flag_set(void)
{
  uint32_t instruction = 0x3b080000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xbb0, coreReg[3]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}


//boundary test, minimum immediate number allowed which is 0
//test SUBS R3, #0 given R3 = 3000
void test_SUBImmediateT2_given_0x3b00_and_r3_is_3000_should_get_3000_at_r3_C_flag_set(void)
{
  uint32_t instruction = 0x3b000000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(3000, coreReg[3]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}



//boundary test, maximum immediate number allowed which is 0xff
//test SUBS R3, #0xff given R3 = 3000
void test_SUBImmediateT2_given_0x3bff_and_r3_is_3000_should_get_0xab9_at_r3_C_flag_set(void)
{
  uint32_t instruction = 0x3bff0000;
  
  coreReg[3] = 3000;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xab9, coreReg[3]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Subtract Register T1

  
//test SUBS R2, R3, R4 given R3 = 3000 and R4 = 2000
void test_SUBRegisterToRegisterT1_given_0x1b1a_and_r3_is_3000_r4_is_2000_should_get_0x3e8_at_r2_C_flag_set(void)
{
  uint32_t instruction = 0x1b1a0000;
  
  coreReg[3] = 3000;
  coreReg[4] = 2000;
  SUBRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x3e8, coreReg[2]);
  TEST_ASSERT_EQUAL(1,isCarry());
}


//testing flag change
//test SUBS R2, R3, R4 given R3 = 0xffffffff and R4 = 0x80000000
void test_SUBRegisterToRegisterT1_given_0x1b1a_and_r3_is_0xffffffff_r4_is_0x80000000_should_get_0x1388_at_r2_OV_flag_set_C_flag_set(void)
{
  uint32_t instruction = 0x1b1a0000;
  
  coreReg[3] = 0xffffffff;
  coreReg[4] = 0x80000000;
  SUBRegisterToRegisterT1(instruction);
  
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[2]);
  TEST_ASSERT_EQUAL(1, isCarry() );
}



