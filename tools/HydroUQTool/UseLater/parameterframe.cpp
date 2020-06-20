#include "parameterframe.h"
#include "ui_parameterframe.h"
#include "optionsframe.h"
#include <QObject>
#include <iostream>

ParameterFrame::ParameterFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ParameterFrame)
{
    ui->setupUi(this);
}

ParameterFrame::~ParameterFrame()
{
    delete ui;
}

void ParameterFrame::on_SimOptions_itemClicked(QTreeWidgetItem *item, int column)
{
    OptionsFrame *Cathy = new OptionsFrame;

    const bool connected = connect(this,SIGNAL(chgpgno()),Cathy,SLOT(Listen()),Qt::QueuedConnection);
    qDebug() << "Connection established?" << connected;

    qDebug() << "Item clicked";
    emit chgpgno();

}
