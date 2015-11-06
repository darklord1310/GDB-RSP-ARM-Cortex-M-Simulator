#include "unity.h"
#include "MemoryMapping.h"
#include "GPIOs.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initDirectory_should_initialize_4kb_directory_to_zero(void)
{
  int i;

  for(i = 0; i < DIR_SIZE; i++)
  {
    TEST_ASSERT_EQUAL(0, directory[i]);
  }
}

void test_initPage_should_initialize_1kb_page_to_zero(void)
{
  int i;

  for(i = 0; i < PAGE_SIZE; i++)
  {
    TEST_ASSERT_EQUAL(0, page[i]);
  }
}

void test_initOffset_should_initialize_1kb_offset_to_zero(void)
{
  int i;

  for(i = 0; i < OFFSET_SIZE; i++)
  {
    TEST_ASSERT_EQUAL(0, offset[i]);
  }
}

void test_memoryMap_given_startAddress_and_a_function_should_map_the_function_according_to_the_start_address(void)
{
	memoryMap(0x40020000, 0x400203FF - 0x40020000, initGPIOs);

  TEST_ASSERT_EQUAL_PTR(page, directory[0x400]);
  TEST_ASSERT_EQUAL_PTR(&initGPIOs, page[0x200]);
  TEST_ASSERT_EQUAL_PTR(&initGPIOs, directory[0x400]);
}

void test_memoryMap_given_startAddress_and_no_function_should_map_the_virtual_addr_to_the_physical_address(void)
{
  
	memoryMap(0x40020000, 0x400203FF - 0x40020000, NULL);

  TEST_ASSERT_EQUAL_PTR(page, directory[0x400]);
  TEST_ASSERT_EQUAL_PTR(offset, page[0x200]);
}
