/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <myopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *FooterGroup;
    QLabel *BottomText;
    QLabel *NSFLogo;
    QLabel *SimCenterLogo;
    QGroupBox *DataGroup;
    MyOpenGLWidget *widget;
    QFrame *MainFrame;
    QTreeWidget *SimOptions;
    QLabel *DescriptionHeading;
    QLabel *DescriptionBox;
    QStackedWidget *stackedWidget;
    QWidget *StatusPage;
    QLabel *StatusPageLabel;
    QCheckBox *ProjCheckBox;
    QCheckBox *GeometryBox;
    QCheckBox *MaterialBox;
    QCheckBox *Meshox;
    QCheckBox *BoundaryBox;
    QCheckBox *InitialCondBox;
    QCheckBox *SolverBox;
    QCheckBox *BuildingBox;
    QWidget *ProjectPage;
    QLabel *ProjPageLabel;
    QLabel *WorkDirLabel;
    QLabel *ProjNameLabel;
    QPlainTextEdit *ProjNameTEdit;
    QLabel *ProjDescLabel;
    QPlainTextEdit *ProjDescTEdit;
    QPushButton *WorkDirBut;
    QComboBox *ProjSimType;
    QLabel *SimTypeLabel;
    QPushButton *ProjAccept;
    QPushButton *ProjCancel;
    QLabel *TurbTypeLabel;
    QComboBox *ProjTurbType;
    QWidget *GeoPage_A;
    QLabel *GeoAHeading;
    QLabel *GeoA_SWSolverLabel;
    QPushButton *GeoA_BathfileBut;
    QLabel *GeoA_BathfileLabel;
    QComboBox *GeoA_SWSolverOptions;
    QLabel *GeoA_SWSolLabel;
    QComboBox *GeoA_SWSolOptions;
    QLabel *GeoA_InterfaceLabel;
    QLabel *GeoA_BathfiletypeLabel;
    QComboBox *GeoA_BathfiletypeOptions;
    QTableWidget *GeoA_InterfaceTable;
    QPushButton *GeoA_Cancel;
    QPushButton *GeoA_Accept;
    QCheckBox *GeoA_InterfaceCheck;
    QPushButton *GeoA_InterfacefileBut;
    QToolButton *GeoA_RemPoint;
    QToolButton *GeoA_AddPoint;
    QWidget *GeoPage_B;
    QTableWidget *GeoB_InterfaceTable;
    QComboBox *GeoB_SimLibOptions;
    QLabel *GeoB_InterfaceLabel;
    QLabel *GeoBHeading;
    QLabel *GeoB_SimLibLabel;
    QPushButton *GeoB_Cancel;
    QPushButton *GeoB_Accept;
    QPushButton *GeoB_InterfacefileBut;
    QCheckBox *GeoB_InterfaceCheck;
    QToolButton *GeoB_RemPoint;
    QToolButton *GeoB_AddPoint;
    QWidget *GeoPage_C;
    QComboBox *GeoC_BathfiletypeOptions;
    QLabel *GeoCHeading;
    QLabel *GeoC_BathfiletypeLabel;
    QPushButton *GeoC_BathfileBut;
    QLabel *GeoC_BathfileLabel;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QWidget *GeoPage_D;
    QLabel *GeoCHeading_2;
    QLabel *FlumeBreadthPic;
    QLabel *FlumeLengthPic;
    QLabel *GeoC_BathfileLabel_2;
    QTextEdit *B1_TEdit;
    QLabel *B1_Label;
    QTextEdit *B1_TEdit_2;
    QLabel *B1_Label_2;
    QLabel *GeoC_BathfileLabel_3;
    QLabel *GeoC_BathfileLabel_4;
    QTableWidget *GeoB_InterfaceTable_2;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QToolButton *GeoB_RemPoint_2;
    QToolButton *GeoB_AddPoint_2;
    QWidget *GeoPage_E;
    QLabel *GeoEHeading;
    QLabel *GeoE_NoticeLabel;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QWidget *BuildingPage_A;
    QLabel *GeoEHeading_2;
    QLabel *GeoE_NoticeLabel_2;
    QPushButton *pushButton_25;
    QPushButton *pushButton_26;
    QWidget *BuildingsPage_B;
    QLabel *GeoEHeading_3;
    QLabel *GeoC_BathfileLabel_5;
    QTableWidget *GeoB_InterfaceTable_3;
    QPushButton *pushButton_29;
    QPushButton *pushButton_30;
    QToolButton *GeoB_RemPoint_3;
    QToolButton *GeoB_AddPoint_3;
    QWidget *MeshPage;
    QLabel *label_11;
    QLabel *GeoC_BathfileLabel_6;
    QSlider *horizontalSlider;
    QLabel *GeoC_BathfileLabel_7;
    QLabel *GeoC_BathfileLabel_8;
    QTableWidget *GeoB_InterfaceTable_4;
    QLabel *GeoC_BathfileLabel_9;
    QLabel *GeoC_BathfiletypeLabel_2;
    QComboBox *GeoC_BathfiletypeOptions_2;
    QPushButton *pushButton_31;
    QPushButton *pushButton_32;
    QToolButton *GeoB_RemPoint_4;
    QToolButton *GeoB_AddPoint_4;
    QWidget *MaterialsPage;
    QLabel *label_10;
    QGroupBox *groupBox;
    QLabel *B1_Label_3;
    QTextEdit *B1_TEdit_3;
    QLabel *B1_Label_4;
    QTextEdit *B1_TEdit_4;
    QGroupBox *groupBox_2;
    QLabel *B1_Label_5;
    QTextEdit *B1_TEdit_5;
    QLabel *B1_Label_6;
    QTextEdit *B1_TEdit_6;
    QTextEdit *B1_TEdit_7;
    QLabel *B1_Label_7;
    QPushButton *pushButton_33;
    QPushButton *pushButton_34;
    QWidget *InitialPage;
    QLabel *label_16;
    QGroupBox *groupBox_3;
    QLabel *B1_Label_8;
    QTextEdit *B1_TEdit_8;
    QLabel *B1_Label_9;
    QTextEdit *B1_TEdit_9;
    QTextEdit *B1_TEdit_10;
    QLabel *B1_Label_10;
    QGroupBox *groupBox_4;
    QLabel *B1_Label_11;
    QTextEdit *B1_TEdit_11;
    QGroupBox *groupBox_5;
    QLabel *B1_Label_12;
    QTextEdit *B1_TEdit_12;
    QPushButton *pushButton_35;
    QPushButton *pushButton_36;
    QTableWidget *GeoB_InterfaceTable_5;
    QToolButton *GeoB_AddPoint_5;
    QLabel *GeoC_BathfileLabel_10;
    QToolButton *GeoB_RemPoint_5;
    QWidget *BCPage;
    QLabel *label_12;
    QWidget *page;
    QPushButton *pushButton_39;
    QPushButton *pushButton_40;
    QLabel *label_17;
    QWidget *TurbulencePage;
    QLabel *label_13;
    QWidget *SolveBasicPage;
    QLabel *label_14;
    QWidget *SolveAdvPage;
    QLabel *label_15;
    QGroupBox *HeaderGroup;
    QLabel *HydroLogo;
    QLabel *ProjectName;
    QLabel *ProjectDesc;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(1523, 1074);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        FooterGroup = new QGroupBox(centralwidget);
        FooterGroup->setObjectName(QString::fromUtf8("FooterGroup"));
        FooterGroup->setGeometry(QRect(10, 940, 1501, 80));
        FooterGroup->setAutoFillBackground(true);
        FooterGroup->setAlignment(Qt::AlignCenter);
        BottomText = new QLabel(FooterGroup);
        BottomText->setObjectName(QString::fromUtf8("BottomText"));
        BottomText->setGeometry(QRect(330, 30, 741, 21));
        QFont font;
        font.setPointSize(14);
        BottomText->setFont(font);
        BottomText->setAlignment(Qt::AlignCenter);
        NSFLogo = new QLabel(FooterGroup);
        NSFLogo->setObjectName(QString::fromUtf8("NSFLogo"));
        NSFLogo->setGeometry(QRect(270, 10, 51, 51));
        SimCenterLogo = new QLabel(FooterGroup);
        SimCenterLogo->setObjectName(QString::fromUtf8("SimCenterLogo"));
        SimCenterLogo->setGeometry(QRect(1070, 10, 191, 61));
        DataGroup = new QGroupBox(centralwidget);
        DataGroup->setObjectName(QString::fromUtf8("DataGroup"));
        DataGroup->setGeometry(QRect(10, 99, 1501, 831));
        DataGroup->setAutoFillBackground(true);
        DataGroup->setAlignment(Qt::AlignCenter);
        widget = new MyOpenGLWidget(DataGroup);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(false);
        widget->setGeometry(QRect(690, 20, 791, 791));
        widget->setMouseTracking(true);
        widget->setFocusPolicy(Qt::ClickFocus);
        widget->setContextMenuPolicy(Qt::NoContextMenu);
        MainFrame = new QFrame(DataGroup);
        MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->setGeometry(QRect(20, 20, 321, 791));
        MainFrame->setFrameShape(QFrame::StyledPanel);
        MainFrame->setFrameShadow(QFrame::Raised);
        SimOptions = new QTreeWidget(MainFrame);
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font1);
        SimOptions->setHeaderItem(__qtreewidgetitem);
        new QTreeWidgetItem(SimOptions);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(SimOptions);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(SimOptions);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        SimOptions->setObjectName(QString::fromUtf8("SimOptions"));
        SimOptions->setGeometry(QRect(10, 10, 301, 331));
        SimOptions->setFont(font);
        SimOptions->setStyleSheet(QString::fromUtf8(""));
        SimOptions->setFrameShape(QFrame::Panel);
        SimOptions->setFrameShadow(QFrame::Plain);
        DescriptionHeading = new QLabel(MainFrame);
        DescriptionHeading->setObjectName(QString::fromUtf8("DescriptionHeading"));
        DescriptionHeading->setGeometry(QRect(10, 360, 256, 21));
        DescriptionHeading->setFont(font);
        DescriptionHeading->setTextFormat(Qt::RichText);
        DescriptionHeading->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        DescriptionHeading->setWordWrap(true);
        DescriptionBox = new QLabel(MainFrame);
        DescriptionBox->setObjectName(QString::fromUtf8("DescriptionBox"));
        DescriptionBox->setGeometry(QRect(10, 390, 291, 375));
        DescriptionBox->setFont(font);
        DescriptionBox->setTextFormat(Qt::RichText);
        DescriptionBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        DescriptionBox->setWordWrap(true);
        stackedWidget = new QStackedWidget(DataGroup);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(350, 20, 331, 791));
        stackedWidget->setFrameShape(QFrame::StyledPanel);
        stackedWidget->setFrameShadow(QFrame::Sunken);
        stackedWidget->setLineWidth(2);
        StatusPage = new QWidget();
        StatusPage->setObjectName(QString::fromUtf8("StatusPage"));
        StatusPageLabel = new QLabel(StatusPage);
        StatusPageLabel->setObjectName(QString::fromUtf8("StatusPageLabel"));
        StatusPageLabel->setGeometry(QRect(10, 10, 141, 16));
        StatusPageLabel->setFont(font);
        ProjCheckBox = new QCheckBox(StatusPage);
        ProjCheckBox->setObjectName(QString::fromUtf8("ProjCheckBox"));
        ProjCheckBox->setEnabled(true);
        ProjCheckBox->setGeometry(QRect(10, 50, 261, 20));
        ProjCheckBox->setFont(font);
        ProjCheckBox->setCheckable(false);
        GeometryBox = new QCheckBox(StatusPage);
        GeometryBox->setObjectName(QString::fromUtf8("GeometryBox"));
        GeometryBox->setEnabled(true);
        GeometryBox->setGeometry(QRect(10, 80, 261, 20));
        GeometryBox->setFont(font);
        GeometryBox->setCheckable(false);
        MaterialBox = new QCheckBox(StatusPage);
        MaterialBox->setObjectName(QString::fromUtf8("MaterialBox"));
        MaterialBox->setEnabled(true);
        MaterialBox->setGeometry(QRect(10, 170, 261, 20));
        MaterialBox->setFont(font);
        MaterialBox->setCheckable(false);
        Meshox = new QCheckBox(StatusPage);
        Meshox->setObjectName(QString::fromUtf8("Meshox"));
        Meshox->setEnabled(true);
        Meshox->setGeometry(QRect(10, 140, 261, 20));
        Meshox->setFont(font);
        Meshox->setCheckable(false);
        BoundaryBox = new QCheckBox(StatusPage);
        BoundaryBox->setObjectName(QString::fromUtf8("BoundaryBox"));
        BoundaryBox->setEnabled(true);
        BoundaryBox->setGeometry(QRect(10, 230, 261, 20));
        BoundaryBox->setFont(font);
        BoundaryBox->setCheckable(false);
        InitialCondBox = new QCheckBox(StatusPage);
        InitialCondBox->setObjectName(QString::fromUtf8("InitialCondBox"));
        InitialCondBox->setEnabled(true);
        InitialCondBox->setGeometry(QRect(10, 200, 261, 20));
        InitialCondBox->setFont(font);
        InitialCondBox->setCheckable(false);
        SolverBox = new QCheckBox(StatusPage);
        SolverBox->setObjectName(QString::fromUtf8("SolverBox"));
        SolverBox->setEnabled(true);
        SolverBox->setGeometry(QRect(10, 260, 261, 20));
        SolverBox->setFont(font);
        SolverBox->setCheckable(false);
        BuildingBox = new QCheckBox(StatusPage);
        BuildingBox->setObjectName(QString::fromUtf8("BuildingBox"));
        BuildingBox->setEnabled(true);
        BuildingBox->setGeometry(QRect(10, 110, 261, 20));
        BuildingBox->setFont(font);
        BuildingBox->setCheckable(false);
        stackedWidget->addWidget(StatusPage);
        ProjectPage = new QWidget();
        ProjectPage->setObjectName(QString::fromUtf8("ProjectPage"));
        ProjPageLabel = new QLabel(ProjectPage);
        ProjPageLabel->setObjectName(QString::fromUtf8("ProjPageLabel"));
        ProjPageLabel->setGeometry(QRect(10, 10, 141, 16));
        ProjPageLabel->setFont(font);
        WorkDirLabel = new QLabel(ProjectPage);
        WorkDirLabel->setObjectName(QString::fromUtf8("WorkDirLabel"));
        WorkDirLabel->setGeometry(QRect(10, 50, 256, 21));
        WorkDirLabel->setFont(font);
        WorkDirLabel->setFocusPolicy(Qt::ClickFocus);
        ProjNameLabel = new QLabel(ProjectPage);
        ProjNameLabel->setObjectName(QString::fromUtf8("ProjNameLabel"));
        ProjNameLabel->setGeometry(QRect(10, 160, 256, 21));
        ProjNameLabel->setFont(font);
        ProjNameTEdit = new QPlainTextEdit(ProjectPage);
        ProjNameTEdit->setObjectName(QString::fromUtf8("ProjNameTEdit"));
        ProjNameTEdit->setGeometry(QRect(10, 190, 311, 31));
        ProjNameTEdit->setFont(font);
        ProjNameTEdit->setTabChangesFocus(true);
        ProjDescLabel = new QLabel(ProjectPage);
        ProjDescLabel->setObjectName(QString::fromUtf8("ProjDescLabel"));
        ProjDescLabel->setGeometry(QRect(10, 230, 256, 21));
        ProjDescLabel->setFont(font);
        ProjDescTEdit = new QPlainTextEdit(ProjectPage);
        ProjDescTEdit->setObjectName(QString::fromUtf8("ProjDescTEdit"));
        ProjDescTEdit->setGeometry(QRect(10, 260, 311, 251));
        ProjDescTEdit->setFont(font);
        ProjDescTEdit->setTabChangesFocus(true);
        WorkDirBut = new QPushButton(ProjectPage);
        WorkDirBut->setObjectName(QString::fromUtf8("WorkDirBut"));
        WorkDirBut->setGeometry(QRect(5, 80, 321, 71));
        ProjSimType = new QComboBox(ProjectPage);
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->addItem(QString());
        ProjSimType->setObjectName(QString::fromUtf8("ProjSimType"));
        ProjSimType->setGeometry(QRect(5, 550, 321, 32));
        SimTypeLabel = new QLabel(ProjectPage);
        SimTypeLabel->setObjectName(QString::fromUtf8("SimTypeLabel"));
        SimTypeLabel->setGeometry(QRect(10, 520, 256, 21));
        SimTypeLabel->setFont(font);
        ProjAccept = new QPushButton(ProjectPage);
        ProjAccept->setObjectName(QString::fromUtf8("ProjAccept"));
        ProjAccept->setGeometry(QRect(301, 2, 27, 27));
        ProjAccept->setAutoFillBackground(false);
        ProjAccept->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        ProjAccept->setText(QString::fromUtf8(""));
        ProjAccept->setIconSize(QSize(28, 28));
        ProjAccept->setFlat(false);
        ProjCancel = new QPushButton(ProjectPage);
        ProjCancel->setObjectName(QString::fromUtf8("ProjCancel"));
        ProjCancel->setGeometry(QRect(272, 2, 27, 27));
        ProjCancel->setAutoFillBackground(false);
        ProjCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        ProjCancel->setText(QString::fromUtf8(""));
        ProjCancel->setIconSize(QSize(28, 28));
        ProjCancel->setFlat(false);
        TurbTypeLabel = new QLabel(ProjectPage);
        TurbTypeLabel->setObjectName(QString::fromUtf8("TurbTypeLabel"));
        TurbTypeLabel->setGeometry(QRect(10, 590, 256, 21));
        TurbTypeLabel->setFont(font);
        ProjTurbType = new QComboBox(ProjectPage);
        ProjTurbType->addItem(QString());
        ProjTurbType->addItem(QString());
        ProjTurbType->addItem(QString());
        ProjTurbType->addItem(QString());
        ProjTurbType->setObjectName(QString::fromUtf8("ProjTurbType"));
        ProjTurbType->setGeometry(QRect(5, 620, 321, 32));
        stackedWidget->addWidget(ProjectPage);
        GeoPage_A = new QWidget();
        GeoPage_A->setObjectName(QString::fromUtf8("GeoPage_A"));
        GeoAHeading = new QLabel(GeoPage_A);
        GeoAHeading->setObjectName(QString::fromUtf8("GeoAHeading"));
        GeoAHeading->setGeometry(QRect(10, 10, 141, 16));
        GeoAHeading->setFont(font);
        GeoA_SWSolverLabel = new QLabel(GeoPage_A);
        GeoA_SWSolverLabel->setObjectName(QString::fromUtf8("GeoA_SWSolverLabel"));
        GeoA_SWSolverLabel->setGeometry(QRect(10, 230, 256, 21));
        GeoA_SWSolverLabel->setFont(font);
        GeoA_BathfileBut = new QPushButton(GeoPage_A);
        GeoA_BathfileBut->setObjectName(QString::fromUtf8("GeoA_BathfileBut"));
        GeoA_BathfileBut->setGeometry(QRect(5, 80, 321, 71));
        GeoA_BathfileLabel = new QLabel(GeoPage_A);
        GeoA_BathfileLabel->setObjectName(QString::fromUtf8("GeoA_BathfileLabel"));
        GeoA_BathfileLabel->setGeometry(QRect(10, 50, 256, 21));
        GeoA_BathfileLabel->setFont(font);
        GeoA_BathfileLabel->setFocusPolicy(Qt::ClickFocus);
        GeoA_SWSolverOptions = new QComboBox(GeoPage_A);
        GeoA_SWSolverOptions->addItem(QString());
        GeoA_SWSolverOptions->addItem(QString());
        GeoA_SWSolverOptions->addItem(QString());
        GeoA_SWSolverOptions->setObjectName(QString::fromUtf8("GeoA_SWSolverOptions"));
        GeoA_SWSolverOptions->setGeometry(QRect(5, 260, 321, 32));
        GeoA_SWSolLabel = new QLabel(GeoPage_A);
        GeoA_SWSolLabel->setObjectName(QString::fromUtf8("GeoA_SWSolLabel"));
        GeoA_SWSolLabel->setGeometry(QRect(10, 300, 256, 21));
        GeoA_SWSolLabel->setFont(font);
        GeoA_SWSolOptions = new QComboBox(GeoPage_A);
        GeoA_SWSolOptions->addItem(QString());
        GeoA_SWSolOptions->addItem(QString());
        GeoA_SWSolOptions->addItem(QString());
        GeoA_SWSolOptions->addItem(QString());
        GeoA_SWSolOptions->setObjectName(QString::fromUtf8("GeoA_SWSolOptions"));
        GeoA_SWSolOptions->setGeometry(QRect(5, 330, 321, 32));
        GeoA_InterfaceLabel = new QLabel(GeoPage_A);
        GeoA_InterfaceLabel->setObjectName(QString::fromUtf8("GeoA_InterfaceLabel"));
        GeoA_InterfaceLabel->setGeometry(QRect(10, 370, 256, 21));
        GeoA_InterfaceLabel->setFont(font);
        GeoA_BathfiletypeLabel = new QLabel(GeoPage_A);
        GeoA_BathfiletypeLabel->setObjectName(QString::fromUtf8("GeoA_BathfiletypeLabel"));
        GeoA_BathfiletypeLabel->setGeometry(QRect(10, 160, 256, 21));
        GeoA_BathfiletypeLabel->setFont(font);
        GeoA_BathfiletypeOptions = new QComboBox(GeoPage_A);
        GeoA_BathfiletypeOptions->addItem(QString());
        GeoA_BathfiletypeOptions->addItem(QString());
        GeoA_BathfiletypeOptions->addItem(QString());
        GeoA_BathfiletypeOptions->addItem(QString());
        GeoA_BathfiletypeOptions->addItem(QString());
        GeoA_BathfiletypeOptions->setObjectName(QString::fromUtf8("GeoA_BathfiletypeOptions"));
        GeoA_BathfiletypeOptions->setGeometry(QRect(5, 190, 321, 32));
        GeoA_InterfaceTable = new QTableWidget(GeoPage_A);
        GeoA_InterfaceTable->setObjectName(QString::fromUtf8("GeoA_InterfaceTable"));
        GeoA_InterfaceTable->setGeometry(QRect(10, 435, 311, 281));
        GeoA_Cancel = new QPushButton(GeoPage_A);
        GeoA_Cancel->setObjectName(QString::fromUtf8("GeoA_Cancel"));
        GeoA_Cancel->setGeometry(QRect(272, 2, 27, 27));
        GeoA_Cancel->setAutoFillBackground(false);
        GeoA_Cancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        GeoA_Cancel->setText(QString::fromUtf8(""));
        GeoA_Cancel->setIconSize(QSize(28, 28));
        GeoA_Cancel->setFlat(false);
        GeoA_Accept = new QPushButton(GeoPage_A);
        GeoA_Accept->setObjectName(QString::fromUtf8("GeoA_Accept"));
        GeoA_Accept->setGeometry(QRect(301, 2, 27, 27));
        GeoA_Accept->setAutoFillBackground(false);
        GeoA_Accept->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        GeoA_Accept->setText(QString::fromUtf8(""));
        GeoA_Accept->setIconSize(QSize(28, 28));
        GeoA_Accept->setFlat(false);
        GeoA_InterfaceCheck = new QCheckBox(GeoPage_A);
        GeoA_InterfaceCheck->setObjectName(QString::fromUtf8("GeoA_InterfaceCheck"));
        GeoA_InterfaceCheck->setEnabled(true);
        GeoA_InterfaceCheck->setGeometry(QRect(10, 400, 261, 20));
        GeoA_InterfaceCheck->setFont(font);
        GeoA_InterfaceCheck->setCheckable(true);
        GeoA_InterfacefileBut = new QPushButton(GeoPage_A);
        GeoA_InterfacefileBut->setObjectName(QString::fromUtf8("GeoA_InterfacefileBut"));
        GeoA_InterfacefileBut->setGeometry(QRect(5, 440, 271, 71));
        GeoA_RemPoint = new QToolButton(GeoPage_A);
        GeoA_RemPoint->setObjectName(QString::fromUtf8("GeoA_RemPoint"));
        GeoA_RemPoint->setGeometry(QRect(180, 730, 81, 21));
        GeoA_AddPoint = new QToolButton(GeoPage_A);
        GeoA_AddPoint->setObjectName(QString::fromUtf8("GeoA_AddPoint"));
        GeoA_AddPoint->setGeometry(QRect(80, 730, 81, 21));
        stackedWidget->addWidget(GeoPage_A);
        GeoA_InterfacefileBut->raise();
        GeoA_InterfaceTable->raise();
        GeoAHeading->raise();
        GeoA_SWSolverLabel->raise();
        GeoA_BathfileBut->raise();
        GeoA_BathfileLabel->raise();
        GeoA_SWSolverOptions->raise();
        GeoA_SWSolLabel->raise();
        GeoA_SWSolOptions->raise();
        GeoA_InterfaceLabel->raise();
        GeoA_BathfiletypeLabel->raise();
        GeoA_BathfiletypeOptions->raise();
        GeoA_Cancel->raise();
        GeoA_Accept->raise();
        GeoA_InterfaceCheck->raise();
        GeoA_RemPoint->raise();
        GeoA_AddPoint->raise();
        GeoPage_B = new QWidget();
        GeoPage_B->setObjectName(QString::fromUtf8("GeoPage_B"));
        GeoB_InterfaceTable = new QTableWidget(GeoPage_B);
        GeoB_InterfaceTable->setObjectName(QString::fromUtf8("GeoB_InterfaceTable"));
        GeoB_InterfaceTable->setGeometry(QRect(10, 180, 311, 280));
        GeoB_SimLibOptions = new QComboBox(GeoPage_B);
        GeoB_SimLibOptions->addItem(QString());
        GeoB_SimLibOptions->addItem(QString());
        GeoB_SimLibOptions->addItem(QString());
        GeoB_SimLibOptions->addItem(QString());
        GeoB_SimLibOptions->setObjectName(QString::fromUtf8("GeoB_SimLibOptions"));
        GeoB_SimLibOptions->setGeometry(QRect(5, 80, 321, 32));
        GeoB_InterfaceLabel = new QLabel(GeoPage_B);
        GeoB_InterfaceLabel->setObjectName(QString::fromUtf8("GeoB_InterfaceLabel"));
        GeoB_InterfaceLabel->setGeometry(QRect(10, 120, 256, 21));
        GeoB_InterfaceLabel->setFont(font);
        GeoBHeading = new QLabel(GeoPage_B);
        GeoBHeading->setObjectName(QString::fromUtf8("GeoBHeading"));
        GeoBHeading->setGeometry(QRect(10, 10, 141, 16));
        GeoBHeading->setFont(font);
        GeoB_SimLibLabel = new QLabel(GeoPage_B);
        GeoB_SimLibLabel->setObjectName(QString::fromUtf8("GeoB_SimLibLabel"));
        GeoB_SimLibLabel->setGeometry(QRect(10, 50, 256, 21));
        GeoB_SimLibLabel->setFont(font);
        GeoB_Cancel = new QPushButton(GeoPage_B);
        GeoB_Cancel->setObjectName(QString::fromUtf8("GeoB_Cancel"));
        GeoB_Cancel->setGeometry(QRect(272, 2, 27, 27));
        GeoB_Cancel->setAutoFillBackground(false);
        GeoB_Cancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        GeoB_Cancel->setText(QString::fromUtf8(""));
        GeoB_Cancel->setIconSize(QSize(28, 28));
        GeoB_Cancel->setFlat(false);
        GeoB_Accept = new QPushButton(GeoPage_B);
        GeoB_Accept->setObjectName(QString::fromUtf8("GeoB_Accept"));
        GeoB_Accept->setGeometry(QRect(301, 2, 27, 27));
        GeoB_Accept->setAutoFillBackground(false);
        GeoB_Accept->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        GeoB_Accept->setText(QString::fromUtf8(""));
        GeoB_Accept->setIconSize(QSize(28, 28));
        GeoB_Accept->setFlat(false);
        GeoB_InterfacefileBut = new QPushButton(GeoPage_B);
        GeoB_InterfacefileBut->setObjectName(QString::fromUtf8("GeoB_InterfacefileBut"));
        GeoB_InterfacefileBut->setGeometry(QRect(5, 175, 271, 71));
        GeoB_InterfaceCheck = new QCheckBox(GeoPage_B);
        GeoB_InterfaceCheck->setObjectName(QString::fromUtf8("GeoB_InterfaceCheck"));
        GeoB_InterfaceCheck->setEnabled(true);
        GeoB_InterfaceCheck->setGeometry(QRect(10, 150, 261, 20));
        GeoB_InterfaceCheck->setFont(font);
        GeoB_InterfaceCheck->setCheckable(true);
        GeoB_RemPoint = new QToolButton(GeoPage_B);
        GeoB_RemPoint->setObjectName(QString::fromUtf8("GeoB_RemPoint"));
        GeoB_RemPoint->setGeometry(QRect(170, 480, 81, 21));
        GeoB_AddPoint = new QToolButton(GeoPage_B);
        GeoB_AddPoint->setObjectName(QString::fromUtf8("GeoB_AddPoint"));
        GeoB_AddPoint->setGeometry(QRect(70, 480, 81, 21));
        stackedWidget->addWidget(GeoPage_B);
        GeoB_InterfacefileBut->raise();
        GeoB_InterfaceTable->raise();
        GeoB_SimLibOptions->raise();
        GeoB_InterfaceLabel->raise();
        GeoBHeading->raise();
        GeoB_SimLibLabel->raise();
        GeoB_Cancel->raise();
        GeoB_Accept->raise();
        GeoB_InterfaceCheck->raise();
        GeoB_RemPoint->raise();
        GeoB_AddPoint->raise();
        GeoPage_C = new QWidget();
        GeoPage_C->setObjectName(QString::fromUtf8("GeoPage_C"));
        GeoC_BathfiletypeOptions = new QComboBox(GeoPage_C);
        GeoC_BathfiletypeOptions->addItem(QString());
        GeoC_BathfiletypeOptions->addItem(QString());
        GeoC_BathfiletypeOptions->addItem(QString());
        GeoC_BathfiletypeOptions->addItem(QString());
        GeoC_BathfiletypeOptions->addItem(QString());
        GeoC_BathfiletypeOptions->addItem(QString());
        GeoC_BathfiletypeOptions->setObjectName(QString::fromUtf8("GeoC_BathfiletypeOptions"));
        GeoC_BathfiletypeOptions->setGeometry(QRect(5, 190, 321, 32));
        GeoCHeading = new QLabel(GeoPage_C);
        GeoCHeading->setObjectName(QString::fromUtf8("GeoCHeading"));
        GeoCHeading->setGeometry(QRect(10, 10, 141, 16));
        GeoCHeading->setFont(font);
        GeoC_BathfiletypeLabel = new QLabel(GeoPage_C);
        GeoC_BathfiletypeLabel->setObjectName(QString::fromUtf8("GeoC_BathfiletypeLabel"));
        GeoC_BathfiletypeLabel->setGeometry(QRect(10, 160, 256, 21));
        GeoC_BathfiletypeLabel->setFont(font);
        GeoC_BathfileBut = new QPushButton(GeoPage_C);
        GeoC_BathfileBut->setObjectName(QString::fromUtf8("GeoC_BathfileBut"));
        GeoC_BathfileBut->setGeometry(QRect(5, 80, 321, 71));
        GeoC_BathfileLabel = new QLabel(GeoPage_C);
        GeoC_BathfileLabel->setObjectName(QString::fromUtf8("GeoC_BathfileLabel"));
        GeoC_BathfileLabel->setGeometry(QRect(10, 50, 256, 21));
        GeoC_BathfileLabel->setFont(font);
        GeoC_BathfileLabel->setFocusPolicy(Qt::ClickFocus);
        pushButton_19 = new QPushButton(GeoPage_C);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(272, 2, 27, 27));
        pushButton_19->setAutoFillBackground(false);
        pushButton_19->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_19->setText(QString::fromUtf8(""));
        pushButton_19->setIconSize(QSize(28, 28));
        pushButton_19->setFlat(false);
        pushButton_20 = new QPushButton(GeoPage_C);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(301, 2, 27, 27));
        pushButton_20->setAutoFillBackground(false);
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_20->setText(QString::fromUtf8(""));
        pushButton_20->setIconSize(QSize(28, 28));
        pushButton_20->setFlat(false);
        stackedWidget->addWidget(GeoPage_C);
        GeoPage_D = new QWidget();
        GeoPage_D->setObjectName(QString::fromUtf8("GeoPage_D"));
        GeoCHeading_2 = new QLabel(GeoPage_D);
        GeoCHeading_2->setObjectName(QString::fromUtf8("GeoCHeading_2"));
        GeoCHeading_2->setGeometry(QRect(10, 10, 141, 16));
        GeoCHeading_2->setFont(font);
        FlumeBreadthPic = new QLabel(GeoPage_D);
        FlumeBreadthPic->setObjectName(QString::fromUtf8("FlumeBreadthPic"));
        FlumeBreadthPic->setGeometry(QRect(10, 275, 311, 94));
        QFont font2;
        font2.setPointSize(48);
        FlumeBreadthPic->setFont(font2);
        FlumeBreadthPic->setScaledContents(true);
        FlumeBreadthPic->setAlignment(Qt::AlignCenter);
        FlumeBreadthPic->setWordWrap(true);
        FlumeLengthPic = new QLabel(GeoPage_D);
        FlumeLengthPic->setObjectName(QString::fromUtf8("FlumeLengthPic"));
        FlumeLengthPic->setGeometry(QRect(10, 80, 311, 110));
        FlumeLengthPic->setFont(font2);
        FlumeLengthPic->setScaledContents(true);
        FlumeLengthPic->setAlignment(Qt::AlignCenter);
        FlumeLengthPic->setWordWrap(true);
        GeoC_BathfileLabel_2 = new QLabel(GeoPage_D);
        GeoC_BathfileLabel_2->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_2"));
        GeoC_BathfileLabel_2->setGeometry(QRect(10, 50, 256, 21));
        GeoC_BathfileLabel_2->setFont(font);
        GeoC_BathfileLabel_2->setFocusPolicy(Qt::ClickFocus);
        B1_TEdit = new QTextEdit(GeoPage_D);
        B1_TEdit->setObjectName(QString::fromUtf8("B1_TEdit"));
        B1_TEdit->setGeometry(QRect(160, 200, 104, 32));
        B1_TEdit->setFont(font);
        B1_TEdit->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit->setTabChangesFocus(true);
        B1_TEdit->setAcceptRichText(false);
        B1_Label = new QLabel(GeoPage_D);
        B1_Label->setObjectName(QString::fromUtf8("B1_Label"));
        B1_Label->setGeometry(QRect(10, 208, 151, 16));
        B1_Label->setFont(font);
        B1_Label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label->setWordWrap(true);
        B1_TEdit_2 = new QTextEdit(GeoPage_D);
        B1_TEdit_2->setObjectName(QString::fromUtf8("B1_TEdit_2"));
        B1_TEdit_2->setGeometry(QRect(160, 370, 104, 32));
        B1_TEdit_2->setFont(font);
        B1_TEdit_2->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_2->setTabChangesFocus(true);
        B1_TEdit_2->setAcceptRichText(false);
        B1_Label_2 = new QLabel(GeoPage_D);
        B1_Label_2->setObjectName(QString::fromUtf8("B1_Label_2"));
        B1_Label_2->setGeometry(QRect(10, 378, 151, 16));
        B1_Label_2->setFont(font);
        B1_Label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_2->setWordWrap(true);
        GeoC_BathfileLabel_3 = new QLabel(GeoPage_D);
        GeoC_BathfileLabel_3->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_3"));
        GeoC_BathfileLabel_3->setGeometry(QRect(10, 250, 256, 21));
        GeoC_BathfileLabel_3->setFont(font);
        GeoC_BathfileLabel_3->setFocusPolicy(Qt::ClickFocus);
        GeoC_BathfileLabel_4 = new QLabel(GeoPage_D);
        GeoC_BathfileLabel_4->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_4"));
        GeoC_BathfileLabel_4->setGeometry(QRect(10, 430, 151, 21));
        GeoC_BathfileLabel_4->setFont(font);
        GeoC_BathfileLabel_4->setFocusPolicy(Qt::ClickFocus);
        GeoB_InterfaceTable_2 = new QTableWidget(GeoPage_D);
        GeoB_InterfaceTable_2->setObjectName(QString::fromUtf8("GeoB_InterfaceTable_2"));
        GeoB_InterfaceTable_2->setGeometry(QRect(10, 460, 311, 241));
        pushButton_21 = new QPushButton(GeoPage_D);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setGeometry(QRect(272, 2, 27, 27));
        pushButton_21->setAutoFillBackground(false);
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_21->setText(QString::fromUtf8(""));
        pushButton_21->setIconSize(QSize(28, 28));
        pushButton_21->setFlat(false);
        pushButton_22 = new QPushButton(GeoPage_D);
        pushButton_22->setObjectName(QString::fromUtf8("pushButton_22"));
        pushButton_22->setGeometry(QRect(301, 2, 27, 27));
        pushButton_22->setAutoFillBackground(false);
        pushButton_22->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_22->setText(QString::fromUtf8(""));
        pushButton_22->setIconSize(QSize(28, 28));
        pushButton_22->setFlat(false);
        GeoB_RemPoint_2 = new QToolButton(GeoPage_D);
        GeoB_RemPoint_2->setObjectName(QString::fromUtf8("GeoB_RemPoint_2"));
        GeoB_RemPoint_2->setGeometry(QRect(180, 720, 91, 21));
        GeoB_AddPoint_2 = new QToolButton(GeoPage_D);
        GeoB_AddPoint_2->setObjectName(QString::fromUtf8("GeoB_AddPoint_2"));
        GeoB_AddPoint_2->setGeometry(QRect(70, 720, 91, 21));
        stackedWidget->addWidget(GeoPage_D);
        GeoPage_E = new QWidget();
        GeoPage_E->setObjectName(QString::fromUtf8("GeoPage_E"));
        GeoEHeading = new QLabel(GeoPage_E);
        GeoEHeading->setObjectName(QString::fromUtf8("GeoEHeading"));
        GeoEHeading->setGeometry(QRect(10, 10, 141, 16));
        GeoEHeading->setFont(font);
        GeoE_NoticeLabel = new QLabel(GeoPage_E);
        GeoE_NoticeLabel->setObjectName(QString::fromUtf8("GeoE_NoticeLabel"));
        GeoE_NoticeLabel->setGeometry(QRect(10, 50, 311, 161));
        GeoE_NoticeLabel->setFont(font);
        GeoE_NoticeLabel->setFocusPolicy(Qt::ClickFocus);
        GeoE_NoticeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        GeoE_NoticeLabel->setWordWrap(true);
        pushButton_23 = new QPushButton(GeoPage_E);
        pushButton_23->setObjectName(QString::fromUtf8("pushButton_23"));
        pushButton_23->setGeometry(QRect(272, 2, 27, 27));
        pushButton_23->setAutoFillBackground(false);
        pushButton_23->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_23->setText(QString::fromUtf8(""));
        pushButton_23->setIconSize(QSize(28, 28));
        pushButton_23->setFlat(false);
        pushButton_24 = new QPushButton(GeoPage_E);
        pushButton_24->setObjectName(QString::fromUtf8("pushButton_24"));
        pushButton_24->setGeometry(QRect(301, 2, 27, 27));
        pushButton_24->setAutoFillBackground(false);
        pushButton_24->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_24->setText(QString::fromUtf8(""));
        pushButton_24->setIconSize(QSize(28, 28));
        pushButton_24->setFlat(false);
        stackedWidget->addWidget(GeoPage_E);
        BuildingPage_A = new QWidget();
        BuildingPage_A->setObjectName(QString::fromUtf8("BuildingPage_A"));
        GeoEHeading_2 = new QLabel(BuildingPage_A);
        GeoEHeading_2->setObjectName(QString::fromUtf8("GeoEHeading_2"));
        GeoEHeading_2->setGeometry(QRect(10, 10, 141, 16));
        GeoEHeading_2->setFont(font);
        GeoE_NoticeLabel_2 = new QLabel(BuildingPage_A);
        GeoE_NoticeLabel_2->setObjectName(QString::fromUtf8("GeoE_NoticeLabel_2"));
        GeoE_NoticeLabel_2->setGeometry(QRect(10, 50, 311, 161));
        GeoE_NoticeLabel_2->setFont(font);
        GeoE_NoticeLabel_2->setFocusPolicy(Qt::ClickFocus);
        GeoE_NoticeLabel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        GeoE_NoticeLabel_2->setWordWrap(true);
        pushButton_25 = new QPushButton(BuildingPage_A);
        pushButton_25->setObjectName(QString::fromUtf8("pushButton_25"));
        pushButton_25->setGeometry(QRect(272, 2, 27, 27));
        pushButton_25->setAutoFillBackground(false);
        pushButton_25->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_25->setText(QString::fromUtf8(""));
        pushButton_25->setIconSize(QSize(28, 28));
        pushButton_25->setFlat(false);
        pushButton_26 = new QPushButton(BuildingPage_A);
        pushButton_26->setObjectName(QString::fromUtf8("pushButton_26"));
        pushButton_26->setGeometry(QRect(301, 2, 27, 27));
        pushButton_26->setAutoFillBackground(false);
        pushButton_26->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_26->setText(QString::fromUtf8(""));
        pushButton_26->setIconSize(QSize(28, 28));
        pushButton_26->setFlat(false);
        stackedWidget->addWidget(BuildingPage_A);
        BuildingsPage_B = new QWidget();
        BuildingsPage_B->setObjectName(QString::fromUtf8("BuildingsPage_B"));
        GeoEHeading_3 = new QLabel(BuildingsPage_B);
        GeoEHeading_3->setObjectName(QString::fromUtf8("GeoEHeading_3"));
        GeoEHeading_3->setGeometry(QRect(10, 10, 141, 16));
        GeoEHeading_3->setFont(font);
        GeoC_BathfileLabel_5 = new QLabel(BuildingsPage_B);
        GeoC_BathfileLabel_5->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_5"));
        GeoC_BathfileLabel_5->setGeometry(QRect(10, 50, 151, 21));
        GeoC_BathfileLabel_5->setFont(font);
        GeoC_BathfileLabel_5->setFocusPolicy(Qt::ClickFocus);
        GeoB_InterfaceTable_3 = new QTableWidget(BuildingsPage_B);
        GeoB_InterfaceTable_3->setObjectName(QString::fromUtf8("GeoB_InterfaceTable_3"));
        GeoB_InterfaceTable_3->setGeometry(QRect(10, 80, 311, 331));
        GeoB_InterfaceTable_3->setFont(font);
        pushButton_29 = new QPushButton(BuildingsPage_B);
        pushButton_29->setObjectName(QString::fromUtf8("pushButton_29"));
        pushButton_29->setGeometry(QRect(272, 2, 27, 27));
        pushButton_29->setAutoFillBackground(false);
        pushButton_29->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_29->setText(QString::fromUtf8(""));
        pushButton_29->setIconSize(QSize(28, 28));
        pushButton_29->setFlat(false);
        pushButton_30 = new QPushButton(BuildingsPage_B);
        pushButton_30->setObjectName(QString::fromUtf8("pushButton_30"));
        pushButton_30->setGeometry(QRect(301, 2, 27, 27));
        pushButton_30->setAutoFillBackground(false);
        pushButton_30->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_30->setText(QString::fromUtf8(""));
        pushButton_30->setIconSize(QSize(28, 28));
        pushButton_30->setFlat(false);
        GeoB_RemPoint_3 = new QToolButton(BuildingsPage_B);
        GeoB_RemPoint_3->setObjectName(QString::fromUtf8("GeoB_RemPoint_3"));
        GeoB_RemPoint_3->setGeometry(QRect(180, 430, 91, 21));
        GeoB_AddPoint_3 = new QToolButton(BuildingsPage_B);
        GeoB_AddPoint_3->setObjectName(QString::fromUtf8("GeoB_AddPoint_3"));
        GeoB_AddPoint_3->setGeometry(QRect(70, 430, 91, 21));
        stackedWidget->addWidget(BuildingsPage_B);
        MeshPage = new QWidget();
        MeshPage->setObjectName(QString::fromUtf8("MeshPage"));
        label_11 = new QLabel(MeshPage);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 10, 141, 16));
        label_11->setFont(font);
        GeoC_BathfileLabel_6 = new QLabel(MeshPage);
        GeoC_BathfileLabel_6->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_6"));
        GeoC_BathfileLabel_6->setGeometry(QRect(10, 120, 151, 21));
        GeoC_BathfileLabel_6->setFont(font);
        GeoC_BathfileLabel_6->setFocusPolicy(Qt::ClickFocus);
        horizontalSlider = new QSlider(MeshPage);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 150, 311, 22));
        horizontalSlider->setMouseTracking(true);
        horizontalSlider->setFocusPolicy(Qt::WheelFocus);
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
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
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(5);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(1);
        GeoC_BathfileLabel_7 = new QLabel(MeshPage);
        GeoC_BathfileLabel_7->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_7"));
        GeoC_BathfileLabel_7->setGeometry(QRect(0, 170, 51, 16));
        GeoC_BathfileLabel_7->setFont(font);
        GeoC_BathfileLabel_7->setFocusPolicy(Qt::ClickFocus);
        GeoC_BathfileLabel_7->setAlignment(Qt::AlignCenter);
        GeoC_BathfileLabel_8 = new QLabel(MeshPage);
        GeoC_BathfileLabel_8->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_8"));
        GeoC_BathfileLabel_8->setGeometry(QRect(260, 170, 61, 16));
        GeoC_BathfileLabel_8->setFont(font);
        GeoC_BathfileLabel_8->setFocusPolicy(Qt::ClickFocus);
        GeoC_BathfileLabel_8->setAlignment(Qt::AlignCenter);
        GeoB_InterfaceTable_4 = new QTableWidget(MeshPage);
        if (GeoB_InterfaceTable_4->columnCount() < 3)
            GeoB_InterfaceTable_4->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        GeoB_InterfaceTable_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        GeoB_InterfaceTable_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        GeoB_InterfaceTable_4->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        GeoB_InterfaceTable_4->setObjectName(QString::fromUtf8("GeoB_InterfaceTable_4"));
        GeoB_InterfaceTable_4->setGeometry(QRect(10, 240, 311, 331));
        GeoB_InterfaceTable_4->setAlternatingRowColors(true);
        GeoC_BathfileLabel_9 = new QLabel(MeshPage);
        GeoC_BathfileLabel_9->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_9"));
        GeoC_BathfileLabel_9->setGeometry(QRect(10, 210, 151, 21));
        GeoC_BathfileLabel_9->setFont(font);
        GeoC_BathfileLabel_9->setFocusPolicy(Qt::ClickFocus);
        GeoC_BathfiletypeLabel_2 = new QLabel(MeshPage);
        GeoC_BathfiletypeLabel_2->setObjectName(QString::fromUtf8("GeoC_BathfiletypeLabel_2"));
        GeoC_BathfiletypeLabel_2->setGeometry(QRect(10, 50, 256, 21));
        GeoC_BathfiletypeLabel_2->setFont(font);
        GeoC_BathfiletypeOptions_2 = new QComboBox(MeshPage);
        GeoC_BathfiletypeOptions_2->addItem(QString());
        GeoC_BathfiletypeOptions_2->addItem(QString());
        GeoC_BathfiletypeOptions_2->addItem(QString());
        GeoC_BathfiletypeOptions_2->addItem(QString());
        GeoC_BathfiletypeOptions_2->setObjectName(QString::fromUtf8("GeoC_BathfiletypeOptions_2"));
        GeoC_BathfiletypeOptions_2->setGeometry(QRect(5, 80, 321, 32));
        pushButton_31 = new QPushButton(MeshPage);
        pushButton_31->setObjectName(QString::fromUtf8("pushButton_31"));
        pushButton_31->setGeometry(QRect(301, 2, 27, 27));
        pushButton_31->setAutoFillBackground(false);
        pushButton_31->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_31->setText(QString::fromUtf8(""));
        pushButton_31->setIconSize(QSize(28, 28));
        pushButton_31->setFlat(false);
        pushButton_32 = new QPushButton(MeshPage);
        pushButton_32->setObjectName(QString::fromUtf8("pushButton_32"));
        pushButton_32->setGeometry(QRect(272, 2, 27, 27));
        pushButton_32->setAutoFillBackground(false);
        pushButton_32->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_32->setText(QString::fromUtf8(""));
        pushButton_32->setIconSize(QSize(28, 28));
        pushButton_32->setFlat(false);
        GeoB_RemPoint_4 = new QToolButton(MeshPage);
        GeoB_RemPoint_4->setObjectName(QString::fromUtf8("GeoB_RemPoint_4"));
        GeoB_RemPoint_4->setGeometry(QRect(180, 590, 91, 21));
        GeoB_AddPoint_4 = new QToolButton(MeshPage);
        GeoB_AddPoint_4->setObjectName(QString::fromUtf8("GeoB_AddPoint_4"));
        GeoB_AddPoint_4->setGeometry(QRect(70, 590, 91, 21));
        stackedWidget->addWidget(MeshPage);
        MaterialsPage = new QWidget();
        MaterialsPage->setObjectName(QString::fromUtf8("MaterialsPage"));
        label_10 = new QLabel(MaterialsPage);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 10, 141, 16));
        label_10->setFont(font);
        groupBox = new QGroupBox(MaterialsPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 50, 311, 121));
        groupBox->setFont(font);
        B1_Label_3 = new QLabel(groupBox);
        B1_Label_3->setObjectName(QString::fromUtf8("B1_Label_3"));
        B1_Label_3->setGeometry(QRect(10, 40, 131, 16));
        B1_Label_3->setFont(font);
        B1_Label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_3->setWordWrap(true);
        B1_TEdit_3 = new QTextEdit(groupBox);
        B1_TEdit_3->setObjectName(QString::fromUtf8("B1_TEdit_3"));
        B1_TEdit_3->setGeometry(QRect(170, 30, 101, 32));
        B1_TEdit_3->setFont(font);
        B1_TEdit_3->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_3->setTabChangesFocus(true);
        B1_TEdit_3->setAcceptRichText(false);
        B1_Label_4 = new QLabel(groupBox);
        B1_Label_4->setObjectName(QString::fromUtf8("B1_Label_4"));
        B1_Label_4->setGeometry(QRect(10, 80, 131, 16));
        B1_Label_4->setFont(font);
        B1_Label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_4->setWordWrap(true);
        B1_TEdit_4 = new QTextEdit(groupBox);
        B1_TEdit_4->setObjectName(QString::fromUtf8("B1_TEdit_4"));
        B1_TEdit_4->setGeometry(QRect(170, 70, 101, 32));
        B1_TEdit_4->setFont(font);
        B1_TEdit_4->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_4->setTabChangesFocus(true);
        B1_TEdit_4->setAcceptRichText(false);
        groupBox_2 = new QGroupBox(MaterialsPage);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 180, 311, 121));
        groupBox_2->setFont(font);
        B1_Label_5 = new QLabel(groupBox_2);
        B1_Label_5->setObjectName(QString::fromUtf8("B1_Label_5"));
        B1_Label_5->setGeometry(QRect(10, 40, 131, 16));
        B1_Label_5->setFont(font);
        B1_Label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_5->setWordWrap(true);
        B1_TEdit_5 = new QTextEdit(groupBox_2);
        B1_TEdit_5->setObjectName(QString::fromUtf8("B1_TEdit_5"));
        B1_TEdit_5->setGeometry(QRect(170, 30, 101, 32));
        B1_TEdit_5->setFont(font);
        B1_TEdit_5->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_5->setTabChangesFocus(true);
        B1_TEdit_5->setAcceptRichText(false);
        B1_Label_6 = new QLabel(groupBox_2);
        B1_Label_6->setObjectName(QString::fromUtf8("B1_Label_6"));
        B1_Label_6->setGeometry(QRect(10, 80, 131, 16));
        B1_Label_6->setFont(font);
        B1_Label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_6->setWordWrap(true);
        B1_TEdit_6 = new QTextEdit(groupBox_2);
        B1_TEdit_6->setObjectName(QString::fromUtf8("B1_TEdit_6"));
        B1_TEdit_6->setGeometry(QRect(170, 70, 101, 32));
        B1_TEdit_6->setFont(font);
        B1_TEdit_6->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_6->setTabChangesFocus(true);
        B1_TEdit_6->setAcceptRichText(false);
        B1_TEdit_7 = new QTextEdit(MaterialsPage);
        B1_TEdit_7->setObjectName(QString::fromUtf8("B1_TEdit_7"));
        B1_TEdit_7->setGeometry(QRect(180, 320, 101, 32));
        B1_TEdit_7->setFont(font);
        B1_TEdit_7->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_7->setTabChangesFocus(true);
        B1_TEdit_7->setAcceptRichText(false);
        B1_Label_7 = new QLabel(MaterialsPage);
        B1_Label_7->setObjectName(QString::fromUtf8("B1_Label_7"));
        B1_Label_7->setGeometry(QRect(10, 314, 131, 41));
        B1_Label_7->setFont(font);
        B1_Label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_7->setWordWrap(true);
        pushButton_33 = new QPushButton(MaterialsPage);
        pushButton_33->setObjectName(QString::fromUtf8("pushButton_33"));
        pushButton_33->setGeometry(QRect(301, 2, 27, 27));
        pushButton_33->setAutoFillBackground(false);
        pushButton_33->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"Material.elevation: 6\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_33->setText(QString::fromUtf8(""));
        pushButton_33->setIconSize(QSize(28, 28));
        pushButton_33->setFlat(false);
        pushButton_34 = new QPushButton(MaterialsPage);
        pushButton_34->setObjectName(QString::fromUtf8("pushButton_34"));
        pushButton_34->setGeometry(QRect(272, 2, 27, 27));
        pushButton_34->setAutoFillBackground(false);
        pushButton_34->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_34->setText(QString::fromUtf8(""));
        pushButton_34->setIconSize(QSize(28, 28));
        pushButton_34->setFlat(false);
        stackedWidget->addWidget(MaterialsPage);
        InitialPage = new QWidget();
        InitialPage->setObjectName(QString::fromUtf8("InitialPage"));
        label_16 = new QLabel(InitialPage);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 10, 141, 16));
        label_16->setFont(font);
        groupBox_3 = new QGroupBox(InitialPage);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 50, 311, 151));
        groupBox_3->setFont(font);
        B1_Label_8 = new QLabel(groupBox_3);
        B1_Label_8->setObjectName(QString::fromUtf8("B1_Label_8"));
        B1_Label_8->setGeometry(QRect(10, 40, 131, 16));
        B1_Label_8->setFont(font);
        B1_Label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_8->setWordWrap(true);
        B1_TEdit_8 = new QTextEdit(groupBox_3);
        B1_TEdit_8->setObjectName(QString::fromUtf8("B1_TEdit_8"));
        B1_TEdit_8->setGeometry(QRect(170, 30, 101, 32));
        B1_TEdit_8->setFont(font);
        B1_TEdit_8->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_8->setTabChangesFocus(true);
        B1_TEdit_8->setAcceptRichText(false);
        B1_Label_9 = new QLabel(groupBox_3);
        B1_Label_9->setObjectName(QString::fromUtf8("B1_Label_9"));
        B1_Label_9->setGeometry(QRect(10, 80, 131, 16));
        B1_Label_9->setFont(font);
        B1_Label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_9->setWordWrap(true);
        B1_TEdit_9 = new QTextEdit(groupBox_3);
        B1_TEdit_9->setObjectName(QString::fromUtf8("B1_TEdit_9"));
        B1_TEdit_9->setGeometry(QRect(170, 70, 101, 32));
        B1_TEdit_9->setFont(font);
        B1_TEdit_9->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_9->setTabChangesFocus(true);
        B1_TEdit_9->setAcceptRichText(false);
        B1_TEdit_10 = new QTextEdit(groupBox_3);
        B1_TEdit_10->setObjectName(QString::fromUtf8("B1_TEdit_10"));
        B1_TEdit_10->setGeometry(QRect(170, 110, 101, 32));
        B1_TEdit_10->setFont(font);
        B1_TEdit_10->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_10->setTabChangesFocus(true);
        B1_TEdit_10->setAcceptRichText(false);
        B1_Label_10 = new QLabel(groupBox_3);
        B1_Label_10->setObjectName(QString::fromUtf8("B1_Label_10"));
        B1_Label_10->setGeometry(QRect(10, 120, 131, 16));
        B1_Label_10->setFont(font);
        B1_Label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_10->setWordWrap(true);
        groupBox_4 = new QGroupBox(InitialPage);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 210, 311, 71));
        groupBox_4->setFont(font);
        B1_Label_11 = new QLabel(groupBox_4);
        B1_Label_11->setObjectName(QString::fromUtf8("B1_Label_11"));
        B1_Label_11->setGeometry(QRect(10, 40, 131, 16));
        B1_Label_11->setFont(font);
        B1_Label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_11->setWordWrap(true);
        B1_TEdit_11 = new QTextEdit(groupBox_4);
        B1_TEdit_11->setObjectName(QString::fromUtf8("B1_TEdit_11"));
        B1_TEdit_11->setGeometry(QRect(170, 30, 101, 32));
        B1_TEdit_11->setFont(font);
        B1_TEdit_11->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_11->setTabChangesFocus(true);
        B1_TEdit_11->setAcceptRichText(false);
        groupBox_5 = new QGroupBox(InitialPage);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 290, 311, 71));
        groupBox_5->setFont(font);
        B1_Label_12 = new QLabel(groupBox_5);
        B1_Label_12->setObjectName(QString::fromUtf8("B1_Label_12"));
        B1_Label_12->setGeometry(QRect(10, 40, 131, 16));
        B1_Label_12->setFont(font);
        B1_Label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        B1_Label_12->setWordWrap(true);
        B1_TEdit_12 = new QTextEdit(groupBox_5);
        B1_TEdit_12->setObjectName(QString::fromUtf8("B1_TEdit_12"));
        B1_TEdit_12->setGeometry(QRect(170, 30, 101, 32));
        B1_TEdit_12->setFont(font);
        B1_TEdit_12->setStyleSheet(QString::fromUtf8("QPushButton#SetWorkDirBut { background-color: rgb(255, 255, 255) }"));
        B1_TEdit_12->setTabChangesFocus(true);
        B1_TEdit_12->setAcceptRichText(false);
        pushButton_35 = new QPushButton(InitialPage);
        pushButton_35->setObjectName(QString::fromUtf8("pushButton_35"));
        pushButton_35->setGeometry(QRect(272, 2, 27, 27));
        pushButton_35->setAutoFillBackground(false);
        pushButton_35->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_35->setText(QString::fromUtf8(""));
        pushButton_35->setIconSize(QSize(28, 28));
        pushButton_35->setFlat(false);
        pushButton_36 = new QPushButton(InitialPage);
        pushButton_36->setObjectName(QString::fromUtf8("pushButton_36"));
        pushButton_36->setGeometry(QRect(301, 2, 27, 27));
        pushButton_36->setAutoFillBackground(false);
        pushButton_36->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"Material.elevation: 6\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_36->setText(QString::fromUtf8(""));
        pushButton_36->setIconSize(QSize(28, 28));
        pushButton_36->setFlat(false);
        GeoB_InterfaceTable_5 = new QTableWidget(InitialPage);
        if (GeoB_InterfaceTable_5->columnCount() < 4)
            GeoB_InterfaceTable_5->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem3->setFont(font);
        GeoB_InterfaceTable_5->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem4->setFont(font);
        GeoB_InterfaceTable_5->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem5->setFont(font);
        GeoB_InterfaceTable_5->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem6->setFont(font);
        GeoB_InterfaceTable_5->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        GeoB_InterfaceTable_5->setObjectName(QString::fromUtf8("GeoB_InterfaceTable_5"));
        GeoB_InterfaceTable_5->setGeometry(QRect(10, 400, 311, 331));
        GeoB_InterfaceTable_5->setAlternatingRowColors(true);
        GeoB_AddPoint_5 = new QToolButton(InitialPage);
        GeoB_AddPoint_5->setObjectName(QString::fromUtf8("GeoB_AddPoint_5"));
        GeoB_AddPoint_5->setGeometry(QRect(70, 750, 91, 21));
        GeoC_BathfileLabel_10 = new QLabel(InitialPage);
        GeoC_BathfileLabel_10->setObjectName(QString::fromUtf8("GeoC_BathfileLabel_10"));
        GeoC_BathfileLabel_10->setGeometry(QRect(10, 370, 151, 21));
        GeoC_BathfileLabel_10->setFont(font);
        GeoC_BathfileLabel_10->setFocusPolicy(Qt::ClickFocus);
        GeoB_RemPoint_5 = new QToolButton(InitialPage);
        GeoB_RemPoint_5->setObjectName(QString::fromUtf8("GeoB_RemPoint_5"));
        GeoB_RemPoint_5->setGeometry(QRect(180, 750, 91, 21));
        stackedWidget->addWidget(InitialPage);
        BCPage = new QWidget();
        BCPage->setObjectName(QString::fromUtf8("BCPage"));
        label_12 = new QLabel(BCPage);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 10, 141, 16));
        label_12->setFont(font);
        stackedWidget->addWidget(BCPage);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        pushButton_39 = new QPushButton(page);
        pushButton_39->setObjectName(QString::fromUtf8("pushButton_39"));
        pushButton_39->setGeometry(QRect(301, 2, 27, 27));
        pushButton_39->setAutoFillBackground(false);
        pushButton_39->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"Material.elevation: 6\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/Yes.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/Yes-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_39->setText(QString::fromUtf8(""));
        pushButton_39->setIconSize(QSize(28, 28));
        pushButton_39->setFlat(false);
        pushButton_40 = new QPushButton(page);
        pushButton_40->setObjectName(QString::fromUtf8("pushButton_40"));
        pushButton_40->setGeometry(QRect(272, 2, 27, 27));
        pushButton_40->setAutoFillBackground(false);
        pushButton_40->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 25px;\n"
