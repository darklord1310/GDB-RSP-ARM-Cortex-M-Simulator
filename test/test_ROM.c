#include "unity.h"
#include "ROM.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void xtest_initROM_should_initialize_the_ROM_properly()
{
  ROM *rom = initROM();
  int i;

  TEST_ASSERT_NOT_NULL(rom);
  // TEST_ASSERT_NULL(rom->address);
  
  // resetROM();
  // for(i = 0 ; i < sizeOfROM ; i ++ )
  // {
      // TEST_ASSERT_NOT_NULL(rom->address[i].data);
    // TEST_ASSERT_EQUAL(0, rom->address[i].data);
  // }

  destroyROM(rom);

}


void test_resetROM_should_reset_all_the_ROM_data_to_0(void)
{
  int i;
  ROM *rom = initROM();
  /*
  //write some value into the ROM
  for(i = 0 ; i < sizeOfROM ; i ++ )
  {
    rom->address[i].data = 1234;
  }
  */

  resetROM();

  for(i = 0 ; i < 0xFFFFFFF ; i ++ )
  {
    TEST_ASSERT_EQUAL(0, address[i].data);
  }
}
