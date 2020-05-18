//*****************************************************************************
// Routine to reset everything if process failed
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::processfail()
{
    // Move to first tab
    ui->HydroTabs->setCurrentIndex(0);

    // Disable all items except work dir and reset
    ui->WorkDir_box->setEnabled(true);
    ui->SetWorkDirBut->setEnabled(true);
    ui->Datafile_box->setEnabled(false);
    ui->Interface_box->setEnabled(false);
    ui->Tab1Accept->setEnabled(false);
    ui->Tab1Reset->setEnabled(true);

    // Set Tab 01 variables to null
    defaultdir = QUrl();
    bathfilename = QString();
    bathfilenames = QStringList();
    ui->BathType->setCurrentIndex(0);
    ui->Interface_type->setCurrentIndex(0);
    ui->WorkDirText->setText(defaultdir.toString());

    // Disable other tabs
    ui->GenBathymetry_tab->setEnabled(false);
    ui->bcondition_tab->setEnabled(false);
    ui->cfd_tab->setEnabled(false);
    ui->surrogate_tab->setEnabled(false);

}
