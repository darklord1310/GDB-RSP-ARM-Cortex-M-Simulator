#ifndef Packet_H
#define Packet_H

// const char hex[] = "0123456789abcdef";

char *gdbCreateMsgPacket(char *data);
void destroyPacket(char *packet);

char *createdHexToString(unsigned int regVal);
void destroyHexToString(char *asciiString);

#endif // Packet_H
