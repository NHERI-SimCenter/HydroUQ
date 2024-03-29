/********************************************************************************
** Form generated from reading UI file 'initialconvel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALCONVEL_H
#define UI_INITIALCONVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_initialconVel
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_Notice;
    QHBoxLayout *HLY_Vel;
    QLabel *Lbl_Vel;
    QDoubleSpinBox *DSpBx_Vx;
    QDoubleSpinBox *DSpBx_Vy;
    QDoubleSpinBox *DSpBx_Vz;
    QLabel *Lbl_Regions;
    QTableWidget *Tbl_IniCondTable;
    QHBoxLayout *HLY_AddRegion;
    QToolButton *Btn_AddRegion;
    QToolButton *Btn_RemRegion;
    QSpacerItem *VSp;

    void setupUi(QFrame *initialconVel)
    {
        if (initialconVel->objectName().isEmpty())
            initialconVel->setObjectName(QString::fromUtf8("initialconVel"));
        initialconVel->resize(450, 937);
        verticalLayout = new QVBoxLayout(initialconVel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(initialconVel);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_Notice = new QLabel(initialconVel);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font);

        verticalLayout->addWidget(Lbl_Notice);

        HLY_Vel = new QHBoxLayout();
        HLY_Vel->setObjectName(QString::fromUtf8("HLY_Vel"));
        Lbl_Vel = new QLabel(initialconVel);
        Lbl_Vel->setObjectName(QString::fromUtf8("Lbl_Vel"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_Vel->setFont(font1);
        Lbl_Vel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Vel->setWordWrap(true);

        HLY_Vel->addWidget(Lbl_Vel);

        DSpBx_Vx = new QDoubleSpinBox(initialconVel);
        DSpBx_Vx->setObjectName(QString::fromUtf8("DSpBx_Vx"));
        DSpBx_Vx->setFont(font);
        DSpBx_Vx->setAlignment(Qt::AlignCenter);

        HLY_Vel->addWidget(DSpBx_Vx);

        DSpBx_Vy = new QDoubleSpinBox(initialconVel);
        DSpBx_Vy->setObjectName(QString::fromUtf8("DSpBx_Vy"));
        DSpBx_Vy->setFont(font);
        DSpBx_Vy->setAlignment(Qt::AlignCenter);

        HLY_Vel->addWidget(DSpBx_Vy);

        DSpBx_Vz = new QDoubleSpinBox(initialconVel);
        DSpBx_Vz->setObjectName(QString::fromUtf8("DSpBx_Vz"));
        DSpBx_Vz->setFont(font);
        DSpBx_Vz->setAlignment(Qt::AlignCenter);

        HLY_Vel->addWidget(DSpBx_Vz);


        verticalLayout->addLayout(HLY_Vel);

        Lbl_Regions = new QLabel(initialconVel);
        Lbl_Regions->setObjectName(QString::fromUtf8("Lbl_Regions"));
        Lbl_Regions->setFont(font);
        Lbl_Regions->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_Regions);

        Tbl_IniCondTable = new QTableWidget(initialconVel);
        if (Tbl_IniCondTable->columnCount() < 3)
            Tbl_IniCondTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        Tbl_IniCondTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        Tbl_IniCondTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        Tbl_IniCondTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        Tbl_IniCondTable->setObjectName(QString::fromUtf8("Tbl_IniCondTable"));
        Tbl_IniCondTable->setFont(font);
        Tbl_IniCondTable->setToolTipDuration(10000);
        Tbl_IniCondTable->setAlternatingRowColors(true);

        verticalLayout->addWidget(Tbl_IniCondTable);

        HLY_AddRegion = new QHBoxLayout();
        HLY_AddRegion->setObjectName(QString::fromUtf8("HLY_AddRegion"));
        Btn_AddRegion = new QToolButton(initialconVel);
        Btn_AddRegion->setObjectName(QString::fromUtf8("Btn_AddRegion"));
        Btn_AddRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_AddRegion);

        Btn_RemRegion = new QToolButton(initialconVel);
        Btn_RemRegion->setObjectName(QString::fromUtf8("Btn_RemRegion"));
        Btn_RemRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_RemRegion);


        verticalLayout->addLayout(HLY_AddRegion);

        VSp = new QSpacerItem(20, 375, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(initialconVel);

        QMetaObject::connectSlotsByName(initialconVel);
    } // setupUi

    void retranslateUi(QFrame *initialconVel)
    {
        initialconVel->setWindowTitle(QCoreApplication::translate("initialconVel", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("initialconVel", "<html><head/><body><p><span style=\" font-weight:600;\">INITIAL CONDITIONS (VELOCITY)</span></p></body></html>", nullptr));
        Lbl_Notice->setText(QCoreApplication::translate("initialconVel", "Initial conditions are already prescribed through \n"
"the shallow water solvers", nullptr));
        Lbl_Vel->setText(QCoreApplication::translate("initialconVel", "Velocity", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Vx->setToolTip(QCoreApplication::translate("initialconVel", "Global x-component of velocity", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_Vy->setToolTip(QCoreApplication::translate("initialconVel", "Global y-component of velocity", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_Vz->setToolTip(QCoreApplication::translate("initialconVel", "Global z-component of velocity", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Regions->setText(QCoreApplication::translate("initialconVel", "<html><head/><body><p><span style=\" font-weight:600;\">Regions</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Tbl_IniCondTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("initialconVel", "P1(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Tbl_IniCondTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("initialconVel", "P2(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Tbl_IniCondTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("initialconVel", "(Vx,Vy,Vz)", nullptr));
#if QT_CONFIG(tooltip)
        Tbl_IniCondTable->setToolTip(QCoreApplication::translate("initialconVel", "Regions for initial condition (Velocity)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddRegion->setToolTip(QCoreApplication::translate("initialconVel", "Add regions for defining initial conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddRegion->setText(QCoreApplication::translate("initialconVel", "Add region", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemRegion->setToolTip(QCoreApplication::translate("initialconVel", "Remove regions for defining initial conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemRegion->setText(QCoreApplication::translate("initialconVel", "Remove region", nullptr));
    } // retranslateUi

};

namespace Ui {
    class initialconVel: public Ui_initialconVel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALCONVEL_H
