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
void test_VMLA_given_s1_0x2DE12E13_and_s2_0x2D893814_should_get_s0_0x1BF165F8()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  writeSinglePrecision(0, 0x2e0cbccc);
  
  writeInstructionToMemoryGivenByAddress(0xee000a81, 0x08000046);  // VMLA.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  armStep();

  TEST_ASSERT_EQUAL(0x2de12e131bf165f8, fpuDoublePrecision[0]);
  TEST_ASSERT_EQUAL(0x1BF165F8, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VMLS.F32 s0, s1, s2
void test_VMLS_given_s1_0x2DE12E13_and_s2_0x2D893814_should_get_s0_0x9BF165F8()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee000ac1, 0x08000046);  // VMLS.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
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
  
  armStep();

  TEST_ASSERT_EQUAL(0x2D893814, fpuSinglePrecision[6] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}    

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNeg


/*

uint32_t FPMul(uint32_t noOfBits, uint32_t value1, uint32_t value2, bool fpscr_controlled)
{
  FPInfo value1Info, value2Info;
  
  if(fpscr_controlled == true)
    fpscr_val = coreReg[fPSCR];
  else
    fpscr_val = setBits(0b00000011000000000000000000000000, getBits(coreReg[fPSCR],26,26), 26, 26);
  
  value1Info = FPUnpack(noOfBits,value1,fpscr_val);
  value2Info = FPUnpack(noOfBits,value2,fpscr_val);
  
}



FPInfo FPUnpack(uint32_t noOfBits, uint32_t FPValue, uint32_t FPSCRValue)
{
  FPInfo info;
  uint32_t sign;
  uint32_t exp16;
  uint32_t frac16;
  uint32_t exp32;
  uint32_t frac32;
  uint32_t exp64;
  uint32_t frac64;
  
  if(noOfBits == 16)
  {
    sign = getBits(FPValue,15,15);
    exp16 = getBits(FPValue,14,10);
    frac16 = getBits(FPValue,9,0);
    
    if(exp16 == 0)
    {
      if(frac16 == 0)
      {
        info.type = FPTYPE_ZERO;
        info.realNumber = 0.0;
      }
      else
      {
        info.type = FPTYPE_NONZERO;
        info.realNumber = ( pow(2.0, -14) ) * ( frac16 * (pow(2.0,-10))) ;
      }
    }
    else if(exp16 == 1 && getBits(FPValue,26,26) == 0)
    {
      if(frac16 == 0)
      {
        info.type = FPTYPE_INFINITY;
        info.realNumber = pow(2.0,1000000);
      }
      else
      {
        if( getBits(frac16,9,9) == 1)
          info.type = FPTYPE_QNAN;
        else
          info.type = FPTYPE_SNAN;
        
        info.realNumber = 0.0;
      }
    }
    else
    {
      info.type = FPTYPE_NONZERO;
      info.realNumber = ( pow(2.0, exp16-15 ) ) * (1.0 + frac16 * (pow(2.0,-10)));
    }
  }
  else if(noOfBits == 32)
  {
    sign = getBits(FPValue,31,31);
    exp32 = getBits(FPValue,30,23);
    frac32 = getBits(FPValue,22,0);
    
    if(exp32 == 0)
    {
      if(frac32 == 0 || getBits(FPValue,24,24) == 1)
      {
        info.type = FPTYPE_ZERO;
        info.realNumber = 0.0;
        if(frac32 != 0)
          FPProcessException();
      }
      else
      {
        info.type = FPTYPE_NONZERO;
        info.realNumber = ( pow(2.0,-126) * frac32 * poww(2.0,-23) );
      }
    }
    else if(exp32 == 1)
    {
      if(frac32 == 0)
      {
        info.type = FPTYPE_INFINITY;
        info.realNumber = pow(2.0,1000000);
      }
      else
      {
        if(getBits(frac32,22,22) == 1)
          info.type = FPTYPE_QNAN;
        else
          info.type = FPTYPE_SNAN;
        value = 0.0;
      }
    }
    else
    {
      info.type = FPTYPE_NONZERO;
      info.realNumber = pow(2.0,exp32-127) * (1.0 + (frac32 * pow(2.0,-23) ) );
    }
  }
  else
  {
    sign = getBits(FPValue,63,63);
    exp64 = getBits(FPValue,62,52);
    frac64 = getBits(FPValue,51,0);
    
    if(exp64 == 0)
    {
      if(frac64 == 0 || getBits(FPValue,24,24) == 1)
      {
        info.type = FPTYPE_ZERO;
        info.realNumber = 0.0;
        if(frac64 != 0)
          FPProcessException();
      }
      else
      {
        info.type = FPTYPE_NONZERO;
        info.realNumber = pow(2.0,-1022) * frac64 * pow(2.0,-52) ;
      }
    }
    else if(exp64 == 1)
    {
      if(frac64 == 0)
      {
        info.type = FPTYPE_INFINITY;
        info.realNumber = pow(2.0,1000000);
      }
      else
      {
        if( getBits(frac64,51,51) == 1)
          info.type = FPTYPE_QNAN;
        else
          info.type = FPTYPE_SNAN;
        
        info.realNumber = 0.0;
      }
    }
    else
    {
      info.type = FPTYPE_NONZERO;
      info.realNumber = pow(2.0,exp64-1023) * (1.0 + frac64 * pow(2.0,-52)) ;
    }
  }
  
  if(sign == 1)
    info.realNumber = ~info.realNumber;
  
  info.signBit = sign;
  
  return info;
}


void FPProcessException()
{
  
}
*/


