#include "TCPClient.h"

TCPClient::TCPClient() : TCPClient("127.0.0.1", 12345)
{
}

TCPClient::TCPClient(QString ip, unsigned int port)
{
    isConected = false;

    IP = ip;
    Port = port;

    StartCheckingptr = NULL;

    //Socket address information
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP.toStdString().data());
    addr.sin_port = htons(Port);
}

TCPClient::~TCPClient()
{
    Disconnect();
}

void TCPClient::InisializedClient()
{
    Inisialized();
    freeaddrinfo(resAddr);
}

void TCPClient::StartChecking()
{
    int resultSelect = 0;
    unsigned long length;
    int count = 0;
    while (StartCheckingptr->getObj()->GetLiveStatus()) {
        fd_set s_set;
        FD_ZERO(&s_set);
        FD_SET(Socket, &s_set);
        timeval timeout = {0, 0};
        resultSelect = select(1, &s_set, NULL, NULL, &timeout);
        ioctlsocket(Socket, FIONREAD, &length);
        if (resultSelect == 1 && length == 0) {
            count++;
            if (count == 3) break; // Если сокет мёртв (3 попытки)
        } else {
            count = 0;
        }
        Sleep(50); // В некоторых случаях не срабатывает проверка выше без переключения процессов
    }

    CloseConnected();
}

QString TCPClient::getIPServer()
{
    return IP;
}

unsigned int TCPClient::getPortServer()
{
    return Port;
}

int TCPClient::Connect()
{
    if (isConected) return 1;
    InisializedClient();

    int conn = ::connect(Socket, (SOCKADDR*)&addr, sizeof(addr));
    if (conn == SOCKET_ERROR){
        isConected = false;
        std::cout << "Error - when connecting " << WSAGetLastError() << std::endl;
        closesocket(Socket);
        if (!isWSACleanup) WSACleanup();
        isWSACleanup = true;
    } else {
        isConected = true;
        StartCheckingptr = createPostFuncA(TCPClient, this, &TCPClient::StartChecking);
        StartCheckingptr->AddPostEvent();
    }
    return conn;
}

int TCPClient::Connect(QString ip, unsigned int port)
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.toStdString().data());
    addr.sin_port = htons(port);

    return Connect();
}

bool TCPClient::SetSettings(QString ip, unsigned int port)
{
    if (isConected) return false;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.toStdString().data());
    addr.sin_port = htons(port);
    return true;
}

void TCPClient::CloseConnected()
{
    isConected = false;
    shutdown(Socket, SD_BOTH);
    closesocket(Socket);
    if (!isWSACleanup) WSACleanup();
    isWSACleanup = true;
}

void TCPClient::Disconnect()
{   
    if (isConected) {
        if (!StartCheckingptr.isNull()) StartCheckingptr->getObj()->die();
        StartCheckingptr = NULL;
    }    
}

bool TCPClient::IsConected()
{
    return isConected;
}

QByteArray TCPClient::Read(int count_byte, int wait)
{
    if (!isConected) return QByteArray();
    QByteArray recvData;
    do {
        TCPSocket::Read(Socket, count_byte, recvData);
        if (recvData.size() != 0) break;
        Sleep(1);
        wait--;
    } while (wait > 0);

    return recvData;
}

QByteArray TCPClient::ReadAll(int wait, int duration)
{
    if (!isConected) return QByteArray();
    QByteArray recvData;
    QByteArray buffer;
    do {
//        TCPSocket::ReadAll(Socket, recvData); // Читаем всё что есть в сокете
//        if (recvData.size() != 0) break; // если в сокете больше данных нет, то выходим
//        Sleep(1); // Ожидаем записи данных
//        if (wait <= 0) break;
//        wait--;

        if (!isConected) break;
        TCPSocket::ReadAll(Socket, buffer); // Читаем всё что есть в сокете
        if (recvData.size() != 0 && buffer.size() == 0) break; // если в сокете больше данных нет, то выходим
        recvData += buffer;
        if (buffer.size() != 0) Sleep(duration); // После последнего вычитывания ждём записи новых данных
        else Sleep(1); // Ожидаем записи данных
        if (recvData.size() == 0 && buffer.size() == 0) { // Если данные ещё не получены
            if (wait <= 0) break;
            wait--;
        }
    } while (1);

    return recvData;
}

void TCPClient::Write(QByteArray send_data)
{
    if (!isConected) return;
    TCPSocket::Write(Socket, send_data);
}
