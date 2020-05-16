/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "bottomframe.h"
#include "parameterframe.h"
#include "topframe.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    TopFrame *topFrame;
    ParameterFrame *treeFrame;
    QFrame *paraFrame;
    QFrame *graphicsFrame;
    BottomFrame *bottomFrame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1366, 768);
        MainWindow->setMinimumSize(QSize(960, 540));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        topFrame = new TopFrame(centralwidget);
        topFrame->setObjectName(QString::fromUtf8("topFrame"));
        topFrame->setBaseSize(QSize(0, 0));
        topFrame->setFrameShape(QFrame::Box);
        topFrame->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(topFrame, 0, 0, 1, 3);

        treeFrame = new ParameterFrame(centralwidget);
        treeFrame->setObjectName(QString::fromUtf8("treeFrame"));
        treeFrame->setFrameShape(QFrame::Box);
        treeFrame->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(treeFrame, 1, 0, 1, 1);

        paraFrame = new QFrame(centralwidget);
        paraFrame->setObjectName(QString::fromUtf8("paraFrame"));
        paraFrame->setFrameShape(QFrame::Box);
        paraFrame->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(paraFrame, 1, 1, 1, 1);

        graphicsFrame = new QFrame(centralwidget);
        graphicsFrame->setObjectName(QString::fromUtf8("graphicsFrame"));
        graphicsFrame->setFrameShape(QFrame::Box);
        graphicsFrame->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(graphicsFrame, 1, 2, 1, 1);

        bottomFrame = new BottomFrame(centralwidget);
        bottomFrame->setObjectName(QString::fromUtf8("bottomFrame"));
        bottomFrame->setFrameShape(QFrame::Box);
        bottomFrame->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(bottomFrame, 2, 0, 1, 3);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 8);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1366, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
