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
// Set the description depending on type of bathymetry we are using
//*********************************************************************************
void MainWindow::bathymetrydesc(int simtypeindex)
{

    // Show description based on simulation type chosen
    // Also show hide elements depending on simulation type
    // If empty option is chose
    if(simtypeindex == 0)
    {
        // Set description box
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Please set the simulation type before proceeding");
    }
    // Simulation with SW solution
    else if(simtypeindex == 1)
    {
        // Set description box
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the bathymetry data related to the simulation is initialized."
                                  "In this case, upload the shallow water solutions and bathymetry data."
                                  "Additionally provide the information of the interface between "
                                  "shallow-water and CFD domain either in the form of a table or as "
                                  "a .csv file");
        // Show hide elements
        ui->Btn_BA_UploadFile->hide();
    }
    // Simulation with SW Library
    else if(simtypeindex == 2)
    {
        // Set description box
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the bathymetry data related to the simulation is initialized."
                                  "Use this case if you do not have pre-existing shallow water solutions. "
                                  "You can choose simulation done on pre-selected subduction zone. "
                                  "Additionally provide the information of the interface between "
                                  "shallow-water and CFD domain either in the form of a table or as "
                                  "a .csv file");
        // Show hide elements
        ui->Btn_BB_UploadFile->hide();
    }
    // Simulation with bathymetry
    else if(simtypeindex == 3)
    {
        // Set description box
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the bathymetry data related to the simulation is initialized."
                                  "Use this case if your entire domain is used for CFD simulation. "
                                  "Here, the geometry for the CFD simulation is initialized using the "
                                  "bathymetry datafiles. At the moment GeoClaw and SimCenter formats "
                                  "are accepted.");
    }
    // Simulation with Wave flume
    else if(simtypeindex == 4)
    {
        // Set description box
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the CFD simulation is initialized on teh wave flume."
                                  "Use this case, if your domain can be modeled as a wave flume. "
                                  "The ramp can be modeled as multiple surfaces of different lengths"
                                  " and angle of inclinations.");
    }
    // Simulation with STL file
    else if(simtypeindex == 5)
    {
        // Set description box
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Use this option if you are using an STL file to run a generic CFD "
                                  "multiphase simulation.");
    }
    // Simulation with maps
    // Set description box
    else if(simtypeindex == 6)
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }
    // Simulation with surrogate
    else if(simtypeindex == 7)
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }

}

//*********************************************************************************
// For widgets related to that where pre-existing SW solutions are used
//*********************************************************************************

//*********************************************************************************
// Button to upload interface files: With SW solution
//*********************************************************************************
void MainWindow::on_Btn_BA_UploadFile_clicked()
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
    //QModelIndexList indexes = ui->Tbl_BA_S01IntePt->selectionMode().selectedRows();
}
