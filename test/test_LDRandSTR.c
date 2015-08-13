#include "unity.h"
#include "LDRImmediate.h"
#include "ARMSimulator.h"
#include "ARMRegisters.h"
#include "ConditionalExecution.h"
#include "StatusRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
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
#include "MOVRegister.h"
#include "CMPRegister.h"
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
#include "ADDSPRegister.h"
#include "ADDSPImmediate.h"
#include "ADR.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "CException.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"


void setUp(void)
{
  initializeSimulator();
  resetMemoryBlock();
}

void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Literal T1

//test bit 1 is 0 after PC add with 4
//test ldr r0, [pc,#36]
/*  PC = 0x08000008
 *  Memory address 0x08000030 = 0x44
 *  Memory address 0x08000031 = 0x44
 *  Memory address 0x08000032 = 0x44
 *  Memory address 0x08000033 = 0x84
 */
void test_LDRLiteralT1_given_ROM_value_as_above_should_load_r0_wth_0x84444444(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000030) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000031) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000032) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000033) ] = 0x84;
  
  coreReg[PC] = 0x08000008;
  uint32_t instruction = 0x48090000;
  ARMSimulator(instruction);                  //ldr r0, [pc,#36]
 
  TEST_ASSERT_EQUAL( 0x84444444, coreReg[0]);
}
  

  
//test bit 1 is 1 after PC add with 4
//test ldr r3, [pc,#844]
/*  PC = 0x08000016
 *  Memory address 0x08000364 = 0xef
 *  Memory address 0x08000365 = 0xbe
 *  Memory address 0x08000366 = 0xad
 *  Memory address 0x08000367 = 0xde
 */
void test_LDRLiteralT1_given_ROM_value_as_above_should_load_r3_wth_0xdeadbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000364) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x08000365) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x08000366) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x08000367) ] = 0xde;
  
  coreReg[PC] = 0x08000016;
  uint32_t instruction = 0x4bd30000;
  ARMSimulator(instruction);                  //ldr r3, [pc,#844]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[3]);
}



//test inside IT block
//test ldr r0, [pc,#36]
/*     ldr r1, [pc,#36]
 *  PC = 0x0800000a
 *  Memory address 0x08000030 = 0x44
 *  Memory address 0x08000031 = 0x44
 *  Memory address 0x08000032 = 0x44
 *  Memory address 0x08000033 = 0x08
 *  Memory address 0x08000034 = 0x01
 *  Memory address 0x08000035 = 0x01
 *  Memory address 0x08000036 = 0x01
 *  Memory address 0x08000037 = 0x00
 */
void test_LDRLiteralT1_given_inside_IT_block_should_load_r0_0x08444444_xPSR_0x01000000(void)
{

  memoryBlock[ virtualMemToPhysicalMem(0x08000030) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000031) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000032) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000033) ] = 0x08;
  memoryBlock[ virtualMemToPhysicalMem(0x08000034) ] = 0x01;
  memoryBlock[ virtualMemToPhysicalMem(0x08000035) ] = 0x01;
  memoryBlock[ virtualMemToPhysicalMem(0x08000036) ] = 0x01;
  memoryBlock[ virtualMemToPhysicalMem(0x08000037) ] = 0x00;
  
  resetCarryFlag();
  ARMSimulator(0xbf340000);                   //ITE CC
  coreReg[PC] = 0x0800000a;
  ARMSimulator(0x48090000);                   //ldr r0, [pc,#36]
  TEST_ASSERT_EQUAL( 0x08444444, coreReg[0]);
  ARMSimulator(0x49090000);                   //ldr r1, [pc,#36]
  TEST_ASSERT_EQUAL( 0x01000000, coreReg[xPSR]);
}
  
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Immediate T1

//test ldr r3, [r3,#0x00]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 */
void test_LDRImmediateT1_given_ROM_value_as_above_should_load_r3_wth_0xdeadbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x681b0000;
  ARMSimulator(instruction);                  //ldr r3, [r3,#0x00]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[3]);
}



