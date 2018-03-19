#ifndef TESTSERVER_H
#define TESTSERVER_H

#include "testserverwindow.h"
#include "testservermanager.h"

class TestServer
{
public:
    TestServer();
    ~TestServer();

    void Start();

private:
    TestServerWindow window;
    TestServerManager manager;
};

#endif // TESTSERVER_H
