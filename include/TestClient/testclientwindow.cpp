#include "testclientwindow.h"
#include "ui_testclientwindow.h"

TestClientWindow::TestClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestClientWindow)
{
    ui->setupUi(this);

    ui->statusBar->addWidget(&label);
    label.setText(tr("Клиент не подключен"));

    connect(ui->pbStartClient, SIGNAL(clicked()), this, SIGNAL(signalSrartClient()));
    connect(ui->pbStopClient, SIGNAL(clicked()), this, SIGNAL(signalStopClient()));
    connect(this, SIGNAL(signalUpdateStatus(QString)), &label, SLOT(setText(QString)));
}

TestClientWindow::~TestClientWindow()
{
    delete ui;
}

void TestClientWindow::on_pbSend_clicked()
{
    if (!ui->leMessage->text().isEmpty()) {
        emit signalSendMessage(ui->leMessage->text());
    }
}

void TestClientWindow::slotWriteMessageToList(QString text)
{
    ui->lwList->addItem(text);
}
