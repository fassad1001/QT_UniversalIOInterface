#ifndef TESTSERVERWINDOW_H
#define TESTSERVERWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class TestServerWindow;
}

class TestServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestServerWindow(QWidget *parent = 0);
    ~TestServerWindow();

private:
    Ui::TestServerWindow *ui;

    QLabel label;

signals:
    void signalSrartServer();
    void signalStopServer();
    void signalSetAnswer(QString text);
private slots:
    void on_pbStartServer_clicked();
    void on_pbStopServer_clicked();
    void on_pbAnswer_clicked();

    void slotWriteMessageToList(QString text);
};

#endif // TESTSERVERWINDOW_H
