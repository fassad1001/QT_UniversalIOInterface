#ifndef TESTSERVERMANAGER_H
#define TESTSERVERMANAGER_H

#include "../TCPServer.h"
#include <QObject>

class TestServerManager : public QObject
{
    Q_OBJECT
public:
    TestServerManager();
    ~TestServerManager();

    QMap<int, Client> clients;

    QString textAnswer;

private:
    TCPServer server;
public slots:
    void StartMonitoring();
    void StopMonitoring();
signals:
    void signalSendData(Client client, QByteArray data);
    void signalWriteMessageToList(QString text);
private slots:
    void slotAcceptClient(Client client);
    void slotDisconnectClient(Client client);
    void slotRecvData(Client client, QByteArray data);
    void slotSetAnswer(QString text);
};

#endif // TESTSERVERMANAGER_H
