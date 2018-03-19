#ifndef ASYNCTIMER_H
#define ASYNCTIMER_H

#include <QObject>
#include <QDebug>
#include "../include/plugcmdlist.h"

class AsyncTimer : public QObject
{
    Q_OBJECT
public:
    explicit AsyncTimer(QObject *parent = nullptr);
    explicit AsyncTimer(int TimerPeriod, bool isSingleTime = false, QObject *parent = nullptr);
    void start();
    void start(int timer);
    void stop();
    void setSingleShot(bool value);
    void setPeriod(int period);

private:
    defPostPtrFuncA2(AsyncTimer, TStartTimer, StartTimerPtr)
    void StartTimerInAnotherThread();
    void StartTimer();
    void StopTimer();

    void myDebug(QString message);
    void initPostPointers();

    bool _isLive;
    bool _isDebug;
    int _timer;
    bool _isSingleTime;

signals:
    void TimerTick();
public slots:
};

#endif // ASYNCTIMER_H
