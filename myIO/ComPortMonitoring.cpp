#include "ComPortMonitoring.h"

ComPortMonitoring::ComPortMonitoring()
{
}

ComPortMonitoring::~ComPortMonitoring()
{
    stop();
    if (!StartMonitoringPtr.isNull())
        StartMonitoringPtr->getObj()->die();
}

void ComPortMonitoring::start(ParamSerialPort parameters, int period, bool clearStart)
{
    if (!m_ComPortPtr.isNull() && m_ComPortPtr->isOpen())
        stop();
    setComPortParameters(parameters);

    m_ComPortPtr = new CSerial(_comPortParameters.port);
    StartMonitoringPtr = createPostFuncA(ComPortMonitoring, this, &ComPortMonitoring::StartMonitoring);

    if (!m_ComPortPtr->open( GENERIC_READ | GENERIC_WRITE )){
        qDebug("Faild to open %s", _comPortParameters.port.toStdString().c_str());
        return;
    }else{
        applyComPortParameters();
        setMonitorPeriod(period);
        if (clearStart)
            m_ComPortPtr->readAll();        
        StartMonitoringInAnotherThread();
    }

}

void ComPortMonitoring::setMonitorPeriod(int period)
{
    _monitorPeriod = period;
}

void ComPortMonitoring::setComPortParameters(ParamSerialPort parameters)
{
    _comPortParameters = parameters;
}

bool ComPortMonitoring::open()
{
    if (!m_ComPortPtr->open( GENERIC_READ | GENERIC_WRITE )){
        qDebug("Faild to open %s", _comPortParameters.port.toStdString().c_str());
        return false;
    }else{
        qDebug("Open ok");
        clearComPort();
        applyComPortParameters();
    }
}

void ComPortMonitoring::close()
{
    if (!m_ComPortPtr.isNull() && m_ComPortPtr->isOpen())
        m_ComPortPtr->close();
}

bool ComPortMonitoring::isOpen()
{
    if (!m_ComPortPtr.isNull())
        m_ComPortPtr->isOpen();
    return false;
}

void ComPortMonitoring::stop()
{
    StopMonitoring();
    close();
}

QByteArray ComPortMonitoring::readAll()
{
    QByteArray message = m_ComPortPtr->readAll();
    return message;
}

void ComPortMonitoring::write(QByteArray message)
{
    if (!m_ComPortPtr.isNull() && m_ComPortPtr->isOpen())
        m_ComPortPtr->write(message);
}

void ComPortMonitoring::clearComPort()
{
    if (!m_ComPortPtr.isNull() && m_ComPortPtr->isOpen()) {
        m_ComPortPtr->readAll();
    }
}

void ComPortMonitoring::prepareFoMonitoring()
{
    if (StartMonitoringPtr.isNull())
        StartMonitoringPtr = createPostFuncA(ComPortMonitoring, this, &ComPortMonitoring::StartMonitoring);
}

bool ComPortMonitoring::monitoringIsActive()
{
    if (StartMonitoringPtr.isNull())
        return false;
    else
        return true;
}


void ComPortMonitoring::applyComPortParameters()
{
    m_ComPortPtr->setBaudRate( static_cast<QSerialPort::BaudRate>(_comPortParameters.rate) );
    m_ComPortPtr->setStopBits( static_cast<QSerialPort::StopBits>(_comPortParameters.sbits) );
    m_ComPortPtr->setParity( static_cast<QSerialPort::Parity>(_comPortParameters.parity) );
    m_ComPortPtr->setFlowControl( QSerialPort::NoFlowControl );
    m_ComPortPtr->setDataBits( static_cast<QSerialPort::DataBits>(_comPortParameters.dbits) );
    m_ComPortPtr->waitForBytesWritten(30);
    m_ComPortPtr->waitForReadyRead(50);
}

void ComPortMonitoring::StartMonitoringInAnotherThread()
{
    if (m_ComPortPtr->isOpen())
        StartMonitoringPtr->AddPostEvent();
}

void ComPortMonitoring::StartMonitoring()
{
    while (StartMonitoringPtr->getObj()->GetLiveStatus()){

        QByteArray message = m_ComPortPtr->readAll();;

        if (!message.isEmpty())
            emit wildMessageAppears(message);

        Sleep(_monitorPeriod);
    }
}

void ComPortMonitoring::StopMonitoring()
{
    if (!StartMonitoringPtr.isNull())
        StartMonitoringPtr->getObj()->die();

}