//test ldr r3, [r3,#0x04]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 *  Memory address 0x20000020 = 0x02
 *  Memory address 0x20000021 = 0x0f
 *  Memory address 0x20000022 = 0x0f
 *  Memory address 0x20000023 = 0x12
 */
void test_LDRImmediateT1_given_ROM_value_as_above_should_load_r3_wth_0x120f0f02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x20000020) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x20000021) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000022) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000023) ] = 0x12;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x685b0000;
  ARMSimulator(instruction);                  //ldr r3, [r3,#0x04]

  TEST_ASSERT_EQUAL( 0x120f0f02, coreReg[3]);
}



//test ldr r4, [r3,#0x04]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 *  Memory address 0x20000020 = 0x02
 *  Memory address 0x20000021 = 0x0f
 *  Memory address 0x20000022 = 0x0f
 *  Memory address 0x20000023 = 0x12
 */
void test_LDRImmediateT1_given_ROM_value_as_above_should_load_r4_wth_0x120f0f02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x20000020) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x20000021) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000022) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000023) ] = 0x12;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x685c0000;
  ARMSimulator(instruction);                  //ldr r3, [r3,#0x04]

  TEST_ASSERT_EQUAL( 0x120f0f02, coreReg[4]);
  TEST_ASSERT_EQUAL( 0x2000001c, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRB Immediate T1
  
//test ldrb r3, [r3,#0x00]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 */
void test_LDRBImmediateT1_given_ROM_value_as_above_should_load_r3_wth_0xef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x781b0000;
  ARMSimulator(instruction);                  //ldrb r3, [r3,#0x00]
  
  TEST_ASSERT_EQUAL( 0xef, coreReg[3]);
}


//test ldrb r3, [r3,#0x04]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 *  Memory address 0x20000020 = 0x02
 *  Memory address 0x20000021 = 0x0f
 *  Memory address 0x20000022 = 0x0f
 *  Memory address 0x20000023 = 0x12
 */
void test_LDRBImmediateT1_given_ROM_value_as_above_should_load_r3_wth_0x02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x20000020) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x20000021) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000022) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000023) ] = 0x12;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x791b0000;
  ARMSimulator(instruction);                  //ldrb r3, [r3,#0x04]

  TEST_ASSERT_EQUAL( 0x02, coreReg[3]);
}


//test ldrb r4, [r3,#0x04]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 *  Memory address 0x20000020 = 0x02
 *  Memory address 0x20000021 = 0x0f
 *  Memory address 0x20000022 = 0x0f
 *  Memory address 0x20000023 = 0x12
 */
void test_LDRBImmediateT1_given_ROM_value_as_above_should_load_r4_wth_0x02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x20000020) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x20000021) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000022) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000023) ] = 0x12;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x791c0000;
  ARMSimulator(instruction);                  //ldrb r4, [r3,#0x04]

  TEST_ASSERT_EQUAL( 0x02, coreReg[4]);
  TEST_ASSERT_EQUAL( 0x2000001c, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRH Immediate T1
  
//test ldrh r3, [r3,#0x00]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 */
void test_LDRHImmediateT1_given_ROM_value_as_above_should_load_r3_wth_0xbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x881b0000;
  ARMSimulator(instruction);                  //ldrh r3, [r3,#0x00]
  
  TEST_ASSERT_EQUAL( 0xbeef, coreReg[3]);
}



//test ldrh r3, [r3,#0x04]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 *  Memory address 0x20000020 = 0x02
 *  Memory address 0x20000021 = 0x0f
 *  Memory address 0x20000022 = 0x0f
 *  Memory address 0x20000023 = 0x12
 */
void test_LDRHImmediateT1_given_ROM_value_as_above_should_load_r3_wth_0x0f02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x20000020) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x20000021) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000022) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000023) ] = 0x12;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x889b0000;
  ARMSimulator(instruction);                  //ldrh r3, [r3,#0x04]

  TEST_ASSERT_EQUAL( 0x0f02, coreReg[3]);
}



