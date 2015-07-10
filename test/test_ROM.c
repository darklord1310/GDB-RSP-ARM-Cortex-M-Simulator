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
        rom->address[i].data = 0x1234;
    }

    resetROM();

    for(i = 0 ; i < TWO_HUND_FIFTY_SIX_KB * 2 ; i ++ )
    {
        TEST_ASSERT_EQUAL(0, rom->address[i].data);
    }

    destroyROM();
}

void test_virtualMemToPhysicalMem_given_0x8000000_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x8000000;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);

    TEST_ASSERT_EQUAL(0x10000, virtMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x0_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x0;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);

    TEST_ASSERT_EQUAL(0x0, virtMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x80009d6_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x80009d6;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);

    TEST_ASSERT_EQUAL(0x109d6, virtMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x20001020_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x20001020;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);

    TEST_ASSERT_EQUAL(0x1020 + RAM_BASE_ADDR, virtMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x40001020_should_convert_the_mem_addr_into_virtual_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x40001020;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);

    TEST_ASSERT_EQUAL(0x800000, virtMemAddr);
}