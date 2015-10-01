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


#include "LDRImmediate.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "ErrorSignal.h"
#include "ADR.h"
#include "LoadAndWriteMemory.h"
#include "ExceptionObject.h"


/*Load Register(Immediate) Encoding T1

   LDR<c> <Rt>, [<Rn>{,#<imm5>}]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  1   0  1|      imm5    |    Rn  |   Rt   |                unused               |

  where:
              <c><q>            See Standard assembler syntax fields on page A6-7.

              <Rt>              Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                                be the PC, provided the instruction is either outside an IT block or the last instruction of an
                                IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.

              <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                                LDR (literal) on page A6-90.

              +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                                (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                                instructions are generated for #0 and #-0.

              <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                                address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                                4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                                any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                                omitted, meaning an offset of 0.

*/
void LDRImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction,26,22);
  uint32_t Rn   = getBits(instruction,21,19);
  uint32_t Rt   = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  4*imm5;
      coreReg[Rt] = loadByteFromMemory(address, 4);                        //load a word from the address and store it into the register
    }

    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + 4*imm5;
    coreReg[Rt] = loadByteFromMemory(address, 4);                        //load a word from the address and store it into the register
  }

  coreReg[PC] += 2;
}




/*Load Register(Immediate) Encoding T2

   LDR<c> <Rt>,[SP{,#<imm8>}]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  0   1  1|   Rt   |          imm8         |                unused               |

  where:
              <c><q>            See Standard assembler syntax fields on page A6-7.

              <Rt>              Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                                be the PC, provided the instruction is either outside an IT block or the last instruction of an
                                IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.

              <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                                LDR (literal) on page A6-90.

              +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                                (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                                instructions are generated for #0 and #-0.

              <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                                address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                                4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                                any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                                omitted, meaning an offset of 0.

*/
void LDRImmediateT2(uint32_t instruction)
{ 
  uint32_t imm8 = getBits(instruction,23,16);
  uint32_t Rt   = getBits(instruction,26,24);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[SP] +  4*imm8;
      coreReg[Rt] = loadByteFromMemory(address, 4);                        //load a word from the address and store it into the register
    }

    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[SP] + 4*imm8;
    coreReg[Rt] = loadByteFromMemory(address, 4);                        //load a word from the address and store it into the register
  }

  coreReg[PC] += 2;
}


/*Load Register(Immediate) Encoding T3

   LDR<c>.W <Rt>,[<Rn>{,#<imm12>}]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1   1  1| 0  0| 0  1  1  0  1|     Rn    |     Rt    |          imm12          |

  where:
              <c><q>            See Standard assembler syntax fields on page A6-7.

              <Rt>              Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                                be the PC, provided the instruction is either outside an IT block or the last instruction of an
                                IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.

              <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                                LDR (literal) on page A6-90.

              +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                                (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                                instructions are generated for #0 and #-0.

              <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                                address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                                4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                                any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                                omitted, meaning an offset of 0.

*/
void LDRImmediateT3(uint32_t instruction)
{
  uint32_t address;
  uint32_t imm12 = getBits(instruction,11,0);
  uint32_t Rn   = getBits(instruction,19,16);
  uint32_t Rt   = getBits(instruction,15,12);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      address = coreReg[Rn] + imm12;
      if(Rt == PC)
      {
        if( getBits(address,1,0) == 0b00)
          coreReg[Rt] = loadByteFromMemory(address, 4);
        else
        {
          //placePCtoVectorTable(UsageFault);
          ThrowError();
        }
      }
      else
        coreReg[Rt] = loadByteFromMemory(address, 4);
    }

    shiftITState();
  }
  else
  {
    address = coreReg[Rn] + imm12;
    if(Rt == PC)
    {
      if( getBits(address,1,0) == 0b00)
        coreReg[Rt] = loadByteFromMemory(address, 4);
      else
      {
        //placePCtoVectorTable(UsageFault);
        ThrowError();
      }
    }
    else
      coreReg[Rt] = loadByteFromMemory(address, 4);
  }

  if(Rt != PC)
    coreReg[PC] += 4;
}



