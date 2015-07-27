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


void setUp(void)
{
  initializeSimulator();
  resetMemoryBlock();
}

void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Literal

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
  //LDR Immediate

//test ldr r0, [pc,#20]
/*
 * 
 * 
 * 
 */
void xtest_LDRImmediateT1_given_ROM_value_as_above_should_load_r0_wth_0xdeadbeef(void)
{
  memoryBlock[ virtualMemToPhysicalMem(0x08000534) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x08000535) ] = 0xbe;
  memoryBlock[ virtualMemToPhysicalMem(0x08000536) ] = 0xad;
  memoryBlock[ virtualMemToPhysicalMem(0x08000537) ] = 0xde;
  
  coreReg[PC] = 0x0800051e;
  uint32_t instruction = 0x48050000;
  //ARMSimulator(instruction);                  //ldr r0, [pc,#20]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[0]);
}
