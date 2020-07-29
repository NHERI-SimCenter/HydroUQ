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
// When the check box is checked or not
//*********************************************************************************
void MainWindow::on_ChB_CA_UploadFile_stateChanged(int arg1)
{
    if(arg1 > 0)
    {
        // Show the upload box
        ui->Btn_CA_UploadFile->show();
        // Hide the stacked widget & buttons
        ui->SWg_CA_Interface->hide();
        ui->Btn_CA_Next->hide();
        ui->Btn_CA_Previous->hide();
    }
    else
    {
        // Hide the upload box
        ui->Btn_CA_UploadFile->hide();
        // Show the stacked widget & buttons
        ui->SWg_CA_Interface->show();
        if(ui->SWg_CA_Interface->count() > 0)
        {
            ui->Btn_CA_Next->show();
            ui->Btn_CA_Previous->show();
        }
    }
}

//*********************************************************************************
// Activate & deactivate buttons when the stacked widget changes
//*********************************************************************************
void MainWindow::on_SWg_CA_Interface_currentChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->Btn_CA_Previous->setDisabled(true);
    }
    else if(arg1 == ui->SWg_CA_Interface->count())
    {
        ui->Btn_CA_Next->setDisabled(true);
    }
    else
    {
        ui->Btn_CA_Next->setDisabled(false);
        ui->Btn_CA_Previous->setDisabled(false);
    }
}

//*********************************************************************************
// When the next button is clicked: SW-CFD Interface
//*********************************************************************************
void MainWindow::on_Btn_CA_Next_clicked()
{
    // Get total number of frames
    int totind = ui->SWg_CA_Interface->count();
    // Get current frame number
    int curind = ui->SWg_CA_Interface->currentIndex();
    // If current index is less than max then change
    if(curind < totind)
    {
        ui->SWg_CA_Interface->setCurrentIndex(curind+1);
    }
}

//*********************************************************************************
// When the previous button is clicked: SW-CFD Interface
//*********************************************************************************
void MainWindow::on_Btn_CA_Previous_clicked()
{
    // Get current frame number
    int curind = ui->SWg_CA_Interface->currentIndex();
    // If current index is less than max then change
    if(curind > 0)
    {
        ui->SWg_CA_Interface->setCurrentIndex(curind-1);
    }
}

//*********************************************************************************
// Hide-Show SW-CFD interface elements
//*********************************************************************************
void MainWindow::swcfdhideshow()
{
    // If count is zero - hide the buttons
    if(ui->SWg_CA_Interface->count() == 0)
    {
        ui->Btn_CA_Next->hide();
        ui->Btn_CA_Previous->hide();
    }

    // Check button
    if(ui->ChB_CA_UploadFile->isChecked())
    {
        // Show the upload box
        ui->Btn_CA_UploadFile->show();

        // Hide the stacked widget & buttons
        ui->SWg_CA_Interface->hide();
        ui->Btn_CA_Next->hide();
        ui->Btn_CA_Previous->hide();

    }
    else
    {
        // Hide the upload box
        ui->Btn_CA_UploadFile->hide();

        // Show the stacked widget & buttons
        ui->SWg_CA_Interface->show();
        if(ui->SWg_CA_Interface->count() > 0)
        {
            ui->Btn_CA_Next->show();
            ui->Btn_CA_Previous->show();
        }

    }

    // If the simulation is type of Wave Flume / STL / Maps / Surrogate
    // Then show only notice & hide rest
    if( ((ui->CmB_AA_SimType->currentIndex() == 4) || (ui->CmB_AA_SimType->currentIndex() == 5))
            || ((ui->CmB_AA_SimType->currentIndex() == 6) || (ui->CmB_AA_SimType->currentIndex() == 7)) )
    {
        // Show notice
        ui->Lbl_CA_Notice->show();

        // Hide everything else
        ui->ChB_CA_UploadFile->hide();
        ui->Btn_CA_UploadFile->hide();
        ui->SWg_CA_Interface->hide();
        ui->Btn_CA_Next->hide();
        ui->Btn_CA_Previous->hide();
    }
    // Else hide notice but show everything
    else
    {
        // Hide notice
        ui->Lbl_CA_Notice->hide();
    }
}
