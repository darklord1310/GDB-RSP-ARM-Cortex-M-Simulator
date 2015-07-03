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
    createROM();
    int i;

    TEST_ASSERT_NOT_NULL(rom);
    TEST_ASSERT_NOT_NULL(rom->address);

    destroyROM();
}


void test_resetROM_should_reset_all_the_ROM_data_to_0(void)
{
    int i;
    createROM();

    //write some value into the ROM
    for(i = 0; i < TWO_HUND_FIFTY_SIX_KB * 2; i ++ )
    {
        rom->address[i].data = 1234;
    }

    resetROM();

    for(i = 0 ; i < TWO_HUND_FIFTY_SIX_KB * 2 ; i ++ )
    {
        TEST_ASSERT_EQUAL(0, rom->address[i].data);
    }

    destroyROM();
}
