//*****************************************************************************
// Button to confirm meshing type
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_ConfMeshing_But_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Get the index
    int ind = ui->MeshType->currentIndex();

    // Write out to file
    opfiles << "#Meshing\n";
    if(ind == 0) opfiles << "Very coarse\n";
    else if(ind == 1) opfiles << "Coarse\n";
    else if(ind == 2) opfiles << "Moderate\n";
    else if(ind == 2) opfiles << "Fine\n";
    else if(ind == 2) opfiles << "Very fine\n";
    opfiles << "\n";

    // Close files
    opfiles.close();

    // Deactivate the button
    ui->ConfMeshing_But->setEnabled(false);
    ui->MeshType->setEnabled(false);
}
