#include <string.h>
#include <malloc.h>
#include "unity.h"
#include "LoadElfToMemory.h"
#include "ProgramElf.h"
#include "Relocator.h"
#include "Read_File.h"
#include "GetHeaders.h"
#include "elf.h"
#include "MemoryBlock.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "assert.h"
#include "getMask.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_loadElf(void)
{
  loadElf();
}
