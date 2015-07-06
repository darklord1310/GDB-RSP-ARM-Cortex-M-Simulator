#include "unity.h"
#include "MOVImmediate.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "ARMRegisters.h"

void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}


// mov r7, #0x2f00
void test_MOVImmediateT2_given_instruction_0xf44f573c_should_move_into_0x2f00_into_R7_and_update_the_flag()
{
  uint32_t instruction = 0xf45f573c;
  
  MOVImmediateT2(instruction);
  TEST_ASSERT_EQUAL(0x2f00, coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// mov r5, #-1 and not affecting the flag register
void test_MOVImmediateT2_given_instruction_0xf04f35ff_should_move_into_0xffffffff_into_R5_and_do_not_update_flag()
{
  uint32_t instruction = 0xf04f35ff;

  MOVImmediateT2(instruction);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[5]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

//test case modify control smaller than 0b00111
// movs r5, #-1 and affect flag register
void test_MOVImmediateT2_given_instruction_0xf05f35ff_should_move_into_0xffffffff_into_R5_and_set_negative_flag()
{
  uint32_t instruction = 0xf05f35ff;

  MOVImmediateT2(instruction);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg[5]);
  TEST_ASSERT_EQUAL(0x81000000, coreReg[xPSR]);
}

//test case modify control larger than 0b00111
// movs r0, #80000000 and affect flag register
void test_MOVImmediateT2_given_instruction_0xf05f4000_should_move_into_0x80000000_into_R0_and_set_negative_flag()
{
  uint32_t instruction = 0xf05f4000;

  MOVImmediateT2(instruction);
  TEST_ASSERT_EQUAL(0x80000000, coreReg[0]);
  TEST_ASSERT_EQUAL(0xa1000000, coreReg[xPSR]);
}


/* case 1: i = 0
           imm4 = 0
           imm3 = 0
           imm8 = 0x42
   MOVW R5, #0x42
 */
void test_MOVImmediateT3_given_instruction_0xf2400542_should_move_into_0x42_into_R5()
{
  uint32_t instruction = 0xf2400542;
  
  MOVImmediateT3(instruction);
  
  TEST_ASSERT_EQUAL(0x42, coreReg[5]);

}


/* case 2: i = 0
           imm4 = 0
           imm3 = 0x5
           imm8 = 0x42
   MOVW R12, #0x542 
 */
void test_MOVImmediateT3_given_instruction_0xf2405c42_should_move_into_0x542_into_R12()
{
  uint32_t instruction = 0xf2405c42;
  
  MOVImmediateT3(instruction);
  
  TEST_ASSERT_EQUAL(0x542, coreReg[12]);
}



/* case 3: i = 1
           imm4 = 0x00
           imm3 = 0x5
           imm8 = 0x42
   MOVW R12, #0xd42 
 */
void test_MOVImmediateT3_given_instruction_0xf6405c42_should_move_into_0xd42_into_R12()
{
  uint32_t instruction = 0xf6405c42;
  
  MOVImmediateT3(instruction);
  
  TEST_ASSERT_EQUAL(0xd42, coreReg[12]);
}



/* case 4: i = 1
           imm4 = 0x3
           imm3 = 0x5
           imm8 = 0x42
   MOVW R3, #0xd42 
 */
void test_MOVImmediateT3_given_instruction_0xf6435342_should_move_into_0x3d42_into_R3()
{
  uint32_t instruction = 0xf6435342;
  
  MOVImmediateT3(instruction);
  
  TEST_ASSERT_EQUAL(0x3d42, coreReg[3]);
}

// MOVW r5, 0xF360
void test_MOVImmediateT3_given_instruction_0xf24f3560_should_move_into_0xf360_into_R5()
{
  uint32_t instruction = 0xf24f3560;
  
  MOVImmediateT3(instruction);
  
  TEST_ASSERT_EQUAL(0xf360, coreReg[5]);
}




