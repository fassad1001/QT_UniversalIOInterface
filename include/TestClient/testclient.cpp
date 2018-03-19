#include "testclient.h"

TestClient::TestClient()
{
    QObject::connect(&window, SIGNAL(signalSrartClient()), &manager, SLOT(StartMonitoring()));
    QObject::connect(&window, SIGNAL(signalStopClient()), &manager, SLOT(StopMonitoring()));
    QObject::connect(&window, SIGNAL(signalSendMessage(QString)), &manager, SLOT(slotSendMessage(QString)));
    QObject::connect(&manager, SIGNAL(signalUpdateStatus(QString)), &window, SIGNAL(signalUpdateStatus(QString)));
    QObject::connect(&manager, SIGNAL(signalWriteMessageToList(QString)), &window, SLOT(slotWriteMessageToList(QString)));
}

TestClient::~TestClient()
{

}

void TestClient::Start()
{
    window.show();
}
