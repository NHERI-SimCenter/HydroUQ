//*****************************************************************************
// Button to confirm transport settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_Transport_ConfirmBut_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Write out to file
    opfiles << "#Transport\n";

    opfiles << "Water, " << ui->KinVisWater_TEdit->toPlainText().toStdString() << ", " << ui->DenWater_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "Air, " << ui->KinVisAir_TEdit->toPlainText().toStdString() << ", " << ui->DenAir_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "SurfaceTension, " << ui->SurfTension_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "\n";

    // Close files
    opfiles.close();

    // Deactivate the button
    ui->KinVisAir_TEdit->setEnabled(false);
    ui->KinVisWater_TEdit->setEnabled(false);
    ui->DenAir_TEdit->setEnabled(false);
    ui->DenWater_TEdit->setEnabled(false);
    ui->SurfTension_TEdit->setEnabled(false);
    ui->Transport_ConfirmBut->setEnabled(false);
}
