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


#ifndef LDRImmediate_H
#define LDRImmediate_H

#include <stdint.h>

void LDRImmediateT1(uint32_t instruction);
void LDRImmediateT2(uint32_t instruction);
void LDRImmediateT3(uint32_t instruction);
void LDRImmediateT4(uint32_t instruction);
void LDRBImmediateT1(uint32_t instruction);
void LDRBImmediateT2(uint32_t instruction);
void LDRBImmediateT3(uint32_t instruction);
void LDRHImmediateT1(uint32_t instruction);
void LDRBT(uint32_t instruction);


#endif // LDRImmediate_H
