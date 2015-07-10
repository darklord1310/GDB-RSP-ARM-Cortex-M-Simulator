#include "unity.h"
#include "ARMRegisters.h"
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initCoreRegister_reset_the_coreReg_correctly(void)
{
  int i;
  initCoreRegister();
  
  for(i = 0; i < NUM_OF_CORE_Register; i++)
  {
    if(i < 16)
      TEST_ASSERT_EQUAL(0, coreReg[i]);
    else
      TEST_ASSERT_EQUAL(0x01000000, coreReg[i]);
  }
  
}

