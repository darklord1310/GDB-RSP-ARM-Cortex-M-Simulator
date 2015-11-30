#include "unity.h"
#include "ErrorSignal.h"
#include "ARMRegisters.h"
#include "LoadAndWriteMemory.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "MemoryBlock.h"

void setUp(void)
{
  initCoreRegister();
  resetVectorTableAddress();
}

void tearDown(void)
{
}

void test_setThevectorTableAddress_given_address_0x01000000_should_change_vectorTable_to_0x01000000(void)
{
  TEST_ASSERT_EQUAL(0x00000000,vectorTable);                        //before that is pointing at address 0x00
	setTheVectorTableAddress(0x01000000);                             //after that is pointing at address 0x01000000
  
  TEST_ASSERT_EQUAL(0x01000000,vectorTable);
}


void test_resetVectorTableAddress_should_change_vectorTable_to_0x00000000(void)
{
	setTheVectorTableAddress(0x01000000);                             //after that is pointing at address 0x01000000
  resetVectorTableAddress();
  
  TEST_ASSERT_EQUAL(0x00000000,vectorTable);
}


void test_placePCtoVectorTable_given_UsageFault_should_change_PC_to_0x00000000(void)
{
  resetVectorTableAddress();
  placePCtoVectorTable(UsageFault);
  
  TEST_ASSERT_EQUAL(0x00000018,coreReg[PC]);
}