/*Load Register(Immediate) Encoding T4

   LDR<c> <Rt>,[<Rn>,#-<imm8>]
   LDR<c> <Rt>,[<Rn>],#+/-<imm8>
   LDR<c> <Rt>,[<Rn>,#+/-<imm8>]!

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1   1  1| 0  0| 0  0  1  0  1|     Rn    |     Rt    | 1| P U W|     imm8      |

  where:
              <c><q>            See Standard assembler syntax fields on page A6-7.

              <Rt>              Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                                be the PC, provided the instruction is either outside an IT block or the last instruction of an
                                IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.

              <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                                LDR (literal) on page A6-90.

              +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                                (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                                instructions are generated for #0 and #-0.

              <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                                address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                                4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                                any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                                omitted, meaning an offset of 0.

*/
void LDRImmediateT4(uint32_t instruction)
{
  uint32_t address;
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t Rn   = getBits(instruction,19,16);
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t P = getBits(instruction,10,10);
  uint32_t U = getBits(instruction,9,9);
  uint32_t W = getBits(instruction,8,8);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(U == 1)
        address = coreReg[Rn] +  imm8;
      else
        address = coreReg[Rn] -  imm8;

      if(P == 1 && W == 0)
      {
        if(Rt == PC)
        {
          if( getBits(address,1,0) == 0b00)
          {
            coreReg[Rt] = loadByteFromMemory(address, 4);
            coreReg[Rt] = coreReg[Rt] & 0xfffffffe;
            // uint32_t bit0 = getBits(coreReg[Rt], 0, 0);
            // coreReg[xPSR] = setBits(coreReg[xPSR], bit0, 24, 24);   // EPSR.T = coreReg[Rt]<0>
          }
          else
          {
            //placePCtoVectorTable(UsageFault);
            ThrowError();
          }
        }
        else
          coreReg[Rt] = loadByteFromMemory(address, 4);
      }
      else if(P == 1 && W == 1)
      {
        if(Rt != PC)
        {
          coreReg[Rt] = loadByteFromMemory(address, 4);
          coreReg[Rn] = address;
        }
        else
        {
          if( getBits(address,1,0) == 0b00)
          {
            coreReg[Rt] = loadByteFromMemory(address, 4);
            coreReg[Rt] = coreReg[Rt] & 0xfffffffe;
            // uint32_t bit0 = getBits(coreReg[Rt], 0, 0);
            // coreReg[xPSR] = setBits(coreReg[xPSR], bit0, 24, 24);   // EPSR.T = coreReg[Rt]<0>
            coreReg[Rn] = address;
          }
          else
          {
            //placePCtoVectorTable(UsageFault);
            ThrowError();
          }
        }
      }
      else if(P == 0 && W == 1)
      {
        if(Rt != PC)
        {
          coreReg[Rt] = loadByteFromMemory(coreReg[Rn], 4);
          coreReg[Rn] = address;
        }
        else
        {
          if( getBits(coreReg[Rn],1,0) == 0b00)
          {
            coreReg[Rt] = loadByteFromMemory(coreReg[Rn], 4);
            coreReg[Rt] = coreReg[Rt] & 0xfffffffe;
            // uint32_t bit0 = getBits(coreReg[Rt], 0, 0);
            // coreReg[xPSR] = setBits(coreReg[xPSR], bit0, 24, 24);   // EPSR.T = coreReg[Rt]<0>
            coreReg[Rn] = address;
          }
          else
          {
            //placePCtoVectorTable(UsageFault);
            ThrowError();
          }
        }
      }
    }
    shiftITState();
  }
  else
  {
      if(U == 1)
        address = coreReg[Rn] +  imm8;
      else
        address = coreReg[Rn] -  imm8;

      if(P == 1 && W == 0)
      {
        if(Rt == PC)
        {
          if( getBits(address,1,0) == 0b00)
          {
            coreReg[Rt] = loadByteFromMemory(address, 4);
            coreReg[Rt] = coreReg[Rt] & 0xfffffffe;
            // uint32_t bit0 = getBits(coreReg[Rt], 0, 0);
            // coreReg[xPSR] = setBits(coreReg[xPSR], bit0, 24, 24);   // EPSR.T = coreReg[Rt]<0>
          }
          else
          {
            //placePCtoVectorTable(UsageFault);
            ThrowError();
          }
        }
        else
          coreReg[Rt] = loadByteFromMemory(address, 4);
      }
      else if(P == 1 && W == 1)
      {
        if(Rt != PC)
        {
          coreReg[Rt] = loadByteFromMemory(address, 4);
          coreReg[Rn] = address;
        }
        else
        {
          if( getBits(address,1,0) == 0b00)
          {
            coreReg[Rt] = loadByteFromMemory(address, 4);
            coreReg[Rt] = coreReg[Rt] & 0xfffffffe;
            // uint32_t bit0 = getBits(coreReg[Rt], 0, 0);
            // coreReg[xPSR] = setBits(coreReg[xPSR], bit0, 24, 24);   // EPSR.T = coreReg[Rt]<0>
            coreReg[Rn] = address;
          }
          else
          {
            //placePCtoVectorTable(UsageFault);
            ThrowError();
          }
        }
      }
      else if(P == 0 && W == 1)
      {
        if(Rt != PC)
        {
          coreReg[Rt] = loadByteFromMemory(coreReg[Rn], 4);
          coreReg[Rn] = address;
        }
        else
        {
          if( getBits(coreReg[Rn],1,0) == 0b00)
          {
            coreReg[Rt] = loadByteFromMemory(coreReg[Rn], 4);
            coreReg[Rt] = coreReg[Rt] & 0xfffffffe;
            // uint32_t bit0 = getBits(coreReg[Rt], 0, 0);
            // coreReg[xPSR] = setBits(coreReg[xPSR], bit0, 24, 24);   // EPSR.T = coreReg[Rt]<0>
            coreReg[Rn] = address;
          }
          else
          {
            //placePCtoVectorTable(UsageFault);
            ThrowError();
          }
        }
      }
  }

  if(Rt != PC)
    coreReg[PC] += 4;
}



