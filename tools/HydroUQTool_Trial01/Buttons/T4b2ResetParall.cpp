//*****************************************************************************
// Button to reset domain decomposition properties
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetParall_But_clicked()
{
    ui->DecompType->setEnabled(true);
    ui->DecompType->setCurrentIndex(0);
    ui->ParallelConf_But->setEnabled(true);
    ui->Domains_x_TEdit->setEnabled(true);
    ui->Domains_y_TEdit->setEnabled(true);
    ui->Domains_z_TEdit->setEnabled(true);
    ui->Domains_x_TEdit->setText("");
    ui->Domains_y_TEdit->setText("");
    ui->Domains_z_TEdit->setText("");
}
