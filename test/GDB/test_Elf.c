#include <string.h>
#include <malloc.h>
#include "unity.h"
#include "ProgramElf.h"
#include "Relocator.h"
#include "Read_File.h"
#include "GetHeaders.h"
#include "elf.h"
#include "ErrorCode.h"
#include "CException.h"

extern ElfData *elfData;
extern ElfSection *isr, *text, *rodata, *init_array, *fini_array, *data;
extern uint32_t entryAddress;
extern int fileStatus;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getElfSection_to_get_the_info_of_the_elf_file(void)
{
    char *elfFile = "C:/Users/Asus/Desktop/TDD/Project/GDB-RSP-ARM-Cortex-M-Simulator/data/Ccode.elf";
    getElfSection(elfFile);

    printf(".text section\n");
    printf("%x:       %2x%2x\n", text->destAddress, *(text->dataAddress), *(text->dataAddress + 1));

    printf(".isr_vector section\n");
    printf("%x:       %2x%2x\n", isr->destAddress, *(isr->dataAddress), *(isr->dataAddress + 1));

    printf(".rodata section\n");
    printf("%x:       %2x%2x\n", rodata->destAddress, *(rodata->dataAddress), *(rodata->dataAddress + 1));
}
