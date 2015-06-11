#include "ModifiedImmediateConstant.h"
#include <stdio.h>



/*
  This function will modify the 8 bits constant which is represented
  by abcdefgh according to the ModifyControl
  
  i:imm3:a (ModifyControl)

case 0000x        00000000 00000000 00000000 abcdefgh
case 0001x        00000000 abcdefgh 00000000 abcdefgh 
case 0010x        abcdefgh 00000000 abcdefgh 00000000 
case 0011x        abcdefgh abcdefgh abcdefgh abcdefgh 
case 01000        1bcdefgh 00000000 00000000 00000000
case 01001        01bcdefg h0000000 00000000 00000000
case 01010        001bcdef gh000000 00000000 00000000
case 01011        0001bcde fgh00000 00000000 00000000
case 11101        00000000 00000000 000001bc defgh000
case 11110        00000000 00000000 0000001b cdefgh00
case 11111        00000000 00000000 00000001 bcdefgh0

Return :  the modified constant

*/
unsigned int ModifyImmediateConstant(unsigned int ModifyControl, unsigned int input_value)
{
  if( ModifyControl < 0b00010)
  {
    return input_value;
  }
  else if( ModifyControl < 4)
  {
    unsigned int returnValue = ModifyControlLessThan4(input_value);
    return returnValue;
  }
  else if( ModifyControl < 6)
  {
    unsigned int returnValue = ModifyControlLessThan6(input_value);
    return returnValue;
  }
  else if( ModifyControl < 8)
  {
    unsigned int returnValue = ModifyControlLessThan8(input_value);
    return returnValue;
  }
  else if( ModifyControl == 8)
  {
    unsigned int returnValue = ModifyControlIs8(input_value);
    return returnValue;
  }
  else if( ModifyControl == 9)
  {
    unsigned int returnValue = ModifyControlIs9(input_value);
    return returnValue;
  }
  else if( ModifyControl == 10)
  {
    unsigned int returnValue = ModifyControlIs10(input_value);
    return returnValue;
  }
  else if( ModifyControl == 11)
  {
    unsigned int returnValue = ModifyControlIs11(input_value);
    return returnValue;
  }
  else if( ModifyControl == 12)
  {
    unsigned int returnValue = ModifyControlIs12(input_value);
    return returnValue;    
  }
  else if( ModifyControl == 13)
  {
    unsigned int returnValue = ModifyControlIs13(input_value);
    return returnValue;     
  }
  else if( ModifyControl == 14)
  {
    unsigned int returnValue = ModifyControlIs14(input_value);
    return returnValue;     
  }
  
}



unsigned int ModifyControlIs14(unsigned int input_value)
{
  input_value = ModifyControlIs8(input_value);
  input_value = input_value >> 23;

  return input_value;
}



unsigned int ModifyControlIs13(unsigned int input_value)
{
  input_value = ModifyControlIs8(input_value);
  input_value = input_value >> 22;

  return input_value;
}




unsigned int ModifyControlIs12(unsigned int input_value)
{
  input_value = ModifyControlIs8(input_value);
  input_value = input_value >> 21;

  return input_value;
}



unsigned int ModifyControlIs11(unsigned int input_value)
{
  input_value = ModifyControlIs8(input_value);
  input_value = input_value >> 3;

  return input_value;
}



unsigned int ModifyControlIs10(unsigned int input_value)
{
  input_value = ModifyControlIs8(input_value);
  input_value = input_value >> 2;

  return input_value;
}



unsigned int ModifyControlIs9(unsigned int input_value)
{
  input_value = ModifyControlIs8(input_value);
  input_value = input_value >> 1;

  return input_value;
}



unsigned int ModifyControlIs8(unsigned int input_value)
{
  input_value = input_value | 0b10000000;
  input_value = input_value << 24;

  return input_value;
}



unsigned int ModifyControlLessThan8(unsigned int input_value)
{
  int i;
  unsigned int dummy = input_value;
  
  for(i=0; i < 3; i++)
  {
    input_value = ( input_value << 8 ) | dummy;
  }
  
  return input_value;
}



unsigned int ModifyControlLessThan6(unsigned int input_value)
{
  unsigned int dummy = input_value << 8;
  input_value = ( input_value << 24 ) | dummy;
  return input_value;
}



unsigned int ModifyControlLessThan4(unsigned int input_value)
{
  unsigned int dummy = input_value;
  input_value = ( input_value << 16 ) | dummy;
  return input_value;
}