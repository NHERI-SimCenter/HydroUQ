/********************************************************************************
** Form generated from reading UI file 'swcfdint.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWCFDINT_H
#define UI_SWCFDINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_swcfdint
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_Interface;
    QLabel *Lbl_Notice;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Led_path;
    QPushButton *Btn_UploadFile;
    QSpacerItem *VSp;

    void setupUi(QFrame *swcfdint)
    {
        if (swcfdint->objectName().isEmpty())
            swcfdint->setObjectName(QString::fromUtf8("swcfdint"));
        swcfdint->resize(428, 1018);
        verticalLayout = new QVBoxLayout(swcfdint);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(swcfdint);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_Interface = new QLabel(swcfdint);
        Lbl_Interface->setObjectName(QString::fromUtf8("Lbl_Interface"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_Interface->setFont(font1);

        verticalLayout->addWidget(Lbl_Interface);

        Lbl_Notice = new QLabel(swcfdint);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));

        verticalLayout->addWidget(Lbl_Notice);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Led_path = new QLineEdit(swcfdint);
        Led_path->setObjectName(QString::fromUtf8("Led_path"));
        Led_path->setFont(font);
        Led_path->setReadOnly(true);

        horizontalLayout->addWidget(Led_path);

        Btn_UploadFile = new QPushButton(swcfdint);
        Btn_UploadFile->setObjectName(QString::fromUtf8("Btn_UploadFile"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Btn_UploadFile->sizePolicy().hasHeightForWidth());
        Btn_UploadFile->setSizePolicy(sizePolicy);
        Btn_UploadFile->setToolTipDuration(10000);

        horizontalLayout->addWidget(Btn_UploadFile);


        verticalLayout->addLayout(horizontalLayout);

        VSp = new QSpacerItem(20, 395, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(swcfdint);

        QMetaObject::connectSlotsByName(swcfdint);
    } // setupUi

    void retranslateUi(QFrame *swcfdint)
    {
        swcfdint->setWindowTitle(QCoreApplication::translate("swcfdint", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("swcfdint", "<html><head/><body><p><span style=\" font-weight:600;\">SW-CFD INTERFACE</span></p></body></html>", nullptr));
        Lbl_Interface->setText(QCoreApplication::translate("swcfdint", "<html><head/><body><p>SW - CFD interface definition</p></body></html>", nullptr));
        Lbl_Notice->setText(QCoreApplication::translate("swcfdint", "SW-CFD settings are not available for this option", nullptr));
#if QT_CONFIG(tooltip)
        Btn_UploadFile->setToolTip(QCoreApplication::translate("swcfdint", "Upload a latitude-longitude file to define the interfaces", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadFile->setText(QCoreApplication::translate("swcfdint", "Upload interface file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class swcfdint: public Ui_swcfdint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWCFDINT_H
