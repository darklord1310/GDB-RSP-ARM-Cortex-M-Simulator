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


#ifndef STRRegister_H
#define STRRegister_H

#include <stdint.h>

void STRRegisterT1(uint32_t instruction);
void STRRegisterT2(uint32_t instruction);
void STRHRegisterT1(uint32_t instruction);
void STRHRegisterT2(uint32_t instruction);
void STRBRegisterT1(uint32_t instruction);
void STRBRegisterT2(uint32_t instruction);
void STMRegisterT1(uint32_t instruction);
void STMRegisterT2(uint32_t instruction);
void STMDB(uint32_t instruction);
int getBitCount(uint32_t value, int bitSize);
void writeMultipleRegisterToMemory(uint32_t address, uint32_t registerList, uint32_t sizeOfRegisterList, uint32_t writeBack, uint32_t Rn);


#endif // STRRegister_H
