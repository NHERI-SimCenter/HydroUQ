/*********************************************************************************
**
** Copyright (c) 2020 University of California, Berkeley
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Ajay B Harish, Post-Doc @ SimCenter, UC Berkeley
// Dr. Frank McKenna, CTO of SimCenter, UC Berkeley
// Prof. Sanjay Govindjee, Director of SimCenter, UC Berkeley

//*********************************************************************************
// In this routines related to bathymetry are included. For various simulation types
// Different actions are considered
//*********************************************************************************

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"

//*********************************************************************************
// For widgets related to that where pre-existing SW solutions are used
//*********************************************************************************

//*********************************************************************************
// Button to upload bathymetry files: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_SelFiles_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(workdirUrl.toString());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Button to upload shallow-water solution files: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_UploadSolution_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(workdirUrl.toString());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) solfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Checkbox for interface points: With SW solution
//*********************************************************************************
void MainWindow::on_ChB_BA_UploadBox_stateChanged(int arg1)
{
    // If the item is unchecked
    if(arg1 == 0)
    {
        ui->Btn_BA_UploadFile->hide(); // Hide upload button
        ui->SWg_BA_Interface->show(); // Show the interface table
        ui->Btn_BA_Next->show(); // Show the button to move to next interface
        ui->Btn_BA_Previous->show(); // Show the button to move to previous interface
    }
    else
    {
        ui->Btn_BA_UploadFile->show(); // Show upload button
        ui->SWg_BA_Interface->hide(); // Hige the interface table
        ui->Btn_BA_Next->hide(); // Hide the button to move ot next interface
        ui->Btn_BA_Previous->hide(); // Hide the button to move to previous interface
    }
}

//*********************************************************************************
// Button to upload interface files: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_UploadFile_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(workdirUrl.toString());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) intefilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// When page changes: With SW solution
//*********************************************************************************
void MainWindow::on_SWg_BA_Interface_currentChanged(int arg1)
{
    //int ind = ui->SWg_BA_Interface->currentIndex();
    //qDebug() << arg1 << ind;
    if((arg1 > 0) && (arg1 < 3))
    {
        ui->Btn_BA_Next->setDisabled(false);
        ui->Btn_BA_Previous->setDisabled(false);
    }
    else if(arg1 == 0)
    {
        ui->Btn_BA_Previous->setDisabled(true);
    }
    else if(arg1 == 3)
    {
        ui->Btn_BA_Next->setDisabled(true);
    }
}

//*********************************************************************************
// Navigation to previous interface: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_Previous_clicked()
{
    int ind = ui->SWg_BA_Interface->currentIndex();
    if(ind > 0)
    {
        ui->SWg_BA_Interface->setCurrentIndex(ind-1);
    }
}

//*********************************************************************************
// Navigation to next interface: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_Next_clicked()
{
    int ind = ui->SWg_BA_Interface->currentIndex();
    if(ind < 3)
    {
        ui->SWg_BA_Interface->setCurrentIndex(ind+1);
    }
}

//*********************************************************************************
// Add points to interface of Entry: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_EntryAddPt_clicked()
{
    ui->Tbl_BA_EntryIntePt->insertRow(ui->Tbl_BA_EntryIntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Entry: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_EntryRemPt_clicked()
{

}

//*********************************************************************************
// Add points to interface of Exit: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_ExitAddPt_clicked()
{
    ui->Tbl_BA_ExitIntePt->insertRow(ui->Tbl_BA_ExitIntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Exit: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_ExitRemPt_clicked()
{

}

//*********************************************************************************
// Add points to interface of Side 01: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_S01AddPt_clicked()
{
    ui->Tbl_BA_S01IntePt->insertRow(ui->Tbl_BA_S01IntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Side 01: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_S01RemPt_clicked()
{

}

//*********************************************************************************
// Add points to interface of Side 02: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_S02AddPt_clicked()
{
    ui->Tbl_BA_S02IntePt->insertRow(ui->Tbl_BA_S02IntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Side 02: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_S02RemPt_clicked()
{
    //ui->Tbl_BA_S02IntePt->removeRow();
    /*QModelIndexList selection = ui->Tbl_BA_S01IntePt->selectionModel()->selectedRows();
    // Multiple rows can be selected
    qDebug()<<selection.count();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
    }*/
}


