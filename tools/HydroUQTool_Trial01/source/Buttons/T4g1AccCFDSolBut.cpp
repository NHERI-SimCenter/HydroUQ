//*****************************************************************************
// Button to confirm CFD solver settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_AcceptCFDSolver_But_clicked()
{
    // Set the solver name for a variable
    if(ui->CFDSolver->currentIndex() == 0) cfdsolver = "openfoam";
    else if(ui->CFDSolver->currentIndex() == 1)cfdsolver = "olafoam";

    // Deactivate
    ui->CFDSolver->setEnabled(false);
    ui->AcceptCFDSolver_But->setEnabled(false);

}
