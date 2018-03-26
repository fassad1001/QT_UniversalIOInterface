#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T10:05:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = superCom
TEMPLATE = app

# Подключаю библиотеку виза
DEPENDPATH += . ../Visa/visa
INCLUDEPATH += . ../Visa/visa
LIBS     += -L. -lvisa32
LIBS += -lWs2_32
QMAKE_CXXFLAGS += -std=c++11
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    include/cserial.cpp \
    include/TCPSocket2.cpp \
    newTimers/AsyncTimer.cpp \
    myIO/ComPortMonitoring.cpp \
    myIO/DeviceIOInterface.cpp \
    myIO/DeviceParameters.cpp \
    myIO/TCPSocketMonitoring.cpp \
    myIO/VISAMonitoring.cpp \
    include/TCPServer.cpp \
    include/TCPSocket.cpp \
    myIO/TCPServerMonitoring.cpp

HEADERS += \
        mainwindow.h \
    include/cserial.h \
    include/plugcmdlist.h \
    include/pluging.h \
    include/usermsgtemplate.h \
    include/TCPSocket2.h \
    newTimers/AsyncTimer.h \
    myIO/ComPortMonitoring.h \
    myIO/DeviceIOInterface.h \
    myIO/DeviceParameters.h \
    myIO/TCPSocketMonitoring.h \
    myIO/VISAMonitoring.h \
    include/TCPServer.h \
    include/TCPSocket.h \
    myIO/TCPServerMonitoring.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    include/ReadMe.txt
