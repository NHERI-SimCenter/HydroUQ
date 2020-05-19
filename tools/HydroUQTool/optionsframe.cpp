#include "optionsframe.h"
#include "ui_optionsframe.h"

OptionsFrame::OptionsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OptionsFrame)
{
    ui->setupUi(this);
}

OptionsFrame::~OptionsFrame()
{
    delete ui;
}
