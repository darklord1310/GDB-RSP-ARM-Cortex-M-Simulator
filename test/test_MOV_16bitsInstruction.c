#include "unity.h"
#include "MOV_16bitsInstruction.h"
#include "ARMRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>

void setUp(void)
{
  coreReg = initCoreRegister();
}

void tearDown(void)
{
}


//test MOVS R1, #0xFF
void test_MOVImmediate16bitsT1_given_instruction_0x21FF0000_should_move_0xFF_into_R1(void)
{
  uint32_t instruction = 0x21ff0000;
  
  MOVImmediate16bitsT1(instruction);
  
  TEST_ASSERT_EQUAL(0xff, coreReg->reg[1].data);
  
  destroyCoreRegister(coreReg);
}


//test MOVS R7, #0x13
void test_MOVImmediate16bitsT1_given_instruction_0x27130000_should_move_0x13_into_R7(void)
{
  uint32_t instruction = 0x27130000;
  
  MOVImmediate16bitsT1(instruction);
  
  TEST_ASSERT_EQUAL(0x13, coreReg->reg[7].data);
  
  destroyCoreRegister(coreReg);
}


//test MOVS R7, R3
void test_MOVRegisterToRegister16bitsT2_given_instruction_0x001f0000_should_move_R3_to_R7(void)
{
  uint32_t instruction = 0x001f0000;
  
  coreReg->reg[3].data = 0xff101c00;                    //set R3 to be 0xff101c00
  MOVRegisterToRegister16bitsT2(instruction);            //move r3 to r7
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[7].data);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[3].data);
  destroyCoreRegister(coreReg);
}


//test MOV R8, R3, case D is 1
void test_MOVRegisterToRegister16bitsT1_given_instruction_0x46980000_should_move_R3_to_R8(void)
{
  uint32_t instruction = 0x46980000;
  
  coreReg->reg[3].data = 0xff101c00;                    //set R3 to be 0xff101c00
  MOVRegisterToRegister16bitsT1(instruction);           //move r3 to r8
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[8].data);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[3].data);
  destroyCoreRegister(coreReg);
}


//test MOV R4, R3, case D is 0
void test_MOVRegisterToRegister16bitsT1_given_instruction_0x461c0000_should_move_R3_to_R4(void)
{
  uint32_t instruction = 0x461c0000;
    
  coreReg->reg[3].data = 0xff101c00;                    //set R3 to be 0xff101c00
  MOVRegisterToRegister16bitsT1(instruction);           //move r3 to r4
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[4].data);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[3].data);
  destroyCoreRegister(coreReg);
}

