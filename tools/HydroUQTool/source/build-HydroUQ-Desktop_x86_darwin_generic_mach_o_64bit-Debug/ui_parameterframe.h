/********************************************************************************
** Form generated from reading UI file 'parameterframe.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERFRAME_H
#define UI_PARAMETERFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterFrame
{
public:
    QGridLayout *gridLayout;
    QLabel *Lbl_Descript;
    QLabel *Lbl_DescriptTitle;
    QTreeWidget *OptionTree;

    void setupUi(QWidget *ParameterFrame)
    {
        if (ParameterFrame->objectName().isEmpty())
            ParameterFrame->setObjectName(QString::fromUtf8("ParameterFrame"));
        ParameterFrame->resize(266, 531);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ParameterFrame->sizePolicy().hasHeightForWidth());
        ParameterFrame->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        ParameterFrame->setFont(font);
        gridLayout = new QGridLayout(ParameterFrame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Lbl_Descript = new QLabel(ParameterFrame);
        Lbl_Descript->setObjectName(QString::fromUtf8("Lbl_Descript"));
        Lbl_Descript->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(Lbl_Descript, 2, 0, 1, 1);

        Lbl_DescriptTitle = new QLabel(ParameterFrame);
        Lbl_DescriptTitle->setObjectName(QString::fromUtf8("Lbl_DescriptTitle"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        Lbl_DescriptTitle->setFont(font1);
        Lbl_DescriptTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(Lbl_DescriptTitle, 1, 0, 1, 1);

        OptionTree = new QTreeWidget(ParameterFrame);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        OptionTree->setHeaderItem(__qtreewidgetitem);
        OptionTree->setObjectName(QString::fromUtf8("OptionTree"));

        gridLayout->addWidget(OptionTree, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 12);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 7);

        retranslateUi(ParameterFrame);

        QMetaObject::connectSlotsByName(ParameterFrame);
    } // setupUi

    void retranslateUi(QWidget *ParameterFrame)
    {
        ParameterFrame->setWindowTitle(QCoreApplication::translate("ParameterFrame", "Form", nullptr));
        Lbl_Descript->setText(QCoreApplication::translate("ParameterFrame", "TextLabel", nullptr));
        Lbl_DescriptTitle->setText(QCoreApplication::translate("ParameterFrame", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterFrame: public Ui_ParameterFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERFRAME_H
