#ifndef RemoteSerialProtocol_H
#define RemoteSerialProtocol_H

char *handleQueryPacket(char *data);
char *readSingleRegister(char *data);
char *readAllRegister();

#endif // RemoteSerialProtocol_H
