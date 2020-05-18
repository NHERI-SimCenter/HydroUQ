//*****************************************************************************
// Button to reset mesh settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetMeshing_But_clicked()
{
    ui->MeshType->setCurrentIndex(0);
    ui->MeshType->setEnabled(true);
    ui->ConfMeshing_But->setEnabled(true);
}
