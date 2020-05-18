/********************************************************************************
** Form generated from reading UI file 'topframe.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPFRAME_H
#define UI_TOPFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TopFrame
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QLabel *label;

    void setupUi(QWidget *TopFrame)
    {
        if (TopFrame->objectName().isEmpty())
            TopFrame->setObjectName(QString::fromUtf8("TopFrame"));
        TopFrame->resize(1187, 126);
        gridLayout = new QGridLayout(TopFrame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame_2 = new QFrame(TopFrame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(frame_2, 0, 1, 1, 1);

        label = new QLabel(TopFrame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 9);

        retranslateUi(TopFrame);

        QMetaObject::connectSlotsByName(TopFrame);
    } // setupUi

    void retranslateUi(QWidget *TopFrame)
    {
        TopFrame->setWindowTitle(QCoreApplication::translate("TopFrame", "Form", nullptr));
        label->setText(QCoreApplication::translate("TopFrame", "<html><head/><body><p><img src=\":/images/images/SimCenter_H2O_logo\" height=\"55\"></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TopFrame: public Ui_TopFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPFRAME_H
