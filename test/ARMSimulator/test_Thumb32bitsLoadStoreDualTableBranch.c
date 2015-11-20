#include "unity.h"
#include "ExceptionObject.h"
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
#include "CException.h"
#include "SVC.h"
#include "ADDSPImmediate.h"
#include "ADR.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "ExceptionObject.h"
#include "BKPT.h"
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


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STRD Immediate T1

//test STRD  r0, r1, [r2, #1020]
void test_STRDImmediate_given_offIndex_and_positive_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9c201ff, 0x08000046);  // STRD  r0, r1, [r2, #1020]
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200013fc) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200013fd) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x200013fe) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x200013ff) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001400) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001401) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001402) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001403) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test STRD  r0, r1, [r2, #-1020]
void test_STRDImmediate_given_offIndex_and_negative_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe94201ff, 0x08000046);  // STRD  r0, r1, [r2, #-1020]
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000c04) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000c05) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000c06) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x20000c07) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c08) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c09) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c0a) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c0b) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test STRD  r0, r1, [r2], #1020
void test_STRDImmediate_given_postIndex_and_positive_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20000c04;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8e201ff, 0x08000046);  // STRD  r0, r1, [r2], #1020
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[2]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000c04) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000c05) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000c06) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x20000c07) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c08) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c09) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c0a) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000c0b) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test STRD  r0, r1, [r2], #1020
void test_STRDImmediate_given_preIndex_and_positive_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20000c04;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9e201ff, 0x08000046);  // STRD  r0, r1, [r2], #1020
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[2]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRD Immediate T1

//test LDRD  r0, r1, [r2, #1020]
void test_LDRDImmediate_given_offIndex_and_positive_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;

  memoryBlock[ virtualMemToPhysicalMem(0x200013fc) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013fd) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013fe) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013ff) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x20001400) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001401) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001402) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001403) ] = 0x44;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9d201ff, 0x08000046);  // LDRD  r0, r1, [r2, #1020]
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x33333333, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x44444444, coreReg[1]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test LDRD  r0, r1, [r2], #1020
void test_LDRDImmediate_given_postIndex_and_positive_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x200013fc;

  memoryBlock[ virtualMemToPhysicalMem(0x200013fc) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013fd) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013fe) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013ff) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x20001400) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001401) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001402) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001403) ] = 0x44;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8f201ff, 0x08000046);  // LDRD  r0, r1, [r2], #1020
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x33333333, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x44444444, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x200017f8, coreReg[2]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test LDRD  r0, r1, [r2, #1020]!
void test_LDRDImmediate_given_preIndex_and_positive_immediate_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;

  memoryBlock[ virtualMemToPhysicalMem(0x200013fc) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013fd) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013fe) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x200013ff) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x20001400) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001401) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001402) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001403) ] = 0x44;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9f201ff, 0x08000046);  // LDRD  r0, r1, [r2, #1020]!
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x33333333, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x44444444, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x200013fc, coreReg[2]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRD Literal T1

//test LDRD  r0, r1, [PC, #-0x10]
void test_LDRDImmediate_given_negative_label_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;

  memoryBlock[ virtualMemToPhysicalMem(0x0800000c) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000d) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000e) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000f) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x08000010) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000011) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000012) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000013) ] = 0x44;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe95f0104, 0x08000018);
    coreReg[PC] = 0x08000018;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800001c, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x33333333, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x44444444, coreReg[1]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test LDRD  r0, r1, [PC, #0x4]
void test_LDRDImmediate_given_positive_label_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x20001000;

  memoryBlock[ virtualMemToPhysicalMem(0x08000028) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x08000029) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002a) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002b) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002c) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002d) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002e) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002f) ] = 0x44;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9df0101, 0x08000020);
    coreReg[PC] = 0x08000020;
    armStep();
    TEST_ASSERT_EQUAL( 0x08000024, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x33333333, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x44444444, coreReg[1]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}
