#include "getMask.h"


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
unsigned int getMask(int bitPosition)
{
  int i;
  unsigned int mask = 0x00;     //initialize the mask to be 0x00 first, then slowly
                                //shift to left to get the mask we wanted
   
  for(i = 0; i < bitPosition + 1; i++)
  {
    mask = ( mask << 1 ) | 0x01;
    
  }
  
  return mask;
}