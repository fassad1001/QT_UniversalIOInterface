#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <winsock2.h>
#include <windows.h>
#include <QString>
#include <iostream>
#include <ws2tcpip.h>
#include <QObject>

const int SOCKET_READ_TIMEOUT_SEC = 5;

class TCPSocket : public QObject
{
    Q_OBJECT
private:
    WSAData version;
protected:
    QString IP;
    unsigned int Port;

    SOCKET Socket;

    struct addrinfo *resAddr;

    bool isWSACleanup;

    bool Inisialized();

    bool Read(SOCKET _socket, int count_byte, QByteArray &recvData);
    bool ReadAll(SOCKET _socket, QByteArray &recvData);

    bool Write(SOCKET _socket, QByteArray send_data);
public:
    TCPSocket();
     ~TCPSocket();
};

#endif // TCPSOCKET_H
