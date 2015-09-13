/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef ModifiedImmediateConstant_H
#define ModifiedImmediateConstant_H


#include <stdint.h>

unsigned int ModifyControlLessThan4(unsigned int input_value);
unsigned int ModifyControlLessThan6(unsigned int input_value);
unsigned int ModifyControlLessThan8(unsigned int input_value);
unsigned int SetFirstBitAndShiftRight(unsigned int input_value, unsigned int timesOfShifting);
uint32_t ModifyImmediateConstant(uint32_t ModifyControl, uint32_t input_value);

#endif // ModifiedImmediateConstant_H
