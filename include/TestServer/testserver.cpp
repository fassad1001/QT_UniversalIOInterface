#include "testserver.h"

TestServer::TestServer()
{
    QObject::connect(&window, SIGNAL(signalSrartServer()), &manager, SLOT(StartMonitoring()));
    QObject::connect(&window, SIGNAL(signalStopServer()), &manager, SLOT(StopMonitoring()));
    QObject::connect(&window, SIGNAL(signalSetAnswer(QString)), &manager, SLOT(slotSetAnswer(QString)));
    QObject::connect(&manager, SIGNAL(signalWriteMessageToList(QString)), &window, SLOT(slotWriteMessageToList(QString)));
}

TestServer::~TestServer()
{

}

void TestServer::Start()
{
    window.show();
}
