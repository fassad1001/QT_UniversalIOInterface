#include "TCPSocket.h"

TCPSocket::TCPSocket() : isWSACleanup(false)
{
    Port = 12345;
}

TCPSocket::~TCPSocket()
{
}

bool TCPSocket::Inisialized()
{
    //We need to check the version.
    int isResult = WSAStartup(MAKEWORD(2, 2), &version);
    if (isResult != 0){
        std::cout << "This version is not supported! - \n" << WSAGetLastError() << std::endl;
        return false;
    } else {
        isWSACleanup = false;
        std::cout << "Good - Everything fine!\n" << std::endl;
    }

    resAddr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    isResult = getaddrinfo(NULL, QString::number(Port).toStdString().c_str(), &hints, &resAddr);
    if ( isResult != 0 ) {
        std::cout << "getaddrinfo failed with error: " << isResult << std::endl;
        freeaddrinfo(resAddr);
        WSACleanup();
        return false;
    }

    Socket = socket(resAddr->ai_family, resAddr->ai_socktype, resAddr->ai_protocol);
    if (Socket == INVALID_SOCKET) {
        std::cout << "Creating socket fail\n";
        freeaddrinfo(resAddr);
        WSACleanup();
    } else {
        std::cout << "It was okay to create the socket\n";

        //DWORD timeout = SOCKET_READ_TIMEOUT_SEC * 1000;
        //setsockopt(u_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    }

    return true;
}

bool TCPSocket::Read(SOCKET _socket, int count_byte, QByteArray &recvData)
{
    recvData.clear();
    unsigned long length;
    ioctlsocket(_socket, FIONREAD, &length);
    if (length != 0) {
        char *buff = new char[length];

        int get = recv(_socket, &buff[0], count_byte, 0);
        if (get == SOCKET_ERROR){
            std::cout << "Error in Receiving: " << WSAGetLastError() << std::endl;
            return false;
        }
        recvData.append(buff, get);
        delete [] buff;
    }
    return true;
}

bool TCPSocket::ReadAll(SOCKET _socket, QByteArray &recvData)
{
    recvData.clear();
    unsigned long length;
    ioctlsocket(_socket, FIONREAD, &length); // получить максимальное число байт, которое можно вычитать из порта
    if (!Read(_socket, length, recvData)) {
        return false;
    }
    return true;
}

bool TCPSocket::Write(SOCKET _socket, QByteArray send_data)
{
    int smsg = send(_socket, send_data.data(), send_data.size() * sizeof(char), 0);
    if(smsg == SOCKET_ERROR){
        std::cout << "Error: " << WSAGetLastError() << std::endl;
        if (!isWSACleanup) WSACleanup();
        isWSACleanup = true;
        return false;
    }
    return true;
}
