#include "unity.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdbool.h>
#include <stdint.h>
#include "MemoryBlock.h"
#include "ErrorSignal.h"
#include "ExceptionObject.h"
#include "LoadAndWriteMemory.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "NOP.h"

void setUp(void)
{
  initCoreRegister();                          //initialize the status register
}

void tearDown(void)
{
}


void test_setNegativeFlag_xPSR_should_get_0x81000000(void)
{
  setNegativeFlag();                                //set NEGATIVE flag

  TEST_ASSERT_EQUAL( 0x81000000 , coreReg[xPSR]);
  TEST_ASSERT_EQUAL( 1 , isNegative() );

}


void test_setCarryFlag_xPSR_should_get_0x21000000(void)
{
  setCarryFlag();                                //set CARRY flag

  TEST_ASSERT_EQUAL( 0x21000000 , coreReg[xPSR]);
  TEST_ASSERT_EQUAL( 1 , isCarry() );

}



void test_setOverflowFlag_xPSR_should_get_0x11000000(void)
{
  setOverflowFlag();                                //set OVERFLOW flag

  TEST_ASSERT_EQUAL( 0x11000000 , coreReg[xPSR]);
  TEST_ASSERT_EQUAL( 1 , isOverflow() );

}



void test_setZeroFlag_xPSR_should_get_0x41000000(void)
{
  setZeroFlag();                                //set ZERO flag

  TEST_ASSERT_EQUAL( 0x41000000 , coreReg[xPSR]);
  TEST_ASSERT_EQUAL( 1 , isZero() );

}


void test_setQFlag_xPSR_should_get_0x09000000(void)
{
  setQFlag();                                //set Q flag

  TEST_ASSERT_EQUAL( 0x09000000 , coreReg[xPSR]);
  TEST_ASSERT_EQUAL( 1 , isQSet() );

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

void test_updateCarryFlagAddition_given_value1_0x80000000_and_value2_0x80000000_should_set_carry_flag()
{
  uint32_t value1 = 0x80000000;
  uint32_t value2 = 0x80000000;
  updateCarryFlagAddition(value1,value2);

  TEST_ASSERT_EQUAL( 1 , isCarry() );
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


void test_updateCarryFlagSubtraction_given_value1_3_and_value2_1_should_set_carry_flag()
{
  uint32_t value1 = 3;
  uint32_t value2 = 2;
  updateCarryFlagSubtraction(value1,value2);

  TEST_ASSERT_EQUAL( 1 , isCarry() );
}


void test_updateCarryFlagSubtraction_given_value1_3_and_value2_3_should_set_carry_flag()
{
  uint32_t value1 = 3;
  uint32_t value2 = 3;
  updateCarryFlagSubtraction(value1,value2);

  TEST_ASSERT_EQUAL( 1 , isCarry() );
}

void test_updateCarryFlagSubtraction_given_value1_1_and_value2_3_should_not_set_carry_flag()
{
  uint32_t value1 = 1;
  uint32_t value2 = 3;
  updateCarryFlagSubtraction(value1,value2);

  TEST_ASSERT_EQUAL(0 , isCarry() );
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


//ITT    EQ
void test_inITBlock_given_xPSR_0x01000400_should_return_1()
{
  coreReg[xPSR] = 0x01000400;
  int result = inITBlock();

  TEST_ASSERT_EQUAL(1, result);
}


//ITT    NE
void test_inITBlock_given_xPSR_0x05001800_should_return_1()
{
  coreReg[xPSR] = 0x05001800;
  int result = inITBlock();

  TEST_ASSERT_EQUAL(1, result);
}

//no IT block
void test_inITBlock_given_xPSR_0xa1000000_should_return_0()
{
  coreReg[xPSR] = 0xa1000000;
  int result = inITBlock();

  TEST_ASSERT_EQUAL(0, result);
}

//ITT    EQ
void test_getITCond_given_xPSR_0xbf010000_should_return_0000()
{
  ITandHints(0xbf010000);
  uint32_t result =  getITCond();

  TEST_ASSERT_EQUAL(0b0000, result);
}

//ITT    NE
void test_getITCond_given_xPSR_0xbf110000_should_return_0001()
{
  ITandHints(0xbf110000);
  uint32_t result =  getITCond();

  TEST_ASSERT_EQUAL(0b0001, result);
}


//ITT    LE
void test_getITCond_given_xPSR_0xbfd10000_should_return_1101()
{
  ITandHints(0xbfd10000);
  uint32_t result =  getITCond();

  TEST_ASSERT_EQUAL(0b1101, result);
}


//testing shift 1 time
void test_shiftITState_given_xPSR_0x07001000_shift_1_times_should_get_0x05000400()
{
  ITandHints(0xbf130000);

  //shift 1 time
  shiftITState();
  TEST_ASSERT_EQUAL(0x05000400, coreReg[xPSR]);
}


//testing shift 2 time
void test_shiftITState_given_xPSR_0x03001000_shift_2_times_should_get_0x01000c00()
{
  ITandHints(0xbf130000);

  //shift 2 times
  shiftITState();
  shiftITState();

  TEST_ASSERT_EQUAL(0x01000c00, coreReg[xPSR]);
}


//testing shift 3 time
void test_shiftITState_given_xPSR_0x03001000_shift_3_times_should_get_0x01001800()
{
  ITandHints(0xbf130000);

  //shift 2 times
  shiftITState();
  shiftITState();
  shiftITState();

  TEST_ASSERT_EQUAL(0x01001800, coreReg[xPSR]);
}


//testing shift 4 time , should expect 0x01000000
void test_shiftITState_given_xPSR_0x03001000_shift_4_times_should_get_0x01000000()
{
  ITandHints(0xbf130000);

  //shift 2 times
  shiftITState();
  shiftITState();
  shiftITState();
  shiftITState();

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


void test_updateQFlag_given_signedRange_is_0x8000_sign_is_1_and_value_is_0x8000_should_set_Q_flag()
{
  int value = 0x8000;
  int sign = 1;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x09000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_1_and_value_is_0xfffe0000_should_set_Q_flag()
{
  int value = 0xfffe0000;
  int sign = 1;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x09000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_1_and_value_is_0x7fff_should_not_set_Q_flag()
{
  int value = 0x7fff;
  int sign = 1;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_1_and_value_is_0xffff8000_should_not_set_Q_flag()
{
  int value = 0xffff8000;
  int sign = 1;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_0_and_value_is_0x8000_should_set_Q_flag()
{
  int value = 0x8000;
  int sign = 0;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x09000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_0_and_value_is_0xfffe0000_should_set_Q_flag()
{
  int value = 0xfffe0000;
  int sign = 0;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x09000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_0_and_value_is_0x7fff_should_not_set_Q_flag()
{
  int value = 0x7fff;
  int sign = 0;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

void test_updateQFlag_given_signedRange_is_0x7fff_sign_is_0_and_value_is_0xffff8000_should_not_set_Q_flag()
{
  int value = 0;
  int sign = 0;

  updateQFlag(0x7fff, 0xffff8000, value, sign);     // 2^16

  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}

