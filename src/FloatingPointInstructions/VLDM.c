/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "VLDM.h"
#include "getAndSetBits.h"
#include "getMask.h"


/* VLDM Encoding T1 and T2
    
      Floating-point Load Multiple loads multiple extension registers from consecutive memory locations using an
      address from an ARM core register.
  
    VLDM{mode}<c> <Rn>{!}, <list>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  0  P  U  D  W  1|     Rn    |     Vd    | 1  0 1 X|      imm8     |

where :
            <mode>              The addressing mode:
            
                                    IA    Increment After. The consecutive addresses start at the address specified in <Rn>. This
                                          is the default and can be omitted. Encoded as P = 0, U = 1.
                                          
                                    DB    Decrement Before. The consecutive addresses end just before the address specified in
                                    
            <Rn>.               Encoded as P = 1, U = 0.
            
            <c>, <q>            See Standard assembler syntax fields on page A7-175.
            
            <size>              An optional data size specifier. If present, it must be equal to the size in bits, 32 or 64, of the registers
                                in <list>.
                                
            <Rn>                The base register. The SP can be used.
            !                   Causes the instruction to write a modified value back to <Rn>. This is required if <mode> == DB, and
                                is optional if <mode> == IA. Encoded as W = 1.
                                If ! is omitted, the instruction does not change <Rn> in this way. Encoded as W = 0.
                                
            <list>              The extension registers to be loaded, as a list of consecutively numbered registers, separated by
                                commas and surrounded by brackets. It is encoded in the instruction by setting D and Vd to specify
                                the first register in the list, and imm8 to the number of registers in the list. <list> must contain at
                                least one register.
*/
void VLDM(uint32_t instruction)
{ 
  uint32_t P = getBits(instruction,24,24);
  uint32_t U = getBits(instruction,23,23);
  uint32_t D = getBits(instruction,22,22);
  uint32_t W = getBits(instruction,21,21);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t imm32 = imm8 << 2;
  uint32_t singleOrDoublePrecision = getBits(instruction,8,8);
  uint32_t d;
  uint32_t regs;

  executeFPUChecking();
  
  if(singleOrDoublePrecision == 1)
  {
    d = (D << 4) | Vd;
    regs = imm8 / 2;
  }
  else
  {
    d = (Vd << 1) | D;
    regs = imm8;
  }
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeIAorDBForLoad(P, U, W, d, !singleOrDoublePrecision, regs, imm32, Rn);
    
    shiftITState();
  }
  else
    executeIAorDBForLoad(P, U, W, d, !singleOrDoublePrecision, regs, imm32, Rn);

  coreReg[PC] += 4;
}




void executeIAorDBForLoad(uint32_t P, uint32_t U, uint32_t W, uint32_t baseRegisterToWrite, uint32_t singleReg, uint32_t registerList, uint32_t imm32, uint32_t Rn)
{
  if(P == 0 && U == 1 && W == 0)
    loadFPMultiple(coreReg[Rn], baseRegisterToWrite, registerList, singleReg);
  else if(P == 0 && U == 1 && W == 1)
  {
    loadFPMultiple(coreReg[Rn], baseRegisterToWrite, registerList, singleReg);
    if(U == 1)
      coreReg[Rn] = coreReg[Rn] + imm32;
    else
      coreReg[Rn] = coreReg[Rn] - imm32;
  }
  else if(P == 1 && U == 0 && W == 1)
  {
    loadFPMultiple(coreReg[Rn] - imm32, baseRegisterToWrite, registerList, singleReg);
    if(U == 1)
      coreReg[Rn] = coreReg[Rn] + imm32;
    else
      coreReg[Rn] = coreReg[Rn] - imm32;
  }
  else if(P == U && W == 1)
    ThrowError();
}



void loadFPMultiple(uint32_t address, uint32_t d, uint32_t regs, uint32_t singleReg)
{
  int i;
  
  for(i = 0; i < regs ; i++)
  {
    if(singleReg == 1)
    {
      fpuSinglePrecision[d+i] = loadByteFromMemory(address, 4);
      address+=4;
    }
    else
    {
      uint64_t word1 = (uint64_t)loadByteFromMemory(address, 4);
      uint64_t word2 = (uint64_t)loadByteFromMemory(address+4, 4);
      
      if( bigEndian() )
        fpuDoublePrecision[d+i] = (word1 << 32) | word2;
      else
        fpuDoublePrecision[d+i] = (word2 << 32) | word1;
      
      address+=8;
    }
  }
}






