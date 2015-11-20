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
#include "VMSR.h"
#include "VMRS.h"
#include "VMLAandVMLS.h"
#include "VMUL.h"
#include "VNMLAandVNMLSandVNMUL.h"
#include "VSTM.h"
#include "VSTR.h"
#include "VPUSH.h"
#include "VLDM.h"
#include "VLDR.h"
#include "VPOP.h"
#include "VNEG.h"
#include "VCMP.h"
#include "VABS.h"
#include "VCVT.h"
#include "VSQRT.h"
#include "MiscellaneousInstructions.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


// VMOV    s0, s1, r0, r1
void test_VMOVBetweenCoreRegAndDoubleFpuReg_should_move_the_correct_values_from_r0_r1_into_s1_and_s2()
{
  writeToCoreRegisters(0, 0xe000ed88);
  writeToCoreRegisters(1, 0x00f00000);
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  
  writeInstructionToMemoryGivenByAddress(0xec410a10, 0x08000046);  // VMOV    s0, s1, r0, r1
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x00f00000e000ed88, fpuDoublePrecision[0]);
  TEST_ASSERT_EQUAL(0, fpuDoublePrecision[1]);
  TEST_ASSERT_EQUAL(0xe000ed88, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00f00000, fpuSinglePrecision[1] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// VMOV    r5, r6, s0, s1
void test_VMOVBetweenCoreRegAndDoubleFpuReg_should_move_the_correct_values_from_s0_s1_into_r5_and_r6()
{
  writeDoublePrecision(0, 0x00f00000e000ed88);
  writeInstructionToMemoryGivenByAddress(0xec565a10, 0x0800002a);  // VMOV    r5, r6, s0, s1
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  coreReg[PC] = 0x0800002a;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0xe000ed88,coreReg[5]);
  TEST_ASSERT_EQUAL(0x00f00000,coreReg[6]);
  TEST_ASSERT_EQUAL(0x0800002e,coreReg[PC]);
}


// VMOV    d1, r0, r1
void test_VMOVBetweenCoreRegAndDoubleFpuReg_should_move_the_correct_value_from_r0_r1_into_d1()
{
  writeToCoreRegisters(0, 0xe000ed88);
  writeToCoreRegisters(1, 0x00f00000);

  writeInstructionToMemoryGivenByAddress(0xec410b11, 0x08000046);  // VMOV    d1, r0, r1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();
  
  TEST_ASSERT_EQUAL(0x00f00000e000ed88, fpuDoublePrecision[1]);
  TEST_ASSERT_EQUAL(0xe000ed88, fpuSinglePrecision[2] );
  TEST_ASSERT_EQUAL(0x00f00000, fpuSinglePrecision[3] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VMOV    r5, r6, d1
void test_VMOVBetweenCoreRegAndDoubleFpuReg_should_move_the_correct_values_from_d1_to_r5_and_r6()
{
  writeDoublePrecision(1, 0x00f00000e000ed88);

  writeInstructionToMemoryGivenByAddress(0xec565b11, 0x08000046);  // VMOV    r5, r6, d1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();
  
  TEST_ASSERT_EQUAL(0xe000ed88, coreReg[5] );
  TEST_ASSERT_EQUAL(0x00f00000, coreReg[6] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}