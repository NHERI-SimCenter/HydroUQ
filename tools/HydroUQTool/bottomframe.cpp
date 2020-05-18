#include "bottomframe.h"
#include "ui_bottomframe.h"

BottomFrame::BottomFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BottomFrame)
{
    ui->setupUi(this);
}

BottomFrame::~BottomFrame()
{
    delete ui;
}
