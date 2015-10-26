#include "unity.h"
#include <stdint.h>
#include "ExceptionObject.h"
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
#include "BL.h"
#include "BKPT.h"
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
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "Thumb32bitsTable.h"
#include "LoadAndWriteMemory.h"
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
#include "VMOV.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMOV (between ARM core register and single-precision register)

// VMOV s3, r10
void test_VMOV_should_move_the_correct_value_from_r10_into_s3()
{
  writeToCoreRegisters(10, 0xbbbbbbbb);

  writeInstructionToMemoryGivenByAddress(0xee01aa90, 0x08000046);  // VMOV s3, r10
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0xbbbbbbbb00000000, fpuDoublePrecision[1]);
  TEST_ASSERT_EQUAL(0xbbbbbbbb, fpuSinglePrecision[3] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VMOV r10, s3
void test_VMOV_should_move_the_correct_value_from_s3_into_r10()
{
  writeSinglePrecision(3, 0xbbbbbbbb);

  writeInstructionToMemoryGivenByAddress(0xee11aa90, 0x08000046);  // VMOV r10, s3
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0xbbbbbbbb, coreReg[10] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    // VMOV (ARM core register to scalar)
    
// VMOV.32 d3[0], r9
void test_VMOV_should_move_the_correct_value_from_r9_into_lower16bits_of_d3()
{
  writeToCoreRegisters(9, 0xaaaaaaaa);

  writeInstructionToMemoryGivenByAddress(0xee039b10, 0x08000046);  // VMOV.32 d3[0], r9
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x00000000aaaaaaaa, fpuDoublePrecision[3]);
  TEST_ASSERT_EQUAL(0xaaaaaaaa, fpuSinglePrecision[6] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VMOV.32 d3[1], r9
void test_VMOV_should_move_the_correct_value_from_r9_into_upper16bits_of_d3()
{
  writeToCoreRegisters(9, 0xaaaaaaaa);

  writeInstructionToMemoryGivenByAddress(0xee239b10, 0x08000046);  // VMOV.32 d3[1], r9
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0xaaaaaaaa00000000, fpuDoublePrecision[3]);
  TEST_ASSERT_EQUAL(0xaaaaaaaa, fpuSinglePrecision[7] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}