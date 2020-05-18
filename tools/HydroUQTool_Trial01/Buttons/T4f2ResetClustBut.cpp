//*****************************************************************************
// Button to reset custer settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetClusterl_But_clicked()
{
    ui->ClusterType->setEnabled(true);
    ui->ClusterType->setCurrentIndex(0);
    ui->ClusterQueue->setEnabled(true);
    ui->ClusterQueue->setCurrentIndex(0);
    ui->Cores_TEdit->setEnabled(true);
    ui->Wallhour_TEdit->setEnabled(true);
    ui->WallMin_TEdit->setEnabled(true);
    ui->WallSec_TEdit->setEnabled(true);
    ui->Email_TEdit->setEnabled(true);
    ui->Cores_TEdit->setText("");
    ui->Wallhour_TEdit->setText("");
    ui->WallMin_TEdit->setText("");
    ui->WallSec_TEdit->setText("");
    ui->Email_TEdit->setText("");
    ui->ClusterConf_But->setEnabled(true);
}
