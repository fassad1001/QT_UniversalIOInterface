/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QPushButton *stopCountdownButton_4;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *TCP_ON;
    QPushButton *startSingleCountButton_2;
    QPushButton *COM_ON;
    QLabel *label;
    QPushButton *clearMessageBufferButton;
    QPushButton *startCountdownButton_3;
    QPushButton *VISA_ON;
    QLabel *label_3;
    QPushButton *SEND;
    QPushButton *OFF;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(556, 376);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout->addWidget(spinBox, 3, 2, 2, 1);

        stopCountdownButton_4 = new QPushButton(centralWidget);
        stopCountdownButton_4->setObjectName(QStringLiteral("stopCountdownButton_4"));

        gridLayout->addWidget(stopCountdownButton_4, 3, 3, 2, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 5, 0, 1, 4);

        TCP_ON = new QPushButton(centralWidget);
        TCP_ON->setObjectName(QStringLiteral("TCP_ON"));

        gridLayout->addWidget(TCP_ON, 1, 1, 1, 1);

        startSingleCountButton_2 = new QPushButton(centralWidget);
        startSingleCountButton_2->setObjectName(QStringLiteral("startSingleCountButton_2"));

        gridLayout->addWidget(startSingleCountButton_2, 3, 0, 1, 2);

        COM_ON = new QPushButton(centralWidget);
        COM_ON->setObjectName(QStringLiteral("COM_ON"));

        gridLayout->addWidget(COM_ON, 0, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        clearMessageBufferButton = new QPushButton(centralWidget);
        clearMessageBufferButton->setObjectName(QStringLiteral("clearMessageBufferButton"));

        gridLayout->addWidget(clearMessageBufferButton, 6, 0, 1, 4);

        startCountdownButton_3 = new QPushButton(centralWidget);
        startCountdownButton_3->setObjectName(QStringLiteral("startCountdownButton_3"));

        gridLayout->addWidget(startCountdownButton_3, 4, 0, 1, 2);

        VISA_ON = new QPushButton(centralWidget);
        VISA_ON->setObjectName(QStringLiteral("VISA_ON"));

        gridLayout->addWidget(VISA_ON, 2, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        SEND = new QPushButton(centralWidget);
        SEND->setObjectName(QStringLiteral("SEND"));

        gridLayout->addWidget(SEND, 0, 3, 3, 1);

        OFF = new QPushButton(centralWidget);
        OFF->setObjectName(QStringLiteral("OFF"));

        gridLayout->addWidget(OFF, 0, 2, 3, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        stopCountdownButton_4->setText(QApplication::translate("MainWindow", "STOP", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "TCPIP", Q_NULLPTR));
        TCP_ON->setText(QApplication::translate("MainWindow", "ON", Q_NULLPTR));
        startSingleCountButton_2->setText(QApplication::translate("MainWindow", "single", Q_NULLPTR));
        COM_ON->setText(QApplication::translate("MainWindow", "ON", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "COM", Q_NULLPTR));
        clearMessageBufferButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", Q_NULLPTR));
        startCountdownButton_3->setText(QApplication::translate("MainWindow", "countdown", Q_NULLPTR));
        VISA_ON->setText(QApplication::translate("MainWindow", "ON", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "VISA", Q_NULLPTR));
        SEND->setText(QApplication::translate("MainWindow", "SEND", Q_NULLPTR));
        OFF->setText(QApplication::translate("MainWindow", "OFF", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