//*********************************************************************************
// For widgets related to that where SW solutions from SimCenter library are used
//*********************************************************************************

//*********************************************************************************
// For widgets related to that where SimCenter SW library are used
//*********************************************************************************
void MainWindow::on_ChB_BB_UploadFile_stateChanged(int arg1)
{
    // If the item is unchecked
    if(arg1 == 0)
    {
        ui->Btn_BB_UploadFile->hide(); // Hide upload button
        ui->SWg_BB_Interface->show(); // Show the interface table
        ui->Btn_BB_Next->show(); // Show the button to move to next interface
        ui->Btn_BB_Previous->show(); // Show the button to move to previous interface
    }
    else
    {
        ui->Btn_BB_UploadFile->show(); // Show upload button
        ui->SWg_BB_Interface->hide(); // Hige the interface table
        ui->Btn_BB_Next->hide(); // Hide the button to move ot next interface
        ui->Btn_BB_Previous->hide(); // Hide the button to move to previous interface
    }
}

//*********************************************************************************
// Button to upload interface files: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_UploadFile_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list bathfilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(workdirUrl.toString());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// When the stacked widget changes: With SimCenter Library
//*********************************************************************************
void MainWindow::on_SWg_BB_Interface_currentChanged(int arg1)
{
    if((arg1 > 0) && (arg1 < 3))
    {
        ui->Btn_BB_Next->setDisabled(false);
        ui->Btn_BB_Previous->setDisabled(false);
    }
    else if(arg1 == 0)
    {
        ui->Btn_BB_Previous->setDisabled(true);
    }
    else if(arg1 == 3)
    {
        ui->Btn_BB_Next->setDisabled(true);
    }
}

//*********************************************************************************
// Navigation to previous interface: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BB_Previous_clicked()
{
    int ind = ui->SWg_BB_Interface->currentIndex();
    if(ind > 0)
    {
        ui->SWg_BB_Interface->setCurrentIndex(ind-1);
    }
}

//*********************************************************************************
// Navigation to next interface: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BB_Next_clicked()
{
    int ind = ui->SWg_BB_Interface->currentIndex();
    if(ind < 3)
    {
        ui->SWg_BB_Interface->setCurrentIndex(ind+1);
    }
}

//*********************************************************************************
// Add points to interface of Entry: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_EntryAddPt_clicked()
{
    ui->Tbl_BB_EntryIntePt->insertRow(ui->Tbl_BB_EntryIntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Exit: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_EntryRemPt_clicked()
{

}

//*********************************************************************************
// Add points to interface of Exit: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_ExitAddPt_clicked()
{
    ui->Tbl_BB_ExitIntePt->insertRow(ui->Tbl_BB_ExitIntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Exit: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_ExitRemPt_clicked()
{

}

//*********************************************************************************
// Add points to interface of Side 01: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_S01AddPt_clicked()
{
    ui->Tbl_BB_S01IntePt->insertRow(ui->Tbl_BB_S01IntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Side 01: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_S01RemPt_clicked()
{

}

//*********************************************************************************
// Add points to interface of Side 02: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_S02AddPt_clicked()
{
    ui->Tbl_BB_S02IntePt->insertRow(ui->Tbl_BB_S02IntePt->rowCount());
}

//*********************************************************************************
// Remove points to interface of Side 02: With SimCenter Library
//*********************************************************************************
void MainWindow::on_Btn_BB_S02RemPt_clicked()
{

}

//*********************************************************************************
// For widgets related to that where only bathymetric files are uploaded
//*********************************************************************************

//*********************************************************************************
// Button to upload bathymetric data by user
//*********************************************************************************
void MainWindow::on_Btn_BC_FileUpload_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(workdirUrl.toString());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// For widgets related to that where Wave flume is used as bathymetry
//*********************************************************************************

//*********************************************************************************
// Button to add segments
//*********************************************************************************
void MainWindow::on_Btn_BD_AddSeg_clicked()
{
    ui->Tbl_BD_Segments->insertRow(ui->Tbl_BD_Segments->rowCount());
}

//*********************************************************************************
// Button to remove segments
//*********************************************************************************
void MainWindow::on_Btn_BD_RemSeg_clicked()
{

}
