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


#include "ModifiedImmediateConstant.h"
#include "StatusRegisters.h"
#include "getAndSetBits.h"
#include <stdio.h>


/*
  This function will modify the 8 bits constant which is represented
  by abcdefgh according to the ModifyControl

  i:imm3:bit7 (ModifyControl)

case 0000x        00000000 00000000 00000000 abcdefgh
case 0001x        00000000 abcdefgh 00000000 abcdefgh
case 0010x        abcdefgh 00000000 abcdefgh 00000000
case 0011x        abcdefgh abcdefgh abcdefgh abcdefgh
case 01000        1bcdefgh 00000000 00000000 00000000
case 01001        01bcdefg h0000000 00000000 00000000
case 01010        001bcdef gh000000 00000000 00000000
case 01011        0001bcde fgh00000 00000000 00000000
    |
    |                 continue shift right
    v
case 11101        00000000 00000000 000001bc defgh000
case 11110        00000000 00000000 0000001b cdefgh00
case 11111        00000000 00000000 00000001 bcdefgh0

Return :  the modified constant

Inputs : carryStatus        to indicate whether it will affect carry status flag, 0 means not affected
*/
uint32_t ModifyImmediateConstant(uint32_t ModifyControl, uint32_t input_value, uint32_t carryStatus)
{
  uint32_t returnValue;

  if( ModifyControl < 0b00010)
  {
    return input_value;
  }
  else if( ModifyControl < 4)
  {
    returnValue = ModifyControlLessThan4(input_value);
    return returnValue;
  }
  else if( ModifyControl < 6)
  {
    returnValue = ModifyControlLessThan6(input_value);
    return returnValue;
  }
  else if( ModifyControl < 8)
  {
    returnValue = ModifyControlLessThan8(input_value);
    return returnValue;
  }
  else if( ModifyControl >= 8)
  {
    returnValue = SetFirstBitAndShiftRight(input_value, ModifyControl);

    if(carryStatus)
    {
      if(getBits(returnValue,31,31) == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }

    return returnValue;
  }
}


/*  This function will set the first bit to 1 and then shift the whole
 *  8bits value to the bit 31 to 24. And shift it to the right according
 *  to the timesOfShiting-8
 *
 *  Return: the modified inputValue after set and shift right
 */
uint32_t SetFirstBitAndShiftRight(uint32_t input_value, uint32_t timesOfShifting)
{
  input_value = input_value | 0b10000000;
  input_value = input_value << 24;
  input_value = input_value >> ( timesOfShifting - 8);
  return input_value;
}



uint32_t ModifyControlLessThan8(uint32_t input_value)
{
  int i;
  uint32_t dummy = input_value;

  for(i=0; i < 3; i++)
  {
    input_value = ( input_value << 8 ) | dummy;
  }

  return input_value;
}



uint32_t ModifyControlLessThan6(uint32_t input_value)
{
  uint32_t dummy = input_value << 8;
  input_value = ( input_value << 24 ) | dummy;
  return input_value;
}



uint32_t ModifyControlLessThan4(uint32_t input_value)
{
  uint32_t dummy = input_value;
  input_value = ( input_value << 16 ) | dummy;
  return input_value;
}


/* This function will return the modified immediate constants in floating point instructions
   Details can be view at page 164, section A6.4.1, document is in the link below:
   https://trello.com/c/JVVQ8Sdr/13-quick-reference-card-for-thumb2-instruction-set
   
   bits(N) VFPExpandImm(bits(8) imm8, integer N)
          assert N IN {32,64};
            if N == 32 then
                E = 8;
            else
                E = 11;
              
            F = N - E - 1;
            sign = imm8<7>;
            exp = NOT(imm8<6>):Replicate(imm8<6>,E-3):imm8<5:4>;
            frac = imm8<3:0>:Zeros(F-4);
            return sign:exp:frac;
   
*/
uint64_t ModifyFPImmediateConstant(uint32_t ModifyControl, uint32_t bitSize)
{
  uint64_t E,F, returnValue;
  uint32_t sign = 0;
  uint32_t exp = 0;
  uint32_t frac = 0;
  
  if(bitSize == 32)
    E = 8;
  else
    E = 11;
  
  F = bitSize - E - 1;
  sign = getBits(ModifyControl,7,7);
  exp = setBits(exp, getBits(ModifyControl,5,4) , 1 , 0);    //set the bits 5:4 of ModifyControl as 1:0 of exp
  
  int j = 2;
  int i;
  for(i = 0; i < E-3; i++ )
  {
    exp = setBits( exp, getBits(ModifyControl,6,6), j,j);   //set the bits 6 of ModifyControl for E-3 times starting from bit 2 of exp
    j++;
  }
  
  exp = setBits( exp, !getBits(ModifyControl,6,6) , j, j); //set the invert of bits 6 of ModifyControl as the MSB of the exp
  frac = getBits(ModifyControl,3,0) << (F-4) ;
  
  if(bitSize == 32)
    returnValue = ( ( ( (sign << 8) | exp) << 23) | frac );
  else
    returnValue = ( ( ( (sign << 11) | exp) << 52) | frac );

  return returnValue; 
}
