//test ldrh r4, [r3,#0x04]
/*  r3 = 0x2000001c
 *  Memory address 0x2000001c = 0xef
 *  Memory address 0x2000001d = 0xbe
 *  Memory address 0x2000001e = 0xad
 *  Memory address 0x2000001f = 0xde
 *  Memory address 0x20000020 = 0x02
 *  Memory address 0x20000021 = 0x0f
 *  Memory address 0x20000022 = 0x0f
 *  Memory address 0x20000023 = 0x12
 */
void test_LDRHImmediateT1_given_ROM_value_as_above_should_load_r4_wth_0x0f02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x20000020) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x20000021) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000022) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x20000023) ] = 0x12;
  
  coreReg[3] = 0x2000001c;
  uint32_t instruction = 0x889c0000;
  ARMSimulator(instruction);                  //ldrh r4, [r3,#0x04]

  TEST_ASSERT_EQUAL( 0x0f02, coreReg[4]);
  TEST_ASSERT_EQUAL( 0x2000001c, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Immediate T2

//test ldr r4, [SP,#0x00]
/*  SP = 0x20000688
 *  Memory address 0x20000688 = 0xef
 *  Memory address 0x20000689 = 0xbe
 *  Memory address 0x2000068a = 0xad
 *  Memory address 0x2000068b = 0xde
 */
void test_LDRImmediateT2_given_ROM_value_as_above_should_load_r4_wth_0xdeadbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x20000688) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x20000689) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068a) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068b) ] = 0xde;
  
  coreReg[SP] = 0x20000688;
  uint32_t instruction = 0x9c000000;
  ARMSimulator(instruction);                  //ldr r4, [SP,#0x00]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[4]);
}



//test ldr r4, [SP,#0x04]
/*  SP = 0x20000688
 *  Memory address 0x20000688 = 0xef
 *  Memory address 0x20000689 = 0xbe
 *  Memory address 0x2000068a = 0xad
 *  Memory address 0x2000068b = 0xde
 *  Memory address 0x2000068c = 0x02
 *  Memory address 0x2000068d = 0x0f
 *  Memory address 0x2000068e = 0x0f
 *  Memory address 0x2000068f = 0x12
 */
void test_LDRImmediateT2_given_ROM_value_as_above_should_load_r4_wth_0x120f0f02(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x20000688) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x20000689) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068a) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068b) ] = 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068c) ] = 0x02;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068d) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068e) ] = 0x0f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000068f) ] = 0x12;
  
  coreReg[SP] = 0x20000688;
  uint32_t instruction = 0x9c010000;
  ARMSimulator(instruction);                  //ldr r4, [SP,#0x04]

  TEST_ASSERT_EQUAL( 0x120f0f02, coreReg[4]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STR Immediate T1

  
//test str r3, [r4,#8]
/*  r3 = 0x0b19face
 *  r4 = 0x20000000
 *  Expected:
 *              Memory address 0x20000008 = 0xce
 *              Memory address 0x20000009 = 0xfa
 *              Memory address 0x2000000a = 0x19
 *              Memory address 0x2000000b = 0x0b
 */
void test_STRImmediateT1_given_offset_8_r3_0x0b19face_and_r4_0x20000000_should_get_expected_result(void)
{
 
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x60a30000;
  ARMSimulator(instruction);                  //str r3, [r4,#8]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
  TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
  TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
}




//test str r3, [r4,#0]
/*  r3 = 0x0b19face
 *  r4 = 0x20000000
 *  Expected:
 *              Memory address 0x20000000 = 0xce
 *              Memory address 0x20000001 = 0xfa
 *              Memory address 0x20000002 = 0x19
 *              Memory address 0x20000003 = 0x0b
 */
void test_STRImmediateT1_given_offset_0_r3_0x0b19face_and_r4_0x20000000_should_get_expected_result(void)
{
 
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x60230000;
  ARMSimulator(instruction);                  //str r3, [r4,#0]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]);
  TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]);
  TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRB Immediate T1

  
