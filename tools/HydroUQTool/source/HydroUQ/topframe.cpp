#include "topframe.h"
#include "ui_topframe.h"

TopFrame::TopFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TopFrame)
{
    ui->setupUi(this);
}

TopFrame::~TopFrame()
{
    delete ui;
}
