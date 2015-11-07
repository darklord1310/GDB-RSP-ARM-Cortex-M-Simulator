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



void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VSTMIA  r2, {s1,s2} 

// VSTMIA  r2, {s1,s2} 
/*
    s1 = 0x2DE12E13
    s2 = 0x2D893814
    r2 = 0x20001000
    Expected:
              MemoryBlock[0x20001000] = 0x13
              MemoryBlock[0x20001001] = 0x2e
              MemoryBlock[0x20001002] = 0xe1
              MemoryBlock[0x20001003] = 0x2d
              MemoryBlock[0x20001004] = 0x14
              MemoryBlock[0x20001005] = 0x38
              MemoryBlock[0x20001006] = 0x89
              MemoryBlock[0x20001007] = 0x2d
              coreReg[2] = 0x20001000
                
*/
void test_VSTMIA_and_no_writeback_with_singlePrecision_should_write_the_correct_values()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  writeToCoreRegisters(2, 0x20001000);

  writeInstructionToMemoryGivenByAddress(0xecc20a02, 0x08000046);  // VSTMIA  r2, {s1,s2} 
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x13, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x2e, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0xe1, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x2d, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
  TEST_ASSERT_EQUAL(0x14, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] );
  TEST_ASSERT_EQUAL(0x38, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] );
  TEST_ASSERT_EQUAL(0x89, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] );
  TEST_ASSERT_EQUAL(0x2d, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] );
  TEST_ASSERT_EQUAL(0x20001000, coreReg[2] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VSTMIA  r2, {d1,d2}
/*
    d1 = 0x9999999980000000
    d2 = 0x7777777766666666
    r2 = 0x20001000
    Expected:
              MemoryBlock[0x20001000] = 0x00
              MemoryBlock[0x20001001] = 0x00
              MemoryBlock[0x20001002] = 0x00
              MemoryBlock[0x20001003] = 0x80
              MemoryBlock[0x20001004] = 0x99
              MemoryBlock[0x20001005] = 0x99
              MemoryBlock[0x20001006] = 0x99
              MemoryBlock[0x20001007] = 0x99
              MemoryBlock[0x20001008] = 0x66
              MemoryBlock[0x20001009] = 0x66
              MemoryBlock[0x2000100a] = 0x66
              MemoryBlock[0x2000100b] = 0x66
              MemoryBlock[0x2000100c] = 0x77
              MemoryBlock[0x2000100d] = 0x77
              MemoryBlock[0x2000100e] = 0x77
              MemoryBlock[0x2000100f] = 0x77
              coreReg[2] = 0x20001000
                
*/
void test_VSTMIA_and_no_writeback_with_doublePrecision_should_write_the_correct_values()
{
  writeDoublePrecision(1, 0x9999999980000000);
  writeDoublePrecision(2, 0x7777777766666666);
  writeToCoreRegisters(2, 0x20001000);

  writeInstructionToMemoryGivenByAddress(0xec821b04, 0x08000046);  // VSTMIA  r2, {d1,d2}
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x80, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001008) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001009) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100a) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100b) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ] );
  TEST_ASSERT_EQUAL(0x20001000, coreReg[2] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VSTMIA  r2!, {s1,s2} 
/*
    s1 = 0x2DE12E13
    s2 = 0x2D893814
    r2 = 0x20001000
    Expected:
              MemoryBlock[0x20001000] = 0x13
              MemoryBlock[0x20001001] = 0x2e
              MemoryBlock[0x20001002] = 0xe1
              MemoryBlock[0x20001003] = 0x2d
              MemoryBlock[0x20001004] = 0x14
              MemoryBlock[0x20001005] = 0x38
              MemoryBlock[0x20001006] = 0x89
              MemoryBlock[0x20001007] = 0x2d
              coreReg[2] = 0x20001008
                
*/
void test_VSTMIA_and_with_writeback_with_singlePrecision_should_write_the_correct_values()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  writeToCoreRegisters(2, 0x20001000);

  writeInstructionToMemoryGivenByAddress(0xece20a02, 0x08000046);  // VSTMIA  r2!, {s1,s2} 
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x13, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x2e, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0xe1, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x2d, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
  TEST_ASSERT_EQUAL(0x14, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] );
  TEST_ASSERT_EQUAL(0x38, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] );
  TEST_ASSERT_EQUAL(0x89, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] );
  TEST_ASSERT_EQUAL(0x2d, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] );
  TEST_ASSERT_EQUAL(0x20001008, coreReg[2] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VSTMIA  r2!, {d1,d2}
/*
    d1 = 0x9999999980000000
    d2 = 0x7777777766666666
    r2 = 0x20001000
    Expected:
              MemoryBlock[0x20001000] = 0x00
              MemoryBlock[0x20001001] = 0x00
              MemoryBlock[0x20001002] = 0x00
              MemoryBlock[0x20001003] = 0x80
              MemoryBlock[0x20001004] = 0x99
              MemoryBlock[0x20001005] = 0x99
              MemoryBlock[0x20001006] = 0x99
              MemoryBlock[0x20001007] = 0x99
              MemoryBlock[0x20001008] = 0x66
              MemoryBlock[0x20001009] = 0x66
              MemoryBlock[0x2000100a] = 0x66
              MemoryBlock[0x2000100b] = 0x66
              MemoryBlock[0x2000100c] = 0x77
              MemoryBlock[0x2000100d] = 0x77
              MemoryBlock[0x2000100e] = 0x77
              MemoryBlock[0x2000100f] = 0x77
              coreReg[2] = 0x20001010
                
*/
void test_VSTMIA_and_with_writeback_with_doublePrecision_should_write_the_correct_values()
{
  writeDoublePrecision(1, 0x9999999980000000);
  writeDoublePrecision(2, 0x7777777766666666);
  writeToCoreRegisters(2, 0x20001000);

  writeInstructionToMemoryGivenByAddress(0xeca21b04, 0x08000046);  // VSTMIA  r2!, {d1,d2}
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x80, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001008) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001009) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100a) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100b) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ] );
  TEST_ASSERT_EQUAL(0x20001010, coreReg[2] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// VSTMDB  r2!, {d1,d2}
/*
    d1 = 0x9999999980000000
    d2 = 0x7777777766666666
    r2 = 0x20001010
    Expected:
              MemoryBlock[0x20001000] = 0x00
              MemoryBlock[0x20001001] = 0x00
              MemoryBlock[0x20001002] = 0x00
              MemoryBlock[0x20001003] = 0x80
              MemoryBlock[0x20001004] = 0x99
              MemoryBlock[0x20001005] = 0x99
              MemoryBlock[0x20001006] = 0x99
              MemoryBlock[0x20001007] = 0x99
              MemoryBlock[0x20001008] = 0x66
              MemoryBlock[0x20001009] = 0x66
              MemoryBlock[0x2000100a] = 0x66
              MemoryBlock[0x2000100b] = 0x66
              MemoryBlock[0x2000100c] = 0x77
              MemoryBlock[0x2000100d] = 0x77
              MemoryBlock[0x2000100e] = 0x77
              MemoryBlock[0x2000100f] = 0x77
              coreReg[2] = 0x20001000
                
*/
void test_VSTMDB_and_with_writeback_with_doublePrecision_should_write_the_correct_values()
{
  writeDoublePrecision(1, 0x9999999980000000);
  writeDoublePrecision(2, 0x7777777766666666);
  writeToCoreRegisters(2, 0x20001010);

  writeInstructionToMemoryGivenByAddress(0xed221b04, 0x08000046);  // VSTMDB  r2!, {d1,d2}
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x80, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] );
  TEST_ASSERT_EQUAL(0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001008) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001009) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100a) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100b) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ] );
  TEST_ASSERT_EQUAL(0x20001000, coreReg[2] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VSTR

//VSTR.32 s0, [r3,#12]
/*
    s0 = 0x66666666
    r3 = 0x20001000
    Expected:
              MemoryBlock[0x2000100c] = 0x66
              MemoryBlock[0x2000100d] = 0x66
              MemoryBlock[0x2000100e] = 0x66
              MemoryBlock[0x2000100f] = 0x66
*/
void test_VSTR_given_single_precision_positive_index_should_store_the_correct_value()
{
  writeSinglePrecision(0, 0x66666666);
  writeToCoreRegisters(3, 0x20001000);

  writeInstructionToMemoryGivenByAddress(0xed830a03, 0x08000046);  // VSTR.32 s0, [r3,#12]
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ] );
}



