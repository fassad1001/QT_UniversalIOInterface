#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QString>
#include <iostream>
#include <ws2tcpip.h>
#include <windows.h>
#include <winsock2.h>

const int SOCKET_READ_TIMEOUT_SEC2 = 5;

class TCPSocket2
{
private:
    bool isConected;
    bool isWSACleanup;

    WSAData version;
    sockaddr_in addr;

    void Inisialized();
protected:
    SOCKET u_sock;
public:
    TCPSocket2();
    TCPSocket2(QString ip, unsigned int port);
     ~TCPSocket2();

    int Connect();
    int Connect(QString ip, unsigned int port);

    void SetSettings(QString ip, unsigned int port);

    void Disconnect();

    bool IsConected();

    QByteArray Read();
    QByteArray Read(int count_byte);
    void Write(QByteArray data);
};

#endif // TCPCLIENT_H
