#include "unity.h"
#include <stdio.h>
#include <malloc.h>
#include "LoadElf.h"
// #include "ARMRegisters.h"
// #include "MemoryBlock.h"
#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Relocator.h"
#include "Read_File.h"
#include "elf.h"
#include "CException.h"
#include "ErrorCode.h"
// #include "getAndSetBits.h"
// #include "getMask.h"

extern ElfData *elfData;
extern ElfSection *isr, *text, *initArray, *rodata, *data, *finiArray;
extern uint32_t entryAddress;
extern int fileStatus;

void setUp(void)
{
}

void tearDown(void)
{
}

void xtest_loadElf(void)
{
	loadElf();
}

void test_mappingVirtAddress_given_sh_virtual_address_and_p_vaddr_should_return_the_correct_physical_address()
{
  uint32_t physAddr;
  loadElf();

  physAddr = mappingVirtAddress(isr->index);
  TEST_ASSERT_EQUAL(0x08000000, physAddr);
  printf(".isr_vector, lma 0x%x\n", physAddr);

  physAddr = mappingVirtAddress(text->index);
  TEST_ASSERT_EQUAL(0x080001b0, physAddr);
  printf(".text, lma 0x%x\n", physAddr);

  physAddr = mappingVirtAddress(rodata->index);
  TEST_ASSERT_EQUAL(0x8000788, physAddr);
  printf(".rodata, lma 0x%x\n", physAddr);

  physAddr = mappingVirtAddress(initArray->index);
  TEST_ASSERT_EQUAL(0x8000790, physAddr);
  printf(".init_array, lma 0x%x\n", physAddr);

  physAddr = mappingVirtAddress(finiArray->index);
  TEST_ASSERT_EQUAL(0x8000798, physAddr);
  printf(".fini_array, lma 0x%x\n", physAddr);

  physAddr = mappingVirtAddress(data->index);
  TEST_ASSERT_EQUAL(0x800079c, physAddr);
  printf(".data, lma 0x%x\n", physAddr);
}
