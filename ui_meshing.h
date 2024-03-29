/********************************************************************************
** Form generated from reading UI file 'meshing.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHING_H
#define UI_MESHING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_meshing
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_MeshType;
    QComboBox *Cmb_MeshType;
    QLabel *Lbl_MeshGen;
    QComboBox *Cmb_MeshGen;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *PText_Path;
    QPushButton *Btn_UploadMesh;
    QLabel *Lbl_FineH2;
    QSlider *HSl_MeshSize;
    QHBoxLayout *HLY_MeshFine;
    QLabel *Lbl_FineMesh;
    QLabel *Lbl_CoarseMesh;
    QLabel *Lbl_H2Regions;
    QTableWidget *Tbl_Regions;
    QHBoxLayout *HLY_AddRegion;
    QToolButton *Btn_AddRegion;
    QToolButton *Btn_RemRegion;
    QSpacerItem *VSp;

    void setupUi(QFrame *meshing)
    {
        if (meshing->objectName().isEmpty())
            meshing->setObjectName(QString::fromUtf8("meshing"));
        meshing->resize(438, 995);
        verticalLayout = new QVBoxLayout(meshing);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(meshing);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_MeshType = new QLabel(meshing);
        Lbl_MeshType->setObjectName(QString::fromUtf8("Lbl_MeshType"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_MeshType->setFont(font1);

        verticalLayout->addWidget(Lbl_MeshType);

        Cmb_MeshType = new QComboBox(meshing);
        Cmb_MeshType->addItem(QString());
        Cmb_MeshType->addItem(QString());
        Cmb_MeshType->addItem(QString());
        Cmb_MeshType->setObjectName(QString::fromUtf8("Cmb_MeshType"));
        Cmb_MeshType->setFont(font);
        Cmb_MeshType->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_MeshType);

        Lbl_MeshGen = new QLabel(meshing);
        Lbl_MeshGen->setObjectName(QString::fromUtf8("Lbl_MeshGen"));
        Lbl_MeshGen->setFont(font1);

        verticalLayout->addWidget(Lbl_MeshGen);

        Cmb_MeshGen = new QComboBox(meshing);
        Cmb_MeshGen->addItem(QString());
        Cmb_MeshGen->addItem(QString());
        Cmb_MeshGen->addItem(QString());
        Cmb_MeshGen->addItem(QString());
        Cmb_MeshGen->addItem(QString());
        Cmb_MeshGen->setObjectName(QString::fromUtf8("Cmb_MeshGen"));
        Cmb_MeshGen->setFont(font);
        Cmb_MeshGen->setToolTipDuration(10000);

        verticalLayout->addWidget(Cmb_MeshGen);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PText_Path = new QPlainTextEdit(meshing);
        PText_Path->setObjectName(QString::fromUtf8("PText_Path"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PText_Path->sizePolicy().hasHeightForWidth());
        PText_Path->setSizePolicy(sizePolicy);
        PText_Path->setMinimumSize(QSize(200, 50));
        PText_Path->setMaximumSize(QSize(400, 50));
        PText_Path->setFont(font);
        PText_Path->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        PText_Path->setReadOnly(true);

        horizontalLayout->addWidget(PText_Path);

        Btn_UploadMesh = new QPushButton(meshing);
        Btn_UploadMesh->setObjectName(QString::fromUtf8("Btn_UploadMesh"));
        Btn_UploadMesh->setFont(font);
        Btn_UploadMesh->setToolTipDuration(10000);

        horizontalLayout->addWidget(Btn_UploadMesh);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        Lbl_FineH2 = new QLabel(meshing);
        Lbl_FineH2->setObjectName(QString::fromUtf8("Lbl_FineH2"));
        Lbl_FineH2->setFont(font1);
        Lbl_FineH2->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_FineH2);

        HSl_MeshSize = new QSlider(meshing);
        HSl_MeshSize->setObjectName(QString::fromUtf8("HSl_MeshSize"));
        HSl_MeshSize->setFont(font);
        HSl_MeshSize->setMouseTracking(true);
        HSl_MeshSize->setFocusPolicy(Qt::WheelFocus);
        HSl_MeshSize->setToolTipDuration(10000);
        HSl_MeshSize->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        HSl_MeshSize->setMinimum(1);
        HSl_MeshSize->setMaximum(5);
        HSl_MeshSize->setPageStep(1);
        HSl_MeshSize->setOrientation(Qt::Horizontal);
        HSl_MeshSize->setTickPosition(QSlider::TicksBelow);
        HSl_MeshSize->setTickInterval(1);

        verticalLayout->addWidget(HSl_MeshSize);

        HLY_MeshFine = new QHBoxLayout();
        HLY_MeshFine->setObjectName(QString::fromUtf8("HLY_MeshFine"));
        Lbl_FineMesh = new QLabel(meshing);
        Lbl_FineMesh->setObjectName(QString::fromUtf8("Lbl_FineMesh"));
        QFont font2;
        font2.setPointSize(10);
        Lbl_FineMesh->setFont(font2);

        HLY_MeshFine->addWidget(Lbl_FineMesh);

        Lbl_CoarseMesh = new QLabel(meshing);
        Lbl_CoarseMesh->setObjectName(QString::fromUtf8("Lbl_CoarseMesh"));
        Lbl_CoarseMesh->setFont(font2);
        Lbl_CoarseMesh->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        HLY_MeshFine->addWidget(Lbl_CoarseMesh);


        verticalLayout->addLayout(HLY_MeshFine);

        Lbl_H2Regions = new QLabel(meshing);
        Lbl_H2Regions->setObjectName(QString::fromUtf8("Lbl_H2Regions"));
        Lbl_H2Regions->setFont(font1);
        Lbl_H2Regions->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_H2Regions);

        Tbl_Regions = new QTableWidget(meshing);
        if (Tbl_Regions->columnCount() < 3)
            Tbl_Regions->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        Tbl_Regions->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        Tbl_Regions->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        Tbl_Regions->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        Tbl_Regions->setObjectName(QString::fromUtf8("Tbl_Regions"));
        Tbl_Regions->setFont(font);
        Tbl_Regions->setToolTipDuration(10000);
        Tbl_Regions->setAlternatingRowColors(true);

        verticalLayout->addWidget(Tbl_Regions);

        HLY_AddRegion = new QHBoxLayout();
        HLY_AddRegion->setObjectName(QString::fromUtf8("HLY_AddRegion"));
        Btn_AddRegion = new QToolButton(meshing);
        Btn_AddRegion->setObjectName(QString::fromUtf8("Btn_AddRegion"));
        Btn_AddRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_AddRegion);

        Btn_RemRegion = new QToolButton(meshing);
        Btn_RemRegion->setObjectName(QString::fromUtf8("Btn_RemRegion"));
        Btn_RemRegion->setToolTipDuration(10000);

        HLY_AddRegion->addWidget(Btn_RemRegion);


        verticalLayout->addLayout(HLY_AddRegion);

        VSp = new QSpacerItem(20, 272, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(meshing);

        QMetaObject::connectSlotsByName(meshing);
    } // setupUi

    void retranslateUi(QFrame *meshing)
    {
        meshing->setWindowTitle(QCoreApplication::translate("meshing", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("meshing", "<html><head/><body><p><span style=\" font-weight:600;\">MESH SETTINGS</span></p></body></html>", nullptr));
        Lbl_MeshType->setText(QCoreApplication::translate("meshing", "<html><head/><body><p>Meshing method</p></body></html>", nullptr));
        Cmb_MeshType->setItemText(0, QCoreApplication::translate("meshing", "Use Hydro-UQ mesher", nullptr));
        Cmb_MeshType->setItemText(1, QCoreApplication::translate("meshing", "Upload mesh files", nullptr));
        Cmb_MeshType->setItemText(2, QCoreApplication::translate("meshing", "Upload solver specific mesh dicts", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_MeshType->setToolTip(QCoreApplication::translate("meshing", "Select type of mesh: in-built mesing / upload mesh files", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_MeshGen->setText(QCoreApplication::translate("meshing", "<html><head/><body><p>External mesh generator</p></body></html>", nullptr));
        Cmb_MeshGen->setItemText(0, QCoreApplication::translate("meshing", "FLUENT mesh .msh", nullptr));
        Cmb_MeshGen->setItemText(1, QCoreApplication::translate("meshing", "I-DEAS mesh ANSYS.ans", nullptr));
        Cmb_MeshGen->setItemText(2, QCoreApplication::translate("meshing", "CFX mesh .geo", nullptr));
        Cmb_MeshGen->setItemText(3, QCoreApplication::translate("meshing", "GAMBIT mesh .neu", nullptr));
        Cmb_MeshGen->setItemText(4, QCoreApplication::translate("meshing", "Gmsh file .msh", nullptr));

#if QT_CONFIG(tooltip)
        Cmb_MeshGen->setToolTip(QCoreApplication::translate("meshing", "Select external mesh generator used", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_UploadMesh->setToolTip(QCoreApplication::translate("meshing", "Upload the mesh files or mesh dictionaries", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadMesh->setText(QCoreApplication::translate("meshing", "Upload mesh", nullptr));
        Lbl_FineH2->setText(QCoreApplication::translate("meshing", "<html><head/><body><p>Fineness of mesh</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        HSl_MeshSize->setToolTip(QCoreApplication::translate("meshing", "Define the fineness of the mesh", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_FineMesh->setText(QCoreApplication::translate("meshing", "Very coarse", nullptr));
        Lbl_CoarseMesh->setText(QCoreApplication::translate("meshing", "Very fine", nullptr));
        Lbl_H2Regions->setText(QCoreApplication::translate("meshing", "<html><head/><body><p>Region refinements</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Tbl_Regions->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("meshing", "Level (1-5)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Tbl_Regions->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("meshing", "P1(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Tbl_Regions->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("meshing", "P2(x,y,z)", nullptr));
#if QT_CONFIG(tooltip)
        Tbl_Regions->setToolTip(QCoreApplication::translate("meshing", "Table of regions where mesh needs to be refined", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddRegion->setToolTip(QCoreApplication::translate("meshing", "Add regions for mesh refinement", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddRegion->setText(QCoreApplication::translate("meshing", "Add region", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemRegion->setToolTip(QCoreApplication::translate("meshing", "Remove regions for mesh refinement", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemRegion->setText(QCoreApplication::translate("meshing", "Remove region", nullptr));
    } // retranslateUi

};

namespace Ui {
    class meshing: public Ui_meshing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHING_H
