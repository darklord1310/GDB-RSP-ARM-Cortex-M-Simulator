#include "LoadAndWriteMemory.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "RemoteSerialProtocol.h"
#include "ErrorSignal.h"
#include "CException.h"


void writeByteToMemory(uint32_t address, uint32_t valueToWrite, int numberOfByteToWrite)
{
  int i, x = 7 , y = 0;
  
  isWatchPointReachedForWrite(address, numberOfByteToWrite);
  
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
  
  isWatchPointReachedForRead(address, numberOfByteToRead);
  
  for(i = 0; i < numberOfByteToRead; i++)
  {
    if(i == 0)
      data = memoryBlock[ virtualMemToPhysicalMem(address) ] ;
    else
      data = ( memoryBlock[ virtualMemToPhysicalMem(address + i) ] <<  (i*8) ) | data ;
  }
  
  return data;
}



void isWatchPointReachedForRead(uint32_t address, int size)
{
  int i;
  
  for(i = 0; i < MAX_HW_WATCHPOINT; i++)
  {
    if( wp[i].type == WP_READ || wp[i].type == WP_ACCESS)
    {
      if(wp[i].addr == address && wp[i].size == size)
        Throw(GDB_SIGNAL_TRAP);
    }
  }
  
}


void isWatchPointReachedForWrite(uint32_t address, int size)
{
  int i;
  
  for(i = 0; i < MAX_HW_WATCHPOINT; i++)
  {
    if( wp[i].type == WP_WRITE || wp[i].type == WP_ACCESS)
    {
      if(wp[i].addr == address && wp[i].size == size)
        Throw(GDB_SIGNAL_TRAP);
    }
  }
  
}