/*Load Register Byte (immediate) Encoding T1

   LDRB<c> <Rt>,[<Rn>{,#<imm5>}]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  1   1  1|      imm5    |    Rn  |   Rt   |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.

            <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                              LDRB (literal) on page A6-96.

            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. The range of allowed values is 0-31 for encoding T1, 0-4095 for encoding T2, and
                              0-255 for encoding T3. For the offset addressing syntax, <imm> can be omitted, meaning an
                              offset of 0.

                              The pre-UAL syntax LDR<c>B is equivalent to LDRB<c>.

*/
void LDRBImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction,26,22);
  uint32_t Rn   = getBits(instruction,21,19);
  uint32_t Rt   = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  imm5;
      coreReg[Rt] = loadByteFromMemory(address, 1);
    }

    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + imm5;
    coreReg[Rt] = loadByteFromMemory(address, 1);
  }


  coreReg[PC] += 2;
}



/*Load Register Byte (immediate) Encoding T2

   LDRB<c>.W <Rt>,[<Rn>{,#<imm12>}]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  1  0  0  1|     Rn    |     Rt    |         imm12           |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.

            <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                              LDRB (literal) on page A6-96.

            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. The range of allowed values is 0-31 for encoding T1, 0-4095 for encoding T2, and
                              0-255 for encoding T3. For the offset addressing syntax, <imm> can be omitted, meaning an
                              offset of 0.

                              The pre-UAL syntax LDR<c>B is equivalent to LDRB<c>.

*/
void LDRBImmediateT2(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm12 = getBits(instruction,11,0);
  uint32_t address = coreReg[Rn] + imm12;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = loadByteFromMemory(address, 1);

    shiftITState();
  }
  else
    coreReg[Rt] = loadByteFromMemory(address, 1);

  coreReg[PC] += 4;

}



