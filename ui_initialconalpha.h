/********************************************************************************
** Form generated from reading UI file 'initialconalpha.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALCONALPHA_H
#define UI_INITIALCONALPHA_H

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

class Ui_initialconAlpha
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QHBoxLayout *HLY_Alpha;
    QLabel *Lbl_Alpha;
    QDoubleSpinBox *DSpBx_Alpha;
    QLabel *Lbl_Notice;
    QLabel *Lbl_Regions;
    QTableWidget *Tbl_IniCondTable;
    QHBoxLayout *HLY_AddRegion;
    QToolButton *Btn_AddRegion;
    QToolButton *Btn_RemRegion;
    QSpacerItem *VSp;

    void setupUi(QFrame *initialconAlpha)
    {
        if (initialconAlpha->objectName().isEmpty())
            initialconAlpha->setObjectName(QString::fromUtf8("initialconAlpha"));
        initialconAlpha->resize(412, 917);
        verticalLayout = new QVBoxLayout(initialconAlpha);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(initialconAlpha);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        HLY_Alpha = new QHBoxLayout();
        HLY_Alpha->setObjectName(QString::fromUtf8("HLY_Alpha"));
        Lbl_Alpha = new QLabel(initialconAlpha);
        Lbl_Alpha->setObjectName(QString::fromUtf8("Lbl_Alpha"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_Alpha->setFont(font1);
        Lbl_Alpha->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Alpha->setWordWrap(true);

        HLY_Alpha->addWidget(Lbl_Alpha);

        DSpBx_Alpha = new QDoubleSpinBox(initialconAlpha);
        DSpBx_Alpha->setObjectName(QString::fromUtf8("DSpBx_Alpha"));
        DSpBx_Alpha->setFont(font);
        DSpBx_Alpha->setAlignment(Qt::AlignCenter);

        HLY_Alpha->addWidget(DSpBx_Alpha);


        verticalLayout->addLayout(HLY_Alpha);

        Lbl_Notice = new QLabel(initialconAlpha);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font);

        verticalLayout->addWidget(Lbl_Notice);

        Lbl_Regions = new QLabel(initialconAlpha);
        Lbl_Regions->setObjectName(QString::fromUtf8("Lbl_Regions"));
        Lbl_Regions->setFont(font);
        Lbl_Regions->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_Regions);

        Tbl_IniCondTable = new QTableWidget(initialconAlpha);
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
        Btn_AddRegion = new QToolButton(initialconAlpha);
        Btn_AddRegion->setObjectName(QString::fromUtf8("Btn_AddRegion"));
        Btn_AddRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_AddRegion);

        Btn_RemRegion = new QToolButton(initialconAlpha);
        Btn_RemRegion->setObjectName(QString::fromUtf8("Btn_RemRegion"));
        Btn_RemRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_RemRegion);


        verticalLayout->addLayout(HLY_AddRegion);

        VSp = new QSpacerItem(20, 365, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(initialconAlpha);

        QMetaObject::connectSlotsByName(initialconAlpha);
    } // setupUi

    void retranslateUi(QFrame *initialconAlpha)
    {
        initialconAlpha->setWindowTitle(QCoreApplication::translate("initialconAlpha", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("initialconAlpha", "<html><head/><body><p><span style=\" font-weight:600;\">INITIAL CONDITIONS (PHASE)</span></p></body></html>", nullptr));
        Lbl_Alpha->setText(QCoreApplication::translate("initialconAlpha", "Alpha value", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Alpha->setToolTip(QCoreApplication::translate("initialconAlpha", "Global initial value of phase", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Notice->setText(QCoreApplication::translate("initialconAlpha", "Initial conditions are already prescribed through \n"
"the shallow water solvers", nullptr));
        Lbl_Regions->setText(QCoreApplication::translate("initialconAlpha", "<html><head/><body><p><span style=\" font-weight:600;\">Regions</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Tbl_IniCondTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("initialconAlpha", "P1(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Tbl_IniCondTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("initialconAlpha", "P2(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Tbl_IniCondTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("initialconAlpha", "Value", nullptr));
#if QT_CONFIG(tooltip)
        Tbl_IniCondTable->setToolTip(QCoreApplication::translate("initialconAlpha", "Regions for initial condition (phase)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddRegion->setToolTip(QCoreApplication::translate("initialconAlpha", "Add regions for defining initial conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddRegion->setText(QCoreApplication::translate("initialconAlpha", "Add region", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemRegion->setToolTip(QCoreApplication::translate("initialconAlpha", "Remove regions for defining initial conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemRegion->setText(QCoreApplication::translate("initialconAlpha", "Remove region", nullptr));
    } // retranslateUi

};

namespace Ui {
    class initialconAlpha: public Ui_initialconAlpha {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALCONALPHA_H