"    min-width: 25px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/new/res/images/No.png) 25;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/new/res/images/No-invert.png) 25;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));
        pushButton_40->setText(QString::fromUtf8(""));
        pushButton_40->setIconSize(QSize(28, 28));
        pushButton_40->setFlat(false);
        label_17 = new QLabel(page);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 10, 141, 16));
        label_17->setFont(font);
        stackedWidget->addWidget(page);
        TurbulencePage = new QWidget();
        TurbulencePage->setObjectName(QString::fromUtf8("TurbulencePage"));
        label_13 = new QLabel(TurbulencePage);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 10, 171, 16));
        label_13->setFont(font);
        stackedWidget->addWidget(TurbulencePage);
        SolveBasicPage = new QWidget();
        SolveBasicPage->setObjectName(QString::fromUtf8("SolveBasicPage"));
        label_14 = new QLabel(SolveBasicPage);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 10, 191, 16));
        label_14->setFont(font);
        stackedWidget->addWidget(SolveBasicPage);
        SolveAdvPage = new QWidget();
        SolveAdvPage->setObjectName(QString::fromUtf8("SolveAdvPage"));
        label_15 = new QLabel(SolveAdvPage);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 10, 141, 16));
        label_15->setFont(font);
        stackedWidget->addWidget(SolveAdvPage);
        HeaderGroup = new QGroupBox(centralwidget);
        HeaderGroup->setObjectName(QString::fromUtf8("HeaderGroup"));
        HeaderGroup->setGeometry(QRect(10, 10, 1501, 80));
        HeaderGroup->setAutoFillBackground(true);
        HeaderGroup->setAlignment(Qt::AlignCenter);
        HydroLogo = new QLabel(HeaderGroup);
        HydroLogo->setObjectName(QString::fromUtf8("HydroLogo"));
        HydroLogo->setGeometry(QRect(20, 10, 111, 61));
        HydroLogo->setWordWrap(true);
        HydroLogo->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        ProjectName = new QLabel(HeaderGroup);
        ProjectName->setObjectName(QString::fromUtf8("ProjectName"));
        ProjectName->setGeometry(QRect(150, 10, 1331, 16));
        ProjectName->setFont(font);
        ProjectName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        ProjectName->setWordWrap(true);
        ProjectDesc = new QLabel(HeaderGroup);
        ProjectDesc->setObjectName(QString::fromUtf8("ProjectDesc"));
        ProjectDesc->setGeometry(QRect(150, 40, 1331, 31));
        ProjectDesc->setFont(font);
        ProjectDesc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        ProjectDesc->setWordWrap(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1523, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(12);
        ProjAccept->setDefault(true);
        ProjCancel->setDefault(true);
        GeoA_Cancel->setDefault(true);
        GeoA_Accept->setDefault(true);
        GeoB_Cancel->setDefault(true);
        GeoB_Accept->setDefault(true);
        pushButton_19->setDefault(true);
        pushButton_20->setDefault(true);
        pushButton_21->setDefault(true);
        pushButton_22->setDefault(true);
        pushButton_23->setDefault(true);
        pushButton_24->setDefault(true);
        pushButton_25->setDefault(true);
        pushButton_26->setDefault(true);
        pushButton_29->setDefault(true);
        pushButton_30->setDefault(true);
        pushButton_31->setDefault(true);
        pushButton_32->setDefault(true);
        pushButton_33->setDefault(true);
        pushButton_34->setDefault(true);
        pushButton_35->setDefault(true);
        pushButton_36->setDefault(true);
        pushButton_39->setDefault(true);
        pushButton_40->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        FooterGroup->setTitle(QString());
        BottomText->setText(QCoreApplication::translate("MainWindow", "This work is based on the material supported by the National Science Foundation under grant 1612843", nullptr));
        NSFLogo->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/res/images/NSFLogo.png\" height=\"50\"></p></body></html>", nullptr));
        SimCenterLogo->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/res/images/SimCenterLogo.png\" height=\"40\"></p></body></html>", nullptr));
        DataGroup->setTitle(QString());
        QTreeWidgetItem *___qtreewidgetitem = SimOptions->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Simulation data", nullptr));

        const bool __sortingEnabled = SimOptions->isSortingEnabled();
        SimOptions->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = SimOptions->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Project details", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = SimOptions->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "Bathymetry", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "Buildings", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = SimOptions->topLevelItem(2);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "Meshing", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = SimOptions->topLevelItem(3);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "Materials", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = SimOptions->topLevelItem(4);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("MainWindow", "Initial conditions", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = SimOptions->topLevelItem(5);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("MainWindow", "Boundary conditions", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = SimOptions->topLevelItem(6);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("MainWindow", "Solvers", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("MainWindow", "Basic", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("MainWindow", "Advanced", nullptr));
        SimOptions->setSortingEnabled(__sortingEnabled);

        DescriptionHeading->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Description</span></p></body></html>", nullptr));
        DescriptionBox->setText(QString());
        StatusPageLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Setup status</span></p></body></html>", nullptr));
        ProjCheckBox->setText(QCoreApplication::translate("MainWindow", "Project details", nullptr));
        GeometryBox->setText(QCoreApplication::translate("MainWindow", "Geometry definition", nullptr));
        MaterialBox->setText(QCoreApplication::translate("MainWindow", "Material properties", nullptr));
        Meshox->setText(QCoreApplication::translate("MainWindow", "Mesh settings", nullptr));
        BoundaryBox->setText(QCoreApplication::translate("MainWindow", "Boundary conditions", nullptr));
        InitialCondBox->setText(QCoreApplication::translate("MainWindow", "Initial conditions", nullptr));
        SolverBox->setText(QCoreApplication::translate("MainWindow", "Solver settings", nullptr));
        BuildingBox->setText(QCoreApplication::translate("MainWindow", "Buildings", nullptr));
        ProjPageLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Project settings</span></p></body></html>", nullptr));
        WorkDirLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Working directory</p></body></html>", nullptr));
        ProjNameLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Project name</p></body></html>", nullptr));
        ProjDescLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Project description</p></body></html>", nullptr));
        WorkDirBut->setText(QCoreApplication::translate("MainWindow", "Set working directory", nullptr));
        ProjSimType->setItemText(0, QCoreApplication::translate("MainWindow", "Choose simulation type", nullptr));
        ProjSimType->setItemText(1, QCoreApplication::translate("MainWindow", "CFD to resolve SW (Using SW results)", nullptr));
        ProjSimType->setItemText(2, QCoreApplication::translate("MainWindow", "CFD to resolve SW (Using sim library)", nullptr));
        ProjSimType->setItemText(3, QCoreApplication::translate("MainWindow", "CFD using bathymetry data", nullptr));
        ProjSimType->setItemText(4, QCoreApplication::translate("MainWindow", "CFD of wave flume", nullptr));
        ProjSimType->setItemText(5, QCoreApplication::translate("MainWindow", "CFD using STL file", nullptr));
        ProjSimType->setItemText(6, QCoreApplication::translate("MainWindow", "CFD using maps", nullptr));
        ProjSimType->setItemText(7, QCoreApplication::translate("MainWindow", "CFD using Surrogate solver", nullptr));

        SimTypeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Simulation type</p></body></html>", nullptr));
        TurbTypeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Turbulence model</p></body></html>", nullptr));
        ProjTurbType->setItemText(0, QCoreApplication::translate("MainWindow", "Laminar", nullptr));
        ProjTurbType->setItemText(1, QCoreApplication::translate("MainWindow", "k-Epsilon", nullptr));
        ProjTurbType->setItemText(2, QCoreApplication::translate("MainWindow", "k-Omega", nullptr));
        ProjTurbType->setItemText(3, QCoreApplication::translate("MainWindow", "k-Omega SST", nullptr));

        GeoAHeading->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bathymetry settings</span></p></body></html>", nullptr));
        GeoA_SWSolverLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Shallow water solver</p></body></html>", nullptr));
        GeoA_BathfileBut->setText(QCoreApplication::translate("MainWindow", "Select bathymetry files", nullptr));
        GeoA_BathfileLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Bathymetry file</p></body></html>", nullptr));
        GeoA_SWSolverOptions->setItemText(0, QCoreApplication::translate("MainWindow", "Select SW solver used", nullptr));
        GeoA_SWSolverOptions->setItemText(1, QCoreApplication::translate("MainWindow", "GeoClaw", nullptr));
        GeoA_SWSolverOptions->setItemText(2, QCoreApplication::translate("MainWindow", "AdCirc", nullptr));

        GeoA_SWSolLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>SW solutions file format</p></body></html>", nullptr));
        GeoA_SWSolOptions->setItemText(0, QCoreApplication::translate("MainWindow", "Choose solution file format", nullptr));
        GeoA_SWSolOptions->setItemText(1, QCoreApplication::translate("MainWindow", "SimCenter format", nullptr));
        GeoA_SWSolOptions->setItemText(2, QCoreApplication::translate("MainWindow", "GeoClaw format", nullptr));
        GeoA_SWSolOptions->setItemText(3, QCoreApplication::translate("MainWindow", "AdCirc format", nullptr));

        GeoA_InterfaceLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>SW - CFD interface definition</p></body></html>", nullptr));
        GeoA_BathfiletypeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Bathymetric data file type</p></body></html>", nullptr));
        GeoA_BathfiletypeOptions->setItemText(0, QCoreApplication::translate("MainWindow", "Select Bathymetric file type", nullptr));
        GeoA_BathfiletypeOptions->setItemText(1, QCoreApplication::translate("MainWindow", "SimCenter format", nullptr));
        GeoA_BathfiletypeOptions->setItemText(2, QCoreApplication::translate("MainWindow", "GeoClaw (Type I)", nullptr));
        GeoA_BathfiletypeOptions->setItemText(3, QCoreApplication::translate("MainWindow", "GeoClaw (Type II)", nullptr));
        GeoA_BathfiletypeOptions->setItemText(4, QCoreApplication::translate("MainWindow", "GeoClaw (Type III)", nullptr));

        GeoA_InterfaceCheck->setText(QCoreApplication::translate("MainWindow", "Upload points file", nullptr));
        GeoA_InterfacefileBut->setText(QCoreApplication::translate("MainWindow", "Select interface points files", nullptr));
        GeoA_RemPoint->setText(QCoreApplication::translate("MainWindow", "Remove point", nullptr));
        GeoA_AddPoint->setText(QCoreApplication::translate("MainWindow", "Add point", nullptr));
        GeoB_SimLibOptions->setItemText(0, QCoreApplication::translate("MainWindow", "Select pre-existing SW solution", nullptr));
        GeoB_SimLibOptions->setItemText(1, QCoreApplication::translate("MainWindow", "Cascadia subduction zone", nullptr));
        GeoB_SimLibOptions->setItemText(2, QCoreApplication::translate("MainWindow", "Alaska-Aleutian subduction zone", nullptr));
        GeoB_SimLibOptions->setItemText(3, QCoreApplication::translate("MainWindow", "Kermadec-Tonga subduction zone", nullptr));

        GeoB_InterfaceLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>SW - CFD interface definition</p><p><br/></p></body></html>", nullptr));
        GeoBHeading->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bathymetry settings</span></p></body></html>", nullptr));
        GeoB_SimLibLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Select SW sim from library</p></body></html>", nullptr));
        GeoB_InterfacefileBut->setText(QCoreApplication::translate("MainWindow", "Select latitude-longitude file", nullptr));
        GeoB_InterfaceCheck->setText(QCoreApplication::translate("MainWindow", "Upload longitude-latitude file", nullptr));
        GeoB_RemPoint->setText(QCoreApplication::translate("MainWindow", "Remove point", nullptr));
        GeoB_AddPoint->setText(QCoreApplication::translate("MainWindow", "Add point", nullptr));
        GeoC_BathfiletypeOptions->setItemText(0, QCoreApplication::translate("MainWindow", "Select Bathymetric file type", nullptr));
        GeoC_BathfiletypeOptions->setItemText(1, QCoreApplication::translate("MainWindow", "SimCenter format", nullptr));
        GeoC_BathfiletypeOptions->setItemText(2, QCoreApplication::translate("MainWindow", "GeoClaw (Type I)", nullptr));
        GeoC_BathfiletypeOptions->setItemText(3, QCoreApplication::translate("MainWindow", "GeoClaw (Type II)", nullptr));
        GeoC_BathfiletypeOptions->setItemText(4, QCoreApplication::translate("MainWindow", "GeoClaw (Type III)", nullptr));
        GeoC_BathfiletypeOptions->setItemText(5, QCoreApplication::translate("MainWindow", "STL file", nullptr));

        GeoCHeading->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bathymetry settings</span></p></body></html>", nullptr));
        GeoC_BathfiletypeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Bathymetric data file type</p></body></html>", nullptr));
        GeoC_BathfileBut->setText(QCoreApplication::translate("MainWindow", "Select bathymetry files", nullptr));
        GeoC_BathfileLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Bathymetry file</p></body></html>", nullptr));
        GeoCHeading_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bathymetry settings</span></p></body></html>", nullptr));
        FlumeBreadthPic->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/res/images/TopView_v2.png\" width=\"275\"></p></body></html>", nullptr));
        FlumeLengthPic->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/res/images/SideView_2.png\" width=\"265\"></p></body></html>", nullptr));
        GeoC_BathfileLabel_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Side view of flume</p></body></html>", nullptr));
        B1_Label->setText(QCoreApplication::translate("MainWindow", "Depth of water", nullptr));
        B1_Label_2->setText(QCoreApplication::translate("MainWindow", "Breadth of wave flume", nullptr));
        GeoC_BathfileLabel_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Top view of flume</p></body></html>", nullptr));
        GeoC_BathfileLabel_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Segments along length </p></body></html>", nullptr));
        GeoB_RemPoint_2->setText(QCoreApplication::translate("MainWindow", "Remove segment", nullptr));
        GeoB_AddPoint_2->setText(QCoreApplication::translate("MainWindow", "Add segment", nullptr));
        GeoEHeading->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bathymetry settings</span></p></body></html>", nullptr));
        GeoE_NoticeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Bathymetry with maps is not yet available. Updates coming soon.</p></body></html>", nullptr));
        GeoEHeading_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Building settings</span></p></body></html>", nullptr));
        GeoE_NoticeLabel_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Building settings are presently not available for this option</p></body></html>", nullptr));
        GeoEHeading_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Building settings</span></p></body></html>", nullptr));
        GeoC_BathfileLabel_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Building table</p></body></html>", nullptr));
        GeoB_RemPoint_3->setText(QCoreApplication::translate("MainWindow", "Remove building", nullptr));
        GeoB_AddPoint_3->setText(QCoreApplication::translate("MainWindow", "Add building", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Mesh settings</span></p></body></html>", nullptr));
        GeoC_BathfileLabel_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Fineness of mesh</p></body></html>", nullptr));
        GeoC_BathfileLabel_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Very fine</span></p></body></html>", nullptr));
        GeoC_BathfileLabel_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Very Coarse</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = GeoB_InterfaceTable_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Level (1-5)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = GeoB_InterfaceTable_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "P1(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = GeoB_InterfaceTable_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "P2(x,y,z)", nullptr));
        GeoC_BathfileLabel_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Region refinements</p></body></html>", nullptr));
        GeoC_BathfiletypeLabel_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Meshing method</p></body></html>", nullptr));
        GeoC_BathfiletypeOptions_2->setItemText(0, QCoreApplication::translate("MainWindow", "Select mesh type", nullptr));
        GeoC_BathfiletypeOptions_2->setItemText(1, QCoreApplication::translate("MainWindow", "Use Hydro-UQ mesher", nullptr));
        GeoC_BathfiletypeOptions_2->setItemText(2, QCoreApplication::translate("MainWindow", "Upload mesh files", nullptr));
        GeoC_BathfiletypeOptions_2->setItemText(3, QCoreApplication::translate("MainWindow", "Upload solver specific mesh dicts", nullptr));

        GeoB_RemPoint_4->setText(QCoreApplication::translate("MainWindow", "Remove region", nullptr));
        GeoB_AddPoint_4->setText(QCoreApplication::translate("MainWindow", "Add region", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Material properties</span></p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Water", nullptr));
        B1_Label_3->setText(QCoreApplication::translate("MainWindow", "Kinematic viscosity", nullptr));
        B1_Label_4->setText(QCoreApplication::translate("MainWindow", "Density", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Air", nullptr));
        B1_Label_5->setText(QCoreApplication::translate("MainWindow", "Kinematic viscosity", nullptr));
        B1_Label_6->setText(QCoreApplication::translate("MainWindow", "Density", nullptr));
        B1_Label_7->setText(QCoreApplication::translate("MainWindow", "Surface tension between fluids", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Initial conditions</span></p></body></html>", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Velocity (U)", nullptr));
        B1_Label_8->setText(QCoreApplication::translate("MainWindow", "Ux", nullptr));
        B1_Label_9->setText(QCoreApplication::translate("MainWindow", "Uy", nullptr));
        B1_Label_10->setText(QCoreApplication::translate("MainWindow", "Uz", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Pressure (p)", nullptr));
        B1_Label_11->setText(QCoreApplication::translate("MainWindow", "p", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "alpha", nullptr));
        B1_Label_12->setText(QCoreApplication::translate("MainWindow", "alpha", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = GeoB_InterfaceTable_5->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "U/p/alpha", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = GeoB_InterfaceTable_5->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "P1(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = GeoB_InterfaceTable_5->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "P2(x,y,z)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = GeoB_InterfaceTable_5->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        GeoB_AddPoint_5->setText(QCoreApplication::translate("MainWindow", "Add region", nullptr));
        GeoC_BathfileLabel_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Regions</p></body></html>", nullptr));
        GeoB_RemPoint_5->setText(QCoreApplication::translate("MainWindow", "Remove region", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Boundary conditions</span></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Boundary conditions</span></p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Solver settings (Basic)</span></p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Solver settings (Advanced)</span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Solutions</span></p></body></html>", nullptr));
        HeaderGroup->setTitle(QString());
        HydroLogo->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/new/res/images/SimCenter_H2O_logo\" height=\"55\"></p></body></html>", nullptr));
        ProjectName->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
        ProjectDesc->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
