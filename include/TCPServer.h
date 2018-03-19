#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "TCPSocket.h"
#include "plugcmdlist.h"

struct Client
{
    unsigned int Number;
    QString Name;
    QString IP;
    unsigned int Port;
    SOCKET Socket;

    Client() : Number(0), Name("Client"), IP("127.0.0.1"), Port(12345), Socket(0) {}
    Client(unsigned int number, QString name, QString ip, unsigned int port, SOCKET _socket)
        : Number(number), Name(name), IP(ip), Port(port), Socket(_socket) {}

    bool operator ==(const Client &client) const {
        return Socket == client.Socket;
    }
};

class TCPServer : public TCPSocket
{
    Q_OBJECT
private:
    defPostPtrFuncA2(TCPServer, TStartAccepting, StartAcceptingptr)
    defPostPtrFunc2(TCPServer, TReceiverClient, ReceiverClientptr, Client)
    defPostPtrFunc2(TCPServer, TSenderClient, SenderClientptr, Client, QByteArray)

    QMap<unsigned int, TReceiverClient> Receivers;
    QMap<unsigned int, TSenderClient> Senders;

    QList<Client> clients;
    unsigned int MaxNumberClient;

    void InisializedServer();
    void StartAccepting();
    void ReceiveFromClient(Client client);
    void SendToClient(Client client, QByteArray data);
    void CloseSocketClient(const Client &client);
public:
    TCPServer();
    TCPServer(unsigned int port);
    ~TCPServer();

    bool setPort(unsigned int port);
    unsigned int getPort();

    void Start();
    void Stop();

    void DisconnectClient(const Client &client);
signals:
    void signalRecvData(Client client, QByteArray data);
    void signalAcceptClient(Client client);
    void signalDisconectClient(Client client);
public slots:
    void slotSendData(Client client, QByteArray data);
};

#endif // TCPSERVER_H
