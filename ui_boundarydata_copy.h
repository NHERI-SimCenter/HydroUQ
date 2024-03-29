/********************************************************************************
** Form generated from reading UI file 'boundarydata_copy.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOUNDARYDATA_COPY_H
#define UI_BOUNDARYDATA_COPY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_boundaryData
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_PatchLoc;
    QComboBox *Cmb_PatchLoc;
    QComboBox *Cmb_PatchStdLoc;
    QLabel *Lbl_VelBC;
    QComboBox *Cmb_UBC;
    QPushButton *Btn_UploadFile;
    QComboBox *Cmb_WaveType;
    QGridLayout *GLY_Vel;
    QDoubleSpinBox *DSpBx_UMeanY;
    QDoubleSpinBox *DSpBx_DirnZ;
    QDoubleSpinBox *DSpBx_OZ;
    QDoubleSpinBox *DSpBx_OY;
    QLabel *Lbl_Origin;
    QDoubleSpinBox *DSpBx_DirnY;
    QLabel *Lbl_Umean;
    QDoubleSpinBox *DSpBx_UMeanX;
    QDoubleSpinBox *DSpBx_UMeanZ;
    QLabel *Lbl_Dirn;
    QDoubleSpinBox *DSpBx_DirnX;
    QDoubleSpinBox *DSpBx_OX;
    QLabel *Lbl_WavePara;
    QLineEdit *Led_WavePara;
    QLabel *Lbl_PresBC;
    QComboBox *Cmb_PresBC;
    QHBoxLayout *HLY_Pres;
    QLabel *Lbl_Pres;
    QDoubleSpinBox *DSpBx_Pres;
    QSpacerItem *VSp;

    void setupUi(QFrame *boundaryData)
    {
        if (boundaryData->objectName().isEmpty())
            boundaryData->setObjectName(QString::fromUtf8("boundaryData"));
        boundaryData->resize(429, 800);
        verticalLayout = new QVBoxLayout(boundaryData);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(boundaryData);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        Lbl_H1->setFont(font);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_PatchLoc = new QLabel(boundaryData);
        Lbl_PatchLoc->setObjectName(QString::fromUtf8("Lbl_PatchLoc"));
        Lbl_PatchLoc->setFont(font);

        verticalLayout->addWidget(Lbl_PatchLoc);

        Cmb_PatchLoc = new QComboBox(boundaryData);
        Cmb_PatchLoc->addItem(QString());
        Cmb_PatchLoc->setObjectName(QString::fromUtf8("Cmb_PatchLoc"));
        QFont font1;
        font1.setPointSize(14);
        Cmb_PatchLoc->setFont(font1);
        Cmb_PatchLoc->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_PatchLoc);

        Cmb_PatchStdLoc = new QComboBox(boundaryData);
        Cmb_PatchStdLoc->addItem(QString());
        Cmb_PatchStdLoc->addItem(QString());
        Cmb_PatchStdLoc->addItem(QString());
        Cmb_PatchStdLoc->addItem(QString());
        Cmb_PatchStdLoc->addItem(QString());
        Cmb_PatchStdLoc->addItem(QString());
        Cmb_PatchStdLoc->setObjectName(QString::fromUtf8("Cmb_PatchStdLoc"));
        Cmb_PatchStdLoc->setFont(font1);
        Cmb_PatchStdLoc->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_PatchStdLoc);

        Lbl_VelBC = new QLabel(boundaryData);
        Lbl_VelBC->setObjectName(QString::fromUtf8("Lbl_VelBC"));
        Lbl_VelBC->setFont(font);

        verticalLayout->addWidget(Lbl_VelBC);

        Cmb_UBC = new QComboBox(boundaryData);
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->addItem(QString());
        Cmb_UBC->setObjectName(QString::fromUtf8("Cmb_UBC"));
        Cmb_UBC->setFont(font1);
        Cmb_UBC->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_UBC);

        Btn_UploadFile = new QPushButton(boundaryData);
        Btn_UploadFile->setObjectName(QString::fromUtf8("Btn_UploadFile"));
        Btn_UploadFile->setFont(font1);
        Btn_UploadFile->setToolTipDuration(10000);

        verticalLayout->addWidget(Btn_UploadFile);

        Cmb_WaveType = new QComboBox(boundaryData);
        Cmb_WaveType->addItem(QString());
        Cmb_WaveType->addItem(QString());
        Cmb_WaveType->addItem(QString());
        Cmb_WaveType->addItem(QString());
        Cmb_WaveType->addItem(QString());
        Cmb_WaveType->setObjectName(QString::fromUtf8("Cmb_WaveType"));
        Cmb_WaveType->setFont(font1);
        Cmb_WaveType->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_WaveType);

        GLY_Vel = new QGridLayout();
        GLY_Vel->setObjectName(QString::fromUtf8("GLY_Vel"));
        DSpBx_UMeanY = new QDoubleSpinBox(boundaryData);
        DSpBx_UMeanY->setObjectName(QString::fromUtf8("DSpBx_UMeanY"));
        DSpBx_UMeanY->setFont(font1);
        DSpBx_UMeanY->setAlignment(Qt::AlignCenter);
        DSpBx_UMeanY->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_UMeanY, 0, 2, 1, 1);

        DSpBx_DirnZ = new QDoubleSpinBox(boundaryData);
        DSpBx_DirnZ->setObjectName(QString::fromUtf8("DSpBx_DirnZ"));
        DSpBx_DirnZ->setFont(font1);
        DSpBx_DirnZ->setAlignment(Qt::AlignCenter);
        DSpBx_DirnZ->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_DirnZ, 2, 3, 1, 1);

        DSpBx_OZ = new QDoubleSpinBox(boundaryData);
        DSpBx_OZ->setObjectName(QString::fromUtf8("DSpBx_OZ"));
        DSpBx_OZ->setFont(font1);
        DSpBx_OZ->setAlignment(Qt::AlignCenter);
        DSpBx_OZ->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_OZ, 1, 3, 1, 1);

        DSpBx_OY = new QDoubleSpinBox(boundaryData);
        DSpBx_OY->setObjectName(QString::fromUtf8("DSpBx_OY"));
        DSpBx_OY->setFont(font1);
        DSpBx_OY->setAlignment(Qt::AlignCenter);
        DSpBx_OY->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_OY, 1, 2, 1, 1);

        Lbl_Origin = new QLabel(boundaryData);
        Lbl_Origin->setObjectName(QString::fromUtf8("Lbl_Origin"));
        Lbl_Origin->setFont(font1);

        GLY_Vel->addWidget(Lbl_Origin, 1, 0, 1, 1);

        DSpBx_DirnY = new QDoubleSpinBox(boundaryData);
        DSpBx_DirnY->setObjectName(QString::fromUtf8("DSpBx_DirnY"));
        DSpBx_DirnY->setFont(font1);
        DSpBx_DirnY->setAlignment(Qt::AlignCenter);
        DSpBx_DirnY->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_DirnY, 2, 2, 1, 1);

        Lbl_Umean = new QLabel(boundaryData);
        Lbl_Umean->setObjectName(QString::fromUtf8("Lbl_Umean"));
        Lbl_Umean->setFont(font1);

        GLY_Vel->addWidget(Lbl_Umean, 0, 0, 1, 1);

        DSpBx_UMeanX = new QDoubleSpinBox(boundaryData);
        DSpBx_UMeanX->setObjectName(QString::fromUtf8("DSpBx_UMeanX"));
        DSpBx_UMeanX->setFont(font1);
        DSpBx_UMeanX->setAlignment(Qt::AlignCenter);
        DSpBx_UMeanX->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_UMeanX, 0, 1, 1, 1);

        DSpBx_UMeanZ = new QDoubleSpinBox(boundaryData);
        DSpBx_UMeanZ->setObjectName(QString::fromUtf8("DSpBx_UMeanZ"));
        DSpBx_UMeanZ->setFont(font1);
        DSpBx_UMeanZ->setAlignment(Qt::AlignCenter);
        DSpBx_UMeanZ->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_UMeanZ, 0, 3, 1, 1);

        Lbl_Dirn = new QLabel(boundaryData);
        Lbl_Dirn->setObjectName(QString::fromUtf8("Lbl_Dirn"));
        Lbl_Dirn->setFont(font1);

        GLY_Vel->addWidget(Lbl_Dirn, 2, 0, 1, 1);

        DSpBx_DirnX = new QDoubleSpinBox(boundaryData);
        DSpBx_DirnX->setObjectName(QString::fromUtf8("DSpBx_DirnX"));
        DSpBx_DirnX->setFont(font1);
        DSpBx_DirnX->setAlignment(Qt::AlignCenter);
        DSpBx_DirnX->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_DirnX, 2, 1, 1, 1);

        DSpBx_OX = new QDoubleSpinBox(boundaryData);
        DSpBx_OX->setObjectName(QString::fromUtf8("DSpBx_OX"));
        DSpBx_OX->setFont(font1);
        DSpBx_OX->setAlignment(Qt::AlignCenter);
        DSpBx_OX->setMaximum(100000.000000000000000);

        GLY_Vel->addWidget(DSpBx_OX, 1, 1, 1, 1);

        Lbl_WavePara = new QLabel(boundaryData);
        Lbl_WavePara->setObjectName(QString::fromUtf8("Lbl_WavePara"));
        Lbl_WavePara->setFont(font1);

        GLY_Vel->addWidget(Lbl_WavePara, 3, 0, 1, 1);

        Led_WavePara = new QLineEdit(boundaryData);
        Led_WavePara->setObjectName(QString::fromUtf8("Led_WavePara"));
        Led_WavePara->setFont(font1);
        Led_WavePara->setToolTipDuration(10000);
        Led_WavePara->setAlignment(Qt::AlignCenter);

        GLY_Vel->addWidget(Led_WavePara, 3, 1, 1, 3);


        verticalLayout->addLayout(GLY_Vel);

        Lbl_PresBC = new QLabel(boundaryData);
        Lbl_PresBC->setObjectName(QString::fromUtf8("Lbl_PresBC"));
        Lbl_PresBC->setFont(font);

        verticalLayout->addWidget(Lbl_PresBC);

        Cmb_PresBC = new QComboBox(boundaryData);
        Cmb_PresBC->addItem(QString());
        Cmb_PresBC->addItem(QString());
        Cmb_PresBC->addItem(QString());
        Cmb_PresBC->addItem(QString());
        Cmb_PresBC->addItem(QString());
        Cmb_PresBC->setObjectName(QString::fromUtf8("Cmb_PresBC"));
        Cmb_PresBC->setFont(font1);
        Cmb_PresBC->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_PresBC);

        HLY_Pres = new QHBoxLayout();
        HLY_Pres->setObjectName(QString::fromUtf8("HLY_Pres"));
        Lbl_Pres = new QLabel(boundaryData);
        Lbl_Pres->setObjectName(QString::fromUtf8("Lbl_Pres"));
        Lbl_Pres->setFont(font1);

        HLY_Pres->addWidget(Lbl_Pres);

        DSpBx_Pres = new QDoubleSpinBox(boundaryData);
        DSpBx_Pres->setObjectName(QString::fromUtf8("DSpBx_Pres"));
        DSpBx_Pres->setFont(font1);
        DSpBx_Pres->setAlignment(Qt::AlignCenter);
        DSpBx_Pres->setMinimum(-1000000.000000000000000);
        DSpBx_Pres->setMaximum(10000000.000000000000000);

        HLY_Pres->addWidget(DSpBx_Pres);

        HLY_Pres->setStretch(0, 1);

        verticalLayout->addLayout(HLY_Pres);

        VSp = new QSpacerItem(20, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(boundaryData);

        QMetaObject::connectSlotsByName(boundaryData);
    } // setupUi

    void retranslateUi(QFrame *boundaryData)
    {
        boundaryData->setWindowTitle(QCoreApplication::translate("boundaryData", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("boundaryData", "<html><head/><body><p>East Face</p></body></html>", nullptr));
        Lbl_PatchLoc->setText(QCoreApplication::translate("boundaryData", "Patch location", nullptr));
        Cmb_PatchLoc->setItemText(0, QCoreApplication::translate("boundaryData", "Standard", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_PatchLoc->setToolTip(QCoreApplication::translate("boundaryData", "Use this to define the type of patch", nullptr));
#endif // QT_CONFIG(tooltip)
        Cmb_PatchStdLoc->setItemText(0, QCoreApplication::translate("boundaryData", "Entry", nullptr));
        Cmb_PatchStdLoc->setItemText(1, QCoreApplication::translate("boundaryData", "Exit", nullptr));
        Cmb_PatchStdLoc->setItemText(2, QCoreApplication::translate("boundaryData", "Top", nullptr));
        Cmb_PatchStdLoc->setItemText(3, QCoreApplication::translate("boundaryData", "Bottom", nullptr));
        Cmb_PatchStdLoc->setItemText(4, QCoreApplication::translate("boundaryData", "Right", nullptr));
        Cmb_PatchStdLoc->setItemText(5, QCoreApplication::translate("boundaryData", "Left", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_PatchStdLoc->setToolTip(QCoreApplication::translate("boundaryData", "Choose the standard patch for this boundary", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_VelBC->setText(QCoreApplication::translate("boundaryData", "Velocity", nullptr));
        Cmb_UBC->setItemText(0, QCoreApplication::translate("boundaryData", "Empty", nullptr));
        Cmb_UBC->setItemText(1, QCoreApplication::translate("boundaryData", "Inlet: Constant velocity", nullptr));
        Cmb_UBC->setItemText(2, QCoreApplication::translate("boundaryData", "Inlet: Wave input", nullptr));
        Cmb_UBC->setItemText(3, QCoreApplication::translate("boundaryData", "Inlet: Time-varying uniform velocity", nullptr));
        Cmb_UBC->setItemText(4, QCoreApplication::translate("boundaryData", "Inlet: Time-varying non-uniform velocity", nullptr));
        Cmb_UBC->setItemText(5, QCoreApplication::translate("boundaryData", "Outlet: Phase-mean velocity", nullptr));
        Cmb_UBC->setItemText(6, QCoreApplication::translate("boundaryData", "Outlet: flowRateOutletVelocity", nullptr));
        Cmb_UBC->setItemText(7, QCoreApplication::translate("boundaryData", "Outlet: inletOutlet", nullptr));
        Cmb_UBC->setItemText(8, QCoreApplication::translate("boundaryData", "Wall: noSlip", nullptr));
        Cmb_UBC->setItemText(9, QCoreApplication::translate("boundaryData", "Moving wall", nullptr));
        Cmb_UBC->setItemText(10, QCoreApplication::translate("boundaryData", "SW solutions", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_UBC->setToolTip(QCoreApplication::translate("boundaryData", "Choose type of velocity boundary condition", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_UploadFile->setToolTip(QCoreApplication::translate("boundaryData", "Upload files related to the boundary patch", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadFile->setText(QCoreApplication::translate("boundaryData", "\n"
"Upload files\n"
"", nullptr));
        Cmb_WaveType->setItemText(0, QCoreApplication::translate("boundaryData", "Airy", nullptr));
        Cmb_WaveType->setItemText(1, QCoreApplication::translate("boundaryData", "Stokes2", nullptr));
        Cmb_WaveType->setItemText(2, QCoreApplication::translate("boundaryData", "Stokes5", nullptr));
        Cmb_WaveType->setItemText(3, QCoreApplication::translate("boundaryData", "Solitary", nullptr));
        Cmb_WaveType->setItemText(4, QCoreApplication::translate("boundaryData", "Custom", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_WaveType->setToolTip(QCoreApplication::translate("boundaryData", "Types of wave inputs", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_UMeanY->setToolTip(QCoreApplication::translate("boundaryData", "Mean velocity (y-direction)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_DirnZ->setToolTip(QCoreApplication::translate("boundaryData", "Wave direction vector (z-component)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_OZ->setToolTip(QCoreApplication::translate("boundaryData", "Wave origian (z-coordinate)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_OY->setToolTip(QCoreApplication::translate("boundaryData", "Wave origian (y-coordinate)", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Origin->setText(QCoreApplication::translate("boundaryData", "Origin", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_DirnY->setToolTip(QCoreApplication::translate("boundaryData", "Wave direction vector (y-component)", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Umean->setText(QCoreApplication::translate("boundaryData", "UMean", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_UMeanX->setToolTip(QCoreApplication::translate("boundaryData", "Mean velocity (x-direction)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_UMeanZ->setToolTip(QCoreApplication::translate("boundaryData", "Mean velocity (z-direction)", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Dirn->setText(QCoreApplication::translate("boundaryData", "Direction", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_DirnX->setToolTip(QCoreApplication::translate("boundaryData", "Wave direction vector (x-component)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_OX->setToolTip(QCoreApplication::translate("boundaryData", "Wave origian (x-coordinate)", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_WavePara->setText(QCoreApplication::translate("boundaryData", "Length, Amplitude, \n"
"Phase, Angle", nullptr));
#if QT_CONFIG(tooltip)
        Led_WavePara->setToolTip(QCoreApplication::translate("boundaryData", "Wave input parameters", nullptr));
#endif // QT_CONFIG(tooltip)
        Led_WavePara->setPlaceholderText(QCoreApplication::translate("boundaryData", "0, 0, 0, 0", nullptr));
        Lbl_PresBC->setText(QCoreApplication::translate("boundaryData", "Pressure", nullptr));
        Cmb_PresBC->setItemText(0, QCoreApplication::translate("boundaryData", "Default choice", nullptr));
        Cmb_PresBC->setItemText(1, QCoreApplication::translate("boundaryData", "Inlet / Outlet / Wall: Zero gradient", nullptr));
        Cmb_PresBC->setItemText(2, QCoreApplication::translate("boundaryData", "Inlet: Calculated pressure", nullptr));
        Cmb_PresBC->setItemText(3, QCoreApplication::translate("boundaryData", "Outlet: Total pressure", nullptr));
        Cmb_PresBC->setItemText(4, QCoreApplication::translate("boundaryData", "Wall: Fixed flux", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_PresBC->setToolTip(QCoreApplication::translate("boundaryData", "Choose type of pressure boundary condition", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Pres->setText(QCoreApplication::translate("boundaryData", "Pressure", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Pres->setToolTip(QCoreApplication::translate("boundaryData", "Value of pressure", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class boundaryData: public Ui_boundaryData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOUNDARYDATA_COPY_H
