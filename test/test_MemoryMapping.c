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
  initDirectory();
  
  for(i = 0; i < DIR_SIZE; i++)
  {
    TEST_ASSERT_EQUAL(0, directory[i]);
  }
}

void test_mapPageToDirectory_given_startAddress_0x20000000_range_3_should_point_0x200_and_0x203_to_page()
{
  uint32_t startAddress = 0x20000000;
  uint32_t range = 3;
  
  mapPageToDirectory(directory, startAddress, range);
  
  int i;
  for(i = 0x200; i < 0x203; i++)
  {
    TEST_ASSERT_NOT_NULL(directory[i]);
  }
  printf("%p\n", directory[0x200]);
  printf("%p\n", directory[0x201]);
  printf("%p\n", directory[0x202]);
}


void test_mapHandlerToPage_given_startAddress_0x20000000_range_3_should_point_0x200_and_0x203_to_page()
{
  uint32_t startAddress = 0x20000000;
  uint32_t range = 3;
  
  //mapPageToDirectory(directory, startAddress, range);
  //mapHandlerToPage(directory[0x200], memoryHandler, 0x00, range);

  //printf("%i\n", (*(*directory[0x20000000]))(0x20000000,0,0,0) );
  // int i;
  // for(i = 0x0; i < 0x3; i++)
  // {
    // TEST_ASSERT_NOT_NULL(page[i]);
  // }
}



// void test_initPage_should_initialize_1kb_page_to_zero(void)
// {
  // int i;

  // for(i = 0; i < PAGE_SIZE; i++)
  // {
    // TEST_ASSERT_EQUAL(0, page[i]);
  // }
// }

// void test_initOffset_should_initialize_1kb_offset_to_zero(void)
// {
  // int i;

  // for(i = 0; i < OFFSET_SIZE; i++)
  // {
    // TEST_ASSERT_EQUAL(0, offset[i]);
  // }
// }

