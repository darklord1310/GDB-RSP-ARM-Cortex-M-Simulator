#include "unity.h"
#include "ARMSimulator.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include "ConditionalExecution.h"
#include "StatusRegisters.h"
#include "Thumb16bitsTable.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "ModifiedImmediateConstant.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ITandHints.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "MemoryBlock.h"
#include "LDRImmediate.h"
#include "LDRLiteral.h"
#include "ErrorSignal.h"
#include "SVC.h"
#include "ADR.h"
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"


void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


void test_is32or16instruction_given_32bits_instruction_should_return_bit32(void)
{
  uint32_t value = 0xF05F0B0F;      // an example of instruction taken from KEIL assembler
                                    // which is MOVS R11, #0xF
  uint32_t result;

  result = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION32bits, result);
}



void test_is32or16instruction_given_16bits_instruction_should_return_bit16()
{
  uint32_t value = 0x46E80000;      // an example of instruction taken from KEIL assembler
                                    // which is  MOV R8, SP

  value = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION16bits, value);

}


/*
 * coreReg[PC]       = 0x08000000
 * ROM[0x10000]      = 0xf3
 * ROM[0x10001]      = 0xf6
 * ROM[0x10002]      = 0xff
 * ROM[0x10003]      = 0x70
 *
 * Expect: retrievedValue = 0xf6f370ff
 *
 */
void test_retrieveInstructionFromROM_given_32bits_instruction_and_ROM_value_as_above_should_retrieve_correctly()
{
  coreReg[PC] = 0x08000000;
  memoryBlock[virtualMemToPhysicalMem(0x08000000)] = 0xf3;
  memoryBlock[virtualMemToPhysicalMem(0x08000000 + 1)] = 0xf6;
  memoryBlock[virtualMemToPhysicalMem(0x08000000 + 2)] = 0xff;
  memoryBlock[virtualMemToPhysicalMem(0x08000000 + 3)] = 0x70;

  uint32_t retrievedValue = retrieveInstructionFromMemory();
  TEST_ASSERT_EQUAL(0xf6f370ff, retrievedValue);
}


/*
 * coreReg[PC]       = 0x08000000
 * ROM[0x10000]      = 0x14
 * ROM[0x10001]      = 0x44
 * ROM[0x10002]      = 0xc9
 * ROM[0x10003]      = 0x07
 *
 * Expect: retrievedValue1 = 0x44140000
 *         retrievedValue2 = 0x07c90000
 */
void test_retrieveInstructionFromROM_given_16bits_instruction_and_ROM_value_as_above_should_retrieve_correctly()
{
  coreReg[PC] = 0x08000000;
  memoryBlock[virtualMemToPhysicalMem(0x08000000)] = 0x14;
  memoryBlock[virtualMemToPhysicalMem(0x08000000 + 1)] = 0x44;
  memoryBlock[virtualMemToPhysicalMem(0x08000000 + 2)] = 0xc9;
  memoryBlock[virtualMemToPhysicalMem(0x08000000 + 3)] = 0x07;

  uint32_t retrievedValue = retrieveInstructionFromMemory();
  TEST_ASSERT_EQUAL(0x44140000, retrievedValue);                  //read instruction 0x4414

  coreReg[PC] += 2;
  retrievedValue = retrieveInstructionFromMemory();
  TEST_ASSERT_EQUAL(0x07c90000, retrievedValue);                  //read instruction 0x07c9
}