/*Load Register Byte (immediate) Encoding T3

   LDRB<c> <Rt>,[<Rn>,#-<imm8>]
   LDRB<c> <Rt>,[<Rn>],#+/-<imm8>
   LDRB<c> <Rt>,[<Rn>,#+/-<imm8>]!

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  0  0  0  1|     Rn    |     Rt    | 1| P|U|W|     imm8      |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.

            <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                              LDRB (literal) on page A6-96.

            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. The range of allowed values is 0-31 for encoding T1, 0-4095 for encoding T2, and
                              0-255 for encoding T3. For the offset addressing syntax, <imm> can be omitted, meaning an
                              offset of 0.

                              The pre-UAL syntax LDR<c>B is equivalent to LDRB<c>.

*/
void LDRBImmediateT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;

  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a LDRBT instruction
    LDRBT(instruction);

  int check = isOffPostOrPreIndex(P,W);

  if(check == UNDEFINED)
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
  }

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        coreReg[Rt] = loadByteFromMemory(address,1);
      else if(check == PREINDEX)
      {
        coreReg[Rt] = loadByteFromMemory(address,1);
        coreReg[Rn] = address;
      }
      else
      {
        coreReg[Rt] = loadByteFromMemory(coreReg[Rn],1);
        coreReg[Rn] = address;
      }
    }

    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      coreReg[Rt] = loadByteFromMemory(address,1);
    else if(check == PREINDEX)
    {
      coreReg[Rt] = loadByteFromMemory(address,1);
      coreReg[Rn] = address;
    }
    else
    {
      coreReg[Rt] = loadByteFromMemory(coreReg[Rn],1);
      coreReg[Rn] = address;
    }
  }

  coreReg[PC] += 4;
}


/*Load Register Halfword (immediate) Encoding T1

  LDRH<c> <Rt>,[<Rn>{,#<imm5>}]

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |1  0  0   0  1|      imm5    |    Rn  |   Rt   |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.

            <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                              LDRH (literal) on page A6-96.

            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. The range of allowed values is 0-31 for encoding T1, 0-4095 for encoding T2, and
                              0-255 for encoding T3. For the offset addressing syntax, <imm> can be omitted, meaning an
                              offset of 0.

                              The pre-UAL syntax LDR<c>B is equivalent to LDRB<c>.

*/
void LDRHImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction,26,22);
  uint32_t Rn   = getBits(instruction,21,19);
  uint32_t Rt   = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  2*imm5;
      coreReg[Rt] = loadByteFromMemory(address, 2);
    }

    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + 2*imm5;
    coreReg[Rt] = loadByteFromMemory(address, 2);
  }

  coreReg[PC] += 2;
}


/*Load Register Halfword (immediate) Encoding T2

   LDRH<c>.W <Rt>,[<Rn>{,#<imm12>}]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 0  1  0  1  1|     Rn    |     Rt    |           imm12         |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.

            <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                              LDRH (literal) on page A6-96.

            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. The range of allowed values is 0-31 for encoding T1, 0-4095 for encoding T2, and
                              0-255 for encoding T3. For the offset addressing syntax, <imm> can be omitted, meaning an
                              offset of 0.

                              The pre-UAL syntax LDR<c>B is equivalent to LDRB<c>.

*/
void LDRHImmediateT2(uint32_t instruction)
{ 
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm12 = getBits(instruction,11,0);
  uint32_t address = coreReg[Rn] + imm12;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = loadByteFromMemory(address, 2);

    shiftITState();
  }
  else
    coreReg[Rt] = loadByteFromMemory(address, 2);

  coreReg[PC] += 4;
}



