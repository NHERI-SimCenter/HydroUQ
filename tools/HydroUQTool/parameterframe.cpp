#include "parameterframe.h"
#include "ui_parameterframe.h"

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

}
