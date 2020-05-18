//*****************************************************************************
// Button to confirm turbulence properties
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_ConfTurb_but_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Get the index
    int ind = ui->Turb_options->currentIndex();

    // WRite out to file
    opfiles << "#Turbulence\n";
    if(ind == 0) opfiles << "Laminar\n";
    else if(ind == 1) opfiles << "RAS:kEpsilon\n";
    else if(ind == 2) opfiles << "RAS:kOmega\n";
    opfiles << "\n";

    // Close files
    opfiles.close();

    // Deactivate the button
    ui->ConfTurb_but->setEnabled(false);
    ui->Turb_options->setEnabled(false);

}
