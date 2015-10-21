#include "unity.h"
#include "ARMSimulator.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include "ConditionalExecution.h"
#include "StatusRegisters.h"
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
#include "SUBSPRegister.h"
#include "BL.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "ExceptionObject.h"
#include "BKPT.h"
#include <math.h>

void setUp(void)
{
  initializeSimulator();
  
}

void tearDown(void)
{
}


void test_findBaseOpcode_given_string_0100XX0XXX_should_get_0100000000_in_baseOpcode()
{
  BitsInfo bitsInfo;
  findBaseOpcode("0100XX0XXX", &bitsInfo);

  TEST_ASSERT_EQUAL(0b0100000000, bitsInfo.baseOpcode);
  
}




void test_findBaseOpcode_given_string_1100XX111X_should_get_1100001110_in_baseOpcode()
{
  BitsInfo bitsInfo;
  findBaseOpcode("1100XX111X", &bitsInfo);

  TEST_ASSERT_EQUAL(0b1100001110, bitsInfo.baseOpcode);
  
}


//worst scenario
void test_findBaseOpcode_given_string_1X1X1X1X1X_should_get_1010101010_in_baseOpcode()
{
  BitsInfo bitsInfo;
  findBaseOpcode("1X1X1X1X1X", &bitsInfo);

  TEST_ASSERT_EQUAL(0b1010101010, bitsInfo.baseOpcode);
  
}


void test_getBitsInfo_given_string_1100XX111X_should_update_the_parameters_in_structure_correctly()
{
  BitsInfo bitsInfo;
  getBitsInfo("1100XX111X", &bitsInfo);
  
  TEST_ASSERT_EQUAL(0, bitsInfo.PositionOfbitX[0]);
  TEST_ASSERT_EQUAL(4, bitsInfo.PositionOfbitX[1]);
  TEST_ASSERT_EQUAL(5, bitsInfo.PositionOfbitX[2]);
  TEST_ASSERT_EQUAL(-1, bitsInfo.PositionOfbitX[3]);
  TEST_ASSERT_EQUAL(3, bitsInfo.noOfDontCareBits);
}


void test_getBitsInfo_given_string_0100XX0XXX_should_update_the_parameters_in_structure_correctly()
{
  BitsInfo bitsInfo;
  getBitsInfo("0100XX0XXX", &bitsInfo);
  
  TEST_ASSERT_EQUAL(0, bitsInfo.PositionOfbitX[0]);
  TEST_ASSERT_EQUAL(1, bitsInfo.PositionOfbitX[1]);
  TEST_ASSERT_EQUAL(2, bitsInfo.PositionOfbitX[2]);
  TEST_ASSERT_EQUAL(4, bitsInfo.PositionOfbitX[3]);
  TEST_ASSERT_EQUAL(5, bitsInfo.PositionOfbitX[4]);
  TEST_ASSERT_EQUAL(-1, bitsInfo.PositionOfbitX[5]);
  TEST_ASSERT_EQUAL(5, bitsInfo.noOfDontCareBits);
}


void test()
{

  
}




