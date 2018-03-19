#include "AsyncTimer.h"

AsyncTimer::AsyncTimer(QObject *parent) :
    QObject(parent) ,
    _isDebug(true)
{
    initPostPointers();
}

AsyncTimer::AsyncTimer(int TimerPeriod, bool isSingleTime, QObject *parent) :
    QObject(parent) ,
    _timer(TimerPeriod) ,
    _isSingleTime(isSingleTime) ,
    _isDebug(true)
{
    initPostPointers();
}

void AsyncTimer::start()
{
    myDebug("start()");
    stop();
    _isLive = true;
    StartTimerInAnotherThread();
}

void AsyncTimer::start(int timer)
{
    myDebug("start(int timer)");
    _timer = timer;
    start();
}

void AsyncTimer::stop()
{
    myDebug("stop()");
    StopTimer();
}

void AsyncTimer::setSingleShot(bool value)
{
     myDebug("setSingleShot(bool value)");
    _isSingleTime = value;
}

void AsyncTimer::setPeriod(int period)
{
    myDebug("setPeriod(int period)");
    _timer = period;
}

void AsyncTimer::StartTimer()
{
    myDebug("StartTimer()");
    while (_isLive){

        Sleep(_timer);

        if (_isLive)
            emit TimerTick();

        if (_isSingleTime) {
            StopTimer();
        }
    }
}

void AsyncTimer::StopTimer()
{
    myDebug("StopTimer()");
    _isLive = false;
//    if (!StartTimerPtr.isNull() && StartTimerPtr->getObj()->GetLiveStatus())
//        StartTimerPtr->getObj()->die();
}

void AsyncTimer::myDebug(QString message)
{
    if (_isDebug) {
        QString debugMsg;
        debugMsg.append("AsyncTimer : ");
        debugMsg.append(message);
        qDebug(debugMsg.toStdString().c_str());
    }
}

void AsyncTimer::initPostPointers()
{
    StartTimerPtr = createPostFuncA(AsyncTimer, this, &AsyncTimer::StartTimer);
}

void AsyncTimer::StartTimerInAnotherThread()
{
    myDebug("StartTimerInAnotherThread()");
    StartTimerPtr->AddPostEvent();
}
