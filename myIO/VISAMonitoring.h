#ifndef VISAMONITORING_H
#define VISAMONITORING_H

#include <QObject>
#include "visa.h"
#include <QPair>
//    void start(ViRsrc VISA_ADDRESS);
//Значения переменных установленны
//    ViSession openSession();
//Открытие данных на базе сохраненных значений

//Отправка команды
//Чтение ответа из буффера

#define PARAMETER QPair<int,int>

class VISAMonitoring : public QObject
{
    Q_OBJECT
public:
    explicit VISAMonitoring(QObject *parent = nullptr);

    void start(ViRsrc VISA_ADDRESS, QList<QPair<int, int>> attributes);
    //после    void start(ViRsrc VISA_ADDRESS);
    void stop();
    //после    void start(ViRsrc VISA_ADDRESS);
    bool isOpen();

    QByteArray readAll();
    void write(QByteArray message);

    void clear();
private:
    ViRsrc _VISA_ADDRESS;
    ViSession _resourceManager;
    ViSession _session;

    ViStatus _sessionStatus;

    QList<QPair<int, int>> _attributes;

    //после    void start(ViRsrc VISA_ADDRESS);
    void openSession();

    //после    void openSession();
    void closeDeviceSession();
    //после    void openSession();
    void closeResourceManagerSession();
    //после    void openSession();
    void closeSession();
    //после    void openSession();
    void setAttribute(int attributeName, int attributeValue);
    //после    void openSession();
    void send(ViString message);
    //после    void openSession();
    QByteArray read();
signals:

public slots:
};

#endif // VISAMONITORING_H
