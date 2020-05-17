//*****************************************************************************
// Button to reset turbulence properties
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_ResetTurb_but_clicked()
{
    ui->Turb_options->setEnabled(true);
    ui->Turb_options->setCurrentIndex(0);
    ui->ConfTurb_but->setEnabled(true);

}
