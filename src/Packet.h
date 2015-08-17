#ifndef Packet_H
#define Packet_H

#include <stdint.h>

char *gdbCreateMsgPacket(char *data);
void destroyPacket(char *packet);

char *createdHexToString(unsigned long long int regVal, int bytes);
void destroyHexToString(char *asciiString);

uint32_t decodeTwoByte(uint32_t byteData);
uint32_t decodeFourByte(uint32_t byteData);
uint64_t decodeEightByte(uint64_t byteData);

int verifyPacket(char *data);

#endif // Packet_H
