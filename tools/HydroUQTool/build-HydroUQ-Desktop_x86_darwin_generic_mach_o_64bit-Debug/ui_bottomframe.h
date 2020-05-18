/********************************************************************************
** Form generated from reading UI file 'bottomframe.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOTTOMFRAME_H
#define UI_BOTTOMFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BottomFrame
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *BottomFrame)
    {
        if (BottomFrame->objectName().isEmpty())
            BottomFrame->setObjectName(QString::fromUtf8("BottomFrame"));
        BottomFrame->resize(1369, 160);
        QFont font;
        font.setPointSize(14);
        BottomFrame->setFont(font);
        gridLayout = new QGridLayout(BottomFrame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(BottomFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(BottomFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(BottomFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);


        retranslateUi(BottomFrame);

        QMetaObject::connectSlotsByName(BottomFrame);
    } // setupUi

    void retranslateUi(QWidget *BottomFrame)
    {
        BottomFrame->setWindowTitle(QCoreApplication::translate("BottomFrame", "Form", nullptr));
        label->setText(QCoreApplication::translate("BottomFrame", "<html><head/><body><p><img src=\":/images/images/NSFLogo.png\" height=\"60\"></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("BottomFrame", "This work is based on the material supported by the National Science Foundation under grant 1612843", nullptr));
        label_3->setText(QCoreApplication::translate("BottomFrame", "<html><head/><body><p><img src=\":/images/images/SimCenterLogo.png\" height=\"40\"></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BottomFrame: public Ui_BottomFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOTTOMFRAME_H
