#ifndef RemoteSerialProtocol_H
#define RemoteSerialProtocol_H

char *handleQueryPacket(char *data);
char *readSingleRegister(char *data);
char *readAllRegister();
void writeSingleRegister(char *data);
void writeAllRegister(char *data);

#endif // RemoteSerialProtocol_H
