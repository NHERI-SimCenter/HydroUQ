//*****************************************************************************
// Button to confirm domain decomposition properties
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_ParallelConf_But_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Get the index
    int ind = ui->DecompType->currentIndex();

    // Get number of processors
    std::string procX = ui->Domains_x_TEdit->toPlainText().toStdString();
    std::string procY = ui->Domains_x_TEdit->toPlainText().toStdString();
    std::string procZ = ui->Domains_x_TEdit->toPlainText().toStdString();

    // Write out to file
    opfiles << "#Parallelize\n";
    if(ind == 0) opfiles << "Simple, ";
    else if(ind == 1) opfiles << "Hierarchial, ";
    else if(ind == 2) opfiles << "Scotch, ";
    opfiles << procX << ", "<< procY << ", " << procZ << "\n";
    opfiles << "\n";

    // Close files
    opfiles.close();

    // Deactivate the button
    ui->ParallelConf_But->setEnabled(false);
    ui->DecompType->setEnabled(false);
    ui->Domains_x_TEdit->setEnabled(false);
    ui->Domains_y_TEdit->setEnabled(false);
    ui->Domains_z_TEdit->setEnabled(false);
}
