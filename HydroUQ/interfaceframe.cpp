#include "interfaceframe.h"
#include "ui_interfaceframe.h"

#include <QString>
#include <QMap>

InterfaceFrame::InterfaceFrame(const QString titleString, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::InterfaceFrame)
{
    ui->setupUi(this);
    ui->Lbl_BB_ExitH2->setText(titleString);

}

InterfaceFrame::~InterfaceFrame()
{
    delete ui;
}
