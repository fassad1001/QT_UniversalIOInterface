#include "testservermanager.h"
#include "../easy_log.h"

TestServerManager::TestServerManager()
{
    textAnswer = "Answer";

    connect(&server, SIGNAL(signalRecvData(Client,QByteArray)), this, SLOT(slotRecvData(Client,QByteArray)));
    connect(&server, SIGNAL(signalAcceptClient(Client)), this, SLOT(slotAcceptClient(Client)));
    connect(&server, SIGNAL(signalDisconectClient(Client)), this, SLOT(slotDisconnectClient(Client)));
    connect(this, SIGNAL(signalSendData(Client,QByteArray)), &server, SLOT(slotSendData(Client,QByteArray)));
}

TestServerManager::~TestServerManager()
{
    StopMonitoring();
}

void TestServerManager::StartMonitoring()
{
    server.Start();
}

void TestServerManager::StopMonitoring()
{
    server.Stop();
}

void TestServerManager::slotRecvData(Client client, QByteArray data)
{
    qDebug() << "Client: " << client.Name;
    qDebug() << "IP: " << client.IP;
    qDebug() << "Port: " << client.Port;
    qDebug() << "Data: " << data << "\n";

    QString message = client.Name + " (" + client.IP + ":" + QString::number(client.Port) + "): " + QString(data) + "\n";

    emit signalWriteMessageToList(message);

    emit signalSendData(client, textAnswer.toUtf8());
}

void TestServerManager::slotAcceptClient(Client client)
{
    clients.insert(client.Number, client);
}

void TestServerManager::slotDisconnectClient(Client client)
{
    clients.remove(client.Number);
}

void TestServerManager::slotSetAnswer(QString text)
{
    textAnswer = text;
}