//test strb r3, [r4,#8]
/*  r3 = 0x0b19face
 *  r4 = 0x20000000
 *  Expected:
 *              Memory address 0x20000008 = 0xce
 *              Memory address 0x20000009 = 0xfa
 *              Memory address 0x2000000a = 0x19
 *              Memory address 0x2000000b = 0x0b
 */
void test_STRBImmediateT1_given_offset_8_r3_0x0b19face_and_r4_0x20000000_should_get_expected_result(void)
{
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x72230000;
  ARMSimulator(instruction);                  //strb r3, [r4,#8]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRH Immediate T1
  
//test strh r3, [r4,#8]
/*  r3 = 0x0b19face
 *  r4 = 0x20000000
 *  Expected:
 *              Memory address 0x20000008 = 0xce
 *              Memory address 0x20000009 = 0xfa
 *              Memory address 0x2000000a = 0x19
 *              Memory address 0x2000000b = 0x0b
 */
void test_STRHImmediateT1_given_offset_8_r3_0x0b19face_and_r4_0x20000000_should_get_expected_result(void)
{
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x81230000;
  ARMSimulator(instruction);                  //strh r3, [r4,#8]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STR Immediate T2
  
//test str r3, [SP,#8]
/*  r3 = 0x0b19face
 *  SP = 0x20000688
 *  Expected:
 *              Memory address 0x20000008 = 0xce
 *              Memory address 0x20000009 = 0xfa
 *              Memory address 0x2000000a = 0x19
 *              Memory address 0x2000000b = 0x0b
 */
void test_STRImmediateT2_given_offset_8_r3_0x0b19face_and_SP_0x20000688_should_get_expected_result(void)
{
 
  coreReg[3] = 0x0b19face;
  coreReg[SP] = 0x20000688;
  uint32_t instruction = 0x93020000;
  ARMSimulator(instruction);                  //str r3, [SP,#8]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000690) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000691) ]);
  TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x20000692) ]);
  TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x20000693) ]);
}




//test str r3, [SP,#0]
/*  r3 = 0x0b19face
 *  SP = 0x20000688
 *  Expected:
 *              Memory address 0x20000688 = 0xce
 *              Memory address 0x20000689 = 0xfa
 *              Memory address 0x2000068a = 0x19
 *              Memory address 0x2000068b = 0x0b
 */
void test_STRImmediateT2_given_offset_0_r3_0x0b19face_and_SP_0x20000688_should_get_expected_result(void)
{
 
  coreReg[3] = 0x0b19face;
  coreReg[SP] = 0x20000688;
  uint32_t instruction = 0x93000000;
  ARMSimulator(instruction);                  //str r3, [SP,#0]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000688) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000689) ]);
  TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x2000068a) ]);
  TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x2000068b) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STR Register T1
  
//test str r3, [r4,r1]
/*  r3 = 0x0b19face
 *  r1 = 0x000000ce
 *  r4 = 0x20000688
 *  Expected:
 *              Memory address 0x200000ce = 0xce
 *              Memory address 0x200000cf = 0xfa
 *              Memory address 0x200000d0 = 0x19
 *              Memory address 0x200000d1 = 0x0b
 */
void test_STRRegisterT1_given_r3_0x0b19face_r4_0x20000000_r1_0x000000ce_should_get_expected_result(void)
{
  coreReg[1] = 0x000000ce;
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;

  uint32_t instruction = 0x50630000;
  ARMSimulator(instruction);                  //str r3, [r4,r1]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ]);
  TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ]);
  TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRH Register T1
  
//test strh r3, [r4,r1]
/*  r3 = 0x0b19face
 *  r1 = 0x000000ce
 *  r4 = 0x20000688
 *  Expected:
 *              Memory address 0x200000ce = 0xce
 *              Memory address 0x200000cf = 0xfa
 *              Memory address 0x200000d0 = 0x00
 *              Memory address 0x200000d1 = 0x00
 */
