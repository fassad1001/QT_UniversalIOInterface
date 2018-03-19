#include "testclientmanager.h"
#include "../easy_log.h"

TestClientManager::TestClientManager()
{
    isActiveMonitor = false;

    Writeptr = NULL;
    Readptr = NULL;
}

TestClientManager::~TestClientManager()
{
    StopMonitoring();
}

void TestClientManager::StartMonitoring()
{
    if (isActiveMonitor) return;
    if (client.Connect() != SOCKET_ERROR) {
        Readptr = createPostFuncA(TestClientManager, this, &TestClientManager::Read);
        Writeptr = createPostFunc(TestClientManager, this, &TestClientManager::Write, QString);
        Readptr->AddPostEvent();
        isActiveMonitor = true;

        emit signalUpdateStatus(tr("Клиент подключен"));
    }
}

void TestClientManager::StopMonitoring()
{
    if (!isActiveMonitor) return;
    if (!Writeptr.isNull()) Writeptr->getObj()->die();
    if (!Readptr.isNull()) Readptr->getObj()->die();
    isActiveMonitor = false;

    client.Disconnect();

    emit signalUpdateStatus(tr("Клиент не подключен"));
}

void TestClientManager::slotSendMessage(QString text)
{
    if (client.IsConected()) {
        Writeptr->AddPostEvent(text);
    }
}

void TestClientManager::Write(QString text)
{
    client.Write(text.toUtf8());
}

void TestClientManager::Read()
{
    while (Readptr->getObj()->GetLiveStatus()) {
        if (!client.IsConected()) break;

        QByteArray recvData = client.ReadAll();
        if (recvData.size() != 0) {
            qDebug() << recvData;

            QString message = "Server (" + client.getIPServer() + ":" + QString::number(client.getPortServer()) + "): " + QString(recvData) + "\n";

            emit signalWriteMessageToList(message);
        }
    }
    qDebug() << "End Read!!!";
    if (!Writeptr.isNull()) Writeptr->getObj()->die();
    isActiveMonitor = false;

    emit signalUpdateStatus(tr("Клиент не подключен"));
}
