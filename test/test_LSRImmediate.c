#include "unity.h"
#include "LSRImmediate.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>

void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}

//maximum shift
//test LSRS  R2 , #32 given R2 = 0xffffffff, maximum shift
void test_LSRImmediateT1_given_0x0812_should_shift_right_r2_32_times_and_write_to_R2_carryflag_set_zeroFlag_set(void)
{
  uint32_t instruction = 0x08120000;
  
  coreReg[2] = 0xffffffff;                    //set R2 to be 0xffffffff
  LSRImmediateT1(instruction);
          
  TEST_ASSERT_EQUAL(0x00, coreReg[2]);        //after shift right 32 times, should get 0x00
  TEST_ASSERT_EQUAL(1, isCarry());
  TEST_ASSERT_EQUAL(1, isZero());

}


//test LSRS  R1, R2 , #15 given R2 = 0xffffffff expect R1 = 0x0001ffff
void test_LSRImmediateT1_given_0x0bd1_should_shift_right_r2_15_times_and_write_to_R1_carryFlag_set(void)
{
  uint32_t instruction = 0x0bd10000;
  
  coreReg[2] = 0xffffffff;                          //set R2 to be 0xffffffff
  LSRImmediateT1(instruction);
          
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
  LSRImmediateT1(instruction);
          
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[2]);    
  TEST_ASSERT_EQUAL(0x7fffffff, coreReg[1]);        //after shift right 1 times, should get 0x7fffffff
  TEST_ASSERT_EQUAL(1 , isCarry() );

}