void test_STRHRegisterT1_given_r3_0x0b19face_r4_0x20000000_r1_0x000000ce_should_get_expected_result(void)
{
  coreReg[1] = 0x000000ce;
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;

  uint32_t instruction = 0x52630000;
  ARMSimulator(instruction);                  //strh r3, [r4,r1]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ]);
  TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRB Register T1
  
//test strb r3, [r4,r1]
/*  r3 = 0x0b19face
 *  r1 = 0x000000ce
 *  r4 = 0x20000688
 *  Expected:
 *              Memory address 0x200000ce = 0xce
 *              Memory address 0x200000cf = 0x00
 *              Memory address 0x200000d0 = 0x00
 *              Memory address 0x200000d1 = 0x00
 */
void test_STRBRegisterT1_given_r3_0x0b19face_r4_0x20000000_r1_0x000000ce_should_get_expected_result(void)
{
  coreReg[1] = 0x000000ce;
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x20000000;

  uint32_t instruction = 0x54630000;
  ARMSimulator(instruction);                  //strb r3, [r4,r1]
 
  TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ]);
  TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Load Register T1
  
  
//test ldr r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0xef
 *  Memory address 0x200000cf = 0xbe
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0xdeadbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x58630000;
  ARMSimulator(instruction);                  //ldr r3, [r4,r1]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRH Register T1
  
