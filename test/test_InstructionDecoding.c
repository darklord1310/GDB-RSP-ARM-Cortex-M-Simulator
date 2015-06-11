#include "unity.h"
#include "InstructionDecoding.h"
#include "getBits.h"
#include "getMask.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_is32or16instruction_given_32bits_instruction_should_return_bit32(void)
{
  unsigned int value = 0xF05F0B0F;      // an example of instruction taken from KEIL assembler
                                        // which is MOVS R11, #0xF
  unsigned int result;

  result = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION32bits, result);
}



void test_is32or16instruction_given_16bits_instruction_should_return_bit16()
{
  unsigned int value = 0x46E80000;      // an example of instruction taken from KEIL assembler
                                        // which is  MOV R8, SP

  value = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION16bits, value);

}

/* opcode = 001100
 * 00xxxx   --->  ShiftAddSubctractMoveCompare
 * 
 */
void test_Categorize16bitsThumbInstruction_given_0x30101011_should_return_SHITFADDSUBTRACTMOVECOMPARE()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x30101011);
  
  TEST_ASSERT_EQUAL( SHITFADDSUBTRACTMOVECOMPARE, returnvalue);
  
}

/* boundary test for SHITFADDSUBTRACTMOVECOMPARE 
 * opcode = 001111 is the largest value which will fall into SHITFADDSUBTRACTMOVECOMPARE category
 * 00xxxx   --->  ShiftAddSubctractMoveCompare
 */
void test_Categorize16bitsThumbInstruction_given_0x3c101011_should_return_SHITFADDSUBTRACTMOVECOMPARE()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x3c101011);
  
  TEST_ASSERT_EQUAL( SHITFADDSUBTRACTMOVECOMPARE, returnvalue);
  
}


/* opcode = 0100 00
 * 010000   --->  Data Processing
 */
void test_Categorize16bitsThumbInstruction_given_0x40101011_should_return_DATAPROCESSING()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x40101011);
  
  TEST_ASSERT_EQUAL( DATAPROCESSING, returnvalue);
  
}

/* opcode = 0100 01 
 * 010001   --->  SpecialDataInstructionAndBranchExchange
 */
void test_Categorize16bitsThumbInstruction_given_0x44101011_should_return_SPECIALDATAINSTRUCTIONANDBRANCHEXCHANGE()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x44101011);
  
  TEST_ASSERT_EQUAL( SPECIALDATAINSTRUCTIONANDBRANCHEXCHANGE, returnvalue);
  
}


/* opcode = 0100 11 
 * 01001x   --->  LoadFromLiteralPool
 */
void test_Categorize16bitsThumbInstruction_given_0x4c101011_should_return_LOADFROMLITERALPOOL()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x4c101011);
  
  TEST_ASSERT_EQUAL( LOADFROMLITERALPOOL, returnvalue);
  
}


/* opcode = 0100 10 
 * 01001x   --->  LoadFromLiteralPool
 */
void test_Categorize16bitsThumbInstruction_given_0x48101011_should_return_LOADFROMLITERALPOOL()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x48101011);
  
  TEST_ASSERT_EQUAL( LOADFROMLITERALPOOL, returnvalue);
  
}



/* opcode = 0101 00 
 *    0101xx   --->  LoadOrStoreSingleData
 *    011xxx   ___|
 *    100xxx   ___|
 */
void test_Categorize16bitsThumbInstruction_given_0x50101011_should_return_LOADORSTORESINGLEDATA()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x50101011);
  
  TEST_ASSERT_EQUAL( LOADORSTORESINGLEDATA, returnvalue);
  
}

//boundary test for LOADORSTORESINGLEDATA
/* opcode = 1001 11 
 *    0101xx   --->  LoadOrStoreSingleData
 *    011xxx   ___|
 *    100xxx   ___|
 */
void test_Categorize16bitsThumbInstruction_given_0x9c101011_should_return_LOADORSTORESINGLEDATA()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0x9c101011);
  
  TEST_ASSERT_EQUAL( LOADORSTORESINGLEDATA, returnvalue);
  
}



/* opcode = 1010 00 
 * 10100x   --->  GeneratePCRelativeAddress
 */
void test_Categorize16bitsThumbInstruction_given_0xa0101011_should_return_GENERATEPCRELATIVEADDRESS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xa0101011);
  
  TEST_ASSERT_EQUAL( GENERATEPCRELATIVEADDRESS, returnvalue);
  
}



/* opcode = 1010 01 
 * 10100x   --->  GeneratePCRelativeAddress
 */
