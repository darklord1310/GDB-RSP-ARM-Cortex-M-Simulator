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



#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "LoadAndWriteMemory.h"
#include "assert.h"
#include "getMask.h"

#define   SP_INIT_VALUE   0x2001fffc    // for Coocox, keil is init to 0x20001000
#define   LR_INIT_VALUE   0xffffffff
#define   FPCCR_INIT_VALUE   0xC0000000   
#define   CPACR_INIT_VALUE   0x00000000
#define   FPDSCR_INIT_VALUE   0x03000000 //according to datasheet page 53
#define   AIRCR_INIT_VALUE   0xfa050000 //this value is confirmed with Keil
#define   CCR_INIT_VALUE   0x00000200   //this value is confirmed with Keil
       
/*
  This function will initialize the general status register, floating point status register and all the other core
  registers.

  
  Below shows the bit assignment of the general status register:
  
  31 30 29 28 27 26  25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |N |Z |C |V |Q|IT[1:0]|T|  Reserved  |  GE[3:0]  |      IT[7:2]    |      Reserved     |

  [31]	N
        Negative or less than flag:
                                      1 = result negative
                                      0 = result positive.

  [30]	Z
        Zero flag:
                    1 = result of 0
                    0 = nonzero result.

  [29]	C	(unsigned overflow)
        Carry or borrow flag:
                                1 = carry true or borrow false
                                0 = carry false or borrow true.

  [28]	V	(signed overflow)
        Overflow flag:
                        1 = overflow
                        0 = no overflow.

  [24]  T     indicator to show whether in ARM/Thumb state, 1 for Thumb, 0 for ARM

  IT[7:5]     encodes the base condition (that is, the top 3 bits of the condition specified by the IT instruction) for
              the current IT block, if any. It contains 0b000 when no IT block is active.

  IT[4:0]     encodes the number of instructions that are due to be conditionally executed, and whether the
              condition for each is the base condition code or the inverse of the base condition code.
              It contains 0b00000 when no IT block is active.
  
  
  
  
  
  
  
  Below shows the bits assignment of the floating point status register:
  
  31 30 29 28 27  26 25 24 23 22 21  -----    8  7  6 5  4   3   2   1   0
 |N |Z |C |V |  |AHP|DN|FZ|RMode|   Reserved   |IDC|   |IXC|UFC|OFC|DZC|IOC|



  N, bit[31]                Negative condition code flag. Floating-point comparison operations update this flag.
  
  Z, bit[30]                Zero condition code flag. Floating-point comparison operations update this flag.
  
  C, bit[29]                Carry condition code flag. Floating-point comparison operations update this flag.
  
  V, bit[28]                Overflow condition code flag. Floating-point comparison operations update this flag.
  
  Bit[27]                   Reserved.
  
  AHP, bit[26]              Alternative half-precision control bit:
                            0     IEEE 754-2008 half-precision format selected.
                            1     Alternative half-precision format selected.
                    
                            For more information see Floating-point half-precision formats on page A2-42.
                    
  DN, bit[25]               Default NaN mode control bit:
                            0     NaN operands propagate through to the output of a floating-point operation.
                            1     Any operation involving one or more NaNs returns the Default NaN.
                    
                            For more information, see NaN handling and the Default NaN on page A2-44.
                    
  FZ, bit[24]               Flush-to-zero mode control bit:
                            0     Flush-to-zero mode disabled. Behavior of the floating-point system is fully
                                  compliant with the IEEE 754 standard.
                            1     Flush-to-zero mode enabled.
                    
                            For more information, see Flush-to-zero on page A2-43.
                    
  RMode, bits[23:22]        Rounding Mode control field. The encoding of this field is:
                              0b00 Round to Nearest (RN) mode.
                              0b01 Round towards Plus Infinity (RP) mode.
                              0b10 Round towards Minus Infinity (RM) mode.
                              0b11 Round towards Zero (RZ) mode.
                              The specified rounding mode is used by almost all floating-point instructions.
  
  Bits[21:8]                Reserved.

  IDC, bit[7]               Input Denormal cumulative exception bit.
                            This bit is set to 1 to indicate that the corresponding exception has occurred since 0 was last
                            written to it. For more information about the exception indicated by this bit see
                            Floating-point exceptions on page A2-44.
                            
  Bits[6:5]                 Reserved.
  
  IXC, bit[4]               Inexact cumulative exception bit.
                            This bit is set to 1 to indicate that the corresponding exception has occurred since 0 was last
                            written to it. For more information about the exceptions indicated by this bit see
                            Floating-point exceptions on page A2-44.
                            
  UFC, bit[3]               Underflow cumulative exception bit.
                            This bit is set to 1 to indicate that the corresponding exception has occurred since 0 was last
                            written to it. For more information about the exceptions indicated by this bit see
                            Floating-point exceptions on page A2-44.
                            
  OFC, bit[2]               Overflow cumulative exception bit.
                            This bit is set to 1 to indicate that the corresponding exception has occurred since 0 was last
                            written to it. For more information about the exceptions indicated by this bit see
                            Floating-point exceptions on page A2-44.
                            
  DZC, bit[1]               Division by Zero cumulative exception bit.
                            This bit is set to 1 to indicate that the corresponding exception has occurred since 0 was last
                            written to it. For more information about the exceptions indicated by this bit see
                            Floating-point exceptions on page A2-44.
                            
  IOC, bit[0]               Invalid Operation cumulative exception bit.
                            This bit is set to 1 to indicate that the corresponding exception has occurred since 0 was last
                            written to it. For more information about the exceptions indicated by this bit see
                            Floating-point exceptions on page A2-44.
  
  
  Writes to the FPSCR can have side-effects on various aspects of processor operation. All of these side-effects are
  synchronous to the FPSCR write. This means they are guaranteed not to be visible to earlier instructions in the
  execution stream, and they are guaranteed to be visible to later instructions in the execution stream.
  
  
*/
void initCoreRegister()
{
  int i;
  
  //initialize ARM Core registers which are R0-R15 and APSCR and FPSCR
  for(i = 0; i < NUM_OF_CORE_Register; i++)
  {
    if(i == SP)
      coreReg[i] = SP_INIT_VALUE;
    else if(i == LR)
      coreReg[i] = LR_INIT_VALUE;
    else if(i == xPSR)
      coreReg[i] = 0x01000000;
    else
      coreReg[i] = 0x0;   //FPSCR
  }
  
  //initialize floating point double precision registers
  for(i = 0; i < NUM_OF_FPUD_Register; i++)
  {
    fpuDoublePrecision[i] = 0;
  }
  
  //initialize floating point single precision registers
  for(i = 0; i < NUM_OF_FPUS_Register; i++)
  {
    fpuSinglePrecision[i] = 0;
  }
  
  //initialize system control block (SCB) registers (initialize values refer to ARMRegisters.h)
  writeByteToMemory(FPCCR, FPCCR_INIT_VALUE, 4);
  writeByteToMemory(CPACR, CPACR_INIT_VALUE, 4);
  writeByteToMemory(FPDSCR, FPDSCR_INIT_VALUE, 4);    
  writeByteToMemory(AIRCR, AIRCR_INIT_VALUE, 4);     
  writeByteToMemory(CCR, CCR_INIT_VALUE, 4);
}