//test ldrh r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0xef
 *  Memory address 0x200000cf = 0xbe
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRHRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0xbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x5a630000;
  ARMSimulator(instruction);                  //ldrh r3, [r4,r1]
  
  TEST_ASSERT_EQUAL( 0xbeef, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRB Register T1
  
//test ldrb r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0xef
 *  Memory address 0x200000cf = 0xbe
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRBRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0xef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x5c630000;
  ARMSimulator(instruction);                  //ldrb r3, [r4,r1]
  
  TEST_ASSERT_EQUAL( 0xef, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSB Register T1

//case : the signed bit is 1
//test ldrsb r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0xef
 *  Memory address 0x200000cf = 0xbe
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRSBRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0xffffffef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x56630000;
  ARMSimulator(instruction);                  //ldrsb r3, [r4,r1]

  TEST_ASSERT_EQUAL( 0xffffffef, coreReg[3]);
}



//case : the signed bit is 0
//test ldrsb r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0x01
 *  Memory address 0x200000cf = 0xbe
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRSBRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0x01(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0x01;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x56630000;
  ARMSimulator(instruction);                  //ldrsb r3, [r4,r1]

  TEST_ASSERT_EQUAL( 0x01, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRSH Register T1

  
//case : the signed bit is 1
//test ldrsb r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0xef
 *  Memory address 0x200000cf = 0xbe
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRSHRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0xffffbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x5e630000;
  ARMSimulator(instruction);                  //ldrsb r3, [r4,r1]

  TEST_ASSERT_EQUAL( 0xffffbeef, coreReg[3]);
}



//case : the signed bit is 0
//test ldrsb r3, [r4,r1]
/*  r3 = 0x2000001c
 *  r4 = 0x20000000
 *  Memory address 0x200000ce = 0x0c
 *  Memory address 0x200000cf = 0x0d
 *  Memory address 0x200000d0 = 0xad
 *  Memory address 0x200000d1 = 0xde
 */
void test_LDRSHRegisterT1_given_ROM_value_as_above_should_load_r3_wth_0x0000000d0c(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x200000ce) ] = 0x0c;
  memoryBlock[ virtualMemToPhysicalMem(0x200000cf) ] = 0x0d;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d0) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x200000d1) ] = 0xde;
  
  coreReg[1] = 0x000000ce;
  coreReg[4] = 0x20000000;
  uint32_t instruction = 0x5e630000;
  ARMSimulator(instruction);                  //ldrsb r3, [r4,r1]

  TEST_ASSERT_EQUAL( 0x0000000d0c, coreReg[3]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Store Multiple Register T1

//test case 1
//test stm r2!, {r3,r7}
/*  r2 = 0x20000000
 *  r3 = 0x0b19face
 *  r4 = 0x12345678
 *  r5 = 0xdeadbeef
 *  r6 = 0x20000000
 *  r7 = 0xabcdef00
 * 
 * Expected:
 *  Memory address 0x20000000 = 0xef
 *  Memory address 0x20000001 = 0xfa
 *  Memory address 0x20000002 = 0x19
 *  Memory address 0x20000003 = 0x0b
 *  Memory address 0x20000004 = 0x78
 *  Memory address 0x20000005 = 0x56
 *  Memory address 0x20000006 = 0x34
 *  Memory address 0x20000007 = 0x12
 *  Memory address 0x20000008 = 0xef
 *  Memory address 0x20000009 = 0xbe
 *  Memory address 0x2000000a = 0xad
 *  Memory address 0x2000000b = 0xde
 *  Memory address 0x2000000c = 0x00
 *  Memory address 0x2000000d = 0x00
 *  Memory address 0x2000000e = 0x00
 *  Memory address 0x2000000f = 0x20
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0xef
 *  Memory address 0x20000012 = 0xcd
 *  Memory address 0x20000013 = 0xab
 */
void test_STMRegisterT1_given_test_case_1_and_the_writeback_register_is_not_in_the_register_list_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[2] = 0x20000000;
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x12345678;
  coreReg[5] = 0xdeadbeef;
  coreReg[6] = 0x20000000;
  coreReg[7] = 0xabcdef00;
  
  uint32_t instruction = 0xc2f80000;
  
  Try
  {
    ARMSimulator(instruction);                  //stm r2!, {r3,r7}
    TEST_ASSERT_EQUAL( 0x20000014, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]);
    TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]);
    TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]);
    TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]);
    TEST_ASSERT_EQUAL( 0x78, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0x56, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0x34, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0x12, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]);
    TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]);
    TEST_ASSERT_EQUAL( 0xcd, memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]);
    TEST_ASSERT_EQUAL( 0xab, memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


//test case 2
//test stm r1!, {r3,r5}
/*  r2 = 0x20000000
 *  r3 = 0x0b19face
 *  r4 = 0x12345678
 *  r5 = 0xdeadbeef
 * 
 * Expected:
 *  Memory address 0x20000000 = 0xef
 *  Memory address 0x20000001 = 0xfa
 *  Memory address 0x20000002 = 0x19
 *  Memory address 0x20000003 = 0x0b
 *  Memory address 0x20000004 = 0x78
 *  Memory address 0x20000005 = 0x56
 *  Memory address 0x20000006 = 0x34
 *  Memory address 0x20000007 = 0x12
 *  Memory address 0x20000008 = 0xef
 *  Memory address 0x20000009 = 0xbe
 *  Memory address 0x2000000a = 0xad
 *  Memory address 0x2000000b = 0xde
 */
void test_STMRegisterT1_given_test_case_2_and_the_writeback_register_is_not_in_the_register_list_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[1] = 0x20000000;
  coreReg[3] = 0x0b19face;
  coreReg[4] = 0x12345678;
  coreReg[5] = 0xdeadbeef;
  
  uint32_t instruction = 0xc1380000;
  
  Try
  {
    ARMSimulator(instruction);                  //stm r1!, {r3,r7}
    TEST_ASSERT_EQUAL( 0x2000000c, coreReg[1]);
    TEST_ASSERT_EQUAL( 0xce, memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]);
    TEST_ASSERT_EQUAL( 0xfa, memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]);
    TEST_ASSERT_EQUAL( 0x19, memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]);
    TEST_ASSERT_EQUAL( 0x0b, memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]);
    TEST_ASSERT_EQUAL( 0x78, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0x56, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0x34, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0x12, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0xef, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0xbe, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0xad, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0xde, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
 
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Load Multiple Register T1
  
//test case 1
//test ldm r2!, {r3,r7}
/*  r2 = 0x20000000
 * 
 *  Memory address 0x20000000 = 0xef
 *  Memory address 0x20000001 = 0xfa
 *  Memory address 0x20000002 = 0x19
 *  Memory address 0x20000003 = 0x0b
 *  Memory address 0x20000004 = 0x78
 *  Memory address 0x20000005 = 0x56
 *  Memory address 0x20000006 = 0x34
 *  Memory address 0x20000007 = 0x12
 *  Memory address 0x20000008 = 0xef
 *  Memory address 0x20000009 = 0xbe
 *  Memory address 0x2000000a = 0xad
 *  Memory address 0x2000000b = 0xde
 *  Memory address 0x2000000c = 0x00
 *  Memory address 0x2000000d = 0x00
 *  Memory address 0x2000000e = 0x00
 *  Memory address 0x2000000f = 0x20
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0xef
 *  Memory address 0x20000012 = 0xcd
 *  Memory address 0x20000013 = 0xab
 * 
 */
void test_LDMRegisterT1_given_test_case_1_and_the_writeback_register_is_not_in_the_register_list_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[2] = 0x20000000;
  memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]= 0xce;
  memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]= 0xfa;
  memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]= 0x19;
  memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]= 0x0b;
  memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]= 0x78;
  memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]= 0x56;
  memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]= 0x34;
  memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]= 0x12;
  memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]= 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]= 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]= 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]= 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]= 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]= 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]= 0xcd;
  memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]= 0xab;
  
  uint32_t instruction = 0xcaf80000;
  
  Try
  {
    ARMSimulator(instruction);                  //ldm r2!, {r3,r7}
    TEST_ASSERT_EQUAL( 0x20000014, coreReg[2]);
    TEST_ASSERT_EQUAL( 0x0b19face, coreReg[3] );
    TEST_ASSERT_EQUAL( 0x12345678, coreReg[4] );
    TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[5]);
    TEST_ASSERT_EQUAL( 0x20000000, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xabcdef00,coreReg[7] );

  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}




