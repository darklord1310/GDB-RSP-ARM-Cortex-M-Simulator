#ifndef RemoteSerialProtocol_H
#define RemoteSerialProtocol_H

char *handleQueryPacket(char *data);
char *readSingleRegister(char *data);
char *readRegister();

#endif // RemoteSerialProtocol_H
