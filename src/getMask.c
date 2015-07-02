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





uint32_t getMaskforSetBits(uint32_t valueToSet, int bitPosition)
{
  int i;
  assert(bitPosition <= 31); 
  assert(valueToSet == 1 || valueToSet == 0);
  uint32_t maskToSet0 = 0xffffffff;             //initialize the mask to be 0xffff first
  uint32_t maskToSet1 = 0x0;                    //initialize the mask to be 0x0000 first

  if(valueToSet == 1)
  {
    maskToSet1 = maskToSet1 | 0x01;
    for(i = 0; i < bitPosition; i++)
    {
      maskToSet1 = maskToSet1 << 1;  
    }
    return maskToSet1;
  }
  else
  {
    maskToSet0 = maskToSet0 << 1 ;                     
    for(i = 0; i < bitPosition; i++)
    {
      maskToSet0 = ( maskToSet0 << 1) | 1;
    }
    return maskToSet0;
  }
}