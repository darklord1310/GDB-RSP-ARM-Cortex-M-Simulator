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