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


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Literal T2

//test U is equal to 1
// LDR.W r0,[PC,#10]
void test_LDRLiteralT2_given_instruction_0xf8df000a_should_load_0xf04f3122_into_R0()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000016) ] = 0x22;
  memoryBlock[ virtualMemToPhysicalMem(0x08000017) ] = 0x31;
  memoryBlock[ virtualMemToPhysicalMem(0x08000018) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000019) ] = 0xf0;
  writeInstructionToMemoryGivenByAddress(0xf8df000a, 0x08000008);  // LDR.W r0,[PC,#10]
  coreReg[PC] = 0x08000008;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xf04f3122, coreReg[0]);
  TEST_ASSERT_EQUAL(0x0800000C, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test U is equal to 0
// LDR.W r0,[PC,#-10]
void test_LDRLiteralT2_given_instruction_0xf85f000a_should_load_0x00092000_into_R0()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x08000004) ] = 0x09;
  memoryBlock[ virtualMemToPhysicalMem(0x08000005) ] = 0x00;
  writeInstructionToMemoryGivenByAddress(0xf85f000a, 0x08000008);  // LDR.W r0,[PC,#-10]
  coreReg[PC] = 0x08000008;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x00092000, coreReg[0]);
  TEST_ASSERT_EQUAL(0x0800000C, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Immediate T3

//test minimum index, 0
// LDR.W r1,[r0,#0]
void test_LDRImmediateT3_given_instruction_0xf8d01000_should_load_0xf05f1000_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000010) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000011) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x08000012) ] = 0x5f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000013) ] = 0xf0;
  coreReg[0] = 0x08000010;
  writeInstructionToMemoryGivenByAddress(0xf8d01000, 0x0800000e);  // LDR.W r1,[r0,#0]
  coreReg[PC] = 0x0800000e;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0xf05f1000, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test maximum index, 4095
// LDR.W r1,[r0,#4095]
void test_LDRImmediateT3_given_instruction_0xf8d01fff_should_load_0x08000007_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000068) ] = 0x07;
  memoryBlock[ virtualMemToPhysicalMem(0x08000069) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006a) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006b) ] = 0x08;
  coreReg[0] = 0x07fff069;
  writeInstructionToMemoryGivenByAddress(0xf8d01fff, 0x0800000e);  // LDR.W r1,[r0,#4095]
  coreReg[PC] = 0x0800000e;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x08000007, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test any intermediate index, 500
// LDR.W r1,[r0,#500]
void test_LDRImmediateT3_given_instruction_0xf8d011f4_should_load_0x08000007_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000068) ] = 0x07;
  memoryBlock[ virtualMemToPhysicalMem(0x08000069) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006a) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006b) ] = 0x08;
  coreReg[0] = 0x7fffe74;
  writeInstructionToMemoryGivenByAddress(0xf8d011f4, 0x0800000e);  // LDR.W r1,[r0,#500]
  coreReg[PC] = 0x0800000e;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x08000007, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Rt is PC
// LDR.W PC,[r0,#500]
void test_LDRImmediateT3_given_instruction_0xf8d0f1f4_should_load_0x08000012_into_PC()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000068) ] = 0x12;
  memoryBlock[ virtualMemToPhysicalMem(0x08000069) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006a) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800006b) ] = 0x08;
  coreReg[0] = 0x7fffe74;
  writeInstructionToMemoryGivenByAddress(0xf8d0f1f4, 0x0800000e);  // LDR.W PC,[r0,#500]
  coreReg[PC] = 0x0800000e;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x08000012, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Immediate T4


//test offset addressing
// LDR.W r1,[r0,#-20]
void test_LDRImmediateT4_given_instruction_0xf8501c14_should_load_0x480a3cdd_into_R1()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000038) ] = 0xdd;
  memoryBlock[ virtualMemToPhysicalMem(0x08000039) ] = 0x3c;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003a) ] = 0x0a;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003b) ] = 0x48;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf8501c14, 0x0800003c);  // LDR.W r1,[r0,-#20]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x480a3cdd, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Pre-indexed addressing, negative index
