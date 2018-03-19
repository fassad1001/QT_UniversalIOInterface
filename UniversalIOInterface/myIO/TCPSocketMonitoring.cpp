#include "TCPSocketMonitoring.h"

TCPSocketMonitoring::TCPSocketMonitoring(QObject *parent) :
    QObject(parent) ,
    TCPSocket() ,
    _clearStart(false) ,
    _isMonitoringActive(false)
{
    StartMonitoringPtr = createPostFuncA(TCPSocketMonitoring, this, &TCPSocketMonitoring::StartMonitoring);
    StopMonitoringPtr = createPostFuncA(TCPSocketMonitoring, this, &TCPSocketMonitoring::StopMonitoring);
}

TCPSocketMonitoring::~TCPSocketMonitoring()
{
    if (!StartMonitoringPtr.isNull())
        StartMonitoringPtr->getObj()->die();
    if (!StopMonitoringPtr.isNull())
        StopMonitoringPtr->getObj()->die();

    Disconnect();
}

void TCPSocketMonitoring::start(QString ip, uint port, int timer, bool clearStart)
{
    stop();

    _ip = ip;
    _port = port;
    _check_timeout = timer;
    _clearStart = clearStart;
    _isMonitoringActive = true;

    StartMonitoringInAnotherThread();

}

void TCPSocketMonitoring::stop()
{
    StopMonitoringInAnotherThread();
}

bool TCPSocketMonitoring::isOpen()
{
    return TCPSocket::IsConected();
}

QByteArray TCPSocketMonitoring::ReadAll()
{
    return Read();
}

void TCPSocketMonitoring::Write(QByteArray message)
{
    TCPSocket::Write(message);
}

void TCPSocketMonitoring::clear()
{
    Read();
}

void TCPSocketMonitoring::StartMonitoringInAnotherThread()
{
    StartMonitoringPtr->AddPostEvent();
}

void TCPSocketMonitoring::StartMonitoring()
{
    while (_isMonitoringActive) {

        CreateTCPClient();

        if (IsConected()) {

            QByteArray message = Read();
            qDebug("ReadingMessage!");
            if (!message.isEmpty()) {
                emit newMessage(message);
                qDebug("NewMessage!");
            }

        }

        Sleep(_check_timeout);
    }
}

void TCPSocketMonitoring::StopMonitoringInAnotherThread()
{
    StopMonitoringPtr->AddPostEvent();
}

void TCPSocketMonitoring::StopMonitoring()
{
    if (_isMonitoringActive && isOpen()) {
        _isMonitoringActive = false;
        Disconnect();
    }
}

void TCPSocketMonitoring::CreateTCPClient()
{
    if (_isMonitoringActive && !IsConected()) {
        Connect(_ip, _port);

        if (IsConected()) {
            if (_clearStart) {
                Read();
                _clearStart = false;
                Sleep(1000);
            }
        }

        qDebug("TCP Created!");
    }
}
