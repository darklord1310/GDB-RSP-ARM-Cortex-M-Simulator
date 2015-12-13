#include "unity.h"
#include <stdint.h>
#include "ExceptionObject.h"
#include "CException.h"
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
#include "VADD.h"
#include "VSUB.h"
#include "VDIV.h"
#include "VCVTBandVCVTT.h"
#include "VCVTandVCVTR.h"
#include "VDIV.h"
#include "SaturateOperation.h"


void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


void test_executeFPUChecking_given_FPU_is_enable_should_not_throw_error()
{
  CEXCEPTION_T err;
  writeByteToMemory(0x080000ac, 0xe000ed88, 4);

  //Instructions to enable the floating point
  writeInstructionToMemoryGivenByAddress(0xf8df0060, 0x08000048);  // LDR.W  R0, =0xE000ED88
  writeInstructionToMemoryGivenByAddress(0x68010000, 0x0800004c);  // LDR     R1, [R0]
  writeInstructionToMemoryGivenByAddress(0xf4410170, 0x0800004e);  // ORR     R1, R1, #(0xF << 20)
  writeInstructionToMemoryGivenByAddress(0x60010000, 0x08000052);  // STR     R1, [R0]
  writeInstructionToMemoryGivenByAddress(0xf3bf8f4f, 0x08000054);  // DSB
  writeInstructionToMemoryGivenByAddress(0xf3bf8f6f, 0x08000058);  // ISB
  
  coreReg[PC] = 0x08000048;
 
  Try
  {
    armStep();
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


void test_executeFPUChecking_given_FPU_is_not_enabled_should_throw_error()
{
  CEXCEPTION_T err;
  
  coreReg[PC] = 0x08000048;
  writeInstructionToMemoryGivenByAddress(0xeef13a60, 0x08000048);  //testing with VNEG.F32 s7, s1
 
  Try
  {
    armStep();    //will throw error when attempt to execute VNEG since FPU is not enabled
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(vectorTable+USAGEFAULT,coreReg[PC]);
    TEST_ASSERT_EQUAL(UsageFault,err);
  }
}



void test_FPInfinity_given_signBit_1_and_16_bits_should_return_0xFC00()
{
  uint32_t signBit = 1;
  int noOfBits = 16;
  
  uint32_t result = FPInfinity(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0x0000FC00,result);
}


void test_FPInfinity_given_signBit_0_and_16_bits_should_return_0x7C00()
{
  uint32_t signBit = 0;
  int noOfBits = 16;
  
  uint32_t result = FPInfinity(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0x00007C00,result);
}


void test_FPInfinity_given_signBit_1_and_32_bits_should_return_0xff800000()
{
  uint32_t signBit = 1;
  int noOfBits = 32;
  
  uint32_t result = FPInfinity(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0xff800000,result);
}


void test_FPInfinity_given_signBit_0_and_32_bits_should_return_0x7f800000()
{
  uint32_t signBit = 0;
  int noOfBits = 32;
  
  uint32_t result = FPInfinity(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0x7f800000,result);
}


void test_FPDefaultNaN_given_32_bits_should_return_0x7fc0000()
{
  int noOfBits = 32;
  
  uint32_t result = FPDefaultNaN(noOfBits);
  TEST_ASSERT_EQUAL(0x7fc00000,result);
}


void test_FPDefaultNaN_given_16_bits_should_return_0x7e00()
{
  int noOfBits = 16;
  
  uint32_t result = FPDefaultNaN(noOfBits);
  TEST_ASSERT_EQUAL(0x7e00,result);
}


void test_FPMaxNormal_given_signBit_1_and_16_bits_should_return_0xfbff()
{
  uint32_t signBit = 1;
  int noOfBits = 16;
  
  uint32_t result = FPMaxNormal(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0xfbff,result);
}


void test_FPMaxNormal_given_signBit_0_and_16_bits_should_return_0x7bff()
{
  uint32_t signBit = 0;
  int noOfBits = 16;
  
  uint32_t result = FPMaxNormal(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0x7bff,result);
}


void test_FPMaxNormal_given_signBit_1_and_32_bits_should_return_0xff7fffff()
{
  uint32_t signBit = 1;
  int noOfBits = 32;
  
  uint32_t result = FPMaxNormal(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0xff7fffff,result);
}


void test_FPMaxNormal_given_signBit_0_and_32_bits_should_return_0x7f7fffff()
{
  uint32_t signBit = 0;
  int noOfBits = 32;
  
  uint32_t result = FPMaxNormal(signBit,noOfBits);
  TEST_ASSERT_EQUAL(0x7f7fffff,result);
}


void test_determineMinimumExp_given_E_is_8_should_get_neg_126()
{
  int E = 8;
  
  int result = determineMinimumExp(E);
  TEST_ASSERT_EQUAL(-126,result);
}


void test_determineMinimumExp_given_E_is_5_should_get_neg_14()
{
  int E = 5;
  
  int result = determineMinimumExp(E);
  TEST_ASSERT_EQUAL(-14,result);
}

/*  value = 3.22E-22
 *  
 *  Expected:  sign     =  +1
 *             exponent =  -72
 *             mantissa =  1.5206019878387451
 */
void test_getFloatingPointNumberData_given_value_as_above_should_return_the_expected_result()
{
  float value = 3.22E-22;
  double mantissa;
  uint32_t exponent,sign;
  
  getFloatingPointNumberData(value,&sign,&exponent,&mantissa);
  TEST_ASSERT_EQUAL(0,sign);
  TEST_ASSERT_EQUAL(-72,exponent);
  TEST_ASSERT_EQUAL(1.5206019878387451,mantissa);
}


/*  value = 0x6aff994c
 *  
 *  Expected:  sign     =  0
 *             exponent =  213
 *             mantissa =  8362316
 */
void test_unpackFloatData_given_0x6aff994c_and_noOfBits_32_should_return_the_expected_result()
{
  uint32_t sign;
  uint32_t exp;
  uint32_t frac;
  uint32_t value = 0x6aff994c;
  
  unpackFloatData(value, &sign, &exp, &frac, 32);
  
  TEST_ASSERT_EQUAL(0,sign);
  TEST_ASSERT_EQUAL(213,exp);
  TEST_ASSERT_EQUAL(8362316,frac);
}


/*  value = 0x6aff994c
 *  
 *  Expected:  sign     =  0
 *             exponent =  0b1101
 *             mantissa =  0b0101010101
 */
void test_unpackFloatData_given_0x3555_and_noOfBits_16_should_return_the_expected_result()
{
  uint32_t sign;
  uint32_t exp;
  uint32_t frac;
  uint32_t value = 0x3555;
  
  unpackFloatData(value, &sign, &exp, &frac, 16);
  
  TEST_ASSERT_EQUAL(sign,0);
  TEST_ASSERT_EQUAL(exp, 0b1101);
  TEST_ASSERT_EQUAL(frac,0b0101010101);
}



void test_FPUnpack_given_noOfBits_16_should_get_expected_result()
{
  uint16_t value = 0x1;
  FPInfo info = FPUnpack(value, fPSCR, 16);
  TEST_ASSERT_EQUAL(info.realNumber,5.96046e-8);
}


void test_FPUnpack_given_noOfBits_32_should_get_expected_result()
{
  uint32_t value = 0xd258301b;
  FPInfo info = FPUnpack(value, fPSCR, 32);

  TEST_ASSERT_EQUAL(info.realNumber,-2.32130003E11);
}


void test_FPRound_given_floating_point_value_above_should_get_()
{
  // uint16_t result = FPSingleToHalf(0xbf99999a, fPSCR);
  // uint32_t result = FPRound(3.213E-14, 16, fPSCR);
  FPInfo info = FPUnpack(0x999a, fPSCR, 16);
  printf("%e\n", info.realNumber );
  //-0.002735138
  // uint32_t result = FPHalfToSingle(0x999a, fPSCR);
  // printf("result : %x\n", result);
  // printf("fPSCR: %x\n", coreReg[fPSCR]);
  // TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR]);
}