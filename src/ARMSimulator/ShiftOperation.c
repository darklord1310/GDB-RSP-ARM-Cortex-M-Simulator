#include "ShiftOperation.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"


/*
(SRshiftType, integer) DecodeImmShift(bits(2) shiftType, bits(5) imm5)
                  case shiftType of
                                when ’00’
                                    shift_t = SRshiftType_LSL; shift_n = UInt(imm5);
                                    
                                when ’01’
                                    shift_t = SRshiftType_LSR; shift_n = if imm5 == ’00000’ then 32 else UInt(imm5);
                                    
                                when ’10’
                                    shift_t = SRshiftType_ASR; shift_n = if imm5 == ’00000’ then 32 else UInt(imm5);
                                    
                                when ’11’
                                    if imm5 == ’00000’ then
                                        shift_t = SRshiftType_RRX; shift_n = 1;
                                    else
                                        shift_t = SRshiftType_ROR; shift_n = UInt(imm5);
                                      
                                return (shift_t, shift_n);
 
*/
int determineShiftOperation(int shiftType, uint32_t shiftAmount)
{
  if(shiftType == 0b00 && shiftAmount == 0)
    return OMITTED;
  else if(shiftType == 0b00 && shiftAmount > 0)
    return LSL;
  else if(shiftType == 0b01)
    return LSR;
  else if(shiftType == 0b10)
    return ASR;
  else if(shiftType == 0b11 && shiftAmount > 0)
    return ROR;
  else if(shiftType == 0b11 && shiftAmount == 0)
    return RRX;

}


uint32_t executeShiftOperation(int shiftType, uint32_t shiftAmount, uint32_t valueToShift, uint32_t S)
{
  uint32_t shiftedValue;
  
  if(shiftType == LSR)
  {
    shiftedValue = executeLSR(shiftAmount, valueToShift, S);
  }
  else if(shiftType == OMITTED)
  {
    return valueToShift;
  }
  else if(shiftType == LSL)
  {
    shiftedValue = executeLSL(shiftAmount, valueToShift, S);
  }
  else if(shiftType == ASR)
  {
    shiftedValue = executeASR(shiftAmount, valueToShift, S);
  }
  else if(shiftType == ROR)
  {
    shiftedValue = executeROR(shiftAmount, valueToShift, S);
  }
  
  return shiftedValue;
}


uint32_t executeLSR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S)
{
  int lastBitShifted, shiftedValue;

  if(shiftAmount == 0)                                                      //if immediate is 0, means maximum shift, shift 32 times
  {
    lastBitShifted = getBits(valueToShift,31,31);                           //this is to get the lastBitShifted out, the value will determine the carry flag
    shiftedValue = 0x0;                                                     //the destination will have value of 0x0 for sure
  }
  else
  {
    lastBitShifted = getBits(valueToShift, shiftAmount-1, shiftAmount-1) ;       //this is to get the lastBitShifted out, the value will determine the carry flag
    shiftedValue = valueToShift >> shiftAmount;
  }
  
  if(S == 1)                                                              //update status register
  {
    if(lastBitShifted == 1)
      setCarryFlag();
    else
      resetCarryFlag();
  }
  
  return shiftedValue;
}


uint32_t executeLSL(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S)
{
  int lastBitShifted, shiftedValue;
    
  if(shiftAmount <= 32)
  {
    if(shiftAmount == 0)
      lastBitShifted = 0;
    else
      lastBitShifted = getBits(valueToShift, 32-shiftAmount, 32-shiftAmount);

    if( shiftAmount == 32)
      shiftedValue = 0;
    else
      shiftedValue =  valueToShift << shiftAmount ;
  }
  else
  {
    lastBitShifted = 0;
    shiftedValue = 0;
  }
  
  if(S == 1)                                                                          //update status register
  {
    if(lastBitShifted == 1)
      setCarryFlag();
    else
      resetCarryFlag();
  }
  
  return shiftedValue;
}



uint32_t executeASR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S)
{
  int i, timesToShift, lastBitShifted, shiftedValue;
  uint32_t MSBofValueToShift = getBits(valueToShift,31,31);

  uint32_t mask = MSBofValueToShift << 31;       //create mask to achieve arithmetic shift
                                                
  uint32_t temp = valueToShift;                  //create a dummy to prevent changing the register value
  
  if( shiftAmount == 0)                          //if shiftAmount is zero, means maximum 32 shift
    shiftAmount = 32;
  
  for(i = 0; i < shiftAmount; i++)
  {
    if( i == shiftAmount - 1)                   //this is to get the last bit of Rm before shifted out
      lastBitShifted = getBits(temp, 0,0);
    temp = ( temp >> 1 ) | mask;
  }
  
  shiftedValue = temp;
  
  if(S == 1)
  {
    if(lastBitShifted == 1)                     //if lastBitShifted is 1, the carry is set, else carry not set
      setCarryFlag();
    else
      resetCarryFlag();
  }
  
  return shiftedValue;
}



uint32_t executeROR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S)
{
  int i, lastBitRotated, shiftedValue;
  uint32_t temp = valueToShift;                   //this temp is used to perform the rotate operation and to avoid destroy the value

  for(i=0; i<shiftAmount; i++)
  {
    if(i == shiftAmount -1 )                     //to get the last bit rotated       
      lastBitRotated = getBits(temp,0,0);
      
    if( getBits(temp,0,0) == 1)
    {
      temp = temp >> 1;
      temp = setBits(temp, 1, 31, 31);
    }
    else
    {
      temp = temp >> 1;
      temp = setBits(temp, 0, 31, 31);
    }
  }
  
  shiftedValue = temp;

  if( S == 1)
  {
    if(shiftAmount != 0)
    {
      if(lastBitRotated == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }
  }
  
  return shiftedValue;
}