/********************************************************************************
** Form generated from reading UI file 'bathymetry.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATHYMETRY_H
#define UI_BATHYMETRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_bathymetry
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_SelFiles;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *PText_Files;
    QPushButton *Btn_UploadFiles;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *PText_Solution;
    QPushButton *Btn_UploadSolution;
    QVBoxLayout *VLY_Gravity;
    QComboBox *CmB_FileType;
    QComboBox *CmB_SolFormat;
    QHBoxLayout *HLY_Gravity;
    QLabel *Lbl_Gravity;
    QComboBox *CmB_Grav01;
    QComboBox *CmB_Grav02;
    QComboBox *CmB_Library;
    QLabel *Lbl_Notice;
    QComboBox *CmB_FlumeGeoType;
    QLabel *Lbl_TopViewH2;
    QLabel *Lbl_TopView;
    QHBoxLayout *HLY_Breadth;
    QLabel *Lbl_Breadth;
    QDoubleSpinBox *DSpBx_Breadth;
    QLabel *Lbl_Segments;
    QTableWidget *Tbl_Segments;
    QHBoxLayout *HLY_AddSeg;
    QToolButton *Btn_AddSeg;
    QToolButton *Btn_RemSeg;
    QSpacerItem *VSp;

    void setupUi(QFrame *bathymetry)
    {
        if (bathymetry->objectName().isEmpty())
            bathymetry->setObjectName(QString::fromUtf8("bathymetry"));
        bathymetry->resize(383, 1204);
        verticalLayout = new QVBoxLayout(bathymetry);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Lbl_H1 = new QLabel(bathymetry);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_SelFiles = new QLabel(bathymetry);
        Lbl_SelFiles->setObjectName(QString::fromUtf8("Lbl_SelFiles"));
        QFont font1;
        font1.setPointSize(10);
        Lbl_SelFiles->setFont(font1);
        Lbl_SelFiles->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_SelFiles);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PText_Files = new QPlainTextEdit(bathymetry);
        PText_Files->setObjectName(QString::fromUtf8("PText_Files"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PText_Files->sizePolicy().hasHeightForWidth());
        PText_Files->setSizePolicy(sizePolicy);
        PText_Files->setMinimumSize(QSize(200, 50));
        PText_Files->setMaximumSize(QSize(400, 50));
        PText_Files->setFont(font1);
        PText_Files->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        PText_Files->setReadOnly(true);

        horizontalLayout->addWidget(PText_Files);

        Btn_UploadFiles = new QPushButton(bathymetry);
        Btn_UploadFiles->setObjectName(QString::fromUtf8("Btn_UploadFiles"));
        Btn_UploadFiles->setFont(font1);
        Btn_UploadFiles->setToolTipDuration(10000);

        horizontalLayout->addWidget(Btn_UploadFiles);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        PText_Solution = new QPlainTextEdit(bathymetry);
        PText_Solution->setObjectName(QString::fromUtf8("PText_Solution"));
        sizePolicy.setHeightForWidth(PText_Solution->sizePolicy().hasHeightForWidth());
        PText_Solution->setSizePolicy(sizePolicy);
        PText_Solution->setMinimumSize(QSize(200, 50));
        PText_Solution->setMaximumSize(QSize(400, 50));
        PText_Solution->setFont(font1);
        PText_Solution->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        PText_Solution->setReadOnly(true);

        horizontalLayout_2->addWidget(PText_Solution);

        Btn_UploadSolution = new QPushButton(bathymetry);
        Btn_UploadSolution->setObjectName(QString::fromUtf8("Btn_UploadSolution"));
        Btn_UploadSolution->setFont(font1);
        Btn_UploadSolution->setToolTipDuration(10000);

        horizontalLayout_2->addWidget(Btn_UploadSolution);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        VLY_Gravity = new QVBoxLayout();
        VLY_Gravity->setObjectName(QString::fromUtf8("VLY_Gravity"));
        CmB_FileType = new QComboBox(bathymetry);
        CmB_FileType->addItem(QString());
        CmB_FileType->addItem(QString());
        CmB_FileType->addItem(QString());
        CmB_FileType->addItem(QString());
        CmB_FileType->addItem(QString());
        CmB_FileType->setObjectName(QString::fromUtf8("CmB_FileType"));
        CmB_FileType->setFont(font1);
        CmB_FileType->setToolTipDuration(10000);

        VLY_Gravity->addWidget(CmB_FileType);

        CmB_SolFormat = new QComboBox(bathymetry);
        CmB_SolFormat->addItem(QString());
        CmB_SolFormat->addItem(QString());
        CmB_SolFormat->addItem(QString());
        CmB_SolFormat->setObjectName(QString::fromUtf8("CmB_SolFormat"));
        CmB_SolFormat->setFont(font1);
        CmB_SolFormat->setToolTipDuration(10000);

        VLY_Gravity->addWidget(CmB_SolFormat);

        HLY_Gravity = new QHBoxLayout();
#ifndef Q_OS_MAC
        HLY_Gravity->setSpacing(-1);
#endif
        HLY_Gravity->setObjectName(QString::fromUtf8("HLY_Gravity"));
        Lbl_Gravity = new QLabel(bathymetry);
        Lbl_Gravity->setObjectName(QString::fromUtf8("Lbl_Gravity"));
        Lbl_Gravity->setFont(font1);

        HLY_Gravity->addWidget(Lbl_Gravity);

        CmB_Grav01 = new QComboBox(bathymetry);
        CmB_Grav01->addItem(QString());
        CmB_Grav01->addItem(QString());
        CmB_Grav01->setObjectName(QString::fromUtf8("CmB_Grav01"));
        CmB_Grav01->setFont(font1);

        HLY_Gravity->addWidget(CmB_Grav01);

        CmB_Grav02 = new QComboBox(bathymetry);
        CmB_Grav02->addItem(QString());
        CmB_Grav02->addItem(QString());
        CmB_Grav02->addItem(QString());
        CmB_Grav02->setObjectName(QString::fromUtf8("CmB_Grav02"));
        CmB_Grav02->setFont(font1);

        HLY_Gravity->addWidget(CmB_Grav02);


        VLY_Gravity->addLayout(HLY_Gravity);

        CmB_Library = new QComboBox(bathymetry);
        CmB_Library->addItem(QString());
        CmB_Library->setObjectName(QString::fromUtf8("CmB_Library"));
        CmB_Library->setFont(font1);
        CmB_Library->setToolTipDuration(10000);

        VLY_Gravity->addWidget(CmB_Library);


        verticalLayout->addLayout(VLY_Gravity);

        Lbl_Notice = new QLabel(bathymetry);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font1);
        Lbl_Notice->setMouseTracking(true);
        Lbl_Notice->setFocusPolicy(Qt::ClickFocus);
        Lbl_Notice->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        Lbl_Notice->setWordWrap(true);

        verticalLayout->addWidget(Lbl_Notice);

        CmB_FlumeGeoType = new QComboBox(bathymetry);
        CmB_FlumeGeoType->addItem(QString());
        CmB_FlumeGeoType->addItem(QString());
        CmB_FlumeGeoType->addItem(QString());
        CmB_FlumeGeoType->setObjectName(QString::fromUtf8("CmB_FlumeGeoType"));
        CmB_FlumeGeoType->setFont(font1);
        CmB_FlumeGeoType->setToolTipDuration(10000);

        verticalLayout->addWidget(CmB_FlumeGeoType);

        Lbl_TopViewH2 = new QLabel(bathymetry);
        Lbl_TopViewH2->setObjectName(QString::fromUtf8("Lbl_TopViewH2"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        Lbl_TopViewH2->setFont(font2);
        Lbl_TopViewH2->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_TopViewH2);

        Lbl_TopView = new QLabel(bathymetry);
        Lbl_TopView->setObjectName(QString::fromUtf8("Lbl_TopView"));
        QFont font3;
        font3.setPointSize(48);
        Lbl_TopView->setFont(font3);
        Lbl_TopView->setScaledContents(true);
        Lbl_TopView->setAlignment(Qt::AlignCenter);
        Lbl_TopView->setWordWrap(true);

        verticalLayout->addWidget(Lbl_TopView);

        HLY_Breadth = new QHBoxLayout();
        HLY_Breadth->setObjectName(QString::fromUtf8("HLY_Breadth"));
        Lbl_Breadth = new QLabel(bathymetry);
        Lbl_Breadth->setObjectName(QString::fromUtf8("Lbl_Breadth"));
        Lbl_Breadth->setFont(font2);
        Lbl_Breadth->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Lbl_Breadth->setWordWrap(true);

        HLY_Breadth->addWidget(Lbl_Breadth);

        DSpBx_Breadth = new QDoubleSpinBox(bathymetry);
        DSpBx_Breadth->setObjectName(QString::fromUtf8("DSpBx_Breadth"));
        DSpBx_Breadth->setFont(font1);
        DSpBx_Breadth->setAlignment(Qt::AlignCenter);
        DSpBx_Breadth->setMinimum(0.000000000000000);

        HLY_Breadth->addWidget(DSpBx_Breadth);

        HLY_Breadth->setStretch(0, 2);
        HLY_Breadth->setStretch(1, 1);

        verticalLayout->addLayout(HLY_Breadth);

        Lbl_Segments = new QLabel(bathymetry);
        Lbl_Segments->setObjectName(QString::fromUtf8("Lbl_Segments"));
        Lbl_Segments->setFont(font2);
        Lbl_Segments->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(Lbl_Segments);

        Tbl_Segments = new QTableWidget(bathymetry);
        if (Tbl_Segments->columnCount() < 2)
            Tbl_Segments->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Tbl_Segments->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Tbl_Segments->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        Tbl_Segments->setObjectName(QString::fromUtf8("Tbl_Segments"));
        Tbl_Segments->setFont(font1);
        Tbl_Segments->setToolTipDuration(10000);

        verticalLayout->addWidget(Tbl_Segments);

        HLY_AddSeg = new QHBoxLayout();
        HLY_AddSeg->setObjectName(QString::fromUtf8("HLY_AddSeg"));
        Btn_AddSeg = new QToolButton(bathymetry);
        Btn_AddSeg->setObjectName(QString::fromUtf8("Btn_AddSeg"));
        Btn_AddSeg->setToolTipDuration(10000);

        HLY_AddSeg->addWidget(Btn_AddSeg);

        Btn_RemSeg = new QToolButton(bathymetry);
        Btn_RemSeg->setObjectName(QString::fromUtf8("Btn_RemSeg"));
        Btn_RemSeg->setToolTipDuration(10000);

        HLY_AddSeg->addWidget(Btn_RemSeg);


        verticalLayout->addLayout(HLY_AddSeg);

        VSp = new QSpacerItem(20, 214, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(bathymetry);

        QMetaObject::connectSlotsByName(bathymetry);
    } // setupUi

    void retranslateUi(QFrame *bathymetry)
    {
        bathymetry->setWindowTitle(QCoreApplication::translate("bathymetry", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("bathymetry", "<html><head/><body><p><span style=\" font-weight:600;\">BATHYMETRY SETTINGS</span></p></body></html>", nullptr));
        Lbl_SelFiles->setText(QCoreApplication::translate("bathymetry", "<html><head/><body><p><span style=\" font-weight:600;\">Bathymetry and SW solution files</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        Btn_UploadFiles->setToolTip(QCoreApplication::translate("bathymetry", "Select the bathymetric files to be used", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadFiles->setText(QCoreApplication::translate("bathymetry", "Upload bathymetry", nullptr));
#if QT_CONFIG(tooltip)
        Btn_UploadSolution->setToolTip(QCoreApplication::translate("bathymetry", "Upload the shallow water solver solution files", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_UploadSolution->setText(QCoreApplication::translate("bathymetry", "Select solution", nullptr));
        CmB_FileType->setItemText(0, QCoreApplication::translate("bathymetry", "SimCenter format bathymetry", nullptr));
        CmB_FileType->setItemText(1, QCoreApplication::translate("bathymetry", "GeoClaw (Type I) bathymetry", nullptr));
        CmB_FileType->setItemText(2, QCoreApplication::translate("bathymetry", "GeoClaw (Type II) bathymetry", nullptr));
        CmB_FileType->setItemText(3, QCoreApplication::translate("bathymetry", "GeoClaw (Type III) bathymetry", nullptr));
        CmB_FileType->setItemText(4, QCoreApplication::translate("bathymetry", "AdCirc data", nullptr));

#if QT_CONFIG(tooltip)
        CmB_FileType->setToolTip(QCoreApplication::translate("bathymetry", "Select the format of the bathymetric files uploaded", nullptr));
#endif // QT_CONFIG(tooltip)
        CmB_SolFormat->setItemText(0, QCoreApplication::translate("bathymetry", "SimCenter solution format", nullptr));
        CmB_SolFormat->setItemText(1, QCoreApplication::translate("bathymetry", "GeoClaw solution format", nullptr));
        CmB_SolFormat->setItemText(2, QCoreApplication::translate("bathymetry", "AdCirc solution format", nullptr));

#if QT_CONFIG(tooltip)
        CmB_SolFormat->setToolTip(QCoreApplication::translate("bathymetry", "Select the format of the solutions files uploaded", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Gravity->setText(QCoreApplication::translate("bathymetry", "Gravity direction", nullptr));
        CmB_Grav01->setItemText(0, QCoreApplication::translate("bathymetry", "+", nullptr));
        CmB_Grav01->setItemText(1, QCoreApplication::translate("bathymetry", "-", nullptr));

#if QT_CONFIG(tooltip)
        CmB_Grav01->setToolTip(QCoreApplication::translate("bathymetry", "Select if gravity is along the positive / negative axis", nullptr));
#endif // QT_CONFIG(tooltip)
        CmB_Grav02->setItemText(0, QCoreApplication::translate("bathymetry", "X", nullptr));
        CmB_Grav02->setItemText(1, QCoreApplication::translate("bathymetry", "Y", nullptr));
        CmB_Grav02->setItemText(2, QCoreApplication::translate("bathymetry", "Z", nullptr));

#if QT_CONFIG(tooltip)
        CmB_Grav02->setToolTip(QCoreApplication::translate("bathymetry", "Select the axis along with gravity acts", nullptr));
#endif // QT_CONFIG(tooltip)
        CmB_Library->setItemText(0, QCoreApplication::translate("bathymetry", "To be coming soon", nullptr));

#if QT_CONFIG(tooltip)
        CmB_Library->setToolTip(QCoreApplication::translate("bathymetry", "Presently SimLibrary is not available", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Notice->setText(QCoreApplication::translate("bathymetry", "<html><head/><body><p>This option is not yet available. but watch out for updates that are coming soon.</p></body></html>", nullptr));
        CmB_FlumeGeoType->setItemText(0, QCoreApplication::translate("bathymetry", "Provide coordinates", nullptr));
        CmB_FlumeGeoType->setItemText(1, QCoreApplication::translate("bathymetry", "Use standard OSU Flume", nullptr));
        CmB_FlumeGeoType->setItemText(2, QCoreApplication::translate("bathymetry", "Geometry from mesh", nullptr));

#if QT_CONFIG(tooltip)
        CmB_FlumeGeoType->setToolTip(QCoreApplication::translate("bathymetry", "Select how flume geometry will be defined", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_TopViewH2->setText(QCoreApplication::translate("bathymetry", "<html><head/><body><p>Top view of flume</p></body></html>", nullptr));
        Lbl_TopView->setText(QCoreApplication::translate("bathymetry", "<html><head/><body><p><img src=\":/images/images/TopView_v2.png\" width=\"275\"></p></body></html>", nullptr));
        Lbl_Breadth->setText(QCoreApplication::translate("bathymetry", "Breadth of wave flume", nullptr));
#if QT_CONFIG(tooltip)
        DSpBx_Breadth->setToolTip(QCoreApplication::translate("bathymetry", "Enter the breadth of the wave flume", nullptr));
#endif // QT_CONFIG(tooltip)
        Lbl_Segments->setText(QCoreApplication::translate("bathymetry", "<html><head/><body><p>Segments along length </p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Tbl_Segments->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("bathymetry", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Tbl_Segments->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("bathymetry", "Z", nullptr));
#if QT_CONFIG(tooltip)
        Tbl_Segments->setToolTip(QCoreApplication::translate("bathymetry", "Table of segments along the length of the flume", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddSeg->setToolTip(QCoreApplication::translate("bathymetry", "Add segment along the length of the flume", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddSeg->setText(QCoreApplication::translate("bathymetry", "Add point", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemSeg->setToolTip(QCoreApplication::translate("bathymetry", "Remove segment along the length of the flume", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemSeg->setText(QCoreApplication::translate("bathymetry", "Remove point", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bathymetry: public Ui_bathymetry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATHYMETRY_H
