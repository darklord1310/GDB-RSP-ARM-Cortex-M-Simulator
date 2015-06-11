#include "unity.h"
#include "MOV_32bitsInstruction.h"
#include "ARMRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
  
}

void tearDown(void)
{
}


/* case 1: i = 0
           imm4 = 0
           imm3 = 0
           imm8 = 0x42
   MOVW R5, #0x42
 */
void test_MOVImmediate32bitsT3_given_instruction_0xf2400542_should_move_into_0x42_into_R5()
{
  unsigned int instruction = 0xf2400542;
  
  CoreRegister *coreReg = initCoreRegister();
  MOVImmediate32bitsT3(instruction, coreReg);
  
  TEST_ASSERT_EQUAL(0x42, coreReg->reg[5].data);
  
  destroyCoreRegister(coreReg);
  
}


/* case 2: i = 0
           imm4 = 0
           imm3 = 0x5
           imm8 = 0x42
   MOVW R12, #0x542 
 */
void test_MOVImmediate32bitsT3_given_instruction_0xf2405c42_should_move_into_0x542_into_R12()
{
  unsigned int instruction = 0xf2405c42;
  
  CoreRegister *coreReg = initCoreRegister();
  MOVImmediate32bitsT3(instruction, coreReg);
  
  TEST_ASSERT_EQUAL(0x542, coreReg->reg[12].data);
  
  destroyCoreRegister(coreReg);
  
}



/* case 3: i = 1
           imm4 = 0x00
           imm3 = 0x5
           imm8 = 0x42
   MOVW R12, #0xd42 
 */
void test_MOVImmediate32bitsT3_given_instruction_0xf6405c42_should_move_into_0xd42_into_R12()
{
  unsigned int instruction = 0xf6405c42;
  
  CoreRegister *coreReg = initCoreRegister();
  MOVImmediate32bitsT3(instruction, coreReg);
  
  TEST_ASSERT_EQUAL(0xd42, coreReg->reg[12].data);
  
  destroyCoreRegister(coreReg);
  
}



/* case 4: i = 1
           imm4 = 0x3
           imm3 = 0x5
           imm8 = 0x42
   MOVW R3, #0xd42 
 */
void test_MOVImmediate32bitsT3_given_instruction_0xf6435342_should_move_into_0x3d42_into_R3()
{
  unsigned int instruction = 0xf6435342;
  
  CoreRegister *coreReg = initCoreRegister();
  MOVImmediate32bitsT3(instruction, coreReg);
  
  TEST_ASSERT_EQUAL(0x3d42, coreReg->reg[3].data);
  
  destroyCoreRegister(coreReg);
  
}

// MOVW r5, 0xF360
void test_MOVImmediate32bitsT3_given_instruction_0xf24f3560_should_move_into_0xf360_into_R5()
{
  unsigned int instruction = 0xf24f3560;
  
  CoreRegister *coreReg = initCoreRegister();
  MOVImmediate32bitsT3(instruction, coreReg);
  
  TEST_ASSERT_EQUAL(0xf360, coreReg->reg[5].data);
  
  destroyCoreRegister(coreReg);
  
}


// mov r5, #-1
// status flag not implemented yet
void test_MOVImmediate32bitsT2_given_instruction_0xf04f35ff_should_move_into_0xffffffff_into_R5()
{
  unsigned int instruction = 0xf04f35ff;
  
  CoreRegister *coreReg = initCoreRegister();
  MOVImmediate32bitsT2(instruction, coreReg);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg->reg[5].data);
  
  destroyCoreRegister(coreReg);
}
