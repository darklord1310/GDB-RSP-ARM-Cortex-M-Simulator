#include "unity.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdbool.h>
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initStatusRegister_should_set_StatusRegisters_to_be_0(void)
{
  initStatusRegister();
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
}


void test_setNegativeFlag_StatusRegisters_should_get_0x80000000(void)
{
  initStatusRegister();                             //initialize all to 0
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setNegativeFlag();                                //set NEGATIVE flag
  
  TEST_ASSERT_EQUAL( 0x80000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isNegative() );

}



void test_setCarryFlag_StatusRegisters_should_get_0x20000000(void)
{
  initStatusRegister();                           //initialize all to 0

  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setCarryFlag();                                //set CARRY flag
  
  TEST_ASSERT_EQUAL( 0x20000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isCarry() );

}



void test_setOverflowFlag_StatusRegisters_should_get_0x10000000(void)
{
  initStatusRegister();                             //initialize all to 0

  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setOverflowFlag();                                //set OVERFLOW flag
  
  TEST_ASSERT_EQUAL( 0x10000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isOverflow() );

}



void test_setZeroFlag_StatusRegisters_should_get_0x40000000(void)
{
  initStatusRegister();                          //initialize all to 0
  int flag;
  
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  setZeroFlag();                                //set ZERO flag
  
  TEST_ASSERT_EQUAL( 0x40000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isZero() );

}


void test_updateZeroFlag_given_value_0_should_set_zero_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value = 0;
  updateZeroFlag(value);
  
  TEST_ASSERT_EQUAL( 1 , isZero() );
}


void test_updateNegativeFlag_given_value_negative_1_should_set_negative_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value = -1;
  updateNegativeFlag(value);
  
  TEST_ASSERT_EQUAL( 1 , isNegative() );
}


void test_updateCarryFlag_given_value1_0xffffffff_and_value2_0x01_should_set_carry_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value1 = 0xffffffff;
  uint32_t value2 = 0x01;
  updateCarryFlag(value1,value2);
  
  TEST_ASSERT_EQUAL( 1 , isCarry() );
}


void test_updateCarryFlag_given_value1_0x0fffffff_and_value2_0x01_should_not_set_carry_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value1 = 0x0fffffff;
  uint32_t value2 = 0x01;
  updateCarryFlag(value1,value2);
  
  TEST_ASSERT_EQUAL( 0 , isCarry() );
}


void test_updateOverflowFlag_given_value1_0x10000000_and_value2_0x10000000_sum_0x00_should_set_overflow_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value1 = 0x80000000;
  uint32_t value2 = 0x80000000;
  uint32_t sum = 0x0;
  updateOverflowFlag(value1,value2,sum);
  
  TEST_ASSERT_EQUAL( 1 , isOverflow() );
}


