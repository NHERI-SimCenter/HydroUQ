#include "H20plotwindow.h"
#include "ui_H20plotwindow.h"

H20plotwindow::H20plotwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::H20plotwindow)
{
    ui->setupUi(this);
}

H20plotwindow::~H20plotwindow()
{
    delete ui;
}

void H20plotwindow::on_pushButton_clicked()
{

}

