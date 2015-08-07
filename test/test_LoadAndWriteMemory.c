#include "unity.h"
#include "LoadAndWriteMemory.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"


void setUp(void)
{
}

void tearDown(void)
{
}


/*
 * Expected : 0x08000000 = 0x22
 * 
 * 
 */
void test_writeByteToMemory_given_value_0x88ff4422_and_address_0x08000000_size_1_should_get_the_expected_result(void)
{
  uint32_t value = 0x88ff4422;
  uint32_t address = 0x08000000;
  
  writeByteToMemory(address, value, 1);
  
  TEST_ASSERT_EQUAL( 0x22 , memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  
}



/*
 * Expected : 0x08000000 = 0x22
 *            0x08000001 = 0x44
 *            
 */
void test_writeByteToMemory_given_value_0x88ff4422_and_address_0x08000000_size_2_should_get_the_expected_result(void)
{
  uint32_t value = 0x88ff4422;
  uint32_t address = 0x08000000;
  
  writeByteToMemory(address, value, 2);
  
  TEST_ASSERT_EQUAL( 0x22 , memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  TEST_ASSERT_EQUAL( 0x44 , memoryBlock[ virtualMemToPhysicalMem(0x08000001) ]);
}



/*
 * Expected : 0x08000000 = 0x22
 *            0x08000001 = 0x44
 *            0x08000002 = 0xff
 *            0x08000003 = 0x88
 */
void test_writeByteToMemory_given_value_0x88ff4422_and_address_0x08000000_size_4_should_get_the_expected_result(void)
{
  uint32_t value = 0x88ff4422;
  uint32_t address = 0x08000000;
  
  writeByteToMemory(address, value, 4);
  
  TEST_ASSERT_EQUAL( 0x22 , memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  TEST_ASSERT_EQUAL( 0x44 , memoryBlock[ virtualMemToPhysicalMem(0x08000001) ]);
  TEST_ASSERT_EQUAL( 0xff , memoryBlock[ virtualMemToPhysicalMem(0x08000002) ]);
  TEST_ASSERT_EQUAL( 0x88 , memoryBlock[ virtualMemToPhysicalMem(0x08000003) ]);
}



/*
 * Expected : data = 0x22
 * 
 * 
 */
void test_loadByteFromMemory_given_value_0x22_at_address_0x08000000_size_1_should_get_the_expected_result(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x22;
  uint32_t address = 0x08000000;
  
  uint32_t data = loadByteFromMemory(address, 1);
  
  TEST_ASSERT_EQUAL( 0x22 , data);
  
}


/*
 * Expected : data = 0x4422
 * 
 * 
 */
void test_loadByteFromMemory_value_given_below_and_size_2_should_get_the_expected_result(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x44;
  
  uint32_t address = 0x08000000;
  
  uint32_t data = loadByteFromMemory(address, 2);
  
  TEST_ASSERT_EQUAL( 0x4422 , data);
}


/*
 * Expected : data = 0x88ff4422
 * 
 * 
 */
void test_loadByteFromMemory_value_given_below_and_size_4_should_get_the_expected_result(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x88;
  
  uint32_t address = 0x08000000;
  
  uint32_t data = loadByteFromMemory(address, 4);

  TEST_ASSERT_EQUAL( 0x88ff4422 , data);
}