#-------------------------------------------------
#
# Project created by QtCreator 2017-04-27T10:46:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestClient
TEMPLATE = app

LIBS += -lWs2_32

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        testclientwindow.cpp \
    testclient.cpp \
    ../TCPClient.cpp \
    testclientmanager.cpp \
    ../TCPSocket.cpp \
    ../TCPServer.cpp

HEADERS  += testclientwindow.h \
    testclient.h \
    ../plugcmdlist.h \
    ../TCPClient.h \
    ../easy_log.h \
    testclientmanager.h \
    ../TCPSocket.h \
    ../TCPServer.h

FORMS    += testclientwindow.ui