void writeSinglePrecision(int regNum, uint32_t valueToWrite)
{
  assert(regNum >= 0 );
  assert(regNum < 32);
  int DRegNumber;

  fpuSinglePrecision[regNum] = valueToWrite;            // update single precision register

  if(regNum == 0)                                       // update double precision register, get the equivalent reg number for double precision reg
    DRegNumber = 0;
  else
    DRegNumber = regNum / 2;

  if( (regNum+1) % 2 == 0)
  {
    uint64_t dummy = fpuSinglePrecision[regNum];
    uint64_t temp =  (dummy << 32) | (uint64_t)fpuSinglePrecision[regNum-1];
    fpuDoublePrecision[DRegNumber] = temp;
  }
  else
  {
    uint64_t dummy = fpuSinglePrecision[regNum+1];
    uint64_t temp =  (dummy << 32) | fpuSinglePrecision[regNum];
    fpuDoublePrecision[DRegNumber] = temp;
  }

}

void writeDoublePrecision(int regNum, uint64_t valueToWrite)
{
  assert(regNum >= 0 );
  assert(regNum < 16 );
  int SRegNumber;

  fpuDoublePrecision[regNum] = valueToWrite;      //update double precision register

  if(regNum == 0)                                 //update single precision register
    SRegNumber = 0;
  else
    SRegNumber = regNum * 2;
  fpuSinglePrecision[SRegNumber] = getBits(fpuDoublePrecision[regNum], 31, 0);
  fpuSinglePrecision[SRegNumber+1] = fpuDoublePrecision[regNum] >> 32;

}



void writeToCoreRegisters(int regNum, uint32_t valueToWrite)
{
  if(regNum == SP)
    coreReg[regNum] = setBits(valueToWrite,0b00,1,0);     //if the register to write is SP, mask off the last 2 bits
  else if(regNum == PC)
    coreReg[regNum] = setBits(valueToWrite,0b0,0,0);      //if the register to write is PC, mask off the last bit
  else
    coreReg[regNum] = valueToWrite;
}


/* StandardFPSCRValue()
// ====================
  bits(32) StandardFPSCRValue()
      return ‘00000’ : FPSCR<26> : ‘11000000000000000000000000’;
*/
uint32_t readSCBRegisters(uint32_t registerName)
{
  if(registerName == FPDSCR)
    return setBits(FPDSCR_INIT_VALUE, getBits(coreReg[fPSCR],26,26), 26,26);
  else
    return loadByteFromMemory(registerName, 4);
}


void writeSCBRegisters(uint32_t registerName, uint32_t valueToWrite)
{
  return writeByteToMemory(registerName, valueToWrite, 4);
}
