#include "unity.h"
#include "VMOV.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "ErrorSignal.h"
#include "ModifiedImmediateConstant.h"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}


void test_VMOV_should_move_the_correct_value_into_s1_and_s2()
{
  writeToCoreRegisters(0, 0xe000ed88);
  writeToCoreRegisters(1, 0x00f00000);

  VMOV(0xec410a30);
  
  TEST_ASSERT_EQUAL(fpuDoublePrecision[0], 0xe000ed8800000000);
  TEST_ASSERT_EQUAL(fpuDoublePrecision[1], 0x0000000000f00000);
  TEST_ASSERT_EQUAL(fpuSinglePrecision[1], 0xe000ed88);
  TEST_ASSERT_EQUAL(fpuSinglePrecision[2], 0x00f00000);
}
