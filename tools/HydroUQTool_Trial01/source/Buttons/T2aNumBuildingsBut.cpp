//*****************************************************************************
// Button to set number of buildings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

void MainWindow::on_NumBuildingsBut_clicked()
{
    // Number of buildings
    QString numbuild = ui->NumBuildings_TEdit->toPlainText();
    int numbuilds = numbuild.split(" ")[0].toInt();

    // Column headers
    QStringList headers;
    headers << "Type" << "Height" << "P1(x)" << "P1(y)" << "P2(x)" << "P2(y)";

    // Initiate tables
    ui->BuildDataTable->setRowCount(numbuilds);
    ui->BuildDataTable->setColumnCount(6);
    ui->BuildDataTable->setHorizontalHeaderLabels(headers);

    // Deactivate this button now
    ui->NumBuildingsBut->setEnabled(false);

    // Activate buttons
    ui->AddBuilding->setEnabled(true);
    ui->RemoveBuilding->setEnabled(true);

}
