/********************************************************************************
** Form generated from reading UI file 'H20plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H20PLOTWINDOW_H
#define UI_H20PLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_H20plotwindow
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *H20plotwindow)
    {
        if (H20plotwindow->objectName().isEmpty())
            H20plotwindow->setObjectName(QString::fromUtf8("H20plotwindow"));
        H20plotwindow->resize(822, 475);
        pushButton = new QPushButton(H20plotwindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(409, 250, 121, 71));

        retranslateUi(H20plotwindow);

        QMetaObject::connectSlotsByName(H20plotwindow);
    } // setupUi

    void retranslateUi(QWidget *H20plotwindow)
    {
        H20plotwindow->setWindowTitle(QCoreApplication::translate("H20plotwindow", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("H20plotwindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class H20plotwindow: public Ui_H20plotwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H20PLOTWINDOW_H
