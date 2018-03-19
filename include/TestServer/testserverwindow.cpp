#include "testserverwindow.h"
#include "ui_testserverwindow.h"

TestServerWindow::TestServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestServerWindow)
{
    ui->setupUi(this);

    ui->statusBar->addWidget(&label);
    label.setText(tr("Сервер выключен"));

    connect(ui->pbStartServer, SIGNAL(clicked()), this, SIGNAL(signalSrartServer()));
    connect(ui->pbStopServer, SIGNAL(clicked()), this, SIGNAL(signalStopServer()));
}

TestServerWindow::~TestServerWindow()
{
    delete ui;
}

void TestServerWindow::on_pbStartServer_clicked()
{
    label.setText(tr("Сервер включен"));
}

void TestServerWindow::on_pbStopServer_clicked()
{
    label.setText(tr("Сервер выключен"));
}

void TestServerWindow::on_pbAnswer_clicked()
{
    emit signalSetAnswer(ui->leAnswer->text());
}

void TestServerWindow::slotWriteMessageToList(QString text)
{
    ui->lwList->addItem(text);
}
