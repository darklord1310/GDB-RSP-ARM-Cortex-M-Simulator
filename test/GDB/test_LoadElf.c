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

#define ELF_FILE    "C:/Users/user06D/Desktop/GDB-RSP-ARM-Cortex-M-Simulator/data/Ccode.elf"

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
  [ 2] .text             PROGBITS        080001b0 0081b0 0005d8 00  AX  0   0  8
  [ 3] .rodata           PROGBITS        08000788 008788 000008 00   A  0   0  4
  [ 4] .init_array       INIT_ARRAY      08000790 008790 000008 00  WA  0   0  4
  [ 5] .fini_array       FINI_ARRAY      08000798 008798 000004 00  WA  0   0  4
  [ 6] .data             PROGBITS        20000000 010000 000428 00  WA  0   0  8
  [ 7] .ccmram           PROGBITS        10000000 010428 000000 00   W  0   0  1
  [ 8] .bss              NOBITS          20000428 010428 00001c 00  WA  0   0  4
  [ 9] ._user_heap_stack NOBITS          20000444 010428 000600 00  WA  0   0  1
  [10] .ARM.attributes   ARM_ATTRIBUTES  00000000 010428 00002a 00      0   0  1
  [11] .debug_line       PROGBITS        00000000 010452 000090 00      0   0  1
  [12] .debug_info       PROGBITS        00000000 0104e2 0000d3 00      0   0  1
  [13] .debug_abbrev     PROGBITS        00000000 0105b5 000067 00      0   0  1
  [14] .debug_aranges    PROGBITS        00000000 010620 000048 00      0   0  8
  [15] .debug_ranges     PROGBITS        00000000 010668 000020 00      0   0  8
  [16] .debug_str        PROGBITS        00000000 010688 0000b8 01  MS  0   0  1
  [17] .comment          PROGBITS        00000000 010740 000070 01  MS  0   0  1
  [18] .debug_frame      PROGBITS        00000000 0107b0 000034 00      0   0  4
  [19] .shstrtab         STRTAB          00000000 0107e4 0000e6 00      0   0  1
  [20] .symtab           SYMTAB          00000000 010c3c 000da0 10     21  93  4
  [21] .strtab           STRTAB          00000000 0119dc 000bdd 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x008000 0x08000000 0x08000000 0x0079c 0x0079c RWE 0x8000
  LOAD           0x010000 0x20000000 0x0800079c 0x00428 0x00428 RW  0x8000
  LOAD           0x010428 0x20000428 0x20000428 0x00000 0x0061c RW  0x8000

 Section to Segment mapping:
  Segment Sections...
   00     .isr_vector .text .rodata .init_array .fini_array
   01     .data
   02     .ccmram .bss ._user_heap_stack
*/
void test_getSectionLma_given_elfData__should_return_the_correct_physical_address()
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
  TEST_ASSERT_EQUAL(0x8000788, physAddr);

  physAddr = getSectionLma(elfData, 4);
  TEST_ASSERT_EQUAL(0x8000790, physAddr);

  physAddr = getSectionLma(elfData, 5);
  TEST_ASSERT_EQUAL(0x8000798, physAddr);

  physAddr = getSectionLma(elfData, 6);
  TEST_ASSERT_EQUAL(0x800079c, physAddr);

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
}

void test_isWithinRange_given_start_addr_size_and_should_return_1_if_its_within_range()
{
  int size = 2048000;   //2048k
  getElfSection(ELF_FILE);

  TEST_ASSERT_EQUAL(1, isWithinRange(isr->destAddress, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(text->destAddress, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(rodata->destAddress, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(initArray->destAddress, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(finiArray->destAddress, 0x08000000, size));
  TEST_ASSERT_EQUAL(1, isWithinRange(data->destAddress, 0x20000000, size));
}

void test_isWithinRange_given_start_addr_and_size_should_return_0_if_its_not_within_range()
{
  int size = 2048000;   //2048k

  TEST_ASSERT_EQUAL(0, isWithinRange(0, 0x08000000, size));
}

void test_loadElf()
{
  getElfSection(ELF_FILE);

  simulatorCopyBlock_Expect(0x08000000, isr->dataAddress, isr->size);
  simulatorCopyBlock_Expect(0x080001b0, text->dataAddress, text->size);
  simulatorCopyBlock_Expect(0x08000788, rodata->dataAddress, rodata->size);
  simulatorCopyBlock_Expect(0x08000790, initArray->dataAddress, initArray->size);
  simulatorCopyBlock_Expect(0x08000798, finiArray->dataAddress, finiArray->size);
  simulatorCopyBlock_Expect(0x0800079c, data->dataAddress, data->size);

  loadElf(elfData);
  
  TEST_ASSERT_EQUAL(0x8000764, coreReg[PC]);
}
