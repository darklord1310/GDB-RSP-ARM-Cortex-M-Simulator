#ifndef FunctionalTest_H
#define FunctionalTest_H

typedef enum
{
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    SP_REG,
    LR_REG,
    PC_REG,
    XPSR,
} RegName;

typedef struct AffectedReg AffectedReg;

struct AffectedReg
{
    int regNum;
    unsigned int regValue;
};

AffectedReg reg;

void tarRemoteCommand();
void loadSimpleAssembly();
void loadITBlock();
void singleStep();

#endif // FunctionalTest_H
