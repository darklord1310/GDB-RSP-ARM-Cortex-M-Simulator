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
  int i, timeToLoop;
  unsigned int mask = 0x00;     //initialize the mask to be 0x00 first, then slowly
                                //shift to left to get the mask we wanted

  if( ( (31 - bitPosition) % 4) != 0)                     //to handle if the bitPosition+1 is multiple of 4
  {
      switch ( (31 - bitPosition) % 4 )
      {
        case 1 : mask = (mask << 4) | 0b0111;
                 break;
        case 2 : mask = (mask << 4) | 0x03;
                 break;
        case 3 : mask = (mask << 4) | 0b0001;
                 break;
      }
        
      timeToLoop = (bitPosition - 0) / 4;                //determine how many times to shift left again to fill it with 0x0f

      for(i = 0; i < timeToLoop ; i++)
      {
          mask = (mask << 4) |  0x0f;                    //shift left and OR with 0x0f to create the mask
      }
  }
  else
  {
      timeToLoop = (bitPosition + 1) / 4;               //determine how many times to shift left again to fill it with 0x0f
      for(i = 0; i < timeToLoop ; i++)
      {
          mask = (mask << 4) |  0x0f;                   //shift left and OR with 0x0f to create the mask
      }
  }
  return mask;
}