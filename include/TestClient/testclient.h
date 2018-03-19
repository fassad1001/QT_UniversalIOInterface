#ifndef TESTSERVER_H
#define TESTSERVER_H

#include "testclientwindow.h"
#include "testclientmanager.h"

class TestClient
{
public:
    TestClient();
    ~TestClient();

    void Start();

private:
    TestClientWindow window;
    TestClientManager manager;
};

#endif // TESTSERVER_H
