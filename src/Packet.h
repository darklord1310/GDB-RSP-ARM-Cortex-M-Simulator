#ifndef Packet_H
#define Packet_H

char *gdbCreateMsgPacket(char *data);
void destroyPacket(char *packet);

char *createdHexToString(unsigned int regVal, int bits);
void destroyHexToString(char *asciiString);

unsigned int decodeTwoByte(unsigned int byteData);
unsigned int decodeFourByte(unsigned int byteData);

#endif // Packet_H
