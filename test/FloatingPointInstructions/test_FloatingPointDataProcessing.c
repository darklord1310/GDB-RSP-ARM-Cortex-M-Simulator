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
#include "VSQRT.h"
#include "MiscellaneousInstructions.h"
#include "VADD.h"
#include "VSUB.h"
#include "VDIV.h"
#include "VCVTBandVCVTT.h"
#include "VCVTandVCVTR.h"
#include "VDIV.h"
#include "SaturateOperation.h"
#include "CException.h"

void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMLA 

// VMLA.F32 s0, s1, s2
void test_VMLA_given_s1_0x2DE12E13_and_s2_0x2D893814_should_get_s0_0x2e0cbccc()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  writeSinglePrecision(0, 0x2e0cbccc);
  
  writeInstructionToMemoryGivenByAddress(0xee000a81, 0x08000046);  // VMLA.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2de12e132e0cbccc, fpuDoublePrecision[0]);
  TEST_ASSERT_EQUAL(0x2e0cbccc, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VMLS.F32 s0, s1, s2
void test_VMLS_given_s1_0x2DE12E13_and_s2_0x2D893814_should_get_s0_0x9BF165F8()
{
  writeSinglePrecision(0, 0x00000000);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee000ac1, 0x08000046);  // VMLS.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x9BF165F8, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMOVImmediate

// VMOV.F32 s5, #0xbff80000
void test_VMOVImmediate_should_load_0xBFF80000_into_s5()
{
  
  writeInstructionToMemoryGivenByAddress(0xeeff2a0f, 0x08000046);  // VMOV.F32 s5, #0xbff80000
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xBFF80000, fpuSinglePrecision[5] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// VMOV.F32 s5, #0x40000000
void test_VMOVImmediate_should_load_0x40000000_into_s5()
{
  writeInstructionToMemoryGivenByAddress(0xeef02a00, 0x08000046);  // VMOV.F32 s5, #0x40000000
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x40000000, fpuSinglePrecision[5] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMOVRegister

// VMOV.F32 s6, s2
void test_VMOVRegister_should_load_value_of_s2_into_s6()
{
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xeeb03a41, 0x08000046);  // VMOV.F32 s6, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2D893814, fpuSinglePrecision[6] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}    

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNEG

    
// VNEG.F32 s7, s2
void test_VNEG_should_negate_the_value_of_s2_and_put_into_s7()
{
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xeef13a41, 0x08000046);  // VNEG.F32 s7, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xAD893814, fpuSinglePrecision[7] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// VNEG.F32 s7, s1
void test_VNEG_should_negate_the_value_of_s1_and_put_into_s7()
{
  writeSinglePrecision(1, 0x0DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeef13a60, 0x08000046);  // VNEG.F32 s7, s1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x8DE12E13, fpuSinglePrecision[7] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VABS
    
// VABS.F32 s8, s7
void test_VABS_given_s7_is_0x8DE12E13_should_get_s8_0x0DE12E13()
{
  writeSinglePrecision(7, 0x8DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb04ae3, 0x08000046);  // VABS.F32 s8, s7
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x0DE12E13, fpuSinglePrecision[8] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VSQRT
    
//test positive value
// VSQRT.F32 s8, s0
void test_VSQRT_given_s0_is_0x2E0CBCCC_should_get_s8_0x36BDD002()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  
  writeInstructionToMemoryGivenByAddress(0xeeb14ac0, 0x08000046);  // VSQRT.F32 s8, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x36BDD002, fpuSinglePrecision[8] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//test negative value
// VSQRT.F32 s8, s0
void test_VSQRT_given_s0_is_0x9BC16D9A_should_get_s8_0x7FC00000()
{
  writeSinglePrecision(0, 0x9BC16D9A);
  
  writeInstructionToMemoryGivenByAddress(0xeeb14ac0, 0x08000046);  // VSQRT.F32 s8, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();
  
  TEST_ASSERT_EQUAL(0x7FC00000, fpuSinglePrecision[8] );
  TEST_ASSERT_EQUAL(0x0000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//test negative value
// VSQRT.F32 s8, s0
void test_VSQRT_given_s0_is_0xBF800000_should_get_s8_0x7FC00000()
{
  writeSinglePrecision(0, 0xBF800000);
  
  writeInstructionToMemoryGivenByAddress(0xeeb14ac0, 0x08000046);  // VSQRT.F32 s8, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FC00000, fpuSinglePrecision[8] );
  TEST_ASSERT_EQUAL(0x0000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNMLA
    
// VNMLA.F32 s0, s1, s2
void test_VNMLA_given_s1_is_0x2DE12E13_s2_is_0x2D893814_s0_is_0x2E0CBCCC_should_get_s0_0xAE0CBCCC()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee100ac1, 0x08000046);  // VNMLA.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xAE0CBCCC, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNMLS

// VNMLS.F32 s0, s1, s2
void test_VNMLS_given_s1_is_0x2DE12E13_s2_is_0x2D893814_s0_is_0x2E0CBCCC_should_get_s0_0xAE0CBCCC()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee100a81, 0x08000046);  // VNMLS.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xAE0CBCCC, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNMUL
    
// VNMUL.F32 s0, s1, s2
void test_VNMUL_given_s1_is_0x2DE12E13_s2_is_0x2D893814_s0_is_0x2E0CBCCC_should_get_s0_0x9BF165F8()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee200ac1, 0x08000046);  // VNMUL.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x9BF165F8, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VADD

// VADD.F32 s0, s1, s2
void test_VADD_given_s1_is_0x2DE12E13_s2_is_0x2D893814_should_get_s0_0x2E3533148()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee300a81, 0x08000046);  // VADD.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2E353314, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}
    
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VSUB
  
// VSUB.F32 s0, s1, s2
void test_VSUB_given_s1_is_0x2DE12E13_s2_is_0x2D893814_should_get_s0_0x2D2FEBFE()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee300ac1, 0x08000046);  // VSUB.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2D2FEBFE, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VDIV

// VDIV.F32 s0, s1, s2
void test_VDIV_given_s1_is_0x2DE12E13_s2_is_0x2D893814_should_get_s0_0x2D2FEBFE()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee800a81, 0x08000046);  // VDIV.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x3FD20D20, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTB (converting from single to half)

//testing move to lower 16 bits, normal value
// VCVTB.F16.F32 s0, s2
void test_VCVTB_given_s2_is_0xbf99999a_should_get_s0_0xBCCDFFFF()
{
  writeSinglePrecision(2, 0xbf99999a);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30a41, 0x08000046);  // VCVTB.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;

  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FFFBCCD, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing move to lower 16 bits, -infinity
// VCVTB.F16.F32 s0, s2
void test_VCVTB_given_s2_is_0xff800000_should_get_s0_0x7FFFFC00()
{
  writeSinglePrecision(2, 0xff800000);
  uint32_t value = fpuSinglePrecision[2];
  writeInstructionToMemoryGivenByAddress(0xeeb30a41, 0x08000046);  // VCVTB.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FFFFC00, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing move to lower 16 bits, +infinity
// VCVTB.F16.F32 s0, s2
void test_VCVTB_given_s2_is_0x7f800000_should_get_s0_0x7FFF7C00()
{
  writeSinglePrecision(2, 0x7f800000);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30a41, 0x08000046);  // VCVTB.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FFF7C00, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing move to lower 16 bits, NaN
// VCVTB.F16.F32 s0, s2
void test_VCVTB_given_s2_is_0x7fffffff_should_get_s0_0x7FFF7FFF()
{
  writeSinglePrecision(2, 0x7fffffff);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30a41, 0x08000046);  // VCVTB.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FFF7FFF, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTT (converting from single to half)

//testing move to upper 16 bits, normal value
// VCVTT.F16.F32 s0, s2
void test_VCVTT_given_s2_is_0xbf99999a_should_get_s0_0xBCCDFFFF()
{
  writeSinglePrecision(2, 0xbf99999a);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30ac1, 0x08000046);  // VCVTT.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xBCCDFFFF, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing move to upper 16 bits, -infinity
// VCVTT.F16.F32 s0, s2
void test_VCVTT_given_s2_is_0xff800000_should_get_s0_0xFC00FFFF()
{
  writeSinglePrecision(2, 0xff800000);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30ac1, 0x08000046);  // VCVTT.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFC00FFFF, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing move to upper 16 bits, +infinity
// VCVTT.F16.F32 s0, s2
void test_VCVTT_given_s2_is_0x7f800000_should_get_s0_0x7C00FFFF()
{
  writeSinglePrecision(2, 0x7f800000);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30ac1, 0x08000046);  // VCVTT.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7C00FFFF, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing move to upper 16 bits, NaN
// VCVTT.F16.F32 s0, s2
void test_VCVTT_given_s2_is_0x7fffffff_should_get_s0_0x7FFFFFFF()
{
  writeSinglePrecision(2, 0x7fffffff);
  
  writeInstructionToMemoryGivenByAddress(0xeeb30ac1, 0x08000046);  // VCVTT.F16.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FFFFFFF, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTB (converting half to single)

//testing lower 16 bits, normal value
// VCVTB.F32.F16 s0, s2
void test_VCVTB_given_s2_is_0xbf99999a_should_get_s0_0xBB334000()
{
  writeSinglePrecision(2, 0xbf99999a);
  
  writeInstructionToMemoryGivenByAddress(0xeeb20a41, 0x08000046);  // VCVTB.F32.F16 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xBB334000, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing lower 16 bits, -infinity
// VCVTB.F32.F16 s0, s2
void test_VCVTB_given_s2_is_0xff80fc00_should_get_s0_0xFF800000()
{
  writeSinglePrecision(2, 0xff80fc00);

  writeInstructionToMemoryGivenByAddress(0xeeb20a41, 0x08000046);  // VCVTB.F32.F16 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFF800000, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing lower 16 bits, +infinity
// VCVTB.F32.F16 s0, s2
void test_VCVTB_given_s2_is_0x7f807C00_should_get_s0_0x7F800000()
{
  writeSinglePrecision(2, 0x7f807C00);
  
  writeInstructionToMemoryGivenByAddress(0xeeb20a41, 0x08000046);  // VCVTB.F32.F16 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7F800000, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTT (converting half to single)

//testing upper 16 bits, normal value
// VCVTT.F32.F16 s0, s2
void test_VCVTT_given_s2_is_0x09bcdb2d_should_get_s0_0xBFF32000()
{
  writeSinglePrecision(2, 0x09bcdb2d);
  
  writeInstructionToMemoryGivenByAddress(0xeeb20ac1, 0x08000046);  // VCVTB.F32.F16 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x39378000, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing upper 16 bits, -infinity
// VCVTT.F32.F16 s0, s2
void test_VCVTT_given_s2_is_0xfc00ff80_should_get_s0_0xFF800000()
{
  writeSinglePrecision(2, 0xfc00ff80);

  writeInstructionToMemoryGivenByAddress(0xeeb20ac1, 0x08000046);  // VCVTB.F32.F16 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFF800000, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//testing upper 16 bits, +infinity
// VCVTT.F32.F16 s0, s2
void test_VCVTT_given_s2_is_0x7C007f80_should_get_s0_0x7F800000()
{
  writeSinglePrecision(2, 0x7C007f80);
  
  writeInstructionToMemoryGivenByAddress(0xeeb20ac1, 0x08000046);  // VCVTB.F32.F16 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7F800000, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCMPT1

//VCMP.F32 s0, s1  (case: greater than)
void test_VCMP_given_greater_than_case_should_get_fPSCR_0x20000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb40a60, 0x08000046);  // VCMP.F32 s0, s1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x20000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



//VCMP.F32 s1, s0  (case: less than)
void test_VCMP_given_less_than_case_should_get_fPSCR_0x80000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeef40a40, 0x08000046);  // VCMP.F32 s1, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCMP.F32 s0, s0  (case: equal)
void test_VCMP_given_equal_case_should_get_fPSCR_0x60000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb40a40, 0x08000046);  // VCMP.F32 s0, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x60000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



//VCMP.F32 s0, s1  (case: unordered)
void test_VCMP_given_unordered_case_should_get_fPSCR_0x30000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x7FFFFFFF);
  
  writeInstructionToMemoryGivenByAddress(0xeeb40a60, 0x08000046);  // VCMP.F32 s0, s1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x30000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCMPE.F32 s0, s1  (case: greater than)
void test_VCMPE_given_greater_than_case_should_get_fPSCR_0x20000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb40ae0, 0x08000046);  // VCMP.F32 s0, s1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x20000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



//VCMPE.F32 s1, s0  (case: less than)
void test_VCMPE_given_less_than_case_should_get_fPSCR_0x80000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeef40ac0, 0x08000046);  // VCMPE.F32 s1, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCMPE.F32 s0, s0  (case: equal)
void test_VCMPE_given_equal_case_should_get_fPSCR_0x60000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb40ac0, 0x08000046);  // VCMPE.F32 s0, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x60000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



//VCMPE.F32 s0, s1  (case: unordered)
void test_VCMPE_given_unordered_case_should_get_fPSCR_0x30000001()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x7FFFFFFF);
  
  writeInstructionToMemoryGivenByAddress(0xeeb40ae0, 0x08000046);  // VCMPE.F32 s0, s1
  coreReg[PC] = 0x08000046;

  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x30000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCMPT2
    
//VCMP.F32 s0, #0.0  (case: greater than)
void test_VCMPT2_given_greater_than_case_should_get_fPSCR_0x20000000()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb50a40, 0x08000046);  // VCMP.F32 s0, #0.0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x20000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



//VCMP.F32 s0, #0.0  (case: less than)
void test_VCMPT2_given_less_than_case_should_get_fPSCR_0x80000000()
{
  writeSinglePrecision(0, 0x9bc16d9a);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb50a40, 0x08000046);  // VCMP.F32 s0, #0.0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x80000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCMP.F32 s0, #0.0  (case: equal)
void test_VCMPT2_given_equal_case_should_get_fPSCR_0x60000000()
{
  writeSinglePrecision(0, 0);
  writeSinglePrecision(1, 0x2DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb50a40, 0x08000046);  // VCMP.F32 s0, #0.0 
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x60000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



//VCMP.F32 s0, #0.0   (case: unordered)
void test_VCMPT2_given_unordered_case_should_get_fPSCR_0x30000000()
{
  writeSinglePrecision(0, 0x7FFFFFFF);
  writeInstructionToMemoryGivenByAddress(0xeeb50a40, 0x08000046);  // VCMP.F32 s0, #0.0 
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x30000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCMPE.F32 s0, #0.0  (case: unordered)
void test_VCMPT2_given_unordered_case_should_get_fPSCR_0x30000001()
{
  writeSinglePrecision(0, 0x7FFFFFFF);
  
  writeInstructionToMemoryGivenByAddress(0xeeb50ac0, 0x08000046);  // VCMPE.F32 s0, #0.0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x30000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTR  (unsigned cases)

//VCVTR.U32.F32 s0, s2
/*  Expected result:     s0 = 0x01
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVTR_unsigned_cases_given_s2_is_0x3F99999A_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0x3F99999A);
  
  writeInstructionToMemoryGivenByAddress(0xeebc0a41, 0x08000046);  // VCVTR.U32.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x01,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCVTR.U32.F32 s0, s2 (boundary case, value is larger than maximum 32bits value)
/*  Expected result:     s0 = 0xFFFFFFFF
 *                       fPSCR = 0x00000001
 *
 */
void test_VCVTR_unsigned_cases_given_s2_is_0x64F08EAF_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0x64F08EAF);
  
  writeInstructionToMemoryGivenByAddress(0xeebc0a41, 0x08000046);  // VCVTR.U32.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFFFFFFFF,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCVTR.U32.F32 s0, s2 (boundary case, value is slightly smaller than maximum 32bits value)
/*  Expected result:     s0 = 0xFFFFFF00
 *                       fPSCR = 0x00000000
 *
 */
void test_VCVTR_unsigned_cases_given_s2_is_0x40633333_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0x4F7FFFFF);
  
  writeInstructionToMemoryGivenByAddress(0xeebc0a41, 0x08000046);  // VCVTR.U32.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFFFFFF00,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTR  (signed cases)
    
//VCVTR.S32.F32 s0, s2 (boundary case, value is smaller than negative 32bits value)
/*  Expected result:     s0 = 0x80000000
 *                       fPSCR = 0x00000001
 *
 */
void test_VCVTR_signed_cases_given_s2_is_0xcf3a2714_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0xcf3a2714);
  
  writeInstructionToMemoryGivenByAddress(0xeebd0a41, 0x08000046);  // VCVTR.S32.F32 s0, s2
  coreReg[PC] = 0x08000046;

  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x80000000,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCVTR.S32.F32 s0, s2 (boundary case, value is larger than maximum 32bits value)
/*  Expected result:     s0 = 0x7FFFFFFF
 *                       fPSCR = 0x00000001
 *
 */
void test_VCVTR_signed_cases_given_s2_is_0x75765ef8_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0x75765ef8);
  
  writeInstructionToMemoryGivenByAddress(0xeebd0a41, 0x08000046);  // VCVTR.S32.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x7FFFFFFF,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000001, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCVTR.S32.F32 s0, s2 
/*  Expected result:     s0 = 0xFFFFFB31
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVTR_signed_cases_given_s2_is_0xc499e9fe_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0xc499e9fe);
  
  writeInstructionToMemoryGivenByAddress(0xeebd0a41, 0x08000046);  // VCVTR.S32.F32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFFFFFB31,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}
    
    
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVT (unsigned cases)

//VCVT.F32.U32 s0, s2 
/*  Expected result:     s0 = 0x4F4499EA
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVT_unsigned_cases_given_s2_is_0xc499e9fe_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0xc499e9fe);
  
  writeInstructionToMemoryGivenByAddress(0xeeb80a41, 0x08000046);  // VCVT.F32.U32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x4F4499EA,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVT (signed cases)
    
//VCVT.F32.S32 s0, s2 
/*  Expected result:     s0 = 0xCE6D9858
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVT_signed_cases_given_s2_is_0xc499e9fe_should_get_the_expected_result()
{
  writeSinglePrecision(2, 0xc499e9fe);
  
  writeInstructionToMemoryGivenByAddress(0xeeb80ac1, 0x08000046);  // VCVT.F32.S32 s0, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();
  
  TEST_ASSERT_EQUAL(0xCE6D9858,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVT (with frac bits, unsigned cases)
    
//VCVT.U32.F32 s0, s0, #6
/*  Expected result:     s0 = 0x000000C9
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVT_unsigned_cases_to_integer_given_s0_is_0x40491687_should_get_the_expected_result()
{
  writeSinglePrecision(0, 0x40491687);
  
  writeInstructionToMemoryGivenByAddress(0xeebf0acd, 0x08000046);  // VCVT.U32.F32 s0, s0, #6
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x000000C9,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCVT.F32.U32 s0, s0, #6
/*  Expected result:     s0 = 0x4C489779
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVT_unsigned_cases_to_floating_point_given_s0_is_0x40491687_should_get_the_expected_result()
{
  writeSinglePrecision(0, 0xc89778f0);
  
  writeInstructionToMemoryGivenByAddress(0xeebb0acd, 0x08000046);  // VCVT.F32.U32 s0, s0, #6
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x4C489779,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVT (with frac bits, signed cases)

//VCVT.S32.F32 s0, s0, #6
/*  Expected result:     s0 = 0xFED10E20
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVT_signed_cases_to_integer_given_s0_is_0xc89778f0_should_get_the_expected_result()
{
  writeSinglePrecision(0, 0xc89778f0);
  
  writeInstructionToMemoryGivenByAddress(0xeebe0acd, 0x08000046);  // VCVT.S32.F32 s0, s0, #6
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xFED10E20,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


//VCVT.F32.S32 s0, s0, #6
/*  Expected result:     s0 = 0xCB5DA21C
 *                       fPSCR = 0x00000010
 *
 */
void test_VCVT_signed_cases_to_floating_point_given_s0_is_0xc89778f0_should_get_the_expected_result()
{
  writeSinglePrecision(0, 0xc89778f0);
  
  writeInstructionToMemoryGivenByAddress(0xeeba0acd, 0x08000046);  // VCVT.F32.S32 s0, s0, #6
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xCB5DA21C,fpuSinglePrecision[0]);
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// void test()
// {
  // CEXCEPTION_T err;
  // printf("start\n");
  // Try
  // {
    // writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
    // (*Thumb32Table[0x1d6])(0xeebe0acd);
    //ARMSimulator(0xeebe0acd);
  // }
  // Catch(err)
  // {
    // printf("err: %i\n", err);
    // TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  // }
  
// }