#include "mymainframe.h"
#include "ui_mymainframe.h"

MyMainFrame::MyMainFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MyMainFrame)
{
    ui->setupUi(this);
}

MyMainFrame::~MyMainFrame()
{
    delete ui;
}
