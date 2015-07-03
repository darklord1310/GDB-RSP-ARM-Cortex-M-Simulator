#include "unity.h"
#include "ThumbOpcode1011XX.h"

void setUp(void)
{
}

void tearDown(void)
{
}


// test ANDS R0, R1
void test_ANDRegisterT1_given_r0_0xf0_r1_0xff_should_get_r0_0xf0(void)
{
  uint32_t instruction = 0x40080000;
  
  coreReg[0] = 0xf0;
  coreReg[1] = 0xff;
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0xcb7, coreReg[3]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}