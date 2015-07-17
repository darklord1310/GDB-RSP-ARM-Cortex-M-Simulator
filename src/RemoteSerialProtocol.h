#ifndef RemoteSerialProtocol_H
#define RemoteSerialProtocol_H

char *handleQueryPacket(char *data);
char *readSingleRegister(char *data);
char *readAllRegister();
char *writeSingleRegister(char *data);
void writeAllRegister(char *data);
char *readMemory(char *data);
void writeMemory(char *data);
char *step(char *data);

#endif // RemoteSerialProtocol_H
