#include "unity.h"
#include "ADDImmediate.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ConditionalExecution.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
  initCoreRegister();
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
  ADDImmediateT1(instruction);
  
  TEST_ASSERT_EQUAL(0x08, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//boundary test, minimum immediate number allowed which is 0
//test ADDS R2, R3, #0x07 given R3 = 3000
void test_ADDImmediateT1_given_0x1dda_and_r3_is_3000_should_get_0x07_at_r2_xPSR_unchanged(void)
{
  uint32_t instruction = 0x1dda0000;
  
  coreReg[3] = 3000;
  ADDImmediateT1(instruction);
  
  TEST_ASSERT_EQUAL(0xbbf, coreReg[2]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//test ADDS R3, #0x08 given R3 = 3000
void test_ADDImmediateT2_given_0x3308_and_r3_is_3000_should_get_0xbc0_at_r3_xPSR_unchanged(void)
{
  uint32_t instruction = 0x33080000;
  
  coreReg[3] = 3000;
  ADDImmediateT2(instruction);
  
  TEST_ASSERT_EQUAL(0xbc0, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//boundary test, minimum immediate number allowed which is 0
//test ADDS R3, #0 given R3 = 3000
void test_ADDImmediateT2_given_0x3300_and_r3_is_3000_should_get_3000_at_r3_xPSR_unchanged(void)
{
  uint32_t instruction = 0x33000000;
  
  coreReg[3] = 3000;
  ADDImmediateT2(instruction);
  
  TEST_ASSERT_EQUAL(3000, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}

//boundary test, maximum immediate number allowed which is 0xff
//test ADDS R3, #0xff given R3 = 3000
void test_ADDImmediateT2_given_0x33ff_and_r3_is_3000_should_get_0xbc0_at_r3_xPSR_unchanged(void)
{
  uint32_t instruction = 0x33ff0000;
  
  coreReg[3] = 3000;
  ADDImmediateT2(instruction);
  
  TEST_ASSERT_EQUAL(0xcb7, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);

}