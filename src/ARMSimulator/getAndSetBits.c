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


#include "getAndSetBits.h"
#include "ARMRegisters.h"
#include <assert.h>

/*  This function will get the number of bits based on the range given by user from the instructions
 *  
 *  Input :     higherRange     is the higher limit of the stream of bits to be obtain
 *              lowerRange      is the lower limit of the stream of bits to be obtain
 *
 *  Return :    the stream of bits that obtain
 *
 *  Note:       It is possible also for this function to only get a single bit
 *              If the higherRange and lowerRange is the same
 *
 */
uint32_t getBits(uint32_t instruction, int higherRange, int lowerRange)
{
    uint32_t StreamOfBits;
    assert(higherRange < 32);
    assert(higherRange >= lowerRange);
    assert(lowerRange >= 0);
    
    uint32_t mask = getMaskforGetBits(higherRange);               //get the mask to mask off the bits before 
                                                                  //the higher limit 

    StreamOfBits = ( instruction & mask ) ;
    StreamOfBits = StreamOfBits >> lowerRange;
   
    return StreamOfBits;
}



/*  This function will set the number of bits based on the range given by user for the setTarget
 *  Eg : higherRange is 13
 *       lowerRange is  8
 *       input value is 0b110101
 * 
 *       The bit of the setTarget from 13 to 8 is set to 110101
 * 
 *       Note* : if the range is larget than the input_value, the result maybe unexpected 
 * 
 *               eg Given higherRange is 16, lowerRange is 13 , range = 16-13+1 = 4 (+1 because of start from 0)
 *               If input_value is 0b10, which is need only need 2 bits to represent
 *               but it will overwrite the bit 16 to bit 13 by 0b0010 which is not what we want
 *               Special care needs to be taken when setting for the range
 */
uint32_t setBits(uint32_t setTarget, uint32_t input_value, int higherRange, int lowerRange)
{
  int i,bitValue;
  int count = 0;                                  //start from 0
  uint32_t mask;
  assert(higherRange >= lowerRange);
  assert(higherRange < 32);
  
  for(i = lowerRange; i < higherRange + 1; i++)
  {
    bitValue = getBits(input_value,count,count);
    if(bitValue == 1)
    {
      mask = getMaskforSetBits(bitValue, i);
      setTarget = setTarget | mask;
    }
    else
    {
      mask = getMaskforSetBits(bitValue, i);
      setTarget = setTarget & mask;
    }
    count++;
  }
   
  return setTarget;
}