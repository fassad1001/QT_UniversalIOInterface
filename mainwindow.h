#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include "myIO/DeviceParameters.h"
#include "myIO/DeviceIOInterface.h"
#include "newTimers/AsyncTimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    DeviceIOInterface ioInterface;
    AsyncTimer timer;

private slots:
    void onTick();
    void onMessage(QByteArray message);

    void on_startSingleCountButton_2_clicked();

    void on_startCountdownButton_3_clicked();

    void on_stopCountdownButton_4_clicked();

    void on_clearMessageBufferButton_clicked();

    void on_TCP_ON_clicked();

    void on_VISA_ON_clicked();

    void on_COM_ON_clicked();

    void on_OFF_clicked();

    void on_SEND_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
