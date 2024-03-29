/********************************************************************************
** Form generated from reading UI file 'materials.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIALS_H
#define UI_MATERIALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_materials
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_WaterH2;
    QGridLayout *GLY_Water;
    QDoubleSpinBox *DSpBx_WaterViscExp;
    QLabel *Lbl_10pb;
    QDoubleSpinBox *DSpBx_WaterVisc;
    QLabel *Lbl_WaterVisc;
    QLabel *Lbl_WaterDen;
    QDoubleSpinBox *DSpBx_WaterDen;
    QLabel *Lbl_AirH2;
    QGridLayout *GLY_Air;
    QDoubleSpinBox *DSpBx_AirViscExp;
    QLabel *Lbl_AirVisc;
    QDoubleSpinBox *DSpBx_AirVisc;
    QLabel *Lbl_10pa;
    QLabel *Lbl_AirDen;
    QDoubleSpinBox *DSpBx_AirDen;
    QLabel *Lbl_SurfTenH2;
    QGridLayout *GLY_SurfTen;
    QLabel *Lbl_SurfTen;
    QDoubleSpinBox *DSpBx_SurfTen;
    QSpacerItem *VSp;

    void setupUi(QFrame *materials)
    {
        if (materials->objectName().isEmpty())
            materials->setObjectName(QString::fromUtf8("materials"));
        materials->resize(386, 1002);
        verticalLayout = new QVBoxLayout(materials);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(materials);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_WaterH2 = new QLabel(materials);
        Lbl_WaterH2->setObjectName(QString::fromUtf8("Lbl_WaterH2"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_WaterH2->setFont(font1);

        verticalLayout->addWidget(Lbl_WaterH2);

        GLY_Water = new QGridLayout();
        GLY_Water->setObjectName(QString::fromUtf8("GLY_Water"));
        DSpBx_WaterViscExp = new QDoubleSpinBox(materials);
        DSpBx_WaterViscExp->setObjectName(QString::fromUtf8("DSpBx_WaterViscExp"));
        DSpBx_WaterViscExp->setFont(font);
        DSpBx_WaterViscExp->setAlignment(Qt::AlignCenter);
        DSpBx_WaterViscExp->setDecimals(0);
        DSpBx_WaterViscExp->setMinimum(-10.000000000000000);
        DSpBx_WaterViscExp->setMaximum(10.000000000000000);
        DSpBx_WaterViscExp->setValue(-6.000000000000000);

        GLY_Water->addWidget(DSpBx_WaterViscExp, 0, 3, 1, 1);

        Lbl_10pb = new QLabel(materials);
        Lbl_10pb->setObjectName(QString::fromUtf8("Lbl_10pb"));
        Lbl_10pb->setFont(font);
        Lbl_10pb->setAlignment(Qt::AlignCenter);

        GLY_Water->addWidget(Lbl_10pb, 0, 2, 1, 1);

        DSpBx_WaterVisc = new QDoubleSpinBox(materials);
        DSpBx_WaterVisc->setObjectName(QString::fromUtf8("DSpBx_WaterVisc"));
        DSpBx_WaterVisc->setFont(font);
        DSpBx_WaterVisc->setAlignment(Qt::AlignCenter);
        DSpBx_WaterVisc->setDecimals(4);
        DSpBx_WaterVisc->setMaximum(100.000000000000000);
        DSpBx_WaterVisc->setSingleStep(0.100000000000000);
        DSpBx_WaterVisc->setValue(1.003500000000000);

        GLY_Water->addWidget(DSpBx_WaterVisc, 0, 1, 1, 1);

        Lbl_WaterVisc = new QLabel(materials);
        Lbl_WaterVisc->setObjectName(QString::fromUtf8("Lbl_WaterVisc"));
        QFont font2;
        font2.setPointSize(14);
        font2.setItalic(false);
        Lbl_WaterVisc->setFont(font2);
        Lbl_WaterVisc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_WaterVisc->setWordWrap(true);

        GLY_Water->addWidget(Lbl_WaterVisc, 0, 0, 1, 1);

        Lbl_WaterDen = new QLabel(materials);
        Lbl_WaterDen->setObjectName(QString::fromUtf8("Lbl_WaterDen"));
        Lbl_WaterDen->setFont(font2);
        Lbl_WaterDen->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_WaterDen->setWordWrap(true);

        GLY_Water->addWidget(Lbl_WaterDen, 1, 0, 1, 1);

        DSpBx_WaterDen = new QDoubleSpinBox(materials);
        DSpBx_WaterDen->setObjectName(QString::fromUtf8("DSpBx_WaterDen"));
        DSpBx_WaterDen->setFont(font);
        DSpBx_WaterDen->setAlignment(Qt::AlignCenter);
        DSpBx_WaterDen->setMaximum(10000.000000000000000);
        DSpBx_WaterDen->setValue(997.000000000000000);

        GLY_Water->addWidget(DSpBx_WaterDen, 1, 1, 1, 3);

        GLY_Water->setColumnStretch(0, 3);
        GLY_Water->setColumnStretch(1, 1);
        GLY_Water->setColumnStretch(2, 1);
        GLY_Water->setColumnStretch(3, 1);

        verticalLayout->addLayout(GLY_Water);

        Lbl_AirH2 = new QLabel(materials);
        Lbl_AirH2->setObjectName(QString::fromUtf8("Lbl_AirH2"));
        Lbl_AirH2->setFont(font1);

        verticalLayout->addWidget(Lbl_AirH2);

        GLY_Air = new QGridLayout();
        GLY_Air->setObjectName(QString::fromUtf8("GLY_Air"));
        DSpBx_AirViscExp = new QDoubleSpinBox(materials);
        DSpBx_AirViscExp->setObjectName(QString::fromUtf8("DSpBx_AirViscExp"));
        DSpBx_AirViscExp->setFont(font);
        DSpBx_AirViscExp->setAlignment(Qt::AlignCenter);
        DSpBx_AirViscExp->setDecimals(0);
        DSpBx_AirViscExp->setMinimum(-10.000000000000000);
        DSpBx_AirViscExp->setMaximum(10.000000000000000);
        DSpBx_AirViscExp->setValue(-4.000000000000000);

        GLY_Air->addWidget(DSpBx_AirViscExp, 0, 3, 1, 1);

        Lbl_AirVisc = new QLabel(materials);
        Lbl_AirVisc->setObjectName(QString::fromUtf8("Lbl_AirVisc"));
        Lbl_AirVisc->setFont(font2);
        Lbl_AirVisc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_AirVisc->setWordWrap(true);

        GLY_Air->addWidget(Lbl_AirVisc, 0, 0, 1, 1);

        DSpBx_AirVisc = new QDoubleSpinBox(materials);
        DSpBx_AirVisc->setObjectName(QString::fromUtf8("DSpBx_AirVisc"));
        DSpBx_AirVisc->setFont(font);
        DSpBx_AirVisc->setAlignment(Qt::AlignCenter);
        DSpBx_AirVisc->setDecimals(4);
        DSpBx_AirVisc->setMaximum(100.000000000000000);
        DSpBx_AirVisc->setValue(1.620000000000000);

        GLY_Air->addWidget(DSpBx_AirVisc, 0, 1, 1, 1);

        Lbl_10pa = new QLabel(materials);
        Lbl_10pa->setObjectName(QString::fromUtf8("Lbl_10pa"));
        Lbl_10pa->setFont(font);
        Lbl_10pa->setAlignment(Qt::AlignCenter);

        GLY_Air->addWidget(Lbl_10pa, 0, 2, 1, 1);

        Lbl_AirDen = new QLabel(materials);
        Lbl_AirDen->setObjectName(QString::fromUtf8("Lbl_AirDen"));
        Lbl_AirDen->setFont(font2);
        Lbl_AirDen->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_AirDen->setWordWrap(true);

        GLY_Air->addWidget(Lbl_AirDen, 1, 0, 1, 1);

        DSpBx_AirDen = new QDoubleSpinBox(materials);
        DSpBx_AirDen->setObjectName(QString::fromUtf8("DSpBx_AirDen"));
        DSpBx_AirDen->setFont(font);
        DSpBx_AirDen->setAlignment(Qt::AlignCenter);
        DSpBx_AirDen->setMaximum(10000.000000000000000);
        DSpBx_AirDen->setValue(1.230000000000000);

        GLY_Air->addWidget(DSpBx_AirDen, 1, 1, 1, 3);

        GLY_Air->setColumnStretch(0, 3);
        GLY_Air->setColumnStretch(1, 1);
        GLY_Air->setColumnStretch(2, 1);
        GLY_Air->setColumnStretch(3, 1);

        verticalLayout->addLayout(GLY_Air);

        Lbl_SurfTenH2 = new QLabel(materials);
        Lbl_SurfTenH2->setObjectName(QString::fromUtf8("Lbl_SurfTenH2"));
        Lbl_SurfTenH2->setFont(font1);

        verticalLayout->addWidget(Lbl_SurfTenH2);

        GLY_SurfTen = new QGridLayout();
        GLY_SurfTen->setObjectName(QString::fromUtf8("GLY_SurfTen"));
        Lbl_SurfTen = new QLabel(materials);
        Lbl_SurfTen->setObjectName(QString::fromUtf8("Lbl_SurfTen"));
        Lbl_SurfTen->setFont(font2);
        Lbl_SurfTen->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_SurfTen->setWordWrap(true);

        GLY_SurfTen->addWidget(Lbl_SurfTen, 0, 0, 1, 1);

        DSpBx_SurfTen = new QDoubleSpinBox(materials);
        DSpBx_SurfTen->setObjectName(QString::fromUtf8("DSpBx_SurfTen"));
        DSpBx_SurfTen->setFont(font);
        DSpBx_SurfTen->setAlignment(Qt::AlignCenter);
        DSpBx_SurfTen->setMaximum(10000.000000000000000);
        DSpBx_SurfTen->setValue(72.859999999999999);

        GLY_SurfTen->addWidget(DSpBx_SurfTen, 0, 1, 1, 2);

        GLY_SurfTen->setColumnStretch(0, 3);

        verticalLayout->addLayout(GLY_SurfTen);

        VSp = new QSpacerItem(20, 722, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(materials);

        QMetaObject::connectSlotsByName(materials);
    } // setupUi

    void retranslateUi(QFrame *materials)
    {
        materials->setWindowTitle(QCoreApplication::translate("materials", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("materials", "<html><head/><body><p><span style=\" font-weight:600;\">MATERIAL PROPERTIES</span></p></body></html>", nullptr));
        Lbl_WaterH2->setText(QCoreApplication::translate("materials", "Water", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_WaterViscExp->setToolTip(QCoreApplication::translate("materials", "Exponent of kinematic viscosity of water", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_10pb->setText(QCoreApplication::translate("materials", "x 10^", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_WaterVisc->setToolTip(QCoreApplication::translate("materials", "Value of kinematic viscosity of water", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_WaterVisc->setText(QCoreApplication::translate("materials", "Kinematic viscosity", nullptr));
        Lbl_WaterDen->setText(QCoreApplication::translate("materials", "Density", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_WaterDen->setToolTip(QCoreApplication::translate("materials", "Density of water", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_AirH2->setText(QCoreApplication::translate("materials", "Air", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_AirViscExp->setToolTip(QCoreApplication::translate("materials", "Exponent of kinematic viscosity of air", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_AirVisc->setText(QCoreApplication::translate("materials", "Kinematic viscosity", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_AirVisc->setToolTip(QCoreApplication::translate("materials", "Value of kinematic viscosity of air", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_10pa->setText(QCoreApplication::translate("materials", "x10^", nullptr));
        Lbl_AirDen->setText(QCoreApplication::translate("materials", "Density", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_AirDen->setToolTip(QCoreApplication::translate("materials", "Density of air", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_SurfTenH2->setText(QCoreApplication::translate("materials", "Interaction between fluids", nullptr));
        Lbl_SurfTen->setText(QCoreApplication::translate("materials", "Surface tension between fluids", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_SurfTen->setToolTip(QCoreApplication::translate("materials", "Surface tension between water and air", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class materials: public Ui_materials {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIALS_H
