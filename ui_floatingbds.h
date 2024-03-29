/********************************************************************************
** Form generated from reading UI file 'floatingbds.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOATINGBDS_H
#define UI_FLOATINGBDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_floatingbds
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Lbl_H1;
    QLabel *Lbl_Notice;
    QSpacerItem *VSp;

    void setupUi(QFrame *floatingbds)
    {
        if (floatingbds->objectName().isEmpty())
            floatingbds->setObjectName(QString::fromUtf8("floatingbds"));
        floatingbds->resize(420, 965);
        verticalLayout = new QVBoxLayout(floatingbds);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        Lbl_H1 = new QLabel(floatingbds);
        Lbl_H1->setObjectName(QString::fromUtf8("Lbl_H1"));
        QFont font;
        font.setPointSize(14);
        Lbl_H1->setFont(font);
        Lbl_H1->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Lbl_H1);

        Lbl_Notice = new QLabel(floatingbds);
        Lbl_Notice->setObjectName(QString::fromUtf8("Lbl_Notice"));
        Lbl_Notice->setFont(font);
        Lbl_Notice->setFocusPolicy(Qt::ClickFocus);
        Lbl_Notice->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        Lbl_Notice->setWordWrap(true);

        verticalLayout->addWidget(Lbl_Notice);

        VSp = new QSpacerItem(20, 900, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(VSp);


        retranslateUi(floatingbds);

        QMetaObject::connectSlotsByName(floatingbds);
    } // setupUi

    void retranslateUi(QFrame *floatingbds)
    {
        floatingbds->setWindowTitle(QCoreApplication::translate("floatingbds", "Frame", nullptr));
        Lbl_H1->setText(QCoreApplication::translate("floatingbds", "<html><head/><body><p><span style=\" font-weight:600;\">FLOATING BODIES</span></p></body></html>", nullptr));
        Lbl_Notice->setText(QCoreApplication::translate("floatingbds", "<html><head/><body><p>This option will be added soon. Watch out for updates!</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class floatingbds: public Ui_floatingbds {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOATINGBDS_H
