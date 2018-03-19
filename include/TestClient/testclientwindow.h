#ifndef TESTSERVERWINDOW_H
#define TESTSERVERWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class TestClientWindow;
}

class TestClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestClientWindow(QWidget *parent = 0);
    ~TestClientWindow();

private:
    Ui::TestClientWindow *ui;

    QLabel label;

signals:
    void signalSrartClient();
    void signalStopClient();
    void signalSendMessage(QString text);
    void signalUpdateStatus(QString text);
private slots:
    void on_pbSend_clicked();
    void slotWriteMessageToList(QString text);
};

#endif // TESTSERVERWINDOW_H
