/********************************************************************************
** Form generated from reading UI file 'solver.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLVER_H
#define UI_SOLVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_solver
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_TimeSettings;
    QGridLayout *GLY01;
    QLabel *Lbl_DeltaT;
    QLabel *Lbl_Start;
    QDoubleSpinBox *DSpBx_Start;
    QLabel *Lbl_End;
    QDoubleSpinBox *DSpBx_End;
    QDoubleSpinBox *DSpBx_DeltaT;
    QLabel *Lbl_WriteT;
    QDoubleSpinBox *DSpBx_WriteT;
    QCheckBox *ChB_Restart;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Led_Path;
    QPushButton *Btn_UploadFiles;
    QLabel *Lbl_Domain;
    QGridLayout *GLY02;
    QDoubleSpinBox *DSpBx_Px;
    QDoubleSpinBox *DSpBx_Pz;
    QLabel *Lbl_Subdomains;
    QDoubleSpinBox *DSpBx_Py;
    QLabel *Lbl_Decomp;
    QComboBox *Cmb_Decomp;
    QLabel *Lbl_CFDSolver;
    QComboBox *Cmb_Solver;
    QSpacerItem *verticalSpacer;

    void setupUi(QFrame *solver)
    {
        if (solver->objectName().isEmpty())
            solver->setObjectName(QString::fromUtf8("solver"));
        solver->resize(394, 872);
        verticalLayout = new QVBoxLayout(solver);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(solver);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_TimeSettings = new QLabel(solver);
        Lbl_TimeSettings->setObjectName(QString::fromUtf8("Lbl_TimeSettings"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_TimeSettings->setFont(font1);

        verticalLayout->addWidget(Lbl_TimeSettings);

        GLY01 = new QGridLayout();
        GLY01->setObjectName(QString::fromUtf8("GLY01"));
        Lbl_DeltaT = new QLabel(solver);
        Lbl_DeltaT->setObjectName(QString::fromUtf8("Lbl_DeltaT"));
        QFont font2;
        font2.setPointSize(14);
        font2.setItalic(false);
        Lbl_DeltaT->setFont(font2);
        Lbl_DeltaT->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_DeltaT->setWordWrap(true);

        GLY01->addWidget(Lbl_DeltaT, 2, 0, 1, 1);

        Lbl_Start = new QLabel(solver);
        Lbl_Start->setObjectName(QString::fromUtf8("Lbl_Start"));
        Lbl_Start->setFont(font2);
        Lbl_Start->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Start->setWordWrap(true);

        GLY01->addWidget(Lbl_Start, 0, 0, 1, 1);

        DSpBx_Start = new QDoubleSpinBox(solver);
        DSpBx_Start->setObjectName(QString::fromUtf8("DSpBx_Start"));
        DSpBx_Start->setFont(font);
        DSpBx_Start->setAlignment(Qt::AlignCenter);
        DSpBx_Start->setDecimals(8);
        DSpBx_Start->setMaximum(100000.000000000000000);

        GLY01->addWidget(DSpBx_Start, 0, 1, 1, 1);

        Lbl_End = new QLabel(solver);
        Lbl_End->setObjectName(QString::fromUtf8("Lbl_End"));
        Lbl_End->setFont(font2);
        Lbl_End->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_End->setWordWrap(true);

        GLY01->addWidget(Lbl_End, 1, 0, 1, 1);

        DSpBx_End = new QDoubleSpinBox(solver);
        DSpBx_End->setObjectName(QString::fromUtf8("DSpBx_End"));
        DSpBx_End->setFont(font);
        DSpBx_End->setAlignment(Qt::AlignCenter);
        DSpBx_End->setDecimals(8);
        DSpBx_End->setValue(20.000000000000000);

        GLY01->addWidget(DSpBx_End, 1, 1, 1, 1);

        DSpBx_DeltaT = new QDoubleSpinBox(solver);
        DSpBx_DeltaT->setObjectName(QString::fromUtf8("DSpBx_DeltaT"));
        DSpBx_DeltaT->setFont(font);
        DSpBx_DeltaT->setAlignment(Qt::AlignCenter);
        DSpBx_DeltaT->setDecimals(8);
        DSpBx_DeltaT->setMaximum(100000.000000000000000);
        DSpBx_DeltaT->setValue(0.000001000000000);

        GLY01->addWidget(DSpBx_DeltaT, 2, 1, 1, 1);

        Lbl_WriteT = new QLabel(solver);
        Lbl_WriteT->setObjectName(QString::fromUtf8("Lbl_WriteT"));
        Lbl_WriteT->setFont(font2);
        Lbl_WriteT->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_WriteT->setWordWrap(true);

        GLY01->addWidget(Lbl_WriteT, 3, 0, 1, 1);

        DSpBx_WriteT = new QDoubleSpinBox(solver);
        DSpBx_WriteT->setObjectName(QString::fromUtf8("DSpBx_WriteT"));
        DSpBx_WriteT->setFont(font);
        DSpBx_WriteT->setAlignment(Qt::AlignCenter);
        DSpBx_WriteT->setDecimals(8);
        DSpBx_WriteT->setMaximum(100000.000000000000000);
        DSpBx_WriteT->setValue(0.001000000000000);

        GLY01->addWidget(DSpBx_WriteT, 3, 1, 1, 1);

        GLY01->setColumnMinimumWidth(0, 3);
        GLY01->setColumnMinimumWidth(1, 1);

        verticalLayout->addLayout(GLY01);

        ChB_Restart = new QCheckBox(solver);
        ChB_Restart->setObjectName(QString::fromUtf8("ChB_Restart"));
        ChB_Restart->setFont(font);
        ChB_Restart->setToolTipDuration(10000);

        verticalLayout->addWidget(ChB_Restart);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Led_Path = new QLineEdit(solver);
        Led_Path->setObjectName(QString::fromUtf8("Led_Path"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Led_Path->sizePolicy().hasHeightForWidth());
        Led_Path->setSizePolicy(sizePolicy);
        Led_Path->setMinimumSize(QSize(200, 30));
        Led_Path->setMaximumSize(QSize(400, 30));
        Led_Path->setFont(font);
        Led_Path->setReadOnly(true);

        horizontalLayout->addWidget(Led_Path);

        Btn_UploadFiles = new QPushButton(solver);
        Btn_UploadFiles->setObjectName(QString::fromUtf8("Btn_UploadFiles"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Btn_UploadFiles->sizePolicy().hasHeightForWidth());
        Btn_UploadFiles->setSizePolicy(sizePolicy1);
        Btn_UploadFiles->setFont(font);
        Btn_UploadFiles->setToolTipDuration(10000);

        horizontalLayout->addWidget(Btn_UploadFiles);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        Lbl_Domain = new QLabel(solver);
        Lbl_Domain->setObjectName(QString::fromUtf8("Lbl_Domain"));
        Lbl_Domain->setFont(font1);

        verticalLayout->addWidget(Lbl_Domain);

        GLY02 = new QGridLayout();
        GLY02->setObjectName(QString::fromUtf8("GLY02"));
        DSpBx_Px = new QDoubleSpinBox(solver);
        DSpBx_Px->setObjectName(QString::fromUtf8("DSpBx_Px"));
        DSpBx_Px->setFont(font);
        DSpBx_Px->setAlignment(Qt::AlignCenter);
        DSpBx_Px->setDecimals(0);
        DSpBx_Px->setMinimum(1.000000000000000);
        DSpBx_Px->setMaximum(10000.000000000000000);
        DSpBx_Px->setValue(3.000000000000000);

        GLY02->addWidget(DSpBx_Px, 0, 1, 1, 1);

        DSpBx_Pz = new QDoubleSpinBox(solver);
        DSpBx_Pz->setObjectName(QString::fromUtf8("DSpBx_Pz"));
        DSpBx_Pz->setFont(font);
        DSpBx_Pz->setAlignment(Qt::AlignCenter);
        DSpBx_Pz->setDecimals(0);
        DSpBx_Pz->setValue(1.000000000000000);

        GLY02->addWidget(DSpBx_Pz, 0, 3, 1, 1);

        Lbl_Subdomains = new QLabel(solver);
        Lbl_Subdomains->setObjectName(QString::fromUtf8("Lbl_Subdomains"));
        Lbl_Subdomains->setFont(font2);
        Lbl_Subdomains->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Subdomains->setWordWrap(true);

        GLY02->addWidget(Lbl_Subdomains, 0, 0, 1, 1);

        DSpBx_Py = new QDoubleSpinBox(solver);
        DSpBx_Py->setObjectName(QString::fromUtf8("DSpBx_Py"));
        DSpBx_Py->setFont(font);
        DSpBx_Py->setAlignment(Qt::AlignCenter);
        DSpBx_Py->setDecimals(0);
        DSpBx_Py->setValue(2.000000000000000);

        GLY02->addWidget(DSpBx_Py, 0, 2, 1, 1);

        Lbl_Decomp = new QLabel(solver);
        Lbl_Decomp->setObjectName(QString::fromUtf8("Lbl_Decomp"));
        Lbl_Decomp->setFont(font2);
        Lbl_Decomp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Decomp->setWordWrap(true);

        GLY02->addWidget(Lbl_Decomp, 1, 0, 1, 1);

        Cmb_Decomp = new QComboBox(solver);
        Cmb_Decomp->addItem(QString());
        Cmb_Decomp->setObjectName(QString::fromUtf8("Cmb_Decomp"));
        Cmb_Decomp->setFont(font);
        Cmb_Decomp->setToolTipDuration(10000);

        GLY02->addWidget(Cmb_Decomp, 1, 1, 1, 3);


        verticalLayout->addLayout(GLY02);

        Lbl_CFDSolver = new QLabel(solver);
        Lbl_CFDSolver->setObjectName(QString::fromUtf8("Lbl_CFDSolver"));
        Lbl_CFDSolver->setFont(font1);

        verticalLayout->addWidget(Lbl_CFDSolver);

        Cmb_Solver = new QComboBox(solver);
        Cmb_Solver->addItem(QString());
        Cmb_Solver->setObjectName(QString::fromUtf8("Cmb_Solver"));
        Cmb_Solver->setFont(font);
        Cmb_Solver->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_Solver);

        verticalSpacer = new QSpacerItem(20, 415, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(solver);

        QMetaObject::connectSlotsByName(solver);
    } // setupUi

    void retranslateUi(QFrame *solver)
    {
        solver->setWindowTitle(QCoreApplication::translate("solver", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("solver", "<html><head/><body><p><span style=\" font-weight:600;\">SOLVER SETTINGS</span></p></body></html>", nullptr));
        Lbl_TimeSettings->setText(QCoreApplication::translate("solver", "Time settings", nullptr));
        Lbl_DeltaT->setText(QCoreApplication::translate("solver", "Time interval", nullptr));
        Lbl_Start->setText(QCoreApplication::translate("solver", "Start time", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Start->setToolTip(QCoreApplication::translate("solver", "Start time of the simulation", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_End->setText(QCoreApplication::translate("solver", "End time", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_End->setToolTip(QCoreApplication::translate("solver", "End time of the simulation", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_DeltaT->setToolTip(QCoreApplication::translate("solver", "Time step size", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_WriteT->setText(QCoreApplication::translate("solver", "Write interval", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_WriteT->setToolTip(QCoreApplication::translate("solver", "Intervals at which output is written", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ChB_Restart->setToolTip(QCoreApplication::translate("solver", "Check if the simularion is being restarted", nullptr));
#endif // QT_CONFIG(tooltip)
        ChB_Restart->setText(QCoreApplication::translate("solver", "Restart on", nullptr));
#if QT_CONFIG(tooltip)
        Btn_UploadFiles->setToolTip(QCoreApplication::translate("solver", "Upload a single .zip file", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadFiles->setText(QCoreApplication::translate("solver", "Upload restart files", nullptr));
        Lbl_Domain->setText(QCoreApplication::translate("solver", "Domain decomposition", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Px->setToolTip(QCoreApplication::translate("solver", "Number of domains along x", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_Pz->setToolTip(QCoreApplication::translate("solver", "Number of domains along z", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Subdomains->setText(QCoreApplication::translate("solver", "Num. of Subdomains", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Py->setToolTip(QCoreApplication::translate("solver", "Number of domains along y", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Decomp->setText(QCoreApplication::translate("solver", "Decomposition type", nullptr));
        Cmb_Decomp->setItemText(0, QCoreApplication::translate("solver", "Scotch", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_Decomp->setToolTip(QCoreApplication::translate("solver", "Type of domain decomposition for parallelization", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_CFDSolver->setText(QCoreApplication::translate("solver", "CFD solver", nullptr));
        Cmb_Solver->setItemText(0, QCoreApplication::translate("solver", "OpenFOAM7", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_Solver->setToolTip(QCoreApplication::translate("solver", "CFD solver to be used here", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class solver: public Ui_solver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLVER_H