//VSTR.32 s0, [r3,#-12]
/*
    s0 = 0x66666666
    r3 = 0x2000100c
    Expected:
              MemoryBlock[0x20001000] = 0x66
              MemoryBlock[0x20001001] = 0x66
              MemoryBlock[0x20001002] = 0x66
              MemoryBlock[0x20001003] = 0x66
*/
void test_VSTR_given_single_precision_negative_index_should_store_the_correct_value()
{
  writeSinglePrecision(0, 0x66666666);
  writeToCoreRegisters(3, 0x2000100c);

  writeInstructionToMemoryGivenByAddress(0xed030a03, 0x08000046);  // VSTR.32 s0, [r3,#-12]
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
}



//VSTR.64 d0, [r3,#12]
/*
    d0 = 0x7777777766666666
    r3 = 0x20001000
    Expected:
              MemoryBlock[0x2000100c] = 0x66
              MemoryBlock[0x2000100d] = 0x66
              MemoryBlock[0x2000100e] = 0x66
              MemoryBlock[0x2000100f] = 0x66
              MemoryBlock[0x20001010] = 0x77
              MemoryBlock[0x20001011] = 0x77
              MemoryBlock[0x20001012] = 0x77
              MemoryBlock[0x20001013] = 0x77
*/
void test_VSTR_given_double_precision_positive_index_should_store_the_correct_value()
{
  writeDoublePrecision(0, 0x7777777766666666);
  writeToCoreRegisters(3, 0x20001000);

  writeInstructionToMemoryGivenByAddress(0xed830b03, 0x08000046);  // VSTR.64 d0, [r3,#12]
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001010) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001011) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001012) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001013) ] );
}



//VSTR.64 d0, [r3,#-12]
/*
    d0 = 0x7777777766666666
    r3 = 0x20001013
    Expected:
              MemoryBlock[0x20001000] = 0x66
              MemoryBlock[0x20001001] = 0x66
              MemoryBlock[0x20001002] = 0x66
              MemoryBlock[0x20001003] = 0x66
              MemoryBlock[0x20001004] = 0x77
              MemoryBlock[0x20001005] = 0x77
              MemoryBlock[0x20001006] = 0x77
              MemoryBlock[0x20001007] = 0x77
*/
void test_VSTR_given_double_precision_negative_index_should_store_the_correct_value()
{
  writeDoublePrecision(0, 0x7777777766666666);
  writeToCoreRegisters(3, 0x2000100c);

  writeInstructionToMemoryGivenByAddress(0xed030b03, 0x08000046);  // VSTR.64 d0, [r3,#-12]
  coreReg[PC] = 0x08000046;
  
  armStep();
  
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] );
  TEST_ASSERT_EQUAL(0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] );
  TEST_ASSERT_EQUAL(0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] );
}