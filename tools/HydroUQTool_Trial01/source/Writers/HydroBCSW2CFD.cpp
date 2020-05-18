//*****************************************************************************
// To write header for the simcenter input file
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include "../Eigen/Dense"
#include <iostream>
#include <fstream>
#include <string>

int MainWindow::HydroBCSW2CFD(int flag)
{

    // About the solver type for shallow water
    if(flag == 1)
    {
        // Get the index of Combox box - SW solver type
        int solvertype = ui->SWSolverType->currentIndex();
        if(solvertype == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("One or more of the boundary conditions specified requires SW solver type to be specified.");
            msgBox.exec();
            return 904;
        }
    }

    // About the solution file format
    else if(flag == 2)
    {
        // Get the index of Combox box - SW solver type
        int solutionformat = ui->SWFormatType->currentIndex();
        if(solutionformat == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("One or more of the boundary conditions specified requires SW solution file format to be specified.");
            msgBox.exec();
            return 905;
        }
    }

    // That the solutions files have been selected
    else if(flag == 3)
    {
        // Check if the string list is not empty
        if(SWsolutionfilenames.isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("One or more of the boundary conditions specified requires SW solution files to be specified.");
            msgBox.exec();
            return 906;
        }
        // Else convert to necessary format as necessary
        else
        {
            // Convert formats
            if(ui->SWFormatType->currentIndex() == 1) SWsolutionfilenamesSC = SWsolutionfilenames;
            //else if(ui->SWFormatType->currentIndex() == 2) SWsolGC2SC(QStringList SWsolutionfilenames);
            //else if(ui->SWFormatType->currentIndex() == 3) SWsolAcirc2SC(QStringList SWsolutionfilenames);
        }
    }

    // Write out the SW solver data to the file
    else if(flag == 4)
    {
        // Open output file
        std::ofstream opfiles;
        opfiles.open(opfilename,std::fstream::app);

        // Header that we are writing SW solutions
        opfiles << "#SWSolutions\n";

        // Provide which solver is used
        if(ui->SWSolverType->currentIndex() == 1) opfiles << "Solver, GeoClaw\n";
        else if(ui->SWSolverType->currentIndex() == 2) opfiles << "Solver, AdCirc\n";

        // Provide which solution format is used
        if(ui->SWFormatType->currentIndex() == 1) opfiles << "Format, SimCenter\n";
        else if(ui->SWFormatType->currentIndex() == 2) opfiles << "Format, GeoClaw\n";
        else if(ui->SWFormatType->currentIndex() == 3) opfiles << "Format, AdCirc\n";

        // Header that files are starting
        opfiles << "\n#SWSolutionfiles\n";
        // Write out the file names
        for(int ii=0; ii<SWsolutionfilenamesSC.size(); ii++)
        {
            opfiles << SWsolutionfilenamesSC.at(ii).toStdString() << "\n";
        }
        opfiles << "\n";
    }

    // Write out the boundary conditions
    else if(flag == 5)
    {
        // Open output file
        std::ofstream opfiles;
        opfiles.open(opfilename,std::fstream::app);

        // Write the boundary conditions
        opfiles << "#BoundaryConditions\n";

        // Write the inlet conditions
        if(ui->InletBC->currentIndex() == 0) opfiles << "Inlet, Wall\n";
        else if(ui->InletBC->currentIndex() == 1) opfiles << "Inlet, CFD2SW\n";
        else if(ui->InletBC->currentIndex() == 2) opfiles << "Inlet, SW2CFD\n";

        // Write the outlet conditions
        if(ui->OutletBC->currentIndex() == 0) opfiles << "Outlet, Wall\n";
        else if(ui->OutletBC->currentIndex() == 1) opfiles << "Outlet, CFD2SW\n";
        else if(ui->OutletBC->currentIndex() == 2) opfiles << "Outlet, SW2CFD\n";

        // Write the front wall BC conditions
        if(ui->FrontBC->currentIndex() == 0) opfiles << "Front, Wall\n";
        else if(ui->FrontBC->currentIndex() == 1) opfiles << "Front, CFD2SW\n";
        else if(ui->FrontBC->currentIndex() == 2) opfiles << "Front, SW2CFD\n";

        // Write the back wall BC conditions
        if(ui->BackBC->currentIndex() == 0) opfiles << "Back, Wall\n";
        else if(ui->BackBC->currentIndex() == 1) opfiles << "Back, CFD2SW\n";
        else if(ui->BackBC->currentIndex() == 2) opfiles << "Back, SW2CFD\n";

        opfiles << "\n";
    }

// If all went well, we will have a zero return code
return 0;

}
