#include "DeviceIOInterface.h"

DeviceIOInterface::DeviceIOInterface(QObject *parent) :
    QObject(parent) ,
    _parameters() ,
    _connections(0)
{
}

DeviceIOInterface::DeviceIOInterface(DeviceParameters parameters
        , QObject *parent) :
    QObject(parent) ,
    _parameters() ,
    _connections(0)
{
    setParameters(parameters);
}

void DeviceIOInterface::setParameters(DeviceParameters parameters)
{
    disconnectAllsignals();
    close();
    _parameters = parameters;
}

void DeviceIOInterface::open(bool clearStart)
{
    disconnectAllsignals();
    switch (_parameters.type()) {
    case DEVICE_IO_PARAMETERS_TYPE::COM_PORT:
        connectSerialsignals();
        _serialIOInterface.start(_parameters.comPortParameters(), _parameters.period(), clearStart);
        break;
    case DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT:
        connectTCPIpSocketSignals();
        _TCPSocketIOInterface.start(_parameters.ip(), _parameters.port(), _parameters.TCPperiod(), clearStart);
        break;
    case DEVICE_IO_PARAMETERS_TYPE::VISA:
        connectVISASocketSignal();
        _VISAIOInterface.start(_parameters.VISA_ADDRESS(), _parameters.attributes());
        break;
    default:
        break;
    }
}

bool DeviceIOInterface::isOpen()
{
    switch (_parameters.type()) {
    case DEVICE_IO_PARAMETERS_TYPE::COM_PORT:
        return _serialIOInterface.isOpen();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT:
        return _TCPSocketIOInterface.isOpen();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::VISA:
        return _VISAIOInterface.isOpen();
        break;
    default:
        return false;
        break;
    }
}

void DeviceIOInterface::close()
{
    switch (_parameters.type()) {
    case DEVICE_IO_PARAMETERS_TYPE::COM_PORT:
        _serialIOInterface.stop();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT:
        _TCPSocketIOInterface.stop();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::VISA:
        _VISAIOInterface.stop();
        break;
    default:
        break;
    }

    disconnectAllsignals();
}

void DeviceIOInterface::write(QByteArray message)
{
    switch (_parameters.type()) {
    case DEVICE_IO_PARAMETERS_TYPE::COM_PORT:
        connectSerialsignals();
        _serialIOInterface.write(message);
        break;
    case DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT:
        connectTCPIpSocketSignals();
        _TCPSocketIOInterface.Write(message);
        break;
    case DEVICE_IO_PARAMETERS_TYPE::VISA:
        connectVISASocketSignal();
        _VISAIOInterface.write(message);
        break;
    default:
        break;
    }
}

void DeviceIOInterface::clear()
{
    switch (_parameters.type()) {
    case DEVICE_IO_PARAMETERS_TYPE::COM_PORT:
        _serialIOInterface.clearComPort();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT:
        _TCPSocketIOInterface.clear();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::VISA:
        _VISAIOInterface.clear();
        break;
    default:
        break;
    }
}

void DeviceIOInterface::connectSerialsignals()
{
    if (_connections == 0) {
        _connections = 1;
        connect (&_serialIOInterface, SIGNAL(wildMessageAppears(QByteArray)), this, SIGNAL(newMessage(QByteArray)));
        qDebug("COM slot connect");
    }
}

void DeviceIOInterface::disconnectSerialsignals()
{
    if (_connections == 1) {
        _connections = 0;
        disconnect (&_serialIOInterface, SIGNAL(wildMessageAppears(QByteArray)), this, SIGNAL(newMessage(QByteArray)));
        qDebug("COM slot disconnect");
    }
}

void DeviceIOInterface::connectTCPIpSocketSignals()
{
    if (_connections == 0) {
        _connections = 1;
        connect (&_TCPSocketIOInterface, SIGNAL(newMessage(QByteArray)), this, SIGNAL(newMessage(QByteArray)));
        qDebug("TCP slot connect");
    }
}

void DeviceIOInterface::disconnectTCPIpSocketSignals()
{
    if (_connections == 1) {
        _connections = 0;
        disconnect (&_TCPSocketIOInterface, SIGNAL(newMessage(QByteArray)), this, SIGNAL(newMessage(QByteArray)));
        qDebug("TCP slot disconnect");
    }
}

void DeviceIOInterface::connectVISASocketSignal()
{
    if (_connections == 0) {
        _connections = 1;
//        connect (&_VISAIOInterface, SIGNAL(newMessage(QByteArray)), this, SIGNAL(newMessage(QByteArray)));
        qDebug("VISA slot connect");
    }
}

void DeviceIOInterface::disconnectVISASocketSignal()
{
    if (_connections == 1) {
        _connections = 0;
//        disconnect (&_VISAIOInterface, SIGNAL(newMessage(QByteArray)), this, SIGNAL(newMessage(QByteArray)));
        qDebug("VISA slot disconnect");
    }

}

void DeviceIOInterface::disconnectAllsignals()
{
    switch (_parameters.type()) {
    case DEVICE_IO_PARAMETERS_TYPE::COM_PORT:
        disconnectSerialsignals();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT:
        disconnectTCPIpSocketSignals();
        break;
    case DEVICE_IO_PARAMETERS_TYPE::VISA:
        disconnectVISASocketSignal();
    default:
        break;
    }

}

