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

#include "SaturateOperation.h"
#include <math.h>
#include <stdio.h>


int32_t saturationQ(int32_t sign, int32_t operand, uint32_t saturatedTo, uint32_t *saturated)
{
  int32_t result, max, min;

  if(sign)
  {
    max = (int32_t)(pow(2, saturatedTo + 1) / 2) - 1;
    min = -(max + 1);
  }
  else
  {
    max = (int32_t)(pow(2, saturatedTo + 1) / 2) - 1;
    min = 0;
  }

  if(operand > max)
  { result = max; *saturated = 1; }
  else if(operand < min)
  { result = min; *saturated = 1; }
  else
  { result = operand; *saturated = 0; }

  return result;
}