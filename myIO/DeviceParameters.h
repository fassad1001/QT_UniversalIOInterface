#ifndef DEVICEPARAMETERS
#define DEVICEPARAMETERS

#include "ComPortMonitoring.h"
#include "TCPServerMonitoring.h"
#include "TCPSocketMonitoring.h"
#include "VISAMonitoring.h"

enum class DEVICE_IO_PARAMETERS_TYPE {
    NONE ,
    COM_PORT ,

    TCP_IP_SERVER ,

    TCP_IP_CLIENT ,
    VISA
};

class DeviceParameters
{
public:
    DeviceParameters();
    DeviceParameters(ParamSerialPort comPortparameters, int period);


    DeviceParameters(uint port, int period);

    DeviceParameters(QString ip, uint port, int period);
    DeviceParameters(QString VISAAddress, int period = -1, QList<QPair<int, int>> attributes = QList<QPair<int, int>>());

    DEVICE_IO_PARAMETERS_TYPE type() const;

    ParamSerialPort comPortParameters() const;
    int period() const;

//    uint portServer() const;
//    int TCPperiodServer() const;

    QString ip() const;
    uint port() const;
    int TCPperiod() const;

    ViRsrc VISA_ADDRESS() const;
    int VISAPeriod() const;
    QList<QPair<int, int> > attributes() const;

private:
    DEVICE_IO_PARAMETERS_TYPE _type;

    ParamSerialPort _comPortParameters;
    int _COMperiod;

//    uint _portServer;
//    int _TCPperiodServer;

    QString _ip;
    uint _port;
    int _TCPperiod;

    QString _VISA_ADDRESS;
    QByteArray _VISA_ADDRESS_QBA;
    int _VISAPeriod;
    QList<QPair<int, int>> _attributes;

};

#endif // DEVICEPARAMETERS
