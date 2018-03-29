#include "TCPServerMonitoring.h"

TCPServerMonitoring::TCPServerMonitoring()
{
    connect(&server, SIGNAL(signalRecvData(Client,QByteArray)), this, SLOT(slotRecvData(Client,QByteArray)));
    connect(&server, SIGNAL(signalAcceptClient(Client)), this, SLOT(slotAcceptClient(Client)));
    connect(&server, SIGNAL(signalDisconectClient(Client)), this, SLOT(slotDisconnectClient(Client)));
    connect(this, SIGNAL(signalSendData(Client,QByteArray)), &server, SLOT(slotSendData(Client,QByteArray)));
}

TCPServerMonitoring::~TCPServerMonitoring()
{
    server.Stop();
}

void TCPServerMonitoring::start(uint port, bool clearStart)
{
    server.setPort(port);
    _clearStart = clearStart;
    server.Start();
}

void TCPServerMonitoring::stop()
{
    server.Stop();
}

bool TCPServerMonitoring::isOpen()
{
    server.Start();
    return true;
}

QByteArray TCPServerMonitoring::ReadAll()
{

}

void TCPServerMonitoring::Write(QByteArray message)
{
    server.sendToAllClients(message);
}

void TCPServerMonitoring::clear()
{
    connect(&server, SIGNAL(signalRecvData(Client,QByteArray)), this, SLOT(slotRecvData(Client,QByteArray)));
}



void TCPServerMonitoring::slotRecvData(Client client, QByteArray data)
{
    qDebug() << "Client: " << client.Name;
    qDebug() << "IP: " << client.IP;
    qDebug() << "Port: " << client.Port;
    qDebug() << "Data: " << data << "\n";

    emit newMessage(data);
}

void TCPServerMonitoring::slotAcceptClient(Client client)
{
    clients.insert(client.Number, client);
}

void TCPServerMonitoring::slotDisconnectClient(Client client)
{
    clients.remove(client.Number);
}

void TCPServerMonitoring::slotSetAnswer(QString text)
{
    textAnswer = text;
}
