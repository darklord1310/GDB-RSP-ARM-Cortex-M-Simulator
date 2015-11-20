#include "unity.h"
#include "ARMRegisters.h"
#include <stdint.h>
#include "LoadAndWriteMemory.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "MemoryBlock.h"

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
    if(i == SP)
      TEST_ASSERT_EQUAL(0x2001fffc, coreReg[i]);
    else if(i == LR)
      TEST_ASSERT_EQUAL(0xffffffff, coreReg[i]);
    else if(i == xPSR)
      TEST_ASSERT_EQUAL(0x01000000, coreReg[i]);
    else
      TEST_ASSERT_EQUAL(0x0, coreReg[i]);

  }

  for(i = 0; i < NUM_OF_FPUD_Register; i++)
  {
    TEST_ASSERT_EQUAL(0, fpuDoublePrecision[i]);
  }

  for(i = 0; i < NUM_OF_FPUS_Register; i++)
  {
    TEST_ASSERT_EQUAL(0, fpuSinglePrecision[i]);
  }
  
  TEST_ASSERT_EQUAL(0xC0000000, loadByteFromMemory(FPCCR, 4) );
  TEST_ASSERT_EQUAL(0x00000000, loadByteFromMemory(CPACR, 4) );
  TEST_ASSERT_EQUAL(0x00000000, loadByteFromMemory(FPDSCR, 4) );
  TEST_ASSERT_EQUAL(0xfa050000, loadByteFromMemory(AIRCR, 4) );
  TEST_ASSERT_EQUAL(0x00000200, loadByteFromMemory(CCR, 4) );
}


void test_writeSinglePrecision_should_write_value_into_fpuSinglePrecsion_correctly(void)
{
  int i;
  uint32_t valueToWrite = 0x00;
  initCoreRegister();

  for(i=0; i < NUM_OF_FPUS_Register; i++)
  {
    writeSinglePrecision(i, valueToWrite++);
  }

  valueToWrite = 0x00;

  for(i=0; i < NUM_OF_FPUS_Register; i++)
  {
    TEST_ASSERT_EQUAL(valueToWrite++, fpuSinglePrecision[i]);
  }
}



void test_writeSinglePrecision_should_write_value_into_fpuDoublePrecision_correctly(void)
{
  int i;
  uint32_t valueToWrite = 0x00;
  initCoreRegister();


  for(i=0; i < NUM_OF_FPUS_Register; i++)
  {
    writeSinglePrecision(i, valueToWrite++);
  }

  TEST_ASSERT_EQUAL( 0x0000000100000000, fpuDoublePrecision[0]);
  TEST_ASSERT_EQUAL( 0x0000000300000002, fpuDoublePrecision[1]);
  TEST_ASSERT_EQUAL( 0x0000000500000004, fpuDoublePrecision[2]);
  TEST_ASSERT_EQUAL( 0x0000000700000006, fpuDoublePrecision[3]);
  TEST_ASSERT_EQUAL( 0x0000000900000008, fpuDoublePrecision[4]);
  TEST_ASSERT_EQUAL( 0x0000000b0000000a, fpuDoublePrecision[5]);
  TEST_ASSERT_EQUAL( 0x0000000d0000000c, fpuDoublePrecision[6]);
  TEST_ASSERT_EQUAL( 0x0000000f0000000e, fpuDoublePrecision[7]);
  TEST_ASSERT_EQUAL( 0x0000001100000010, fpuDoublePrecision[8]);
  TEST_ASSERT_EQUAL( 0x0000001300000012, fpuDoublePrecision[9]);
  TEST_ASSERT_EQUAL( 0x0000001500000014, fpuDoublePrecision[10]);
  TEST_ASSERT_EQUAL( 0x0000001700000016, fpuDoublePrecision[11]);
  TEST_ASSERT_EQUAL( 0x0000001900000018, fpuDoublePrecision[12]);
  TEST_ASSERT_EQUAL( 0x0000001b0000001a, fpuDoublePrecision[13]);
  TEST_ASSERT_EQUAL( 0x0000001d0000001c, fpuDoublePrecision[14]);
  TEST_ASSERT_EQUAL( 0x0000001f0000001e, fpuDoublePrecision[15]);
}


void test_writeDoublePrecision_should_write_value_into_fpuDoublePrecsion_correctly(void)
{
  int i;
  uint32_t valueToWrite = 0x00;
  initCoreRegister();

  for(i=0; i < NUM_OF_FPUD_Register; i++)
  {
    writeDoublePrecision(i, valueToWrite++);
  }

  valueToWrite = 0x00;

  for(i=0; i < NUM_OF_FPUD_Register; i++)
  {
    TEST_ASSERT_EQUAL(valueToWrite++, fpuDoublePrecision[i]);
  }
}


void test_writeDoublePrecision_should_write_value_into_fpuSinglePrecision_correctly(void)
{
  int i;
  initCoreRegister();

  writeDoublePrecision(0,0x0000000100000000);
  writeDoublePrecision(1,0x0000000300000002);
  writeDoublePrecision(2,0x0000000500000004);
  writeDoublePrecision(3,0x0000000700000006);
  writeDoublePrecision(4,0x0000000900000008);
  writeDoublePrecision(5,0x0000000b0000000a);
  writeDoublePrecision(6,0x0000000d0000000c);
  writeDoublePrecision(7,0x0000000f0000000e);
  writeDoublePrecision(8,0x0000001100000010);
  writeDoublePrecision(9,0x0000001300000012);
  writeDoublePrecision(10,0x0000001500000014);
  writeDoublePrecision(11,0x0000001700000016);
  writeDoublePrecision(12,0x0000001900000018);
  writeDoublePrecision(13,0x0000001b0000001a);
  writeDoublePrecision(14,0x0000001d0000001c);
  writeDoublePrecision(15,0x0000001f0000001e);

  uint32_t valueToWrite = 0x00;
  for(i=0; i < NUM_OF_FPUS_Register; i++)
  {
    TEST_ASSERT_EQUAL(valueToWrite++, fpuSinglePrecision[i]);
  }
}

