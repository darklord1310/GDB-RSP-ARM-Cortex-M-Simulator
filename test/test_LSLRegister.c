#include "unity.h"
#include "LSLRegister.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>


void setUp(void)
{
  coreReg = initCoreRegister();
  initStatusRegister();
}

void tearDown(void)
{
}

//test LSLS r2,r1 given r2 = 0xffffffff and r1 = 0x0000ff0f 
void test_LSLRegisterToRegisterT1_given_0x408A_should_shift_left_r1_15_times_and_write_to_R2(void)
{
  uint32_t instruction = 0x408A0000;
  
  coreReg->reg[1].data = 0x0000ff0f;                          //set R1 to be 1
  coreReg->reg[2].data = 0xffffffff;                          //set R2 to be 0xffffffff
  LSLRegisterToRegisterT1(instruction);
  TEST_ASSERT_EQUAL(0xffff8000, coreReg->reg[2].data);        //after shift 15 times, should get 0xffff8000
 
  destroyCoreRegister(coreReg);
}
