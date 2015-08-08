#include "unity.h"
#include "MemoryBlock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_resetMemoryBlock_should_reset_all_the_memory_data_to_0(void)
{
    int i;

    //write some value into the memory block
    memoryBlock[10000] = 0x57;

    resetMemoryBlock();

    for(i = 0; i < sizeof(memoryBlock); i++)
        TEST_ASSERT_EQUAL(0, memoryBlock[i]);
}

void test_virtualMemToPhysicalMem_given_0x8000000_should_convert_the_mem_addr_into_physical_mem_addr(void)
{
    int i;
    uint32_t phyMemAddr, virtMemAddr = 0x80009d7;

    phyMemAddr = virtualMemToPhysicalMem(virtMemAddr);

    TEST_ASSERT_EQUAL(0x109d7, phyMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x0_should_convert_the_mem_addr_into_physical_mem_addr(void)
{
    int i;
    uint32_t phyMemAddr, virtMemAddr = 0x0;

    phyMemAddr = virtualMemToPhysicalMem(virtMemAddr);

    TEST_ASSERT_EQUAL(0x0, phyMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x7ffffff_should_convert_the_mem_addr_into_physical_mem_addr(void)
{
    int i;
    uint32_t phyMemAddr, virtMemAddr = 0x7ffffff;

    phyMemAddr = virtualMemToPhysicalMem(virtMemAddr);

    TEST_ASSERT_EQUAL(0xffffffff, phyMemAddr);
}

void test_virtualMemToPhysicalMem_given_0x20001020_should_convert_the_mem_addr_into_physical_mem_addr(void)
{
    int i;
    uint32_t phyMemAddr, virtMemAddr = 0x20001020;

    phyMemAddr = virtualMemToPhysicalMem(virtMemAddr);

    TEST_ASSERT_EQUAL(0x1020 + RAM_BASE_ADDR, phyMemAddr);
}

void xtest_virtualMemToPhysicalMem_given_0x40001020_should_convert_the_mem_addr_into_physical_mem_addr(void)
{
    int i;
    uint32_t virtMemAddr, phyMemAddr = 0x40001020;

    virtMemAddr = virtualMemToPhysicalMem(phyMemAddr);

    TEST_ASSERT_EQUAL(0xffffffff, virtMemAddr);
}
