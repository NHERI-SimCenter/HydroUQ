/********************************************************************************
** Form generated from reading UI file 'buildings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDINGS_H
#define UI_BUILDINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_buildings
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *Lbl_H1;
    QComboBox *CmB_BuildData;
    QGroupBox *GroupPara;
    QGridLayout *gridLayout;
    QLabel *Lbl_NumBuildX;
    QDoubleSpinBox *DSpBx_NumBuildX;
    QLabel *Lbl_NumBuildY;
    QDoubleSpinBox *DSpBx_NumBuildY;
    QLabel *Lbl_CoastDist;
    QDoubleSpinBox *DSpBx_CoastDist;
    QLabel *Lbl_BuildDistX;
    QDoubleSpinBox *DSpBx_BuildDistX;
    QLabel *Lbl_BuildDistY;
    QDoubleSpinBox *DSpBx_BuildDistY;
    QDoubleSpinBox *DSpBx_OffsetX;
    QDoubleSpinBox *DSpBx_OffsetY;
    QDoubleSpinBox *DSpBx_BuildSize01;
    QDoubleSpinBox *DSpBx_BuildSize02;
    QDoubleSpinBox *DSpBx_BuildSize03;
    QComboBox *CmB_BuildShape;
    QComboBox *CmB_BuildDist;
    QLabel *Lbl_BuildSize;
    QLabel *Lbl_BuildSize_2;
    QGroupBox *GroupNonpara;
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_Building;
    QTableWidget *Tbl_Building;
    QHBoxLayout *HLY_AddBuild;
    QToolButton *Btn_AddBuild;
    QToolButton *Btn_RemBuild;
    QHBoxLayout *horizontalLayout;
    QLineEdit *PText_CustomBuild;
    QPushButton *Btn_CustomBuild;
    QLabel *Lbl_Notice;
    QSpacerItem *verticalSpacer;

    void setupUi(QFrame *buildings)
    {
        if (buildings->objectName().isEmpty())
            buildings->setObjectName(QString::fromUtf8("buildings"));
        buildings->resize(401, 923);
        verticalLayout_2 = new QVBoxLayout(buildings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(buildings);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(Lbl_H1);

        CmB_BuildData = new QComboBox(buildings);
        CmB_BuildData->addItem(QString());
        CmB_BuildData->addItem(QString());
        CmB_BuildData->setObjectName(QString::fromUtf8("CmB_BuildData"));
        CmB_BuildData->setFont(font);

        verticalLayout_2->addWidget(CmB_BuildData);

        GroupPara = new QGroupBox(buildings);
        GroupPara->setObjectName(QString::fromUtf8("GroupPara"));
        gridLayout = new QGridLayout(GroupPara);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_NumBuildX = new QLabel(GroupPara);
        Lbl_NumBuildX->setObjectName(QString::fromUtf8("Lbl_NumBuildX"));
        Lbl_NumBuildX->setFont(font);

        gridLayout->addWidget(Lbl_NumBuildX, 0, 0, 1, 1);

        DSpBx_NumBuildX = new QDoubleSpinBox(GroupPara);
        DSpBx_NumBuildX->setObjectName(QString::fromUtf8("DSpBx_NumBuildX"));
        DSpBx_NumBuildX->setFont(font);
        DSpBx_NumBuildX->setAlignment(Qt::AlignCenter);
        DSpBx_NumBuildX->setDecimals(0);
        DSpBx_NumBuildX->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_NumBuildX, 0, 1, 1, 1);

        Lbl_NumBuildY = new QLabel(GroupPara);
        Lbl_NumBuildY->setObjectName(QString::fromUtf8("Lbl_NumBuildY"));
        Lbl_NumBuildY->setFont(font);

        gridLayout->addWidget(Lbl_NumBuildY, 1, 0, 1, 1);

        DSpBx_NumBuildY = new QDoubleSpinBox(GroupPara);
        DSpBx_NumBuildY->setObjectName(QString::fromUtf8("DSpBx_NumBuildY"));
        DSpBx_NumBuildY->setFont(font);
        DSpBx_NumBuildY->setAlignment(Qt::AlignCenter);
        DSpBx_NumBuildY->setDecimals(0);
        DSpBx_NumBuildY->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_NumBuildY, 1, 1, 1, 1);

        Lbl_CoastDist = new QLabel(GroupPara);
        Lbl_CoastDist->setObjectName(QString::fromUtf8("Lbl_CoastDist"));
        Lbl_CoastDist->setFont(font);

        gridLayout->addWidget(Lbl_CoastDist, 2, 0, 1, 1);

        DSpBx_CoastDist = new QDoubleSpinBox(GroupPara);
        DSpBx_CoastDist->setObjectName(QString::fromUtf8("DSpBx_CoastDist"));
        DSpBx_CoastDist->setFont(font);
        DSpBx_CoastDist->setAlignment(Qt::AlignCenter);
        DSpBx_CoastDist->setDecimals(2);
        DSpBx_CoastDist->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_CoastDist, 2, 1, 1, 1);

        Lbl_BuildDistX = new QLabel(GroupPara);
        Lbl_BuildDistX->setObjectName(QString::fromUtf8("Lbl_BuildDistX"));
        Lbl_BuildDistX->setFont(font);

        gridLayout->addWidget(Lbl_BuildDistX, 3, 0, 1, 1);

        DSpBx_BuildDistX = new QDoubleSpinBox(GroupPara);
        DSpBx_BuildDistX->setObjectName(QString::fromUtf8("DSpBx_BuildDistX"));
        DSpBx_BuildDistX->setFont(font);
        DSpBx_BuildDistX->setAlignment(Qt::AlignCenter);
        DSpBx_BuildDistX->setDecimals(2);
        DSpBx_BuildDistX->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_BuildDistX, 3, 1, 1, 1);

        Lbl_BuildDistY = new QLabel(GroupPara);
        Lbl_BuildDistY->setObjectName(QString::fromUtf8("Lbl_BuildDistY"));
        Lbl_BuildDistY->setFont(font);

        gridLayout->addWidget(Lbl_BuildDistY, 4, 0, 1, 1);

        DSpBx_BuildDistY = new QDoubleSpinBox(GroupPara);
        DSpBx_BuildDistY->setObjectName(QString::fromUtf8("DSpBx_BuildDistY"));
        DSpBx_BuildDistY->setFont(font);
        DSpBx_BuildDistY->setAlignment(Qt::AlignCenter);
        DSpBx_BuildDistY->setDecimals(2);
        DSpBx_BuildDistY->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_BuildDistY, 4, 1, 1, 1);

        DSpBx_OffsetX = new QDoubleSpinBox(GroupPara);
        DSpBx_OffsetX->setObjectName(QString::fromUtf8("DSpBx_OffsetX"));
        DSpBx_OffsetX->setFont(font);
        DSpBx_OffsetX->setAlignment(Qt::AlignCenter);
        DSpBx_OffsetX->setDecimals(2);
        DSpBx_OffsetX->setMaximum(100000.000000000000000);
        DSpBx_OffsetX->setValue(0.000000000000000);

        gridLayout->addWidget(DSpBx_OffsetX, 5, 1, 1, 1);

        DSpBx_OffsetY = new QDoubleSpinBox(GroupPara);
        DSpBx_OffsetY->setObjectName(QString::fromUtf8("DSpBx_OffsetY"));
        DSpBx_OffsetY->setFont(font);
        DSpBx_OffsetY->setAlignment(Qt::AlignCenter);
        DSpBx_OffsetY->setDecimals(2);
        DSpBx_OffsetY->setMaximum(100000.000000000000000);
        DSpBx_OffsetY->setValue(0.000000000000000);

        gridLayout->addWidget(DSpBx_OffsetY, 6, 1, 1, 1);

        DSpBx_BuildSize01 = new QDoubleSpinBox(GroupPara);
        DSpBx_BuildSize01->setObjectName(QString::fromUtf8("DSpBx_BuildSize01"));
        DSpBx_BuildSize01->setFont(font);
        DSpBx_BuildSize01->setAlignment(Qt::AlignCenter);
        DSpBx_BuildSize01->setDecimals(2);
        DSpBx_BuildSize01->setMaximum(100000.000000000000000);
        DSpBx_BuildSize01->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_BuildSize01, 8, 1, 1, 1);

        DSpBx_BuildSize02 = new QDoubleSpinBox(GroupPara);
        DSpBx_BuildSize02->setObjectName(QString::fromUtf8("DSpBx_BuildSize02"));
        DSpBx_BuildSize02->setFont(font);
        DSpBx_BuildSize02->setAlignment(Qt::AlignCenter);
        DSpBx_BuildSize02->setDecimals(2);
        DSpBx_BuildSize02->setMaximum(100000.000000000000000);
        DSpBx_BuildSize02->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_BuildSize02, 9, 1, 1, 1);

        DSpBx_BuildSize03 = new QDoubleSpinBox(GroupPara);
        DSpBx_BuildSize03->setObjectName(QString::fromUtf8("DSpBx_BuildSize03"));
        DSpBx_BuildSize03->setFont(font);
        DSpBx_BuildSize03->setAlignment(Qt::AlignCenter);
        DSpBx_BuildSize03->setDecimals(2);
        DSpBx_BuildSize03->setMaximum(100000.000000000000000);
        DSpBx_BuildSize03->setValue(2.000000000000000);

        gridLayout->addWidget(DSpBx_BuildSize03, 10, 1, 1, 1);

        CmB_BuildShape = new QComboBox(GroupPara);
        CmB_BuildShape->addItem(QString());
        CmB_BuildShape->addItem(QString());
        CmB_BuildShape->addItem(QString());
        CmB_BuildShape->setObjectName(QString::fromUtf8("CmB_BuildShape"));
        CmB_BuildShape->setFont(font);

        gridLayout->addWidget(CmB_BuildShape, 7, 0, 1, 2);

        CmB_BuildDist = new QComboBox(GroupPara);
        CmB_BuildDist->addItem(QString());
        CmB_BuildDist->addItem(QString());
        CmB_BuildDist->addItem(QString());
        CmB_BuildDist->setObjectName(QString::fromUtf8("CmB_BuildDist"));
        CmB_BuildDist->setFont(font);

        gridLayout->addWidget(CmB_BuildDist, 11, 0, 1, 2);

        Lbl_BuildSize = new QLabel(GroupPara);
        Lbl_BuildSize->setObjectName(QString::fromUtf8("Lbl_BuildSize"));
        Lbl_BuildSize->setFont(font);

        gridLayout->addWidget(Lbl_BuildSize, 8, 0, 3, 1);

        Lbl_BuildSize_2 = new QLabel(GroupPara);
        Lbl_BuildSize_2->setObjectName(QString::fromUtf8("Lbl_BuildSize_2"));
        Lbl_BuildSize_2->setFont(font);

        gridLayout->addWidget(Lbl_BuildSize_2, 5, 0, 2, 1);


        verticalLayout_2->addWidget(GroupPara);

        GroupNonpara = new QGroupBox(buildings);
        GroupNonpara->setObjectName(QString::fromUtf8("GroupNonpara"));
        verticalLayout = new QVBoxLayout(GroupNonpara);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_Building = new QLabel(GroupNonpara);
        Lbl_Building->setObjectName(QString::fromUtf8("Lbl_Building"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_Building->setFont(font1);
        Lbl_Building->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_Building);

        Tbl_Building = new QTableWidget(GroupNonpara);
        if (Tbl_Building->columnCount() < 3)
            Tbl_Building->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Tbl_Building->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Tbl_Building->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Tbl_Building->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        Tbl_Building->setObjectName(QString::fromUtf8("Tbl_Building"));
        Tbl_Building->setFont(font);
        Tbl_Building->setToolTipDuration(10000);

        verticalLayout->addWidget(Tbl_Building);

        HLY_AddBuild = new QHBoxLayout();
        HLY_AddBuild->setObjectName(QString::fromUtf8("HLY_AddBuild"));
        Btn_AddBuild = new QToolButton(GroupNonpara);
        Btn_AddBuild->setObjectName(QString::fromUtf8("Btn_AddBuild"));
        Btn_AddBuild->setToolTipDuration(10000);

        HLY_AddBuild->addWidget(Btn_AddBuild);

        Btn_RemBuild = new QToolButton(GroupNonpara);
        Btn_RemBuild->setObjectName(QString::fromUtf8("Btn_RemBuild"));
        Btn_RemBuild->setToolTipDuration(10000);

        HLY_AddBuild->addWidget(Btn_RemBuild);


        verticalLayout->addLayout(HLY_AddBuild);


        verticalLayout_2->addWidget(GroupNonpara);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PText_CustomBuild = new QLineEdit(buildings);
        PText_CustomBuild->setObjectName(QString::fromUtf8("PText_CustomBuild"));
        PText_CustomBuild->setFont(font);

        horizontalLayout->addWidget(PText_CustomBuild);

        Btn_CustomBuild = new QPushButton(buildings);
        Btn_CustomBuild->setObjectName(QString::fromUtf8("Btn_CustomBuild"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Btn_CustomBuild->sizePolicy().hasHeightForWidth());
        Btn_CustomBuild->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Btn_CustomBuild);


        verticalLayout_2->addLayout(horizontalLayout);

        Lbl_Notice = new QLabel(buildings);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font);

        verticalLayout_2->addWidget(Lbl_Notice);

        verticalSpacer = new QSpacerItem(20, 236, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(buildings);

        QMetaObject::connectSlotsByName(buildings);
    } // setupUi

    void retranslateUi(QFrame *buildings)
    {
        buildings->setWindowTitle(QCoreApplication::translate("buildings", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("buildings", "<html><head/><body><p><span style=\" font-weight:600;\">STRUCTURAL SETTINGS</span></p></body></html>", nullptr));
        CmB_BuildData->setItemText(0, QCoreApplication::translate("buildings", "Manually add structural data", nullptr));
        CmB_BuildData->setItemText(1, QCoreApplication::translate("buildings", "Parameterized structure data", nullptr));

#if QT_CONFIG(tooltip)
        CmB_BuildData->setToolTip(QCoreApplication::translate("buildings", "Select how building data will be provided", nullptr));
#endif // QT_CONFIG(tooltip)
        GroupPara->setTitle(QString());
        Lbl_NumBuildX->setText(QCoreApplication::translate("buildings", "Number of structures along the coast", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_NumBuildX->setToolTip(QCoreApplication::translate("buildings", "Number of columns of the buildings along the coast", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_NumBuildY->setText(QCoreApplication::translate("buildings", "Number ofstructures into the coast", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_NumBuildY->setToolTip(QCoreApplication::translate("buildings", "Number of rows of buildings into the coast", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_CoastDist->setText(QCoreApplication::translate("buildings", "Distance from coast", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_CoastDist->setToolTip(QCoreApplication::translate("buildings", "Distance of the building from the coast", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_BuildDistX->setText(QCoreApplication::translate("buildings", "Distance between structures (Side)", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_BuildDistX->setToolTip(QCoreApplication::translate("buildings", "Distance between buildings along the coast", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_BuildDistY->setText(QCoreApplication::translate("buildings", "Distance between structures (Front)", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_BuildDistY->setToolTip(QCoreApplication::translate("buildings", "Distance of the buildings (into the coast)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_OffsetX->setToolTip(QCoreApplication::translate("buildings", "Distance from coast (along the coast)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_OffsetY->setToolTip(QCoreApplication::translate("buildings", "Distance from coast (into the coast)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_BuildSize01->setToolTip(QCoreApplication::translate("buildings", "Building size parameter 01", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_BuildSize02->setToolTip(QCoreApplication::translate("buildings", "Building size parameter 02", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DSpBx_BuildSize03->setToolTip(QCoreApplication::translate("buildings", "Building size parameter 03", nullptr));
#endif // QT_CONFIG(tooltip)
        CmB_BuildShape->setItemText(0, QCoreApplication::translate("buildings", "Choose structure shape", nullptr));
        CmB_BuildShape->setItemText(1, QCoreApplication::translate("buildings", "Cuboid", nullptr));
        CmB_BuildShape->setItemText(2, QCoreApplication::translate("buildings", "User-defined", nullptr));

#if QT_CONFIG(tooltip)
        CmB_BuildShape->setToolTip(QCoreApplication::translate("buildings", "Choose the building shape", nullptr));
#endif // QT_CONFIG(tooltip)
        CmB_BuildDist->setItemText(0, QCoreApplication::translate("buildings", "Choose distribution of structures", nullptr));
        CmB_BuildDist->setItemText(1, QCoreApplication::translate("buildings", "Simple", nullptr));
        CmB_BuildDist->setItemText(2, QCoreApplication::translate("buildings", "Staggered", nullptr));

#if QT_CONFIG(tooltip)
        CmB_BuildDist->setToolTip(QCoreApplication::translate("buildings", "Choose distribution of buildings", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_BuildSize->setText(QCoreApplication::translate("buildings", "Structural size (Length / Breadth / Height)", nullptr));
        Lbl_BuildSize_2->setText(QCoreApplication::translate("buildings", "Coordinate of coastline center (Lat/Long)", nullptr));
        GroupNonpara->setTitle(QString());
        Lbl_Building->setText(QCoreApplication::translate("buildings", "<html><head/><body><p>Structure datatable</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Tbl_Building->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("buildings", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Tbl_Building->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("buildings", "Center (x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Tbl_Building->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("buildings", "Parameters", nullptr));
#if QT_CONFIG(tooltip)
        Tbl_Building->setToolTip(QCoreApplication::translate("buildings", "Table of building position data", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddBuild->setToolTip(QCoreApplication::translate("buildings", "Add building data", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddBuild->setText(QCoreApplication::translate("buildings", "Add building", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemBuild->setToolTip(QCoreApplication::translate("buildings", "Remove building data", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemBuild->setText(QCoreApplication::translate("buildings", "Remove building", nullptr));
        Btn_CustomBuild->setText(QCoreApplication::translate("buildings", "Upload custom \n"
"structure .stl file", nullptr));
        Lbl_Notice->setText(QCoreApplication::translate("buildings", "Structural settings are presently not available for this \n"
"option", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buildings: public Ui_buildings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDINGS_H
