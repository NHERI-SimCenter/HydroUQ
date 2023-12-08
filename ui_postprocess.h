/********************************************************************************
** Form generated from reading UI file 'postprocess.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTPROCESS_H
#define UI_POSTPROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_postprocess
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *Lbl_H1;
    QComboBox *CmB_PPFlag;
    QGroupBox *OpGroupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *ChB_Velocity;
    QCheckBox *ChB_Pressure;
    QCheckBox *ChB_Images;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Led_Path;
    QPushButton *Btn_UploadFiles;
    QSpacerItem *Vsp_PP;

    void setupUi(QFrame *postprocess)
    {
        if (postprocess->objectName().isEmpty())
            postprocess->setObjectName(QString::fromUtf8("postprocess"));
        postprocess->resize(364, 1204);
        verticalLayout_3 = new QVBoxLayout(postprocess);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(postprocess);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(Lbl_H1);

        CmB_PPFlag = new QComboBox(postprocess);
        CmB_PPFlag->addItem(QString());
        CmB_PPFlag->addItem(QString());
        CmB_PPFlag->setObjectName(QString::fromUtf8("CmB_PPFlag"));
        CmB_PPFlag->setFont(font);
        CmB_PPFlag->setToolTipDuration(10000);

        verticalLayout_3->addWidget(CmB_PPFlag);

        OpGroupBox = new QGroupBox(postprocess);
        OpGroupBox->setObjectName(QString::fromUtf8("OpGroupBox"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        OpGroupBox->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(OpGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ChB_Velocity = new QCheckBox(OpGroupBox);
        ChB_Velocity->setObjectName(QString::fromUtf8("ChB_Velocity"));

        verticalLayout->addWidget(ChB_Velocity);

        ChB_Pressure = new QCheckBox(OpGroupBox);
        ChB_Pressure->setObjectName(QString::fromUtf8("ChB_Pressure"));

        verticalLayout->addWidget(ChB_Pressure);

        ChB_Images = new QCheckBox(OpGroupBox);
        ChB_Images->setObjectName(QString::fromUtf8("ChB_Images"));

        verticalLayout->addWidget(ChB_Images);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Led_Path = new QLineEdit(OpGroupBox);
        Led_Path->setObjectName(QString::fromUtf8("Led_Path"));

        horizontalLayout->addWidget(Led_Path);

        Btn_UploadFiles = new QPushButton(OpGroupBox);
        Btn_UploadFiles->setObjectName(QString::fromUtf8("Btn_UploadFiles"));
        Btn_UploadFiles->setFont(font1);
        Btn_UploadFiles->setToolTipDuration(10000);

        horizontalLayout->addWidget(Btn_UploadFiles);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addWidget(OpGroupBox);

        Vsp_PP = new QSpacerItem(20, 1017, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(Vsp_PP);


        retranslateUi(postprocess);

        QMetaObject::connectSlotsByName(postprocess);
    } // setupUi

    void retranslateUi(QFrame *postprocess)
    {
        postprocess->setWindowTitle(QCoreApplication::translate("postprocess", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("postprocess", "<html><head/><body><p><span style=\" font-weight:600;\">EVENT POSTPROCESSING SETTINGS</span></p></body></html>", nullptr));
        CmB_PPFlag->setItemText(0, QCoreApplication::translate("postprocess", "No post-processing", nullptr));
        CmB_PPFlag->setItemText(1, QCoreApplication::translate("postprocess", "Provide points to get data", nullptr));

#if QT_CONFIG(tooltip)
        CmB_PPFlag->setToolTip(QCoreApplication::translate("postprocess", "Select the format of the bathymetric files uploaded", nullptr));
#endif // QT_CONFIG(tooltip)
        OpGroupBox->setTitle(QCoreApplication::translate("postprocess", "Output items", nullptr));
#if QT_CONFIG(tooltip)
        ChB_Velocity->setToolTip(QCoreApplication::translate("postprocess", "Select if velocity needs to be extracted", nullptr));
#endif // QT_CONFIG(tooltip)
        ChB_Velocity->setText(QCoreApplication::translate("postprocess", "Extract velocity", nullptr));
#if QT_CONFIG(tooltip)
        ChB_Pressure->setToolTip(QCoreApplication::translate("postprocess", "Select if pressure needs to be extracted", nullptr));
#endif // QT_CONFIG(tooltip)
        ChB_Pressure->setText(QCoreApplication::translate("postprocess", "Extract pressure", nullptr));
#if QT_CONFIG(tooltip)
        ChB_Images->setToolTip(QCoreApplication::translate("postprocess", "Select if images need to be extracted", nullptr));
#endif // QT_CONFIG(tooltip)
        ChB_Images->setText(QCoreApplication::translate("postprocess", "Extract images for video", nullptr));
#if QT_CONFIG(tooltip)
        Btn_UploadFiles->setToolTip(QCoreApplication::translate("postprocess", "Select a single .zip file", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadFiles->setText(QCoreApplication::translate("postprocess", "Upload .csv file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class postprocess: public Ui_postprocess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTPROCESS_H
