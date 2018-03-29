#ifndef TCPSERVERMONITORING_H
#define TCPSERVERMONITORING_H

#include <QObject>

#include "include/TCPServer.h"
class TCPServerMonitoring : public QObject
{
    Q_OBJECT
public:
    TCPServerMonitoring();
    ~TCPServerMonitoring();
    void start(uint port, bool clearStart);
    void stop();
    bool isOpen();

    QByteArray ReadAll();
    void Write(QByteArray message);
    void clear();
private:
    bool _isMonitoringActive;
    uint _port;
    int _check_timeout;
    bool _clearStart;

    TCPServer server;
    QString textAnswer;
    QMap<int, Client> clients;

signals:
    void newMessage(QByteArray message);
    void signalSendData(Client client, QByteArray data);
    void signalWriteMessageToList(QString text);
private slots:
    void slotAcceptClient(Client client);
    void slotDisconnectClient(Client client);
    void slotRecvData(Client client, QByteArray data);
    void slotSetAnswer(QString text);
};

#endif // TCPSERVERMONITORING_H
