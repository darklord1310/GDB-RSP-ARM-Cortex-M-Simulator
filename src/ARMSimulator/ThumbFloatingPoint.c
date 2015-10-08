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


#include "ThumbFloatingPoint.h"
#include <stdio.h>


void initThumbFloatingPointTable()
{
  
}


void initFloatingPointDataProcessing()
{
  int i,j,k;
  uint32_t dummy;
  
  dummy = 0b1100000010;
  for(i = 0; i <= 0b11; i ++)
  {
    dummy = setBits(dummy,i,5,4);
    for(j = 0; j <= 0b1; j++)
    {
      dummy = setBits(dummy,j,0,0);
      Thumb32Table[dummy] = executeLoadByteMemoryHints;
    }
  }
}



void initExtensionRegisterLoadStore()
{
  
}


void init32BitsTransfer()
{
  
}


void init64BitsTransfer()
{
  
}