// LDR.W r1,[r0,#-20]!
void test_LDRImmediateT4_given_instruction_0xf8501d14_should_load_0x480a3cdd_into_R1_and_R0_is_0x08000038()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000038) ] = 0xdd;
  memoryBlock[ virtualMemToPhysicalMem(0x08000039) ] = 0x3c;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003a) ] = 0x0a;
  memoryBlock[ virtualMemToPhysicalMem(0x0800003b) ] = 0x48;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf8501d14, 0x0800003c);  // LDR.W r1,[r0,-#20]!
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x480a3cdd, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000038, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Pre-indexed addressing, positive index
// LDR.W r1,[r0,#20]!
void test_LDRImmediateT4_given_instruction_0xf8501f14_should_load_0x0800004c_into_R1_and_R0_is_0x08000060()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4c;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf8501f14, 0x0800003c);  // LDR.W r1,[r0,#20]!
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x08000060, coreReg[0]);
  TEST_ASSERT_EQUAL(0x0800004c, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test Post-indexed addressing, negative index
// LDR.W r1,[r0], #-20
void test_LDRImmediateT4_given_instruction_0xf8501914_should_load_0x2fc84414_into_R1_and_R0_is_0x08000038()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x0800004c) ] = 0x14;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004d) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004e) ] = 0xc8;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004f) ] = 0x2f;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf8501914, 0x0800003c);  // LDR.W r1,[r0], #-20
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2fc84414, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000038, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Post-indexed addressing, positive index
// LDR.W r1,[r0], #20
void test_LDRImmediateT4_given_instruction_0xf8501b14_should_load_0x2fc84414_into_R1_and_R0_is_0x08000060()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x0800004c) ] = 0x14;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004d) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004e) ] = 0xc8;
  memoryBlock[ virtualMemToPhysicalMem(0x0800004f) ] = 0x2f;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf8501b14, 0x0800003c);  // LDR.W r1,[r0], #20
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();

  TEST_ASSERT_EQUAL(0x2fc84414, coreReg[1]);
  TEST_ASSERT_EQUAL(0x08000060, coreReg[0]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test Rt is PC
// LDR.W PC,[r0], #20
void test_LDRImmediateT4_given_instruction_0xf850ff14_should_load_0x0800004C_into_PC_and_R0_is_0x08000060()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4c;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[0] = 0x800004c;
  writeInstructionToMemoryGivenByAddress(0xf850ff14, 0x0800003c);  // LDR.W r1,[r0], #20
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x08000060, coreReg[0]);
  TEST_ASSERT_EQUAL(0x0800004C, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



//test if bit 0 and 1 of the address is not 0 should throw error
// LDR.W PC,[r0], #20
void test_LDRImmediateT4_given_instruction_0xf850ff14_should_throw_error()
{
  //create test fixture
  CEXCEPTION_T err;
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[0] = 0x800004f;
  writeInstructionToMemoryGivenByAddress(0xf850ff14, 0x0800003c);  // LDR.W r1,[r0], #20
  coreReg[PC] = 0x0800003c;
  
  //test
  Try{
    
    armStep();
    TEST_FAIL_MESSAGE("Expect to throw here\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
  }
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDR Register T2

//test with minimum shifting, 0
// ldr.w r5, [r4, r1, lsl #0]
void test_LDRRegisterT2_given_instruction_0xf8545001_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x08000060;
  writeInstructionToMemoryGivenByAddress(0xf8545001, 0x0800003c);  // ldr.w r5, [r4, r1, lsl #0]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x0800004f, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test with maximum shifting, 3
// ldr.w r5, [r4, r1, lsl #3]
void test_LDRRegisterT2_given_instruction_0xf8545031_should_load_0x0800004f_into_r5()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x08000060) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000061) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000062) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000063) ] = 0x08;
  coreReg[4] = 0x0;
  coreReg[1] = 0x100000c;
  writeInstructionToMemoryGivenByAddress(0xf8545031, 0x0800003c);  // ldr.w r5, [r4, r1, lsl #3]
  coreReg[PC] = 0x0800003c;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0x0800004f, coreReg[5]);
  TEST_ASSERT_EQUAL(0x08000040, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDRT Register T1

//test ldrt.w LR, [r0, #8]
void test_LDRTT1_given_instruction_0xf850ee08_should_load_0xf850bf00_into_LR()
{
  //create test fixture
  memoryBlock[ virtualMemToPhysicalMem(0x00000008) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x00000009) ] = 0xbf;
  memoryBlock[ virtualMemToPhysicalMem(0x0000000a) ] = 0x50;
  memoryBlock[ virtualMemToPhysicalMem(0x0000000b) ] = 0xf8;
  coreReg[0] = 0x00000000;
  writeInstructionToMemoryGivenByAddress(0xf850ee08, 0x0800000a);  // ldrt.w LR, [r0, #8]
  coreReg[PC] = 0x0800000a;
  
  //test
  armStep();
  
  TEST_ASSERT_EQUAL(0xf850bf00, coreReg[LR]);
  TEST_ASSERT_EQUAL(0x0800000e, coreReg[PC]);
  TEST_ASSERT_EQUAL(0x01000000, coreReg[xPSR]);
}


//test if Rt is PC
// ldrt.w PC, [r0, #8]
void test_LDRTT1_given_instruction_0xf850fe08_should_throw_error()
{
  //create test fixture
  CEXCEPTION_T err;
  coreReg[0] = 0x800004f;
  writeInstructionToMemoryGivenByAddress(0xf850fe08, 0x0800003c);  // ldrt.w PC, [r0, #8]
  coreReg[PC] = 0x0800003c;
  
  //test
  Try{
    armStep();
    TEST_FAIL_MESSAGE("Expect to throw here\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
  }
}



//test if Rt is SP
// ldrt.w SP, [r0, #8]
void test_LDRTT1_given_instruction_0xf850de08_should_throw_error()
{
  //create test fixture
  CEXCEPTION_T err;
  coreReg[0] = 0x800004f;
  writeInstructionToMemoryGivenByAddress(0xf850de08, 0x0800003c);  // ldrt.w SP, [r0, #8]
  coreReg[PC] = 0x0800003c;
  
  //test
  Try{
    armStep();
    TEST_FAIL_MESSAGE("Expect to throw here\n");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL(UsageFault, err);
  }
}
