#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QCloseEvent>

namespace NSWaitDialog {
    const int MAX_TIME_WAIT = 15000;
}

namespace Ui {
class WaitDialog;
}

class WaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitDialog(int max_time = NSWaitDialog::MAX_TIME_WAIT, QWidget *parent = 0);
    ~WaitDialog();

    void SetMaxTimeWait(int time);
    int GetMaxTimeWait();

    void SetText(QString text);
public slots:
    virtual void show();

private slots:
    void slotTimeout();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::WaitDialog *ui;

    QTimer timer;
    int time;
    int maxTimeWait;
signals:
    void complete();
};

#endif // MULTIPLEXERWAITDIALOG_H
