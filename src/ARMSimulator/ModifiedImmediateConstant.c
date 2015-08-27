#include "ModifiedImmediateConstant.h"
#include "StatusRegisters.h"
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

*/
uint32_t ModifyImmediateConstant(uint32_t ModifyControl, uint32_t input_value, uint32_t affectCarry)
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
    
    if(getBits(returnValue,31,31) == 1)
      setCarryFlag();
    else
      resetCarryFlag();
    
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