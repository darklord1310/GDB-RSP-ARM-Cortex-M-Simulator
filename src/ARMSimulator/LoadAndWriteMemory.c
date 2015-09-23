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
        Throw(Watchpoint_Break);
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
        Throw(Watchpoint_Break);
    }
  }

}


int isOffPostOrPreIndex(uint32_t index,uint32_t writeback)
{
  if(index == 1 && writeback == 0)
    return OFFINDEX;
  else if(index == 1 && writeback == 1)
    return PREINDEX;
  else if(index == 0 && writeback == 1)
    return POSTINDEX;
  else
    return UNDEFINED;
}












