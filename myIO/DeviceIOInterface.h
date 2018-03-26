#ifndef DEVICEIOINTERFACE_H
#define DEVICEIOINTERFACE_H

#include <QObject>

#include "DeviceParameters.h"

class DeviceIOInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceIOInterface(QObject *parent = nullptr);
    explicit DeviceIOInterface(DeviceParameters parameters, QObject *parent = nullptr);

    void setParameters(DeviceParameters parameters);

    void open(bool clearStart = false);
    bool isOpen();
    void clear();
    void write(QByteArray message);
    void close();

private:
    int _connections;
    DeviceParameters _parameters;

    ComPortMonitoring _serialIOInterface;
    void connectSerialsignals();
    void disconnectSerialsignals();

    TCPServerMonitoring _TCPServerIOInterface;
    void connectTCPIpServerSignals();
    void disconnectTCPIpServerSignals();

    TCPSocketMonitoring _TCPSocketIOInterface;
    void connectTCPIpSocketSignals();
    void disconnectTCPIpSocketSignals();

    VISAMonitoring _VISAIOInterface;
    void connectVISASocketSignal();
    void disconnectVISASocketSignal();


    void disconnectAllsignals();

signals:
    void newMessage(QByteArray message);
public slots:
};

#endif // DEVICEIOINTERFACE_H
