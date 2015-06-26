#include "getMask.h"
#include <assert.h>

/*  This will get the mask which is needed according to the bitPosition
 *  Eg. if bitPosition is 16
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                       ^      
 *                       |      
 *                      16     
 *
 *  Then this function will provide the mask to mask off the bits before bit16 
 *  It will provide and return a mask of 0x0001FFFF
 *
 */
uint32_t getMaskforGetBits(int bitPosition)
{
  int i;
  uint32_t mask = 0x0;          //initialize the mask to be 0x00 first, then slowly
                                //shift to left to get the mask we wanted
   
  for(i = 0; i < bitPosition + 1; i++)
  {
    mask = ( mask << 1 ) | 0x01;
    
  }
  
  return mask;
}


uint32_t getMaskforSetBits(uint32_t valueToSet, int higherRange, int lowerRange)
{
  unsigned int bitValue;
  assert(higherRange > -1);
  assert(lowerRange > -1);
  assert(higherRange >= lowerRange);
  //int temp_higher = higherRange;
  //int temp_lower = lowerRange;
  
  int i;
  uint32_t mask = 0xffff;             //initialize the mask to be 0xffff first
  mask = mask << higherRange + 1;
  
  /*
  for(i = 0; i < higherRange ; i++)
  {
    bitValue = getBits(valueToSet, temp_higher, temp_lower);
    mask = ( mask << 1 ) | 0x01;
    
  }
  */
  return mask;
  
  
}