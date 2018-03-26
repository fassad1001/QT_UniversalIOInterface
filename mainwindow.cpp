#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ioInterface()
{
    ui->setupUi(this);

    connect (&timer, SIGNAL(TimerTick()), this, SLOT(onTick()));
    connect (&ioInterface, SIGNAL(newMessage(QByteArray)), this, SLOT(onMessage(QByteArray)));

    int simpleAnswerPosition = 5;
    int simpleAnswerLength = 4;
    int messageLength = 19;

    QByteArray test("trashINFOtrashagain");
    QByteArray left = test.mid(0, simpleAnswerPosition);
    QByteArray right = test.mid((simpleAnswerPosition + simpleAnswerLength), messageLength - (simpleAnswerPosition + simpleAnswerLength));
    QByteArray full  = left.append(right);

    QByteArray text = full;
}

MainWindow::~MainWindow()
{
    ioInterface.close();
    delete ui;
}

void MainWindow::onTick()
{
    ui->spinBox->setValue(ui->spinBox->value()-1);

    if (ui->spinBox->value() <= 0)
        timer.stop();
}

void MainWindow::onMessage(QByteArray message)
{
    ui->textEdit->append(message);
}

void MainWindow::on_startSingleCountButton_2_clicked()
{
    timer.setSingleShot(true);
    timer.setPeriod(1000);
    timer.start();
}

void MainWindow::on_startCountdownButton_3_clicked()
{
    timer.setSingleShot(false);
    timer.setPeriod(1000);
    timer.start();
}

void MainWindow::on_stopCountdownButton_4_clicked()
{
    timer.stop();
}

void MainWindow::on_clearMessageBufferButton_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_TCP_ON_clicked()
{
    DeviceParameters parameters("127.0.0.1",10004,10);

    ioInterface.setParameters(parameters);

    ioInterface.open(true);
}


void MainWindow::on_VISA_ON_clicked()
{
    DeviceParameters parameters("VISA_Address!", -1);

    ioInterface.setParameters(parameters);

    ioInterface.open(true);
}

void MainWindow::on_COM_ON_clicked()
{
    ParamSerialPort param;
    param.port = "COM2";
    param.rate = 9600;
    param.dbits = 8;
    DeviceParameters parameters(param, 10);

    ioInterface.setParameters(parameters);

    ioInterface.open(true);
}

void MainWindow::on_OFF_clicked()
{
    ioInterface.close();
}

void MainWindow::on_SEND_clicked()
{
    ioInterface.write(QByteArray("LOLKEKCHEBUREK"));
}

void MainWindow::on_TCP_SERVER_ON_clicked()
{
    DeviceParameters parameters(10004, 10);

    ioInterface.setParameters(parameters);

    ioInterface.open(true);
}
