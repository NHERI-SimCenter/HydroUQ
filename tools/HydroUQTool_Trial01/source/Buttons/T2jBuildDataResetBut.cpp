//*****************************************************************************
// Button to reset building data
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

void MainWindow::on_BuildDataResetBut_clicked()
{
    // Reset table to zero
    ui->BuildDataTable->setEnabled(true);
    ui->BuildDataTable->setRowCount(0);

    // Reset number of buildings
    ui->NumBuildings_TEdit->setEnabled(true);
    ui->NumBuildings_TEdit->setText("");

    // Buildings data
    ui->NumBuildingsBut->setEnabled(true);
    ui->AddBuilding->setEnabled(true);
    ui->RemoveBuilding->setEnabled(true);
    ui->BuildDataAcceptBut->setEnabled(true);

}