/*Load Register Halfword (immediate) Encoding T3

  LDRH<c> <Rt>,[<Rn>,#-<imm8>]
  LDRH<c> <Rt>,[<Rn>],#+/-<imm8>
  LDRH<c> <Rt>,[<Rn>,#+/-<imm8>]!

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |1   1  1  1  1| 0  0| 0  0  0  1  1|     Rn    |     Rt    | 1|P|U|W|       imm8     |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.

            <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                              LDRH (literal) on page A6-96.

            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. The range of allowed values is 0-31 for encoding T1, 0-4095 for encoding T2, and
                              0-255 for encoding T3. For the offset addressing syntax, <imm> can be omitted, meaning an
                              offset of 0.

                              The pre-UAL syntax LDR<c>B is equivalent to LDRB<c>.

*/
void LDRHImmediateT3(uint32_t instruction)
{ 
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;
  
  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a LDRHT instruction
    LDRHT(instruction);

  int check = isOffPostOrPreIndex(P,W);

  if(check == UNDEFINED)
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
  }

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        coreReg[Rt] = loadByteFromMemory(address,2);
      else if(check == PREINDEX)
      {
        coreReg[Rt] = loadByteFromMemory(address,2);
        coreReg[Rn] = address;
      }
      else
      {
        coreReg[Rt] = loadByteFromMemory(coreReg[Rn],2);
        coreReg[Rn] = address;
      }
    }

    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      coreReg[Rt] = loadByteFromMemory(address,2);
    else if(check == PREINDEX)
    {
      coreReg[Rt] = loadByteFromMemory(address,2);
      coreReg[Rn] = address;
    }
    else
    {
      coreReg[Rt] = loadByteFromMemory(coreReg[Rn],2);
      coreReg[Rn] = address;
    }
  }

  coreReg[PC] += 4;

}


/*Load Register Byte Unprivileged Encoding T1

  LDRBT<c> <Rt>,[<Rn>,#<imm8>]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  0  0  0  1|     Rn    |     Rt    | 1| 1 1 0|       imm8    |

  where:
            <c><q>        See Standard assembler syntax fields on page A6-7.

            <Rt>          Specifies the destination register.

            <Rn>          Specifies the base register. This register is allowed to be the SP.

            <imm>         Specifies the immediate offset added to the value of <Rn> to form the address. The range of
                          allowed values is 0-255. <imm> can be omitted, meaning an offset of 0.

*/
void LDRBT(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t address = coreReg[Rn] + imm8;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = loadByteFromMemory(address, 1);

    shiftITState();
  }
  else
    coreReg[Rt] = loadByteFromMemory(address, 1);

  coreReg[PC] += 4;
}




/*Load Register Signed Byte (immediate) Encoding T1

    LDRSB<c> <Rt>,[<Rn>,#<imm12>]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 1  1  0  0  1|     Rn    |     Rt    |           imm12         |

  where:
            <c><q>        See Standard assembler syntax fields on page A6-7.

            <Rt>          Specifies the destination register.

            <Rn>          Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                          LDRSB (literal) on page A6-120.

            +/-           Is + or omitted to indicate that the immediate offset is added to the base register value
                          (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                          instructions are generated for #0 and #-0.

            <imm>         Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                          address. The range of allowed values is 0-4095 for encoding T1, and 0-255 for encoding T2.
                          For the offset addressing syntax, <imm> can be omitted, meaning an offset of 0.

*/
void LDRSBImmediateT1(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm12 = getBits(instruction,11,0);
  uint32_t address = coreReg[Rn] +  imm12;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);

    shiftITState();
  }
  else
    coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);

  coreReg[PC] += 4;
}





/*Load Register Signed Byte (immediate) Encoding T2

    LDRSB<c> <Rt>,[<Rn>,#-<imm8>]
    LDRSB<c> <Rt>,[<Rn>],#+/-<imm8>
    LDRSB<c> <Rt>,[<Rn>,#+/-<imm8>]!

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 1  0  0  0  1|     Rn    |     Rt    |1 |P| U|W|      imm8     |

  where:
            <c><q>        See Standard assembler syntax fields on page A6-7.

            <Rt>          Specifies the destination register.

            <Rn>          Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                          LDRSB (literal) on page A6-120.

            +/-           Is + or omitted to indicate that the immediate offset is added to the base register value
                          (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                          instructions are generated for #0 and #-0.

            <imm>         Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                          address. The range of allowed values is 0-4095 for encoding T1, and 0-255 for encoding T2.
                          For the offset addressing syntax, <imm> can be omitted, meaning an offset of 0.

*/
void LDRSBImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;

  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a LDRSB instruction
    LDRSBT(instruction);

  int check = isOffPostOrPreIndex(P,W);

  if(check == UNDEFINED || Rt == 0b1111 || Rn == 0b1111)
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
  }

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);
      else if(check == PREINDEX)
      {
        coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);
        coreReg[Rn] = address;
      }
      else
      {
        coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);
        coreReg[Rn] = address;
      }
    }

    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);
    else if(check == PREINDEX)
    {
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);
      coreReg[Rn] = address;
    }
    else
    {
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);
      coreReg[Rn] = address;
    }
  }

  coreReg[PC] += 4;

}




