#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "TCPSocket.h"
#include "plugcmdlist.h"
#include <QString>

class TCPClient : public TCPSocket
{
    Q_OBJECT
private:
    defPostPtrFuncA2(TCPClient, TStartChecking, StartCheckingptr)

    bool isConected;

    sockaddr_in addr;

    void InisializedClient();

    void StartChecking();

    void CloseConnected();
public:
    TCPClient();
    TCPClient(QString _ip, unsigned int _port);
    ~TCPClient();

    int Connect();
    int Connect(QString _ip, unsigned int _port);
    void Disconnect();

    bool IsConected();

    bool SetSettings(QString _ip, unsigned int _port);

    unsigned int getPortServer();
    QString getIPServer();

    QByteArray ReadAll(int wait = 0, int duration = 100);
    QByteArray Read(int count_byte, int wait = 0);
    void Write(QByteArray data);
};

#endif // TCPCLIENT_H
