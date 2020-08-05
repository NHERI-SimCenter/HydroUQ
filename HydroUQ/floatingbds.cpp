#include "floatingbds.h"
#include "ui_floatingbds.h"

floatingbds::floatingbds(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::floatingbds)
{
    ui->setupUi(this);
}

floatingbds::~floatingbds()
{
    delete ui;
}
