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
#include "ROM.h"
#include "LDRImmediate.h"
#include "LDRLiteral.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Literal
  
//test ldr r0, [pc,#20]
/*
 * 
 * 
 * 
 */
void test_LDRLiteralT1_given_ROM_value_as_above_should_load_r0_wth_0xdeadbeef(void)
{
  rom->address[ virtualMemToPhysicalMem(0x08000018) ].data = 0xbe;
  rom->address[ virtualMemToPhysicalMem(0x08000019) ].data = 0xbe;
  rom->address[ virtualMemToPhysicalMem(0x08000020) ].data = 0xad;
  rom->address[ virtualMemToPhysicalMem(0x08000021) ].data = 0xde;
  
  coreReg[PC] = 0x08000016;
  uint32_t instruction = 0x4a000000;
  ARMSimulator(instruction);                  //ldr r0, [pc,#20]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[0]);
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
  rom->address[ virtualMemToPhysicalMem(0x08000534) ].data = 0xbe;
  rom->address[ virtualMemToPhysicalMem(0x08000535) ].data = 0xbe;
  rom->address[ virtualMemToPhysicalMem(0x08000536) ].data = 0xad;
  rom->address[ virtualMemToPhysicalMem(0x08000537) ].data = 0xde;
  
  coreReg[PC] = 0x0800051e;
  uint32_t instruction = 0x48050000;
  //ARMSimulator(instruction);                  //ldr r0, [pc,#20]
  
  TEST_ASSERT_EQUAL( 0xdeadbeef, coreReg[0]);
}
