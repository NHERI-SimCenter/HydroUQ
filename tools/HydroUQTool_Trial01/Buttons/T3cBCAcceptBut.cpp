//*****************************************************************************
// Button to accept boundary conditions
//*****************************************************************************
#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QFileDialog>

void MainWindow::on_BCAccept_But_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Even if one of the BC relates to SW solutions, then we get information about it
    if(   (((ui->InletBC->currentIndex()==1) || (ui->OutletBC->currentIndex()==1)) || ((ui->FrontBC->currentIndex()==1) || (ui->BackBC->currentIndex()==1))) ||
          (((ui->InletBC->currentIndex()==2) || (ui->OutletBC->currentIndex()==2)) || ((ui->FrontBC->currentIndex()==2) || (ui->BackBC->currentIndex()==2))) )
    {

        // Check that SW solver has been selected
        // If SW data is all ready, then we will be writing
        // the data to the project file
        int result = HydroBCSW2CFD(1);
        if(result == 0)
        {
            // Check for the solver solution format
            int result2 = HydroBCSW2CFD(2);
            if(result2 == 0)
            {
                // Check that solution files have been selected
                int result3 = HydroBCSW2CFD(3);
                if(result3 == 0)
                {
                    // Write the SW solver data to the file
                    int result4 = HydroBCSW2CFD(4);

                    // Write the boundary conditions
                    result4 = HydroBCSW2CFD(5);

                    // Deactivate all and move to next tab
                    ui->bcondition_tab->setEnabled(false);
                    ui->cfd_tab->setEnabled(true);
                    ui->HydroTabs->setCurrentIndex(3);
                }
            }
        }
    }
    else
    {
        // Write the boundary conditions
        int result4 = HydroBCSW2CFD(5);

        // Deactivate all and move to next tab
        ui->bcondition_tab->setEnabled(false);
        ui->cfd_tab->setEnabled(true);
        ui->HydroTabs->setCurrentIndex(3);
    }
}
