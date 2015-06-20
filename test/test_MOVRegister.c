#include "unity.h"
#include "MOVRegister.h"
#include "ARMRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"

void setUp(void)
{
  coreReg = initCoreRegister();
  initStatusRegister();
}

void tearDown(void)
{
}

//test MOV R8, R3, case D is 1
void test_MOVRegisterToRegisterT1_given_instruction_0x46980000_should_move_R3_to_R8(void)
{
  uint32_t instruction = 0x46980000;
  
  coreReg->reg[3].data = 0xff101c00;              //set R3 to be 0xff101c00
  MOVRegisterToRegisterT1(instruction);           //move r3 to r8
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[8].data);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[3].data);
  destroyCoreRegister(coreReg);
}


//test MOV R4, R3, case D is 0
void test_MOVRegisterToRegisterT1_given_instruction_0x461c0000_should_move_R3_to_R4(void)
{
  uint32_t instruction = 0x461c0000;
    
  coreReg->reg[3].data = 0xff101c00;              //set R3 to be 0xff101c00
  MOVRegisterToRegisterT1(instruction);           //move r3 to r4
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[4].data);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[3].data);
  destroyCoreRegister(coreReg);
}

//test MOVS R7, R3 and status flags are affected
void test_MOVRegisterToRegisterT2_given_instruction_0x001f0000_should_move_R3_value_0xff101c00_to_R7_and_set_negative_flag(void)
{
  uint32_t instruction = 0x001f0000;
  
  coreReg->reg[3].data = 0xff101c00;              //set R3 to be 0xff101c00
  MOVRegisterToRegisterT2(instruction);           //move r3 to r7
  
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[7].data);
  TEST_ASSERT_EQUAL(0xff101c00, coreReg->reg[3].data);
  TEST_ASSERT_EQUAL(1 , isNegative() );              
  destroyCoreRegister(coreReg);
}

  
//test MOVS R7, R3 and set zero flag
void test_MOVRegisterToRegisterT2_given_instruction_0x001f0000_should_move_R3_value_0_to_R7_and_set_zero_flag(void)
{
  uint32_t instruction = 0x001f0000;
  
  coreReg->reg[3].data = 0;                       //set R3 to be 0
  MOVRegisterToRegisterT2(instruction);           //move r3 to r7
  
  TEST_ASSERT_EQUAL(0, coreReg->reg[7].data);
  TEST_ASSERT_EQUAL(0, coreReg->reg[3].data);
  TEST_ASSERT_EQUAL(true , isZero() );                  //zero flag should be updated
  destroyCoreRegister(coreReg);
}



//test MOVS R3, R2 and set negative flag
void test_MOVRegisterToRegisterT2_given_instruction_0x00130000_should_move_R2_value_negative_1_to_R3(void)
{
  uint32_t instruction = 0x00130000;
  
  coreReg->reg[2].data = -1;                      //set R2 to be -1
  MOVRegisterToRegisterT2(instruction);           //move r2 to r3
  
  TEST_ASSERT_EQUAL(0xffffffff, coreReg->reg[2].data);
  TEST_ASSERT_EQUAL(0xffffffff, coreReg->reg[3].data);
  TEST_ASSERT_EQUAL(true , isNegative() );              //negative flag should be updated
  destroyCoreRegister(coreReg);
}


