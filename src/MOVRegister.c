#include "MOVRegister.h"


/*  
  Move Register to Register Encoding T1 
        MOV<c> <Rd>,<Rm>
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0  0  0  1 | 1 0 |D|     Rm     |   Rd   |             unused                  |
    
  where:
            S       If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag
                    
            <c><q>  See Standard assembler syntax fields on page A6-7.
            
            <Rd>    The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.
                    
            <Rm>    The source register. This register can be the SP or PC.The instruction must not specify S if
                    <Rm> is the SP or PC.
                    
            D       is the fourth bit for the Rd, if the address can be reach using 3 bits D = 0, else D = 1
  
*/
void MOVRegisterToRegisterT1(uint32_t instruction)
{
	uint32_t Rm = getBits(instruction, 22, 19);
	uint32_t Rd = getBits(instruction, 18, 16);
  uint32_t D = getBits(instruction, 23, 23);
	
  Rd = ( D << 3 ) | Rd;     // this is to merge the D with Rd to make Rd becomes 4 bits
                            // Eg. new Rd = D Rd2 Rd1 Rd0

  executeMOVRegister(Rm, Rd, 0);

}



/*
  Move Register to Register Encoding T2 
        MOVS <Rd>,<Rm>
        
  Note :  This can only applicable to those registers lower than R7
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0  0  0  0  0  0  0  0  0 |   Rm   |   Rd   |               unused                |
  
  
  where:
            S       If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag
            
            <c><q>  See Standard assembler syntax fields on page A6-7.
            
            <Rd>    The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.
                    
            <Rm>    The source register. This register can be the SP or PC.The instruction must not specify S if
                    <Rm> is the SP or PC.
  
*/
void MOVRegisterToRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
  
  executeMOVRegister(Rm, Rd, 1);
}


void executeMOVRegister(uint32_t Rm, uint32_t Rd, uint32_t S)
{
  coreReg->reg[Rd].data = coreReg->reg[Rm].data;
  
  if(S == 1)
  {
    updateZeroFlag(coreReg->reg[Rd].data);
    updateNegativeFlag(coreReg->reg[Rd].data);
  }
}


/* Move From Register To Register Encoding T3

MOV{S}<c>.W <Rd>,<Rm>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0 1 |0  1| 0  0  1  0 |S| 1  1  1  1 |0  0  0  0 |    Rd   |0 0 0 0|  Rm   |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag
                    
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register.
          
          <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                    encoding T1 and 0-65535 for encoding T3. See Modified immediate constants in Thumb
                    instructions on page A5-15 for the range of allowed values for encoding T2.
                    
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the MOVW syntax)
*/
/*
void MOVRegisterToRegisterT3(uint32_t instruction, CoreRegister *coreReg)
{
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t i = getBits(instruction, 20, 20);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  
  coreReg->reg[Rd].data = coreReg->reg[Rm].data;
  
  if(statusFlag == 1)
    updateStatusRegister(coreReg->reg[Rd].data);
  
}
*/