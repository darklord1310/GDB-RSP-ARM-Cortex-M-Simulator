#include "unity.h"
#include "ARMRegisters.h"
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initCoreRegister_will_create_CoreRegister(void)
{
  coreReg = initCoreRegister();
    
  TEST_ASSERT_NOT_NULL(coreReg);
  TEST_ASSERT_NOT_NULL(coreReg->reg);
    
  destroyCoreRegister(coreReg);
}

void test_write_8_into_R1_should_be_loaded_correctly()
{
  coreReg = initCoreRegister();
	
  coreReg->reg[1].data = 8;
	
	
  TEST_ASSERT_EQUAL(8, coreReg->reg[1].data);
	
  destroyCoreRegister(coreReg);
}
