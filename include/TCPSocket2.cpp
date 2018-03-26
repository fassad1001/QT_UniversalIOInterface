#include "TCPSocket2.h"

TCPSocket2::TCPSocket2() : isWSACleanup(false)
{
}

TCPSocket2::TCPSocket2(QString ip, unsigned int port) : isWSACleanup(false)
{
    //Socket address information
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.toStdString().data());
    addr.sin_port = htons(port);
}


TCPSocket2::~TCPSocket2()
{
    Disconnect();
}

void TCPSocket2::Inisialized()
{
    isConected = false;

    //We need to check the version.
    WORD mkword = MAKEWORD(2, 2);
    int what = WSAStartup(mkword, &version);
    if (what != 0){
        std::cout << "This version is not supported! - \n" << WSAGetLastError() << std::endl;
    } else {
        isWSACleanup = false;
        std::cout << "Good - Everything fine!\n" << std::endl;
    }

    u_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (u_sock == INVALID_SOCKET) {
        std::cout << "Creating socket fail\n";
    } else {
        std::cout << "It was okay to create the socket\n";

        DWORD timeout = SOCKET_READ_TIMEOUT_SEC2 * 1000;
        setsockopt(u_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    }   
}

int TCPSocket2::Connect()
{
    Inisialized();
    int conn = connect(u_sock, (SOCKADDR*)&addr, sizeof(addr));
    if (conn == SOCKET_ERROR){
        isConected = false;
        std::cout << "Error - when connecting " << WSAGetLastError() << std::endl;
        closesocket(u_sock);
        if (!isWSACleanup) WSACleanup();
        isWSACleanup = true;
    } else {
        isConected = true;
    }
    return conn;
}

int TCPSocket2::Connect(QString ip, unsigned int port)
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.toStdString().data());
    addr.sin_port = htons(port);

    return Connect();
}

void TCPSocket2::SetSettings(QString ip, unsigned int port)
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.toStdString().data());
    addr.sin_port = htons(port);
}

void TCPSocket2::Disconnect()
{
    if (isConected) {
        isConected = false;
        closesocket(u_sock);
    }
}

QByteArray TCPSocket2::Read(int count_byte)
{
    if (!isConected) return QByteArray();
    QByteArray recv_data;
    char *buff = new char[count_byte];
    int get = recv(u_sock, &buff[0], count_byte, 0);
    if (get == SOCKET_ERROR){
        int lastError = WSAGetLastError();
        if (lastError > 0) {
            Disconnect();
            isConected = false;
            std::cout << "Error in Receiving: " << lastError << std::endl;
        }
    }
    recv_data.append(buff, get);
    delete [] buff;
    return recv_data;
}


QByteArray TCPSocket2::Read()
{
    return Read(1024);
}

void TCPSocket2::Write(QByteArray send_data)
{
    if (!isConected) return;
    std::cout << send_data.size() << std::endl;
    int smsg = send(u_sock, send_data.data(), send_data.size() * sizeof(char), 0);
    if(smsg == SOCKET_ERROR){
        if (!isWSACleanup) WSACleanup();
        isWSACleanup = true;
        isConected = false;
        Disconnect();
        std::cout << "Error: " << WSAGetLastError() << std::endl;
    }
}

bool TCPSocket2::IsConected()
{
    return isConected;
}
