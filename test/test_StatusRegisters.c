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


void test_updateStatusRegister_given_value_0_should_set_zero_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value = 0;
  updateStatusRegister(value);
  
  TEST_ASSERT_EQUAL( 1 , isZero() );
}


void test_updateStatusRegister_given_value_ngeative_1_should_set_negative_flag()
{
  initStatusRegister();                          //initialize all to 0
  TEST_ASSERT_EQUAL( 0 , StatusRegisters);
  
  uint32_t value = -1;
  updateStatusRegister(value);
  
  TEST_ASSERT_EQUAL( 1 , isNegative() );
}

