#include "TCPServer.h"

TCPServer::TCPServer()
{
    qRegisterMetaType<Client>("Client");

    StartAcceptingptr = NULL;

    MaxNumberClient = 0;
}

TCPServer::TCPServer(unsigned int port)
{
    qRegisterMetaType<Client>("Client");

    Port = port;
    MaxNumberClient = 0;

    StartAcceptingptr = NULL;
}

TCPServer::~TCPServer()
{
    Stop();
}

bool TCPServer::setPort(unsigned int port)
{
    if (StartAcceptingptr.isNull()) { // нельзя изменять порт при включенном сервере
        Port = port;
        return true;
    }
    return false;
}

unsigned int TCPServer::getPort()
{
    return Port;
}

void TCPServer::InisializedServer()
{
    if (Inisialized()) {
        // Setup the TCP listening socket
        int isResult = bind(Socket, resAddr->ai_addr, (int)resAddr->ai_addrlen);
        if (isResult == SOCKET_ERROR) {
            std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
            freeaddrinfo(resAddr);
            closesocket(Socket);
            if (!isWSACleanup) WSACleanup();
            isWSACleanup = true;
            return;
        }

        freeaddrinfo(resAddr);

        isResult = listen(Socket, SOMAXCONN);
        if (isResult == SOCKET_ERROR) {
            std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
            closesocket(Socket);
            if (!isWSACleanup) WSACleanup();
            isWSACleanup = true;
            return;
        }
    }
}

void TCPServer::Start()
{
    if (!StartAcceptingptr.isNull()) return;
    InisializedServer();
    // Запускаем поиск клиентов
    StartAcceptingptr = createPostFuncA(TCPServer, this, &TCPServer::StartAccepting);
    StartAcceptingptr->AddPostEvent();
}

void TCPServer::Stop()
{
    if (StartAcceptingptr.isNull()) return;
    // Отсанавливаем поиск клиентов
    StartAcceptingptr->getObj()->die();
    StartAcceptingptr = NULL;
    MaxNumberClient = 0;

    // Отсоединяем всех клиентоа
    foreach (Client client, clients) {
        DisconnectClient(client);
    }

    shutdown(Socket, SD_BOTH);
    closesocket(Socket);
    if (!isWSACleanup) WSACleanup();
    isWSACleanup = true;
}

void TCPServer::StartAccepting()
{
    while (StartAcceptingptr->getObj()->GetLiveStatus()) {
        fd_set s_set;
        FD_ZERO(&s_set);
        FD_SET(Socket, &s_set);
        timeval timeout = {0, 0};
        int select_res = select(1, &s_set, NULL, NULL, &timeout); // Проверяем наличие клиентов желающих подключиться
        if (select_res == SOCKET_ERROR) continue;
        if (select_res) {
            // Accept a client socket
            struct sockaddr_in client_info;
            int sizeAddr = sizeof(client_info);
            SOCKET socketClient = accept(Socket, (sockaddr*)&client_info, &sizeAddr);
            if (socketClient == INVALID_SOCKET) {
                qDebug() << "accept failed with error:" << WSAGetLastError();
                closesocket(Socket);
                if (!isWSACleanup) WSACleanup();
                isWSACleanup = true;
                return;
            }

            clients.push_back(Client(MaxNumberClient,
                                     QString("Client"),
                                     QString(inet_ntoa(client_info.sin_addr)),
                                     ntohs(client_info.sin_port),
                                     socketClient));

            emit signalAcceptClient(clients.last());

            SenderClientptr = createPostFunc(TCPServer, this, &TCPServer::SendToClient, Client, QByteArray);
            ReceiverClientptr = createPostFunc(TCPServer, this, &TCPServer::ReceiveFromClient, Client);
            ReceiverClientptr->AddPostEvent(clients.last());

            Receivers.insert(MaxNumberClient, ReceiverClientptr);
            Senders.insert(MaxNumberClient, SenderClientptr);

            MaxNumberClient++;
        }
    }
}

void TCPServer::ReceiveFromClient(Client client)
{
    int resultSelect = 0;
    unsigned long length;
    TReceiverClient receiver = Receivers[client.Number];
    while (receiver->getObj()->GetLiveStatus()) {
        fd_set s_set;
        FD_ZERO(&s_set);
        FD_SET(client.Socket, &s_set);
        timeval timeout = {0, 0};
        resultSelect = select(1, &s_set, NULL, NULL, &timeout);
        ioctlsocket(client.Socket, FIONREAD, &length);
        if (resultSelect == 1 && length == 0) break; // Если сокет мёртв
        Sleep(1); // В некоторых случаях не срабатывает проверка выше без переключения процессов

        QByteArray recvData;
        if (TCPSocket::ReadAll(client.Socket, recvData)) {
            if (recvData.size() != 0) {
                emit signalRecvData(client, recvData);
            }
        }
    }
    CloseSocketClient(client);
}

void TCPServer::slotSendData(Client client, QByteArray data)
{
    if (Senders.contains(client.Number)) {
        Senders[client.Number]->AddPostEvent(client, data);
    }
}

void TCPServer::SendToClient(Client client, QByteArray data)
{
    Write(client.Socket, data);
}

void TCPServer::CloseSocketClient(const Client &client)
{
    if (clients.contains(client)) {
        SOCKET socketClient = client.Socket;
        shutdown(socketClient, SD_BOTH);
        closesocket(socketClient);

        emit signalDisconectClient(client);

        Receivers.remove(client.Number);
        Senders.remove(client.Number);
        clients.removeAll(client);
    }
}

void TCPServer::DisconnectClient(const Client &client)
{
    if (clients.contains(client)) {
        TReceiverClient receiver = Receivers[client.Number];
        receiver->getObj()->die();
    }
}


