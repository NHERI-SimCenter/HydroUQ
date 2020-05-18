//*****************************************************************************
// Button to reset transport settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetTransport_But_clicked()
{

    ui->KinVisAir_TEdit->setEnabled(true);
    ui->KinVisWater_TEdit->setEnabled(true);
    ui->SurfTension_TEdit->setEnabled(true);
    ui->DenAir_TEdit->setEnabled(true);
    ui->DenWater_TEdit->setEnabled(true);
    ui->KinVisAir_TEdit->setText("");
    ui->KinVisWater_TEdit->setText("");
    ui->SurfTension_TEdit->setText("");
    ui->DenAir_TEdit->setText("");
    ui->DenWater_TEdit->setText("");
    ui->Transport_ConfirmBut->setEnabled(true);
}
