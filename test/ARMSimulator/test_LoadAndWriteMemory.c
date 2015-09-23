#include "unity.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "CLZ.h"
#include "SUBSPRegister.h"
#include "BL.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "Thumb16bitsTable.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMSimulator.h"
#include "ITandHints.h"
#include "ADDImmediate.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
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
#include "MOVRegister.h"
#include "CMPRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "LDRImmediate.h"
#include "MemoryBlock.h"
#include "LDRLiteral.h"
#include "ErrorSignal.h"
#include "SVC.h"
#include "ADR.h"
#include "ADDSPRegister.h"
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "CException.h"
#include "RemoteSerialProtocol.h"
#include "Thumb32bitsTable.h"
#include "mock_Packet.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"



void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


/*
 * Expected : 0x08000000 = 0x22
 * 
 * 
 */
void test_writeByteToMemory_given_value_0x88ff4422_and_address_0x08000000_size_1_should_get_the_expected_result(void)
{
  uint32_t value = 0x88ff4422;
  uint32_t address = 0x08000000;
  
  writeByteToMemory(address, value, 1);
  
  TEST_ASSERT_EQUAL( 0x22 , memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  
}



/*
 * Expected : 0x08000000 = 0x22
 *            0x08000001 = 0x44
 *            
 */
void test_writeByteToMemory_given_value_0x88ff4422_and_address_0x08000000_size_2_should_get_the_expected_result(void)
{
  uint32_t value = 0x88ff4422;
  uint32_t address = 0x08000000;
  
  writeByteToMemory(address, value, 2);
  
  TEST_ASSERT_EQUAL( 0x22 , memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  TEST_ASSERT_EQUAL( 0x44 , memoryBlock[ virtualMemToPhysicalMem(0x08000001) ]);
}



/*
 * Expected : 0x08000000 = 0x22
 *            0x08000001 = 0x44
 *            0x08000002 = 0xff
 *            0x08000003 = 0x88
 */
void test_writeByteToMemory_given_value_0x88ff4422_and_address_0x08000000_size_4_should_get_the_expected_result(void)
{
  uint32_t value = 0x88ff4422;
  uint32_t address = 0x08000000;
  
  writeByteToMemory(address, value, 4);
  
  TEST_ASSERT_EQUAL( 0x22 , memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  TEST_ASSERT_EQUAL( 0x44 , memoryBlock[ virtualMemToPhysicalMem(0x08000001) ]);
  TEST_ASSERT_EQUAL( 0xff , memoryBlock[ virtualMemToPhysicalMem(0x08000002) ]);
  TEST_ASSERT_EQUAL( 0x88 , memoryBlock[ virtualMemToPhysicalMem(0x08000003) ]);
}



/*
 * Expected : data = 0x22
 * 
 * 
 */
void test_loadByteFromMemory_given_value_0x22_at_address_0x08000000_size_1_should_get_the_expected_result(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x22;
  uint32_t address = 0x08000000;
  
  uint32_t data = loadByteFromMemory(address, 1);
  
  TEST_ASSERT_EQUAL( 0x22 , data);
  
}


/*
 * Expected : data = 0x4422
 * 
 * 
 */
void test_loadByteFromMemory_value_given_below_and_size_2_should_get_the_expected_result(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x44;
  
  uint32_t address = 0x08000000;
  
  uint32_t data = loadByteFromMemory(address, 2);
  
  TEST_ASSERT_EQUAL( 0x4422 , data);
}


/*
 * Expected : data = 0x88ff4422
 * 
 * 
 */
void test_loadByteFromMemory_value_given_below_and_size_4_should_get_the_expected_result(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x88;
  
  uint32_t address = 0x08000000;
  
  uint32_t data = loadByteFromMemory(address, 4);

  TEST_ASSERT_EQUAL( 0x88ff4422 , data);
}



/* Watch Condition:
 *      type = WP_READ
 *      addr = 0x08000000
 *      size = 2;
 * 
 */
void test_loadByteFromMemory_given_condition_is_meet_should_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  uint32_t value = 1;
  wp[0].type = WP_READ;
  wp[0].addr = 0x08000000;
  wp[0].size = 2;
  
  Try{
     
      value = loadByteFromMemory(0x08000000, 2);
      TEST_FAIL_MESSAGE("Expect to throw here\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(Watchpoint_Break, err);
    TEST_ASSERT_EQUAL(1, value);    //the value is remain 1 because it is throw before execute
  }
}



/* Watch Condition:
 *      type = WP_READ
 *      addr = 0x08000002
 *      size = 2;
 * 
 */
void test_loadByteFromMemory_given_addr_condition_is_not_meet_should_not_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  writeInstructionToMemoryGivenByAddress(0x44140000, 0x08000000);
  uint32_t value = 1;
  wp[0].type = WP_READ;
  wp[0].addr = 0x08000002;
  wp[0].size = 2;
  
  Try{
     
      value = loadByteFromMemory(0x08000000, 2);
      TEST_ASSERT_EQUAL(0x4414,value);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect throw\n");
  }
}



/* Watch Condition:
 *      type = WP_WRITE
 *      addr = 0x08000000
 *      size = 2;
 * 
 */
void test_loadByteFromMemory_given_type_condition_is_not_meet_should_not_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  writeInstructionToMemoryGivenByAddress(0x44140000, 0x08000000);
  uint32_t value = 1;
  wp[0].type = WP_WRITE;
  wp[0].addr = 0x08000000;
  wp[0].size = 2;
  
  Try{
     
      value = loadByteFromMemory(0x08000000, 2);
      TEST_ASSERT_EQUAL(0x4414,value);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect throw\n");
  }
}



/* Watch Condition:
 *      type = WP_READ
 *      addr = 0x08000000
 *      size = 1;
 * 
 */
void test_loadByteFromMemory_given_size_condition_is_not_meet_should_not_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  writeInstructionToMemoryGivenByAddress(0x44140000, 0x08000000);
  uint32_t value = 1;
  wp[0].type = WP_READ;
  wp[0].addr = 0x08000000;
  wp[0].size = 1;
  
  Try{
     
      value = loadByteFromMemory(0x08000000, 2);
      TEST_ASSERT_EQUAL(0x4414,value);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect throw\n");
  }
}



