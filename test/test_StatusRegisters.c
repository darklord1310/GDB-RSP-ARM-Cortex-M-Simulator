#include "unity.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdbool.h>
#include <stdint.h>

void setUp(void)
{
  initStatusRegister();                          //initialize the status register
}

void tearDown(void)
{
}

void test_initStatusRegister_should_set_StatusRegisters_to_be_0x01000000(void)
{
  initStatusRegister();
  
  TEST_ASSERT_EQUAL( 0x01000000 , StatusRegisters);
}


void test_setNegativeFlag_StatusRegisters_should_get_0x81000000(void)
{  
  setNegativeFlag();                                //set NEGATIVE flag
  
  TEST_ASSERT_EQUAL( 0x81000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isNegative() );

}



void test_setCarryFlag_StatusRegisters_should_get_0x21000000(void)
{
  setCarryFlag();                                //set CARRY flag
  
  TEST_ASSERT_EQUAL( 0x21000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isCarry() );

}



void test_setOverflowFlag_StatusRegisters_should_get_0x11000000(void)
{
  setOverflowFlag();                                //set OVERFLOW flag
  
  TEST_ASSERT_EQUAL( 0x11000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isOverflow() );

}



void test_setZeroFlag_StatusRegisters_should_get_0x41000000(void)
{
  setZeroFlag();                                //set ZERO flag
  
  TEST_ASSERT_EQUAL( 0x41000000 , StatusRegisters);
  TEST_ASSERT_EQUAL( 1 , isZero() );

}


void test_resetZeroFlag_should_set_the_zero_flag_to_0()
{
  setZeroFlag();
  TEST_ASSERT_EQUAL( 1 , isZero() );
  resetZeroFlag();
  TEST_ASSERT_EQUAL( 0 , isZero() );
}

void test_resetNegativeFlag_should_set_the_negative_flag_to_0()
{
  setNegativeFlag();
  TEST_ASSERT_EQUAL( 1 , isNegative() );
  resetNegativeFlag();
  TEST_ASSERT_EQUAL( 0 , isNegative() );
}

void test_resetOverflowFlag_should_set_the_overflow_flag_to_0()
{
  setOverflowFlag();
  TEST_ASSERT_EQUAL( 1 , isOverflow() );
  resetOverflowFlag();
  TEST_ASSERT_EQUAL( 0 , isOverflow() );
}

void test_resetCarryFlag_should_set_the_carry_flag_to_0()
{
  setCarryFlag();
  TEST_ASSERT_EQUAL( 1 , isCarry() );
  resetCarryFlag();
  TEST_ASSERT_EQUAL( 0 , isCarry() );
}

void test_updateZeroFlag_given_value_0_should_set_zero_flag()
{
  uint32_t value = 0;
  updateZeroFlag(value);
  
  TEST_ASSERT_EQUAL( 1 , isZero() );
}


void test_updateNegativeFlag_given_value_negative_18000_should_set_negative_flag()
{  
  uint32_t value = -18000;
  updateNegativeFlag(value);
  
  TEST_ASSERT_EQUAL( 1 , isNegative() );
}


void test_updateCarryFlagAddition_given_value1_0xffffffff_and_value2_0x01_should_set_carry_flag()
{
  uint32_t value1 = 0xffffffff;
  uint32_t value2 = 0x01;
  updateCarryFlagAddition(value1,value2);
  
  TEST_ASSERT_EQUAL( 1 , isCarry() );
}


void test_updateCarryFlagAddition_given_value1_0x0fffffff_and_value2_0x01_should_not_set_carry_flag()
{
  
  uint32_t value1 = 0x0fffffff;
  uint32_t value2 = 0x01;
  updateCarryFlagAddition(value1,value2);
  
  TEST_ASSERT_EQUAL( 0 , isCarry() );
}


void test_updateCarryFlagSubtraction_given_value1_0x0fffffff_and_value2_0x01_should_set_carry_flag()
{
  
  uint32_t value1 = 0x0fffffff;
  uint32_t value2 = 0x01;
  updateCarryFlagSubtraction(value1,value2);
  
  TEST_ASSERT_EQUAL( 1 , isCarry() );
}


void test_updateCarryFlagSubtraction_given_value1_0x01_and_value2_0x0fffffff_should_not_set_carry_flag()
{
  
  uint32_t value1 = 0x01;
  uint32_t value2 = 0x0fffffff;
  updateCarryFlagSubtraction(value1,value2);
  
  TEST_ASSERT_EQUAL( 0 , isCarry() );
}


void test_updateOverflowFlagAddition_given_value1_0x80000000_and_value2_0x80000000_should_set_overflow_flag()
{
  uint32_t value1 = 0x80000000;
  uint32_t value2 = 0x80000000;
  uint32_t sum = value1 + value2;

  updateOverflowFlagAddition(value1,value2,sum);

  TEST_ASSERT_EQUAL( 1 , isOverflow() );
}


void test_updateOverflowFlagAddition_given_value1_0x40000000_and_value2_0x40000000_should_set_overflow_flag()
{
  uint32_t value1 = 0x40000000;
  uint32_t value2 = 0x40000000;
  uint32_t sum = value1 + value2;

  updateOverflowFlagAddition(value1,value2,sum);

  TEST_ASSERT_EQUAL( 1 , isOverflow() );
}


void test_updateOverflowFlagSubtraction_given_value1_0x40000000_and_value2_0x80000000_should_set_overflow_flag()
{
  uint32_t value1 = 0x40000000;
  uint32_t value2 = 0x80000000;
  uint32_t sum = value1 - value2;

  updateOverflowFlagSubtraction(value1,value2,sum);

  TEST_ASSERT_EQUAL( 1 , isOverflow() );
}


void test_updateOverflowFlagSubtraction_given_value1_0x80000000_and_value2_0x40000000_should_set_overflow_flag()
{
  uint32_t value1 = 0x80000000;
  uint32_t value2 = 0x40000000;
  uint32_t sum = value1 - value2;

  updateOverflowFlagSubtraction(value1,value2,sum);

  TEST_ASSERT_EQUAL( 1 , isOverflow() );
}

void test_inITBlock_given_statusRegister_0x05001800_should_return_1()
{
  StatusRegisters = 0x05001800;
  int result = inITBlock();
  
  TEST_ASSERT_EQUAL(1, result);
}

void test_inITBlock_given_statusRegister_0xa1000000_should_return_0()
{
  StatusRegisters = 0xa1000000;
  int result = inITBlock();
  
  TEST_ASSERT_EQUAL(0, result);
}
