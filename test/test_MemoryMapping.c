#include "unity.h"
#include "MemoryMapping.h"
#include "GPIOs.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_memoryMap_given_startAddress_should_map_the_function_according_to_the_start_address(void)
{
	memoryMap(0x40020000, 0x400203FF - 0x40020000, initGPIOs);

  TEST_ASSERT_EQUAL_PTR(&initGPIOs, page[0]);
}
