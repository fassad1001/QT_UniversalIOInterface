#include "VISAMonitoring.h"

VISAMonitoring::VISAMonitoring(QObject *parent) :
    QObject(parent) ,
    _sessionStatus(-1)
{

}

void VISAMonitoring::start(ViRsrc VISA_ADDRESS, QList<QPair<int, int>> attributes)
{
    _VISA_ADDRESS = VISA_ADDRESS;
    _attributes = attributes;

    openSession();
}

void VISAMonitoring::stop()
{
    closeSession();
}

void VISAMonitoring::openSession()
{
    // Change VISA_ADDRESS to a serial VISA address, e.g. "ASRL2::INSTR"
    //TCPIP0::169.254.149.193::inst0::INSTR - N9000
    //USB::0x0699::0x03A6::C050246::INSTR - TDS2024

    // Create a connection (session) to the serial instrument
    viOpenDefaultRM(&_resourceManager);

    //ТУДУ - возможно значение в _VISA_ADDRESS будет неправильным при копировании!
    _sessionStatus = viOpen(_resourceManager, _VISA_ADDRESS, VI_NO_LOCK, 0, &_session);

    foreach (PARAMETER attribute, _attributes) {
        setAttribute(attribute.first, attribute.second);
    }
}

void VISAMonitoring::closeDeviceSession()
{
    viClose(_session);

    _sessionStatus = -1;
}

void VISAMonitoring::closeResourceManagerSession()
{
    viClose(_resourceManager);
}

void VISAMonitoring::closeSession()
{
    closeDeviceSession();
    closeResourceManagerSession();
}

bool VISAMonitoring::isOpen()
{
    if (_sessionStatus >= VI_SUCCESS) {
        return true;
    } else {
        return false;
    }
}

QByteArray VISAMonitoring::readAll()
{
    return read();
}

void VISAMonitoring::write(QByteArray message)
{
    send(message.data());
}

void VISAMonitoring::clear()
{
    read();
}

void VISAMonitoring::setAttribute(int attributeName, int attributeValue)
{
    viSetAttribute(_session, attributeName, attributeValue);
}

void VISAMonitoring::send(ViString message)
{
    viPrintf(_session, message);
}

QByteArray VISAMonitoring::read()
{
    char readBuf[256] = {0};
    viScanf(_session, "%s", readBuf);

    QByteArray readQBABuf;
    readQBABuf.append(readBuf);

    return readQBABuf;
}
