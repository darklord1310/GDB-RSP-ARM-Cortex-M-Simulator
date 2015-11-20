#include "unity.h"
#include <stdio.h>
#include <malloc.h>
#include "LoadElf.h"
#include "ARMRegisters.h"
#include "mock_MemoryBlock.h"
#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Relocator.h"
#include "Read_File.h"
#include "elf.h"
#include "CException.h"
#include "ErrorCode.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "LoadAndWriteMemory.h"

#define ELF_FILE          "TestElfFile.elf"

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

/* ELF file contain this configuration
Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .isr_vector       PROGBITS        08000000 008000 0001ac 00   A  0   0  1
  [ 2] .text             PROGBITS        080001b0 0081b0 00061c 00  AX  0   0  8
  [ 3] .rodata           PROGBITS        080007cc 0087cc 000008 00   A  0   0  4
  [ 4] .init_array       INIT_ARRAY      080007d4 0087d4 000008 00  WA  0   0  4
  [ 5] .fini_array       FINI_ARRAY      080007dc 0087dc 000004 00  WA  0   0  4
  [ 6] .data             PROGBITS        20000000 010000 000428 00  WA  0   0  8
  [ 7] .ccmram           PROGBITS        10000000 010428 000000 00   W  0   0  1
  [ 8] .bss              NOBITS          20000428 010428 00001c 00  WA  0   0  4
  [ 9] ._user_heap_stack NOBITS          20000444 010428 000600 00  WA  0   0  1
  [10] .ARM.attributes   ARM_ATTRIBUTES  00000000 010428 00002a 00      0   0  1
  [11] .debug_line       PROGBITS        00000000 010452 0000ab 00      0   0  1
  [12] .debug_info       PROGBITS        00000000 0104fd 0000dc 00      0   0  1
  [13] .debug_abbrev     PROGBITS        00000000 0105d9 000067 00      0   0  1
  [14] .debug_aranges    PROGBITS        00000000 010640 000048 00      0   0  8
  [15] .debug_ranges     PROGBITS        00000000 010688 000020 00      0   0  8
  [16] .debug_str        PROGBITS        00000000 0106a8 0000c1 01  MS  0   0  1
  [17] .comment          PROGBITS        00000000 010769 000070 01  MS  0   0  1
  [18] .debug_frame      PROGBITS        00000000 0107dc 000034 00      0   0  4
  [19] .shstrtab         STRTAB          00000000 010810 0000e6 00      0   0  1
  [20] .symtab           SYMTAB          00000000 010c68 000dd0 10     21  91  4
  [21] .strtab           STRTAB          00000000 011a38 000be3 00      0   0  1

Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x008000 0x08000000 0x08000000 0x007e0 0x007e0 RWE 0x8000
  LOAD           0x010000 0x20000000 0x080007e0 0x00428 0x00428 RW  0x8000
  LOAD           0x010428 0x20000428 0x20000428 0x00000 0x0061c RW  0x8000

 Section to Segment mapping:
  Segment Sections...
   00     .isr_vector .text .rodata .init_array .fini_array
   01     .data
   02     .ccmram .bss ._user_heap_stack

*/
void test_getSectionLma_given_elfData_should_return_the_load_memory_address()
{
  uint32_t physAddr;
  elfData = openElfFile(ELF_FILE);

  physAddr = getSectionLma(elfData, 0);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 1);
  TEST_ASSERT_EQUAL(0x08000000, physAddr);

  physAddr = getSectionLma(elfData, 2);
  TEST_ASSERT_EQUAL(0x080001b0, physAddr);

  physAddr = getSectionLma(elfData, 3);
  TEST_ASSERT_EQUAL(0x80007cc, physAddr);

  physAddr = getSectionLma(elfData, 4);
  TEST_ASSERT_EQUAL(0x80007d4, physAddr);

  physAddr = getSectionLma(elfData, 5);
  TEST_ASSERT_EQUAL(0x80007dc, physAddr);

  physAddr = getSectionLma(elfData, 6);
  TEST_ASSERT_EQUAL(0x80007e0, physAddr);

  physAddr = getSectionLma(elfData, 7);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 8);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 9);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 10);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 11);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 12);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 12);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 14);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 15);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 16);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 17);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 18);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 19);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 20);
  TEST_ASSERT_EQUAL(-1, physAddr);

  physAddr = getSectionLma(elfData, 21);
  TEST_ASSERT_EQUAL(-1, physAddr);

  closeElfData(elfData);
}

void test_isWithinRange_given_start_addr_size_and_should_return_1_if_its_within_range()
{
  int size = 2048 * 1024;   //2048k
  getElfSection(ELF_FILE);

  TEST_ASSERT_EQUAL(1, isWithinRange(0x08000000, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(0x07ffffff + size, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(0x080008fe, 0x08000000, size));

  closeElfFile();
}

void test_isWithinRange_given_start_addr_and_size_should_return_0_if_its_not_within_range()
{
  int size = 2048 * 1024;   //2048k

  TEST_ASSERT_EQUAL(0, isWithinRange(0x07ffffff, 0x08000000, size));
  TEST_ASSERT_EQUAL(0, isWithinRange(0x08000000 + size, 0x08000000, size));
}

void test_isProgramLoadType_given_program_type_should_return_1()
{
  elfData = openElfFile(ELF_FILE);

  TEST_ASSERT_EQUAL(1, isProgramLoadType(elfData, 0));

  closeElfData(elfData);
}

void test_isProgramLoadType_given_program_type_other_than_PT_LOAD_should_return_0()
{
  elfData = openElfFile(ELF_FILE);
  elfData->ph[0].p_type = PT_DYNAMIC;

  TEST_ASSERT_EQUAL(0, isProgramLoadType(elfData, 0));

  closeElfData(elfData);
}

void test_loadElf()
{
  getElfSection(ELF_FILE);

  simulatorCopyBlock_Expect(0x08000000, isr->dataAddress, isr->size);
  simulatorCopyBlock_Expect(0x080001b0, text->dataAddress, text->size);
  simulatorCopyBlock_Expect(0x080007cc, rodata->dataAddress, rodata->size);
  simulatorCopyBlock_Expect(0x080007d4, initArray->dataAddress, initArray->size);
  simulatorCopyBlock_Expect(0x080007dc, finiArray->dataAddress, finiArray->size);
  simulatorCopyBlock_Expect(0x080007e0, data->dataAddress, data->size);

  loadElf(elfData, 0x8000000, 2048*1024);

  TEST_ASSERT_EQUAL(0x8000760, coreReg[PC]);

  closeElfFile();
}