/* Watch Condition:
 *      type = WP_WRITE
 *      addr = 0x08000000
 *      size = 1;
 * 
 */
void test_writeByteToMemory_given_all_conditions_are_meet_should_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x11;
  wp[0].type = WP_WRITE;
  wp[0].addr = 0x08000000;
  wp[0].size = 1;
  
  Try{
     
      writeByteToMemory(0x08000000, 0x44, 1);
      TEST_FAIL_MESSAGE("Expect throw here\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(Watchpoint_Break, err);
    TEST_ASSERT_EQUAL(0x11, memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] ); //expect 0x11 here because 0x44 will failed to write into the memory
  }
}


/* Watch Condition:
 *      type = WP_WRITE
 *      addr = 0x08000000
 *      size = 1;
 * 
 */
void test_writeByteToMemory_given_addr_condition_is_not_meet_should_not_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  wp[0].type = WP_WRITE;
  wp[0].addr = 0x08000000;
  wp[0].size = 1;
  
  Try{
     
      writeByteToMemory(0x08000002, 0x44, 1);
      TEST_ASSERT_EQUAL(0x44 ,memoryBlock[ virtualMemToPhysicalMem(0x08000002) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect throw\n");
  }
}



/* Watch Condition:
 *      type = WP_READ
 *      addr = 0x08000000
 *      size = 1;
 * 
 */
void test_writeByteToMemory_given_type_condition_is_not_meet_should_not_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  wp[0].type = WP_READ;
  wp[0].addr = 0x08000000;
  wp[0].size = 1;
  
  Try{
     
      writeByteToMemory(0x08000000, 0x44, 1);
      TEST_ASSERT_EQUAL(0x44 ,memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect throw\n");
  }
}


/* Watch Condition:
 *      type = WP_READ
 *      addr = 0x08000000
 *      size = 2;
 * 
 */
void test_writeByteToMemory_given_size_condition_is_not_meet_should_not_throw()
{
  CEXCEPTION_T err;
  
  //create test fixture
  wp[0].type = WP_READ;
  wp[0].addr = 0x08000000;
  wp[0].size = 2;
  
  Try{
     
      writeByteToMemory(0x08000000, 0x44, 1);
      TEST_ASSERT_EQUAL(0x44 ,memoryBlock[ virtualMemToPhysicalMem(0x08000000) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect throw\n");
  }
}



void test_isOffPostOrPreIndex_given_index_1_writeback_0_should_return_OFFINDEX()
{
  uint32_t index = 1;
  uint32_t writeback = 0;
  
  int answer = isOffPostOrPreIndex(index,writeback);
  
  TEST_ASSERT_EQUAL(OFFINDEX,answer);
}


void test_isOffPostOrPreIndex_given_index_1_writeback_1_should_return_PREINDEX()
{
  uint32_t index = 1;
  uint32_t writeback = 1;
  
  int answer = isOffPostOrPreIndex(index,writeback);
  
  TEST_ASSERT_EQUAL(PREINDEX,answer);
}



void test_isOffPostOrPreIndex_given_index_0_writeback_1_should_return_POSTINDEX()
{
  uint32_t index = 0;
  uint32_t writeback = 1;
  
  int answer = isOffPostOrPreIndex(index,writeback);
  
  TEST_ASSERT_EQUAL(POSTINDEX,answer);
}


void test_isOffPostOrPreIndex_given_index_0_writeback_0_should_return_UNDEFINED()
{
  uint32_t index = 0;
  uint32_t writeback = 0;
  
  int answer = isOffPostOrPreIndex(index,writeback);
  
  TEST_ASSERT_EQUAL(UNDEFINED,answer);
}








