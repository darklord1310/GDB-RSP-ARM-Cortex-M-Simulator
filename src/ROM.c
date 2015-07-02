#include "ROM.h"
#include <malloc.h>

/*
Address range               Memory region       Memory type[a]      Execute Never (XN)[a]   Description

0x00000000- 0x1FFFFFFF      Code                Normal              -                       Executable region for program code.
                                                                                            You can also put data here.

0x20000000- 0x3FFFFFFF      SRAM                Normal              -                       Executable region for data. You can also put code here.
                                                                                            This region includes bit band and bit band alias areas,
                                                                                            see Table 2.13.

0x40000000- 0x5FFFFFFF      Peripheral          Device              XN                      This region includes bit band and bit band alias areas, see Table 2.14.

0x60000000- 0x9FFFFFFF      External RAM        Normal              -                       Executable region for data.

0xA0000000- 0xDFFFFFFF      External device     Device              XN                      External Device memory.

0xE0000000- 0xE00FFFFF      Private Peripheral  Strongly-           XN                      This region includes the NVIC, System timer,
                            Bus                 ordered                                     and system control block.

0xE0100000- 0xFFFFFFFF      Device              Device              XN                      Implementation-specific.

*/
ROM *initROM()
{
  int i;

  ROM *rom = malloc(sizeof(ROM));
  // rom->address = calloc(0xFFFFFFF, sizeof(ROMData));
  // rom->address = malloc(sizeof(ROMData) * sizeOfROM);

  return rom;
}



void resetROM()
{
  int i;
  for(i = 0 ; i < 0xFFFFFFF ; i ++ )
  {
    address[i].data = 0;
  }
}


void destroyROM(ROM *rom)
{
    int i;

    if(rom != NULL)
    {
        // for(i = 0; i < sizeOfROM; i++)
        // {
            // if(rom->address[i] != NULL)
                // free(rom->address);
        // }

        free(rom);
    }
}