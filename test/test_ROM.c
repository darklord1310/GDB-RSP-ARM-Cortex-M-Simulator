#include "unity.h"
#include "ROM.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_initROM_should_initialize_the_ROM_properly()
{
  rom = initROM();
  
  TEST_ASSERT_NOT_NULL(rom);
  TEST_ASSERT_NOT_NULL(rom->address);
  
  destroyROM(rom); 
    
}


void test_resetROM_should_reset_all_the_ROM_data_to_0(void)
{
  int i;
  rom = initROM();
  /*
  //write some value into the ROM
  for(i = 0 ; i < sizeOfROM ; i ++ )
  {
    rom->address[i].data = 1234;
  }
  */

	//resetROM();
  /*
  for(i = 0 ; i < sizeOfROM ; i ++ )
  {
    TEST_ASSERT_EQUAL(0,rom->address[i].data);
  }
  */
}
