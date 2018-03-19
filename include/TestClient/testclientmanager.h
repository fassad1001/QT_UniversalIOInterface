#ifndef TESTSERVERMANAGER_H
#define TESTSERVERMANAGER_H

#include "../TCPClient.h"
#include "../plugcmdlist.h"
#include <QObject>

class TestClientManager : public QObject
{
    Q_OBJECT
public:
    TestClientManager();
    ~TestClientManager();

private:
    defPostPtrFunc2(TestClientManager, TWrite, Writeptr, QString)
    defPostPtrFuncA2(TestClientManager, TRead, Readptr)

    TCPClient client;

    bool isActiveMonitor;

    void Write(QString text);
    void Read();
signals:
    void signalUpdateStatus(QString text);
    void signalWriteMessageToList(QString text);
public slots:
    void StartMonitoring();
    void StopMonitoring();
private slots:
    void slotSendMessage(QString text);
};

#endif // TESTSERVERMANAGER_H
