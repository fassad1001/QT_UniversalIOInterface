#ifndef COMPORTMONITORING_H
#define COMPORTMONITORING_H

#include "QtSerialPort/qserialport.h"
#include "../include/cserial.h"
#include "../include/plugcmdlist.h"
#include <QObject>

_DEFPTR(CSerial, TSerial)

class ComPortMonitoring : public QObject
{
    Q_OBJECT
public:
    //установка параметров  параметры установлены (настройки + периодичность)
    //открытие порта        порт открыт
    //запуск мониторинга    мониторинг ответов идёт
    //    команда найдена, получен результат
    //остановка мониторинга (очистка ком порта, остановка мониторинга, закрытие ком порта)
    ComPortMonitoring();
    ~ComPortMonitoring();

    void start(ParamSerialPort parameters, int period, bool clearStart);
    void stop();
    bool isOpen();

    QByteArray readAll();
    void write(QByteArray message);

    void clearComPort();
private:
    void close();
    bool open();
    void setMonitorPeriod(int period);
    void setComPortParameters(ParamSerialPort parameters);
    void prepareFoMonitoring();
    bool monitoringIsActive();
    TSerial m_ComPortPtr;
    ParamSerialPort _comPortParameters;
    int _monitorPeriod;

    void applyComPortParameters();

    //
    defPostPtrFuncA2(ComPortMonitoring, TStartMonitoring, StartMonitoringPtr)
    void StartMonitoringInAnotherThread();
    void StartMonitoring();
    void StopMonitoring();

signals:
    void wildMessageAppears(QByteArray message);
};

#endif // COMPORTMONITORING_H
