#include "testclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestClient client;
    client.Start();

    return a.exec();
}