/*Load Register Signed Byte Unprivileged Encoding T2

    LDRSBT<c> <Rt>,[<Rn>,#<imm8>]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 1  0  0  0  1|     Rn    |     Rt    |1 |1| 1|0|      imm8     |

  where:
            <c><q>        See Standard assembler syntax fields on page A6-7.

            <Rt>          Specifies the destination register.

            <Rn>          Specifies the base register. This register is allowed to be the SP.

            <imm>         Specifies the immediate offset added to the value of <Rn> to form the address. The range of
                          allowed values is 0-255. <imm> can be omitted, meaning an offset of 0.

*/
void LDRSBT(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t address = coreReg[Rn] + imm8;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);

    shiftITState();
  }
  else
    coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);

  coreReg[PC] += 4;
}


/*Load Register Dual (immediate) Encoding T1

  LDRD<c> <Rt>,<Rt2>,[<Rn>{,#+/-<imm8>}]
  LDRD<c> <Rt>,<Rt2>,[<Rn>],#+/-<imm8>
  LDRD<c> <Rt>,<Rt2>,[<Rn>,#+/-<imm8>]!

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  0  1| 0  0| P  U  1  W  1|     Rn    |     Rt    |   Rt2   |      imm8     |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the first source register.

            <Rt2>             Specifies the second source register.

            <Rn>              Specifies the base register. This register is allowed to be the SP.
                              +/- Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.

            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. Allowed values are multiples of 4 in the range 0-1020. For the offset addressing
                              syntax, <imm> can be omitted, meaning an offset of 0.

*/
void LDRDImmediate(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rt2 = getBits(instruction,11,8);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,21,21);
  uint32_t U = getBits(instruction,23,23);
  uint32_t P = getBits(instruction,24,24);
  uint32_t address;

  if(U == 1)
    address = coreReg[Rn] + (imm8 << 2);
  else
    address = coreReg[Rn] - (imm8 << 2);

  int check = isOffPostOrPreIndex(P,W);

  if(Rn == 0b1111)
  {
    LDRDLiteral(instruction);
  }
  else
  {
    if(inITBlock())
    {
      if( checkCondition(cond) )
      {
        if(check == OFFINDEX)
        {
          coreReg[Rt] = loadByteFromMemory(address, 4);
          coreReg[Rt2] = loadByteFromMemory(address+4, 4);
        }
        else if(check == PREINDEX)
        {
          coreReg[Rt] = loadByteFromMemory(address, 4);
          coreReg[Rt2] = loadByteFromMemory(address+4, 4);
          coreReg[Rn] = address;
        }
        else
        {
          coreReg[Rt] = loadByteFromMemory(coreReg[Rn], 4);
          coreReg[Rt2] = loadByteFromMemory(coreReg[Rn]+4, 4);
          coreReg[Rn] = address;
        }
      }

      shiftITState();
    }
    else
    {
      if(check == OFFINDEX)
      {
        coreReg[Rt] = loadByteFromMemory(address, 4);
        coreReg[Rt2] = loadByteFromMemory(address+4, 4);
      }
      else if(check == PREINDEX)
      {
        coreReg[Rt] = loadByteFromMemory(address, 4);
        coreReg[Rt2] = loadByteFromMemory(address+4, 4);
        coreReg[Rn] = address;
      }
      else
      {
        coreReg[Rt] = loadByteFromMemory(coreReg[Rn], 4);
        coreReg[Rt2] = loadByteFromMemory(coreReg[Rn]+4, 4);
        coreReg[Rn] = address;
      }
    }
  }

  coreReg[PC] += 4;
}