void test_Categorize16bitsThumbInstruction_given_0xa4101011_should_return_GENERATEPCRELATIVEADDRESS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xa4101011);
  
  TEST_ASSERT_EQUAL( GENERATEPCRELATIVEADDRESS, returnvalue);
  
}


/* opcode = 1010 10 
 * 10101x   --->  GenerateSPRelativeAddress
 */
void test_Categorize16bitsThumbInstruction_given_0xa4801011_should_return_GENERATESPRELATIVEADDRESS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xa8101011);
  
  TEST_ASSERT_EQUAL( GENERATESPRELATIVEADDRESS, returnvalue);
  
}


/* opcode = 1010 11 
 * 10101x   --->  GenerateSPRelativeAddress
 */
void test_Categorize16bitsThumbInstruction_given_0xac801011_should_return_GENERATESPRELATIVEADDRESS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xac101011);
  
  TEST_ASSERT_EQUAL( GENERATESPRELATIVEADDRESS, returnvalue);
  
}


/* opcode = 1011 00 
 * 1011xx   --->  Miscellaneous16bitsInstruction
 */
void test_Categorize16bitsThumbInstruction_given_0xb0801011_should_return_MISCELLANEOUS16BITSINSTRUCTION()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xb0101011);
  
  TEST_ASSERT_EQUAL( MISCELLANEOUS16BITSINSTRUCTION, returnvalue);
  
}


/* opcode = 1011 11 
 * 1011xx   --->  Miscellaneous16bitsInstruction
 */
void test_Categorize16bitsThumbInstruction_given_0xbc801011_should_return_MISCELLANEOUS16BITSINSTRUCTION()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xbc101011);
  
  TEST_ASSERT_EQUAL( MISCELLANEOUS16BITSINSTRUCTION, returnvalue);
  
}


/* opcode = 1100 00 
 * 11000x   --->  StoreMultipleRegisters
 */
void test_Categorize16bitsThumbInstruction_given_0xc0801011_should_return_STOREMULTIPLEREGISTERS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xc0101011);
  
  TEST_ASSERT_EQUAL( STOREMULTIPLEREGISTERS, returnvalue);
  
}



/* opcode = 1100 01 
 * 11000x   --->  StoreMultipleRegisters
 */
void test_Categorize16bitsThumbInstruction_given_0xc4801011_should_return_STOREMULTIPLEREGISTERS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xc4101011);
  
  TEST_ASSERT_EQUAL( STOREMULTIPLEREGISTERS, returnvalue);
  
}


/* opcode = 1100 10 
 * 11001x   --->  LoadMultipleRegisters
 */
void test_Categorize16bitsThumbInstruction_given_0xc8801011_should_return_LOADMULTIPLEREGISTERS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xc8101011);
  
  TEST_ASSERT_EQUAL( LOADMULTIPLEREGISTERS, returnvalue);
  
}



/* opcode = 1100 11 
 * 11001x   --->  LoadMultipleRegisters
 */
void test_Categorize16bitsThumbInstruction_given_0xcc801011_should_return_LOADMULTIPLEREGISTERS()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xcc101011);
  
  TEST_ASSERT_EQUAL( LOADMULTIPLEREGISTERS, returnvalue);
  
}



/* opcode = 1101 00 
 * 1101xx   --->  ConditionalBranch
 */
void test_Categorize16bitsThumbInstruction_given_0xd0801011_should_return_CONDITIONALBRANCH()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xd0101011);
  
  TEST_ASSERT_EQUAL( CONDITIONALBRANCH, returnvalue);
  
}


/* opcode = 1101 11 
 * 1101xx   --->  ConditionalBranch
 */
void test_Categorize16bitsThumbInstruction_given_0xdc801011_should_return_CONDITIONALBRANCH()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xdc101011);
  
  TEST_ASSERT_EQUAL( CONDITIONALBRANCH, returnvalue);
  
}


/* opcode = 1110 00 
 * 11100x   --->  UnconditionalBranch
 */
void test_Categorize16bitsThumbInstruction_given_0xe0801011_should_return_UNCONDITIONALBRANCH()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xe0101011);
  
  TEST_ASSERT_EQUAL( UNCONDITIONALBRANCH, returnvalue);
  
}


/* opcode = 1110 01 
 * 11100x   --->  UnconditionalBranch
 */
void test_Categorize16bitsThumbInstruction_given_0xe4801011_should_return_UNCONDITIONALBRANCH()
{
  unsigned int returnvalue; 
  
  returnvalue = Categorize16bitsThumbInstruction(0xe4101011);
  
  TEST_ASSERT_EQUAL( UNCONDITIONALBRANCH, returnvalue);
  
}


