#include "testserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestServer server;
    server.Start();

    return a.exec();
}
