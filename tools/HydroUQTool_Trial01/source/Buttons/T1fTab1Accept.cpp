//*****************************************************************************
// Button to accept data related to Tab 1: Bathymetry data
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include "../Eigen/Dense"

void MainWindow::on_Tab1Accept_clicked()
{
    // Write out the input file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Specify that you are writing bathymetry data
    opfiles << "\n#Bathymetryfiles\n";
    // Write out the Bathymetry data filenames
    for(int ii=0; ii<bathfilenamesSC.size(); ii++)
    {
        opfiles << bathfilenamesSC.at(ii).toStdString() << "\n";
    }

    // Write interface information
    opfiles << "\n#Interface\n";
    if(ui->Interface_type->currentIndex() == 0)
    {
        // Nothing
    }
    else if(ui->Interface_type->currentIndex() == 3)
    {
        // Slope and intercept
        opfiles << "polynomial,1\n";
        opfiles << slopeval << "," << interceptval << "\n";
    }
    //opfiles << "Current index is: " << ui->BathType->currentIndex() << "\n";

    // Write where the openfoam domain is
    if(ui->FlipDomain->isChecked())
    {
        double eqvalue = ymin - slopeval*xmin - interceptval;
        if(eqvalue < 0) opfiles << "OpenFOAM, Negative\n";
        else opfiles << "OpenFOAM, Positive\n";
    }
    else
    {
        double eqvalue = ymax - slopeval*xmax - interceptval;
        if(eqvalue < 0) opfiles << "OpenFOAM, Negative\n";
        else opfiles << "OpenFOAM, Positive\n";
    }

    // Close the project file
    opfiles << "\n";
    opfiles.close();

    // Move to next tab
    ui->HydroTabs->setCurrentIndex(2);
    ui->bcondition_tab->setEnabled(true);
}
