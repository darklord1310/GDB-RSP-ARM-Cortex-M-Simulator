#include "LoadAndWriteMemory.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"




void writeByteToMemory(uint32_t address, uint32_t valueToWrite, int numberOfByteToWrite)
{
  int i, x = 7 , y = 0;
  for(i = 0; i < numberOfByteToWrite; i++)
  {
    memoryBlock[ virtualMemToPhysicalMem(address) ] = (short int)getBits(valueToWrite, x,y);
    address++;
    x+=8;
    y+=8;
  }
}


uint32_t loadByteFromMemory(uint32_t address, int numberOfByteToRead)
{
  int i;
  uint32_t data;
  
  for(i = 0; i < numberOfByteToRead; i++)
  {
    if(i == 0)
      data = memoryBlock[ virtualMemToPhysicalMem(address) ] ;
    else
      data = ( memoryBlock[ virtualMemToPhysicalMem(address + i) ] <<  (i*8) ) | data ;
  }
  
  return data;
}
