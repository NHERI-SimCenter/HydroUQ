//*****************************************************************************
// To write header for the simcenter input file
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include "../Eigen/Dense"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

void MainWindow::HydroHeader()
{
    // Openthe input file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Get current time
    time_t now = time(0);
    char* dt = ctime(&now);

    // Specify that you are writing bathymetry data
    opfiles << "//*************************************************************\n";
    opfiles << "// Hydro-UQ \n";
    opfiles << "// Developed by SimCenter, DesignSafe \n";
    opfiles << "// Project started on: "<< dt;
    opfiles << "//*************************************************************\n\n";
    opfiles.close();
}
