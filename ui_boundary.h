/********************************************************************************
** Form generated from reading UI file 'boundary.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOUNDARY_H
#define UI_BOUNDARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_boundary
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_Notice;
    QStackedWidget *SWg_Interface;
    QHBoxLayout *HLY_AddBuild;
    QToolButton *Btn_AddBoundary;
    QToolButton *Btn_RemBoundary;
    QHBoxLayout *HLY_Scroller;
    QSpacerItem *HSp_Scroll01;
    QPushButton *Btn_Previous;
    QPushButton *Btn_Next;
    QSpacerItem *HSp_Scroll02;
    QSpacerItem *VSp;

    void setupUi(QFrame *boundary)
    {
        if (boundary->objectName().isEmpty())
            boundary->setObjectName(QString::fromUtf8("boundary"));
        boundary->resize(399, 887);
        verticalLayout = new QVBoxLayout(boundary);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(boundary);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_Notice = new QLabel(boundary);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font);
        Lbl_Notice->setFocusPolicy(Qt::ClickFocus);
        Lbl_Notice->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        Lbl_Notice->setWordWrap(true);

        verticalLayout->addWidget(Lbl_Notice);

        SWg_Interface = new QStackedWidget(boundary);
        SWg_Interface->setObjectName(QString::fromUtf8("SWg_Interface"));
        SWg_Interface->setToolTipDuration(10000);

        verticalLayout->addWidget(SWg_Interface);

        HLY_AddBuild = new QHBoxLayout();
        HLY_AddBuild->setObjectName(QString::fromUtf8("HLY_AddBuild"));
        Btn_AddBoundary = new QToolButton(boundary);
        Btn_AddBoundary->setObjectName(QString::fromUtf8("Btn_AddBoundary"));
        Btn_AddBoundary->setToolTipDuration(10000);

        HLY_AddBuild->addWidget(Btn_AddBoundary);

        Btn_RemBoundary = new QToolButton(boundary);
        Btn_RemBoundary->setObjectName(QString::fromUtf8("Btn_RemBoundary"));
        Btn_RemBoundary->setToolTipDuration(10000);

        HLY_AddBuild->addWidget(Btn_RemBoundary);


        verticalLayout->addLayout(HLY_AddBuild);

        HLY_Scroller = new QHBoxLayout();
        HLY_Scroller->setObjectName(QString::fromUtf8("HLY_Scroller"));
        HSp_Scroll01 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HLY_Scroller->addItem(HSp_Scroll01);

        Btn_Previous = new QPushButton(boundary);
        Btn_Previous->setObjectName(QString::fromUtf8("Btn_Previous"));
        Btn_Previous->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/images/images/previous.png) 10;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 10px;\n"
"    min-width: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/images/images/previous.png) 10;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/images/images/previous-invert.png) 10;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));

        HLY_Scroller->addWidget(Btn_Previous);

        Btn_Next = new QPushButton(boundary);
        Btn_Next->setObjectName(QString::fromUtf8("Btn_Next"));
        Btn_Next->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-image: url(:/images/images/next.png) 10;\n"
"    border-width: 0px;                         \n"
"    padding: 0px 0px;\n"
"    min-height: 10px;\n"
"    min-width: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-image: url(:/images/images/next.png) 10;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: lightgray;\n"
"    border-image: url(:/images/images/next-invert.png) 10;\n"
"    padding-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}\n"
"\n"
""));

        HLY_Scroller->addWidget(Btn_Next);

        HSp_Scroll02 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HLY_Scroller->addItem(HSp_Scroll02);


        verticalLayout->addLayout(HLY_Scroller);

        VSp = new QSpacerItem(20, 363, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(boundary);

        SWg_Interface->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(boundary);
    } // setupUi

    void retranslateUi(QFrame *boundary)
    {
        boundary->setWindowTitle(QCoreApplication::translate("boundary", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("boundary", "<html><head/><body><p><span style=\" font-weight:600;\">BOUNDARY CONDITIONS</span></p></body></html>", nullptr));
        Lbl_Notice->setText(QCoreApplication::translate("boundary", "<html><head/><body><p>Boundary conditions are already prescribed through the shallow-water solutions</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        SWg_Interface->setToolTip(QCoreApplication::translate("boundary", "Interface points for all SW-CFD interfaces", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Btn_AddBoundary->setToolTip(QCoreApplication::translate("boundary", "Add building data", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_AddBoundary->setText(QCoreApplication::translate("boundary", "Add Boundary", nullptr));
#if QT_CONFIG(tooltip)
        Btn_RemBoundary->setToolTip(QCoreApplication::translate("boundary", "Remove building data", nullptr));
#endif // QT_CONFIG(tooltip)
        Btn_RemBoundary->setText(QCoreApplication::translate("boundary", "Remove Boundary", nullptr));
        Btn_Previous->setText(QString());
        Btn_Next->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class boundary: public Ui_boundary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOUNDARY_H
