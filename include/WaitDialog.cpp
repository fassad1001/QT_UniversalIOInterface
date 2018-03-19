#include "WaitDialog.h"
#include "ui_WaitDialog.h"
#include <QMessageBox>

WaitDialog::WaitDialog(int max_time_wait, QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
    ui(new Ui::WaitDialog), time(0), maxTimeWait(max_time_wait)
{
    ui->setupUi(this);

    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::show()
{
    timer.start();
    QDialog::show();
}

void WaitDialog::SetMaxTimeWait(int timeWait)
{
    maxTimeWait = timeWait;
}

int WaitDialog::GetMaxTimeWait()
{
    return maxTimeWait;
}

void WaitDialog::SetText(QString text)
{
    ui->lMainText->setText(text);
}

void WaitDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape
            || (event->key() == Qt::Key_F4
                && event->modifiers() == Qt::ALT)) {
        return;
    } else {
        QDialog::keyPressEvent(event);
    }
}

void WaitDialog::slotTimeout()
{
    time += timer.interval();
    if (time == maxTimeWait) {
        timer.stop();
        emit complete();
        time = 0;
        close();
    }
}