//test case 2
//test ldm r3, {r3,r7}
/*  r3 = 0x20000000
 * 
 *  Memory address 0x20000000 = 0xef
 *  Memory address 0x20000001 = 0xfa
 *  Memory address 0x20000002 = 0x19
 *  Memory address 0x20000003 = 0x0b
 *  Memory address 0x20000004 = 0x78
 *  Memory address 0x20000005 = 0x56
 *  Memory address 0x20000006 = 0x34
 *  Memory address 0x20000007 = 0x12
 *  Memory address 0x20000008 = 0xef
 *  Memory address 0x20000009 = 0xbe
 *  Memory address 0x2000000a = 0xad
 *  Memory address 0x2000000b = 0xde
 *  Memory address 0x2000000c = 0x00
 *  Memory address 0x2000000d = 0x00
 *  Memory address 0x2000000e = 0x00
 *  Memory address 0x2000000f = 0x20
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0xef
 *  Memory address 0x20000012 = 0xcd
 *  Memory address 0x20000013 = 0xab
 * 
 */
void test_LDMRegisterT1_given_test_case_2_and_the_writeback_register_is_in_the_register_list_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[3] = 0x20000000;
  memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]= 0xce;
  memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]= 0xfa;
  memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]= 0x19;
  memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]= 0x0b;
  memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]= 0x78;
  memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]= 0x56;
  memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]= 0x34;
  memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]= 0x12;
  memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]= 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]= 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]= 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]= 0xde;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]= 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]= 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]= 0xef;
  memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]= 0xcd;
  memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]= 0xab;
  
  uint32_t instruction = 0xcbf80000;
  
  Try
  {
    ARMSimulator(instruction);                  //ldm r3, {r3,r7}
    TEST_ASSERT_EQUAL( 0x0b19face, coreReg[3] );
    TEST_ASSERT_EQUAL( 0x12345678, coreReg[4] );
    TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[5]);
    TEST_ASSERT_EQUAL( 0x20000000, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xabcdef00,coreReg[7] );

  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}