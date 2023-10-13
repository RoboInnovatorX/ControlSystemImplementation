/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *ParamsButton;
    QPushButton *TorqueButton;
    QPushButton *OutputButton;
    QPushButton *CalculateButton;
    QCheckBox *PauseBox;
    QPushButton *OpenButton;
    QLabel *PauseLabel;
    QLabel *ParamsLabel;
    QLabel *InsertOutLabel;
    QLabel *CalculateLabel;
    QLabel *OpenOutLabel;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(608, 413);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ParamsButton = new QPushButton(centralwidget);
        ParamsButton->setObjectName("ParamsButton");
        ParamsButton->setGeometry(QRect(50, 140, 151, 24));
        TorqueButton = new QPushButton(centralwidget);
        TorqueButton->setObjectName("TorqueButton");
        TorqueButton->setEnabled(true);
        TorqueButton->setGeometry(QRect(50, 180, 151, 24));
        OutputButton = new QPushButton(centralwidget);
        OutputButton->setObjectName("OutputButton");
        OutputButton->setGeometry(QRect(50, 220, 151, 24));
        CalculateButton = new QPushButton(centralwidget);
        CalculateButton->setObjectName("CalculateButton");
        CalculateButton->setGeometry(QRect(50, 260, 151, 24));
        PauseBox = new QCheckBox(centralwidget);
        PauseBox->setObjectName("PauseBox");
        PauseBox->setGeometry(QRect(50, 70, 76, 20));
        OpenButton = new QPushButton(centralwidget);
        OpenButton->setObjectName("OpenButton");
        OpenButton->setGeometry(QRect(50, 300, 151, 24));
        PauseLabel = new QLabel(centralwidget);
        PauseLabel->setObjectName("PauseLabel");
        PauseLabel->setGeometry(QRect(180, 70, 91, 16));
        ParamsLabel = new QLabel(centralwidget);
        ParamsLabel->setObjectName("ParamsLabel");
        ParamsLabel->setGeometry(QRect(240, 140, 121, 16));
        InsertOutLabel = new QLabel(centralwidget);
        InsertOutLabel->setObjectName("InsertOutLabel");
        InsertOutLabel->setGeometry(QRect(240, 220, 141, 16));
        CalculateLabel = new QLabel(centralwidget);
        CalculateLabel->setObjectName("CalculateLabel");
        CalculateLabel->setGeometry(QRect(240, 260, 141, 16));
        OpenOutLabel = new QLabel(centralwidget);
        OpenOutLabel->setObjectName("OpenOutLabel");
        OpenOutLabel->setGeometry(QRect(240, 300, 201, 16));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(true);
        label->setGeometry(QRect(240, 180, 131, 16));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(50, 340, 151, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(240, 340, 141, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 608, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ParamsButton->setText(QCoreApplication::translate("MainWindow", "Insert Params File", nullptr));
        TorqueButton->setText(QCoreApplication::translate("MainWindow", "Insert Input Torque", nullptr));
        OutputButton->setText(QCoreApplication::translate("MainWindow", "Insert Output File", nullptr));
        CalculateButton->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        PauseBox->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        OpenButton->setText(QCoreApplication::translate("MainWindow", "Open Output File", nullptr));
        PauseLabel->setText(QCoreApplication::translate("MainWindow", "Press to Pause", nullptr));
        ParamsLabel->setText(QCoreApplication::translate("MainWindow", "No file added", nullptr));
        InsertOutLabel->setText(QCoreApplication::translate("MainWindow", "No file added", nullptr));
        CalculateLabel->setText(QCoreApplication::translate("MainWindow", "Press to Calculate", nullptr));
        OpenOutLabel->setText(QCoreApplication::translate("MainWindow", "Press to open the output data", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "No file added", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Delete Output File", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Press to delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
