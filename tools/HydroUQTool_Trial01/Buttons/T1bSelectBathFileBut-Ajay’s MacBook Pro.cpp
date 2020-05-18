//*****************************************************************************
// Button to select bathymetric files using a dialog window
//*****************************************************************************
#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

void MainWindow::on_SelectBathFileBut_clicked()
{

    // If we are generating our own file, then we need not select any file
    // We are generating our own file
    if(ui->BathType->currentIndex() == 1)
    {
        ui->HydroTabs->setCurrentIndex(1);
        ui->GenBathymetry_tab->setEnabled(true);

        // Remove later when you generalize
        ui->B2_TEdit->setText("B1");
        ui->B2_TEdit->setEnabled(false);
        ui->Theta4_TEdit->setText("0");
        ui->Theta4_TEdit->setEnabled(false);

    }

    // If we are using SimCenter format, we only need to select one file
    else if(ui->BathType->currentIndex() == 2)
    {
        // If we are not generating the file and it is not in SimCenter format then open a dialog window to select the files
        // Here one can select multiple files
        // The selected files are stored in the String list bathfilenames (declared in mainwindow.h)
        QFileDialog selectfilesdialog(this);
        selectfilesdialog.setDirectory(defaultdir.toString());
        selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
        selectfilesdialog.setNameFilter(tr("All files (*.*)"));
        if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();

        //If the filename is not null
        // activate the accept button
        if(!bathfilenames.isEmpty())
        {
            ui->AcceptBathDataBut->setEnabled(true);
        }

    }

    // If we are using GeoClaw Type 01 file then we still need to select only one file
    else if(ui->BathType->currentIndex() == 3)
    {
        bathfilename = QFileDialog::getOpenFileName(this,
            tr("Open bathymetry file"), defaultdir.toString(), tr("All files (*.*)"));
        //If the filename is not null
        // activate the accept button
        if(!bathfilename.isEmpty())
        {
            ui->AcceptBathDataBut->setEnabled(true);
        }
    }

    // If we are using GeoClaw Type 02/03 file then the data can be avialable as multiple files
    // and hence we need to be able to read multiple files
    else if( (ui->BathType->currentIndex() == 4) || (ui->BathType->currentIndex() == 5) )
    {
        // If we are not generating the file and it is not in SimCenter format then open a dialog window to select the files
        // Here one can select multiple files
        // The selected files are stored in the String list bathfilenames (declared in mainwindow.h)
        QFileDialog selectfilesdialog(this);
        selectfilesdialog.setDirectory(defaultdir.toString());
        selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
        selectfilesdialog.setNameFilter(tr("All files (*.*)"));
        if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
    }

    // If we have an STL file for a full CFD only analysis, we can still have multiple files
    else if( ui->BathType->currentIndex() == 6 )
    {
        // If we are not generating the file and it is not in SimCenter format then open a dialog window to select the files
        // Here one can select multiple files
        // The selected files are stored in the String list bathfilenames (declared in mainwindow.h)
        QFileDialog selectfilesdialog(this);
        selectfilesdialog.setDirectory(defaultdir.toString());
        selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
        selectfilesdialog.setNameFilter(tr("All files (*.stl)"));
        if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
    }
}
