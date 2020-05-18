//*****************************************************************************
// Button to confirm cluster settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_ClusterConf_But_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Write out to file
    opfiles << "#TACC\n";

    // Get the index
    // int ind = ui->TimeType->currentIndex();
    int ind01 = ui->ClusterType->currentIndex();
    int ind02 = ui->ClusterQueue->currentIndex();

    // Write type of cluster out to file
    if(ind01  == 0) opfiles << "KNL\n";
    else if(ind01 == 1) opfiles << "SKX\n";

    // Write queue type out to file
    if(ind02  == 0) opfiles << "Development\n";
    else if(ind02 == 1) opfiles << "Normal\n";
    else if(ind02 == 2) opfiles << "Long\n";

    // Number of cores
    opfiles << "Cores, " << ui->Cores_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "Walltime, " << ui->Wallhour_TEdit->toPlainText().toStdString() << ", " << ui->WallMin_TEdit->toPlainText().toStdString() << ", " << ui->WallSec_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "Email, " << ui->Email_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "\n";

    // Close files
    opfiles.close();

    // Deactivate the button
    ui->ClusterType->setEnabled(false);
    ui->ClusterQueue->setEnabled(false);
    ui->Cores_TEdit->setEnabled(false);
    ui->Wallhour_TEdit->setEnabled(false);
    ui->WallMin_TEdit->setEnabled(false);
    ui->WallSec_TEdit->setEnabled(false);
    ui->Email_TEdit->setEnabled(false);
    ui->ClusterConf_But->setEnabled(false);

}
