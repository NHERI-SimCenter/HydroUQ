//*****************************************************************************
// Button to reset solver settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetSolver_But_clicked()
{
    // Activate and reset
    ui->CFDSolver->setEnabled(true);
    ui->CFDSolver->setCurrentIndex(0);
    ui->AcceptCFDSolver_But->setEnabled(true);
}
