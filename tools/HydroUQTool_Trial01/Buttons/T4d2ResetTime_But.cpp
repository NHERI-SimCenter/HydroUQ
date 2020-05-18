//*****************************************************************************
// Button to reset time settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetTimeBut_clicked()
{

    ui->TimeType->setEnabled(true);
    ui->TimeType->setCurrentIndex(0);
    ui->StartTime_TEdit->setEnabled(true);
    ui->EndTime_TEdit->setEnabled(true);
    ui->TimeInt_TEdit->setEnabled(true);
    ui->WriteInt_TEdit->setEnabled(true);
    ui->StartTime_TEdit->setText("");
    ui->EndTime_TEdit->setText("");
    ui->TimeInt_TEdit->setText("");
    ui->WriteInt_TEdit->setText("");
    ui->TimeSetConf_But->setEnabled(true);
}
