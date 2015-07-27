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