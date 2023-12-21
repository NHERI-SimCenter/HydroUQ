/********************************************************************************
** Form generated from reading UI file 'projectsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTSETTINGS_H
#define UI_PROJECTSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_projectsettings
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_SimType;
    QComboBox *CmB_SimType;
    QLabel *Lbl_TurbModel;
    QComboBox *CmB_TurbModel;
    QSpacerItem *VSp;

    void setupUi(QFrame *projectsettings)
    {
        if (projectsettings->objectName().isEmpty())
            projectsettings->setObjectName(QString::fromUtf8("projectsettings"));
        projectsettings->resize(332, 793);
        verticalLayout = new QVBoxLayout(projectsettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(projectsettings);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_SimType = new QLabel(projectsettings);
        Lbl_SimType->setObjectName(QString::fromUtf8("Lbl_SimType"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        Lbl_SimType->setFont(font1);

        verticalLayout->addWidget(Lbl_SimType);

        CmB_SimType = new QComboBox(projectsettings);
        CmB_SimType->addItem(QString());
        CmB_SimType->addItem(QString());
        CmB_SimType->addItem(QString());
        CmB_SimType->addItem(QString());
        CmB_SimType->addItem(QString());
        CmB_SimType->setObjectName(QString::fromUtf8("CmB_SimType"));
        CmB_SimType->setEnabled(true);
        QFont font2;
        font2.setPointSize(12);
        CmB_SimType->setFont(font2);
        CmB_SimType->setToolTipDuration(10000);
        CmB_SimType->setEditable(false);

        verticalLayout->addWidget(CmB_SimType);

        Lbl_TurbModel = new QLabel(projectsettings);
        Lbl_TurbModel->setObjectName(QString::fromUtf8("Lbl_TurbModel"));
        Lbl_TurbModel->setFont(font1);

        verticalLayout->addWidget(Lbl_TurbModel);

        CmB_TurbModel = new QComboBox(projectsettings);
        CmB_TurbModel->addItem(QString());
        CmB_TurbModel->addItem(QString());
        CmB_TurbModel->addItem(QString());
        CmB_TurbModel->setObjectName(QString::fromUtf8("CmB_TurbModel"));
        CmB_TurbModel->setFont(font2);
        CmB_TurbModel->setToolTipDuration(10000);

        verticalLayout->addWidget(CmB_TurbModel);

        VSp = new QSpacerItem(20, 201, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(projectsettings);

        QMetaObject::connectSlotsByName(projectsettings);
    } // setupUi

    void retranslateUi(QFrame *projectsettings)
    {
        projectsettings->setWindowTitle(QCoreApplication::translate("projectsettings", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("projectsettings", "<html><head/><body><p><span style=\" font-weight:600;\">EVENT SETTINGS</span></p></body></html>", nullptr));
        Lbl_SimType->setText(QCoreApplication::translate("projectsettings", "<html><head/><body><p>Simulation type</p></body></html>", nullptr));
        CmB_SimType->setItemText(0, QCoreApplication::translate("projectsettings", "Choose simulation type", nullptr));
        CmB_SimType->setItemText(1, QCoreApplication::translate("projectsettings", "CFD to resolve SW (Using SW results)", nullptr));
        CmB_SimType->setItemText(2, QCoreApplication::translate("projectsettings", "CFD using bathymetry data", nullptr));
        CmB_SimType->setItemText(3, QCoreApplication::translate("projectsettings", "CFD using STL file", nullptr));
        CmB_SimType->setItemText(4, QCoreApplication::translate("projectsettings", "CFD using Wave Flume Digital Twin", nullptr));

#if QT_CONFIG(tooltip)
        CmB_SimType->setToolTip(QCoreApplication::translate("projectsettings", "Choose the type of simulation to be done", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_TurbModel->setText(QCoreApplication::translate("projectsettings", "<html><head/><body><p>Turbulence model</p></body></html>", nullptr));
        CmB_TurbModel->setItemText(0, QCoreApplication::translate("projectsettings", "Laminar", nullptr));
        CmB_TurbModel->setItemText(1, QCoreApplication::translate("projectsettings", "k-Epsilon", nullptr));
        CmB_TurbModel->setItemText(2, QCoreApplication::translate("projectsettings", "k-Omega SST", nullptr));

#if QT_CONFIG(tooltip)
        CmB_TurbModel->setToolTip(QCoreApplication::translate("projectsettings", "Choose the turbulence model to be used", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class projectsettings: public Ui_projectsettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTSETTINGS_H
