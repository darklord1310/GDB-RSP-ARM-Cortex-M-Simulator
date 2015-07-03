#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "Thumb16bitsTable.h"
#include "ADDImmediate.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "ModifiedImmediateConstant.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ARMSimulator.h"
#include "ITandHints.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


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