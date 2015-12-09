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