/*Load Register Halfword Unprivileged

  LDRHT<c> <Rt>,[<Rn>,#<imm8>]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 0  0  0  1| 1|     Rn    |     Rt    | 1| 1 1 0|      imm8     |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.
            
            <Rn>              Specifies the base register. This register is allowed to be the SP.
            
            <imm>             Specifies the immediate offset added to the value of <Rn> to form the address. The range of
                              allowed values is 0-255. <imm> can be omitted, meaning an offset of 0.

*/
void LDRHT(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t address = coreReg[Rn] + imm8;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = loadByteFromMemory(address, 2);

    shiftITState();
  }
  else
    coreReg[Rt] = loadByteFromMemory(address, 2);

  coreReg[PC] += 4;
}



/*Load Register Signed Halfword (immediate) Encoding T1

    LDRSH<c> <Rt>,[<Rn>,#<imm12>]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 1  1  0  1  1|     Rn    |     Rt    |           imm12         |

  where:
            <c><q>        See Standard assembler syntax fields on page A6-7.

            <Rt>          Specifies the destination register.

            <Rn>          Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                          LDRSH (literal) on page A6-120.

            +/-           Is + or omitted to indicate that the immediate offset is added to the base register value
                          (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                          instructions are generated for #0 and #-0.

            <imm>         Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                          address. The range of allowed values is 0-4095 for encoding T1, and 0-255 for encoding T2.
                          For the offset addressing syntax, <imm> can be omitted, meaning an offset of 0.

*/
void LDRSHImmediateT1(uint32_t instruction)
{ 
  uint32_t imm12 = getBits(instruction,11,0);
  uint32_t Rn   = getBits(instruction,19,16);
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t address = coreReg[Rn] + imm12;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);

    shiftITState();
  }
  else
    coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);


  coreReg[PC] += 4;
}



/*Load Register Signed Halfword (immediate) Encoding T2

    LDRSH<c> <Rt>,[<Rn>,#-<imm8>]
    LDRSH<c> <Rt>,[<Rn>],#+/-<imm8>
    LDRSH<c> <Rt>,[<Rn>,#+/-<imm8>]!

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 1  0  0  1  1|     Rn    |     Rt    | 1| P|U|W|      imm8     |

  where:
            <c><q>        See Standard assembler syntax fields on page A6-7.

            <Rt>          Specifies the destination register.

            <Rn>          Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                          LDRSH (literal) on page A6-120.

            +/-           Is + or omitted to indicate that the immediate offset is added to the base register value
                          (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                          instructions are generated for #0 and #-0.

            <imm>         Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                          address. The range of allowed values is 0-4095 for encoding T1, and 0-255 for encoding T2.
                          For the offset addressing syntax, <imm> can be omitted, meaning an offset of 0.

*/
void LDRSHImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;
  
  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a LDRSB instruction
    LDRSHT(instruction);

  int check = isOffPostOrPreIndex(P,W);

  if(check == UNDEFINED || Rt == 0b1111 || Rn == 0b1111)
    ThrowError();

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);
      else if(check == PREINDEX)
      {
        coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);
        coreReg[Rn] = address;
      }
      else
      {
        coreReg[Rt] = signExtend( loadByteFromMemory(coreReg[Rn], 2), 16);
        coreReg[Rn] = address;
      }
    }

    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);
    else if(check == PREINDEX)
    {
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);
      coreReg[Rn] = address;
    }
    else
    {
      coreReg[Rt] = signExtend( loadByteFromMemory(coreReg[Rn], 2), 16);
      coreReg[Rn] = address;
    }
  }

  coreReg[PC] += 4;
  
}



/*Load Register Signed Halfword Unprivileged

  LDRSHT<c> <Rt>,[<Rn>,#<imm8>]

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 1  0  0  1| 1|     Rn    |     Rt    | 1| 1 1 0|      imm8     |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.

            <Rt>              Specifies the destination register.
            
            <Rn>              Specifies the base register. This register is allowed to be the SP.
            
            <imm>             Specifies the immediate offset added to the value of <Rn> to form the address. The range of
                              allowed values is 0-255. <imm> can be omitted, meaning an offset of 0.

*/
void LDRSHT(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t address = coreReg[Rn] + imm8;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);

    shiftITState();
  }
  else
    coreReg[Rt] = signExtend( loadByteFromMemory(address, 2), 16);

  coreReg[PC] += 4;
}





