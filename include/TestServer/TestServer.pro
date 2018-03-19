#-------------------------------------------------
#
# Project created by QtCreator 2017-04-27T10:46:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestServer
TEMPLATE = app

LIBS += -lWs2_32

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        testserverwindow.cpp \
    testserver.cpp \
    ../TCPClient.cpp \
    testservermanager.cpp \
    ../TCPSocket.cpp \
    ../TCPServer.cpp

HEADERS  += testserverwindow.h \
    testserver.h \
    ../plugcmdlist.h \
    ../TCPClient.h \
    ../easy_log.h \
    testservermanager.h \
    ../TCPSocket.h \
    ../TCPServer.h

FORMS    += testserverwindow.ui
