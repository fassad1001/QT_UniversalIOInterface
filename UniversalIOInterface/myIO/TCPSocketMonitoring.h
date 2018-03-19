#ifndef TCPSOCKETMONITORING_H
#define TCPSOCKETMONITORING_H

#include <QObject>
#include "include/TCPSocket2.h"
#include "include/plugcmdlist.h"

class TCPSocketMonitoring : public QObject, public TCPSocket
{
    Q_OBJECT
public:
    explicit TCPSocketMonitoring(QObject *parent = nullptr);
    ~TCPSocketMonitoring();

    void start(QString ip, uint port, int timer, bool clearStart);
    void stop();
    bool isOpen();

    QByteArray ReadAll();
    void Write(QByteArray message);
    void clear();
private:
    bool _isMonitoringActive;
    QString _ip;
    uint _port;
    int _check_timeout;
    bool _clearStart;

    defPostPtrFuncA2(TCPSocketMonitoring, TStartMonitoring, StartMonitoringPtr)
    void StartMonitoringInAnotherThread();
    void StartMonitoring();

    defPostPtrFuncA2(TCPSocketMonitoring, TStopMonitoring, StopMonitoringPtr)
    void StopMonitoringInAnotherThread();
    void StopMonitoring();
//    void StopMonitoring();

    void CreateTCPClient();
signals:
    void newMessage(QByteArray message);
};

#endif // TCPSOCKETMONITORING_H
