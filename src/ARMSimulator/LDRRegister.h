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


#ifndef LDRRegister_H
#define LDRRegister_H

#include <stdint.h>

void LDRRegisterT1(uint32_t instruction);
void LDRRegisterT2(uint32_t instruction);
void LDRTT1(uint32_t instruction);
void LDRHRegisterT1(uint32_t instruction);
void LDRBRegisterT1(uint32_t instruction);
void LDRBRegisterT2(uint32_t instruction);
void LDRSBRegisterT1(uint32_t instruction);
void LDRSBRegisterT2(uint32_t instruction);
void LDRSHRegisterT1(uint32_t instruction);
void LDMRegisterT1(uint32_t instruction);
void LDMRegisterT2(uint32_t instruction);
void LDMDB(uint32_t instruction);
void loadMultipleRegisterFromMemory(uint32_t address, uint32_t registerList, uint32_t writeBack, uint32_t Rn, int sizeOfRegisterList);
int determineWriteBack(uint32_t Rn, uint32_t registerList, uint32_t W);

#endif // LDRRegister_H
