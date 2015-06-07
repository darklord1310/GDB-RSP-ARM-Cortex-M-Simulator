#include "getBits.h"
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
unsigned int getBits(unsigned int instruction, int higherRange, int lowerRange)
{
    unsigned int StreamOfBits;
    assert(higherRange < 32);
    assert(higherRange >= lowerRange);
    assert(lowerRange >= 0);
    
    unsigned int mask = getMask(higherRange);               //get the mask to mask off the bits before 
                                                            //the higher limit 

    StreamOfBits = ( instruction & mask ) ;
    StreamOfBits = StreamOfBits >> lowerRange;
   
    return StreamOfBits;
}

