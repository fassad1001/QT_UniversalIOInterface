#include "DeviceParameters.h"


DeviceParameters::DeviceParameters() :
    _type(DEVICE_IO_PARAMETERS_TYPE::NONE)
{
}

DeviceParameters::DeviceParameters(ParamSerialPort comPortparameters, int period) :
    _comPortParameters(comPortparameters) ,
    _COMperiod(period) ,
    _type(DEVICE_IO_PARAMETERS_TYPE::COM_PORT)
{
}

DeviceParameters::DeviceParameters(QString ip, uint port, int period) :
    _ip(ip) ,
    _port(port) ,
    _TCPperiod(period) ,
    _type(DEVICE_IO_PARAMETERS_TYPE::TCP_IP_CLIENT)
{
}

DeviceParameters::DeviceParameters(QString VISAAddress, int period, QList<QPair<int, int>> attributes) :
    _VISA_ADDRESS(VISAAddress) ,
    _VISA_ADDRESS_QBA(VISAAddress.toLatin1()) ,
    _VISAPeriod(period) ,
    _attributes(attributes) ,
    _type(DEVICE_IO_PARAMETERS_TYPE::VISA)
{
}

DEVICE_IO_PARAMETERS_TYPE DeviceParameters::type() const
{
    return _type;
}

ParamSerialPort DeviceParameters::comPortParameters() const
{
    return _comPortParameters;
}

int DeviceParameters::period() const
{
    return _COMperiod;
}

QString DeviceParameters::ip() const
{
    return _ip;
}

uint DeviceParameters::port() const
{
    return _port;
}

int DeviceParameters::TCPperiod() const
{
    return _TCPperiod;
}

ViRsrc DeviceParameters::VISA_ADDRESS() const
{
    return (char*)_VISA_ADDRESS_QBA.data();
}

int DeviceParameters::VISAPeriod() const
{
    return _VISAPeriod;
}

QList<QPair<int, int> > DeviceParameters::attributes() const
{
    return _attributes;
}
