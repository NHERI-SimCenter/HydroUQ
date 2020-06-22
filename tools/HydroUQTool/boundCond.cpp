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
// Include user headers
//*********************************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"

//*********************************************************************************
// For widgets related to boundary conditions for user bathymetry
//*********************************************************************************

//*********************************************************************************
// When the stacked widget changes: BC with user bathymetry
//*********************************************************************************
void MainWindow::on_SWg_HB_BConditions_currentChanged(int arg1)
{
    if((arg1 > 0) && (arg1 < 3))
    {
        ui->Btn_HB_Next->setDisabled(false);
        ui->Btn_HB_Previous->setDisabled(false);
    }
    else if(arg1 == 0)
    {
        ui->Btn_HB_Previous->setDisabled(true);
    }
    else if(arg1 == 3)
    {
        ui->Btn_HB_Next->setDisabled(true);
    }
}

//*********************************************************************************
// When the previous button is clicked: BC with user bathymetry
//*********************************************************************************
void MainWindow::on_Btn_HB_Previous_clicked()
{
    int ind = ui->SWg_HB_BConditions->currentIndex();
    if(ind > 0)
    {
        ui->SWg_HB_BConditions->setCurrentIndex(ind-1);
    }
}

//*********************************************************************************
// When the next button is clicked: BC with user bathymetry
//*********************************************************************************
void MainWindow::on_Btn_HB_Next_clicked()
{
    int ind = ui->SWg_HB_BConditions->currentIndex();
    if(ind < 3)
    {
        ui->SWg_HB_BConditions->setCurrentIndex(ind+1);
    }
}

//*********************************************************************************
// Combobox for velocity BC: North face
//*********************************************************************************
void MainWindow::on_Cmb_HB_NorthVelBC_currentIndexChanged(int index)
{
    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {

        if(index == 1) ui->Lbl_HB_NorthU->setText("Velocity");
        else if(index == 5) ui->Lbl_HB_NorthU->setText("UMean");
        else if(index == 7) ui->Lbl_HB_NorthU->setText("UMean");

        ui->Btn_HB_NorthUploadFile->hide();
        ui->Cmb_HB_NorthWaveType->hide();
        ui->Lbl_HB_NorthU->show();
        ui->Led_HB_NorthUx->show();
        ui->Led_HB_NorthUy->show();
        ui->Led_HB_NorthUz->show();
        ui->Lbl_HB_NorthOrigin->hide();
        ui->Led_HB_NorthOriginX->hide();
        ui->Led_HB_NorthOriginY->hide();
        ui->Led_HB_NorthOriginZ->hide();
        ui->Lbl_HB_NorthVec->hide();
        ui->Led_HB_NorthVecX->hide();
        ui->Led_HB_NorthVecY->hide();
        ui->Led_HB_NorthVecZ->hide();
        ui->Lbl_HB_NorthPara->hide();
        ui->Led_HB_NorthPara->hide();
    }
    else if(index == 2) // Wave input
    {
        ui->Btn_HB_NorthUploadFile->hide();
        ui->Cmb_HB_NorthWaveType->show();
        ui->Lbl_HB_NorthU->show();
        ui->Led_HB_NorthUx->show();
        ui->Led_HB_NorthUy->show();
        ui->Led_HB_NorthUz->show();
        ui->Lbl_HB_NorthU->setText("Umean");
        ui->Lbl_HB_NorthOrigin->show();
        ui->Led_HB_NorthOriginX->show();
        ui->Led_HB_NorthOriginY->show();
        ui->Led_HB_NorthOriginZ->show();
        ui->Lbl_HB_NorthVec->show();
        ui->Led_HB_NorthVecX->show();
        ui->Led_HB_NorthVecY->show();
        ui->Led_HB_NorthVecZ->show();
        ui->Lbl_HB_NorthPara->show();
        ui->Led_HB_NorthPara->show();
    }
    else if((index == 3) || (index == 4)) // Uniform / nonuniform
    {
        ui->Btn_HB_NorthUploadFile->show();
        ui->Cmb_HB_NorthWaveType->hide();
        ui->Lbl_HB_NorthU->hide();
        ui->Led_HB_NorthUx->hide();
        ui->Led_HB_NorthUy->hide();
        ui->Led_HB_NorthUz->hide();
        //ui->Lbl_HB_NorthU->setText("Umean");
        ui->Lbl_HB_NorthOrigin->hide();
        ui->Led_HB_NorthOriginX->hide();
        ui->Led_HB_NorthOriginY->hide();
        ui->Led_HB_NorthOriginZ->hide();
        ui->Lbl_HB_NorthVec->hide();
        ui->Led_HB_NorthVecX->hide();
        ui->Led_HB_NorthVecY->hide();
        ui->Led_HB_NorthVecZ->hide();
        ui->Lbl_HB_NorthPara->hide();
        ui->Led_HB_NorthPara->hide();
    }
    else if((index == 6) || (index == 8)) // Flow rate and wall
    {
        if(index == 6)
        {
            ui->Lbl_HB_NorthU->setText("Flow rate");
            ui->Lbl_HB_NorthU->show();
            ui->Led_HB_NorthUx->show();
        }
        else
        {
            ui->Lbl_HB_NorthU->setText("Flow rate");
            ui->Lbl_HB_NorthU->hide();
            ui->Led_HB_NorthUx->hide();
        }
        ui->Btn_HB_NorthUploadFile->hide();
        ui->Cmb_HB_NorthWaveType->hide();
        ui->Led_HB_NorthUy->hide();
        ui->Led_HB_NorthUz->hide();
        ui->Lbl_HB_NorthOrigin->hide();
        ui->Led_HB_NorthOriginX->hide();
        ui->Led_HB_NorthOriginY->hide();
        ui->Led_HB_NorthOriginZ->hide();
        ui->Lbl_HB_NorthVec->hide();
        ui->Led_HB_NorthVecX->hide();
        ui->Led_HB_NorthVecY->hide();
        ui->Led_HB_NorthVecZ->hide();
        ui->Lbl_HB_NorthPara->hide();
        ui->Led_HB_NorthPara->hide();
    }
}

//*********************************************************************************
// Combobox for pressure BC: North face
//*********************************************************************************
void MainWindow::on_Cmb_HB_NorthPresBC_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->Lbl_HB_NorthPres->hide();
        ui->Led_HB_NorthPres->hide();
    }
    else
    {
        ui->Lbl_HB_NorthPres->show();
        ui->Led_HB_NorthPres->show();
        if((index == 2)||(index==3)) ui->Lbl_HB_NorthPres->setText("Pressure");
        else if(index==4) ui->Lbl_HB_NorthPres->setText("Pressure gradient");
    }
}

//*********************************************************************************
// Combobox for velocity BC: South face
//*********************************************************************************
void MainWindow::on_Cmb_HB_SouthUBC_currentIndexChanged(int index)
{
    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {

        if(index == 1) ui->Lbl_HB_SouthU->setText("Velocity");
        else if(index == 5) ui->Lbl_HB_SouthU->setText("UMean");
        else if(index == 7) ui->Lbl_HB_SouthU->setText("UMean");

        ui->Btn_HB_SouthUploadFile->hide();
        ui->Cmb_HB_SouthWaveType->hide();
        ui->Lbl_HB_SouthU->show();
        ui->Led_HB_SouthUx->show();
        ui->Led_HB_SouthUy->show();
        ui->Led_HB_SouthUz->show();
        ui->Lbl_HB_SouthOrigin->hide();
        ui->Led_HB_SouthOriginX->hide();
        ui->Led_HB_SouthOriginY->hide();
        ui->Led_HB_SouthOriginZ->hide();
        ui->Lbl_HB_SouthVec->hide();
        ui->Led_HB_SouthVecX->hide();
        ui->Led_HB_SouthVecY->hide();
        ui->Led_HB_SouthVecZ->hide();
        ui->Lbl_HB_SouthPara->hide();
        ui->Led_HB_SouthPara->hide();
    }
    else if(index == 2) // Wave input
    {
        ui->Btn_HB_SouthUploadFile->hide();
        ui->Cmb_HB_SouthWaveType->show();
        ui->Lbl_HB_SouthU->show();
        ui->Led_HB_SouthUx->show();
        ui->Led_HB_SouthUy->show();
        ui->Led_HB_SouthUz->show();
        ui->Lbl_HB_SouthU->setText("Umean");
        ui->Lbl_HB_SouthOrigin->show();
        ui->Led_HB_SouthOriginX->show();
        ui->Led_HB_SouthOriginY->show();
        ui->Led_HB_SouthOriginZ->show();
        ui->Lbl_HB_SouthVec->show();
        ui->Led_HB_SouthVecX->show();
        ui->Led_HB_SouthVecY->show();
        ui->Led_HB_SouthVecZ->show();
        ui->Lbl_HB_SouthPara->show();
        ui->Led_HB_SouthPara->show();
    }
    else if((index == 3) || (index == 4)) // Uniform / nonuniform
    {
        ui->Btn_HB_SouthUploadFile->show();
        ui->Cmb_HB_SouthWaveType->hide();
        ui->Lbl_HB_SouthU->hide();
        ui->Led_HB_SouthUx->hide();
        ui->Led_HB_SouthUy->hide();
        ui->Led_HB_SouthUz->hide();
        //ui->Lbl_HB_SouthU->setText("Umean");
        ui->Lbl_HB_SouthOrigin->hide();
        ui->Led_HB_SouthOriginX->hide();
        ui->Led_HB_SouthOriginY->hide();
        ui->Led_HB_SouthOriginZ->hide();
        ui->Lbl_HB_SouthVec->hide();
        ui->Led_HB_SouthVecX->hide();
        ui->Led_HB_SouthVecY->hide();
        ui->Led_HB_SouthVecZ->hide();
        ui->Lbl_HB_SouthPara->hide();
        ui->Led_HB_SouthPara->hide();
    }
    else if((index == 6) || (index == 8)) // Flow rate and wall
    {
        if(index == 6)
        {
            ui->Lbl_HB_SouthU->setText("Flow rate");
            ui->Lbl_HB_SouthU->show();
            ui->Led_HB_SouthUx->show();
        }
        else
        {
            ui->Lbl_HB_SouthU->setText("Flow rate");
            ui->Lbl_HB_SouthU->hide();
            ui->Led_HB_SouthUx->hide();
        }
        ui->Btn_HB_SouthUploadFile->hide();
        ui->Cmb_HB_SouthWaveType->hide();
        ui->Led_HB_SouthUy->hide();
        ui->Led_HB_SouthUz->hide();
        ui->Lbl_HB_SouthOrigin->hide();
        ui->Led_HB_SouthOriginX->hide();
        ui->Led_HB_SouthOriginY->hide();
        ui->Led_HB_SouthOriginZ->hide();
        ui->Lbl_HB_SouthVec->hide();
        ui->Led_HB_SouthVecX->hide();
        ui->Led_HB_SouthVecY->hide();
        ui->Led_HB_SouthVecZ->hide();
        ui->Lbl_HB_SouthPara->hide();
        ui->Led_HB_SouthPara->hide();
    }
}

//*********************************************************************************
// Combobox for pressure BC: South face
//*********************************************************************************
void MainWindow::on_Cmb_HB_SouthPreBC_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->Lbl_HB_SouthPres->hide();
        ui->Led_HB_SouthPres->hide();
    }
    else
    {
        ui->Lbl_HB_SouthPres->show();
        ui->Led_HB_SouthPres->show();
        if((index == 2)||(index==3)) ui->Lbl_HB_SouthPres->setText("Pressure");
        else if(index==4) ui->Lbl_HB_SouthPres->setText("Pressure gradient");
    }
}

//*********************************************************************************
// Combobox for velocity BC: East face
//*********************************************************************************
void MainWindow::on_Cmb_HB_EastUBC_currentIndexChanged(int index)
{
    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {

        if(index == 1) ui->Lbl_HB_EastU->setText("Velocity");
        else if(index == 5) ui->Lbl_HB_EastU->setText("UMean");
        else if(index == 7) ui->Lbl_HB_EastU->setText("UMean");

        ui->Btn_HB_EastUploadFile->hide();
        ui->Cmb_HB_EastWaveType->hide();
        ui->Lbl_HB_EastU->show();
        ui->Led_HB_EastUx->show();
        ui->Led_HB_EastUy->show();
        ui->Led_HB_EastUz->show();
        ui->Lbl_HB_EastOrigin->hide();
        ui->Led_HB_EastOriginX->hide();
        ui->Led_HB_EastOriginY->hide();
        ui->Led_HB_EastOriginZ->hide();
        ui->Lbl_HB_EastVec->hide();
        ui->Led_HB_EastVecX->hide();
        ui->Led_HB_EastVecY->hide();
        ui->Led_HB_EastVecZ->hide();
        ui->Lbl_HB_EastPara->hide();
        ui->Led_HB_EastPara->hide();
    }
    else if(index == 2) // Wave input
    {
        ui->Btn_HB_EastUploadFile->hide();
        ui->Cmb_HB_EastWaveType->show();
        ui->Lbl_HB_EastU->show();
        ui->Led_HB_EastUx->show();
        ui->Led_HB_EastUy->show();
        ui->Led_HB_EastUz->show();
        ui->Lbl_HB_EastU->setText("Umean");
        ui->Lbl_HB_EastOrigin->show();
        ui->Led_HB_EastOriginX->show();
        ui->Led_HB_EastOriginY->show();
        ui->Led_HB_EastOriginZ->show();
        ui->Lbl_HB_EastVec->show();
        ui->Led_HB_EastVecX->show();
        ui->Led_HB_EastVecY->show();
        ui->Led_HB_EastVecZ->show();
        ui->Lbl_HB_EastPara->show();
        ui->Led_HB_EastPara->show();
    }
    else if((index == 3) || (index == 4)) // Uniform / nonuniform
    {
        ui->Btn_HB_EastUploadFile->show();
        ui->Cmb_HB_EastWaveType->hide();
        ui->Lbl_HB_EastU->hide();
        ui->Led_HB_EastUx->hide();
        ui->Led_HB_EastUy->hide();
        ui->Led_HB_EastUz->hide();
        //ui->Lbl_HB_EastU->setText("Umean");
        ui->Lbl_HB_EastOrigin->hide();
        ui->Led_HB_EastOriginX->hide();
        ui->Led_HB_EastOriginY->hide();
        ui->Led_HB_EastOriginZ->hide();
        ui->Lbl_HB_EastVec->hide();
        ui->Led_HB_EastVecX->hide();
        ui->Led_HB_EastVecY->hide();
        ui->Led_HB_EastVecZ->hide();
        ui->Lbl_HB_EastPara->hide();
        ui->Led_HB_EastPara->hide();
    }
    else if((index == 6) || (index == 8)) // Flow rate and wall
    {
        if(index == 6)
        {
            ui->Lbl_HB_EastU->setText("Flow rate");
            ui->Lbl_HB_EastU->show();
            ui->Led_HB_EastUx->show();
        }
        else
        {
            ui->Lbl_HB_EastU->setText("Flow rate");
            ui->Lbl_HB_EastU->hide();
            ui->Led_HB_EastUx->hide();
        }
        ui->Btn_HB_EastUploadFile->hide();
        ui->Cmb_HB_EastWaveType->hide();
        ui->Led_HB_EastUy->hide();
        ui->Led_HB_EastUz->hide();
        ui->Lbl_HB_EastOrigin->hide();
        ui->Led_HB_EastOriginX->hide();
        ui->Led_HB_EastOriginY->hide();
        ui->Led_HB_EastOriginZ->hide();
        ui->Lbl_HB_EastVec->hide();
        ui->Led_HB_EastVecX->hide();
        ui->Led_HB_EastVecY->hide();
        ui->Led_HB_EastVecZ->hide();
        ui->Lbl_HB_EastPara->hide();
        ui->Led_HB_EastPara->hide();
    }
}

//*********************************************************************************
// Combobox for pressure BC: East face
//*********************************************************************************
void MainWindow::on_Cmb_HB_EastPresBC_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->Lbl_HB_EastPres->hide();
        ui->Led_HB_EastPres->hide();
    }
    else
    {
        ui->Lbl_HB_EastPres->show();
        ui->Led_HB_EastPres->show();
        if((index == 2)||(index==3)) ui->Lbl_HB_EastPres->setText("Pressure");
        else if(index==4) ui->Lbl_HB_EastPres->setText("Pressure gradient");
    }
}

//*********************************************************************************
// Combobox for velocity BC: West face
//*********************************************************************************
void MainWindow::on_Cmb_HB_WestUBC_currentIndexChanged(int index)
{
    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {

        if(index == 1) ui->Lbl_HB_WestU->setText("Velocity");
        else if(index == 5) ui->Lbl_HB_WestU->setText("UMean");
        else if(index == 7) ui->Lbl_HB_WestU->setText("UMean");

        ui->Btn_HB_WestUploadFile->hide();
        ui->Cmb_HB_WestWaveType->hide();
        ui->Lbl_HB_WestU->show();
        ui->Led_HB_WestUx->show();
        ui->Led_HB_WestUy->show();
        ui->Led_HB_WestUz->show();
        ui->Lbl_HB_WestOrigin->hide();
        ui->Led_HB_WestOriginX->hide();
        ui->Led_HB_WestOriginY->hide();
        ui->Led_HB_WestOriginZ->hide();
        ui->Lbl_HB_WestVec->hide();
        ui->Led_HB_WestVecX->hide();
        ui->Led_HB_WestVecY->hide();
        ui->Led_HB_WestVecZ->hide();
        ui->Lbl_HB_WestPara->hide();
        ui->Led_HB_WestPara->hide();
    }
    else if(index == 2) // Wave input
    {
        ui->Btn_HB_WestUploadFile->hide();
        ui->Cmb_HB_WestWaveType->show();
        ui->Lbl_HB_WestU->show();
        ui->Led_HB_WestUx->show();
        ui->Led_HB_WestUy->show();
        ui->Led_HB_WestUz->show();
        ui->Lbl_HB_WestU->setText("Umean");
        ui->Lbl_HB_WestOrigin->show();
        ui->Led_HB_WestOriginX->show();
        ui->Led_HB_WestOriginY->show();
        ui->Led_HB_WestOriginZ->show();
        ui->Lbl_HB_WestVec->show();
        ui->Led_HB_WestVecX->show();
        ui->Led_HB_WestVecY->show();
        ui->Led_HB_WestVecZ->show();
        ui->Lbl_HB_WestPara->show();
        ui->Led_HB_WestPara->show();
    }
    else if((index == 3) || (index == 4)) // Uniform / nonuniform
    {
        ui->Btn_HB_WestUploadFile->show();
        ui->Cmb_HB_WestWaveType->hide();
        ui->Lbl_HB_WestU->hide();
        ui->Led_HB_WestUx->hide();
        ui->Led_HB_WestUy->hide();
        ui->Led_HB_WestUz->hide();
        //ui->Lbl_HB_WestU->setText("Umean");
        ui->Lbl_HB_WestOrigin->hide();
        ui->Led_HB_WestOriginX->hide();
        ui->Led_HB_WestOriginY->hide();
        ui->Led_HB_WestOriginZ->hide();
        ui->Lbl_HB_WestVec->hide();
        ui->Led_HB_WestVecX->hide();
        ui->Led_HB_WestVecY->hide();
        ui->Led_HB_WestVecZ->hide();
        ui->Lbl_HB_WestPara->hide();
        ui->Led_HB_WestPara->hide();
    }
    else if((index == 6) || (index == 8)) // Flow rate and wall
    {
        if(index == 6)
        {
            ui->Lbl_HB_WestU->setText("Flow rate");
            ui->Lbl_HB_WestU->show();
            ui->Led_HB_WestUx->show();
        }
        else
        {
            ui->Lbl_HB_WestU->setText("Flow rate");
            ui->Lbl_HB_WestU->hide();
            ui->Led_HB_WestUx->hide();
        }
        ui->Btn_HB_WestUploadFile->hide();
        ui->Cmb_HB_WestWaveType->hide();
        ui->Led_HB_WestUy->hide();
        ui->Led_HB_WestUz->hide();
        ui->Lbl_HB_WestOrigin->hide();
        ui->Led_HB_WestOriginX->hide();
        ui->Led_HB_WestOriginY->hide();
        ui->Led_HB_WestOriginZ->hide();
        ui->Lbl_HB_WestVec->hide();
        ui->Led_HB_WestVecX->hide();
        ui->Led_HB_WestVecY->hide();
        ui->Led_HB_WestVecZ->hide();
        ui->Lbl_HB_WestPara->hide();
        ui->Led_HB_WestPara->hide();
    }
}

//*********************************************************************************
// Combobox for pressure BC: West face
//*********************************************************************************
void MainWindow::on_Cmb_HB_WestPresBC_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->Lbl_HB_WestPres->hide();
        ui->Led_HB_WestPres->hide();
    }
    else
    {
        ui->Lbl_HB_WestPres->show();
        ui->Led_HB_WestPres->show();
        if((index == 2)||(index==3)) ui->Lbl_HB_WestPres->setText("Pressure");
        else if(index==4) ui->Lbl_HB_WestPres->setText("Pressure gradient");
    }
}


//*********************************************************************************
// For widgets related to boundary conditions for Wave flume
//*********************************************************************************

//*********************************************************************************
// When the stack of entry and exit changes
//*********************************************************************************
void MainWindow::on_SWg_HC_BConditions_currentChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->Btn_HC_Previous->setDisabled(true);
        ui->Btn_HC_Next->setDisabled(false);
    }
    else if(arg1 == 1)
    {
        ui->Btn_HC_Previous->setDisabled(false);
        ui->Btn_HC_Next->setDisabled(true);
    }
}

//*********************************************************************************
// When previous button is clicked
//*********************************************************************************
void MainWindow::on_Btn_HC_Previous_clicked()
{
    int ind = ui->SWg_HC_BConditions->currentIndex();
    if(ind > 0)
    {
        ui->SWg_HC_BConditions->setCurrentIndex(ind-1);
    }
}

//*********************************************************************************
// When the next button is clicked
//*********************************************************************************
void MainWindow::on_Btn_HC_Next_clicked()
{
    int ind = ui->SWg_HC_BConditions->currentIndex();
    if(ind < 3)
    {
        ui->SWg_HC_BConditions->setCurrentIndex(ind+1);
    }
}

//*********************************************************************************
// Combobox for velocity BC: Entry face
//*********************************************************************************
void MainWindow::on_Cmb_HC_EntryUBC_currentIndexChanged(int index)
{
    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {

        if(index == 1) ui->Lbl_HC_EntryU->setText("Velocity");
        else if(index == 5) ui->Lbl_HC_EntryU->setText("UMean");
        else if(index == 7) ui->Lbl_HC_EntryU->setText("UMean");

        ui->Btn_HC_EntryUploadFile->hide();
        ui->Cmb_HC_EntryWaveType->hide();
        ui->Lbl_HC_EntryU->show();
        ui->Led_HC_EntryUx->show();
        ui->Led_HC_EntryUy->show();
        ui->Led_HC_EntryUz->show();
        ui->Lbl_HC_EntryOrigin->hide();
        ui->Led_HC_EntryOriginX->hide();
        ui->Led_HC_EntryOriginY->hide();
        ui->Led_HC_EntryOriginZ->hide();
        ui->Lbl_HC_EntryVec->hide();
        ui->Led_HC_EntryVecX->hide();
        ui->Led_HC_EntryVecY->hide();
        ui->Led_HC_EntryVecZ->hide();
        ui->Lbl_HC_EntryPara->hide();
        ui->Led_HC_EntryPara->hide();
    }
    else if(index == 2) // Wave input
    {
        ui->Btn_HC_EntryUploadFile->hide();
        ui->Cmb_HC_EntryWaveType->show();
        ui->Lbl_HC_EntryU->show();
        ui->Led_HC_EntryUx->show();
        ui->Led_HC_EntryUy->show();
        ui->Led_HC_EntryUz->show();
        ui->Lbl_HC_EntryU->setText("Umean");
        ui->Lbl_HC_EntryOrigin->show();
        ui->Led_HC_EntryOriginX->show();
        ui->Led_HC_EntryOriginY->show();
        ui->Led_HC_EntryOriginZ->show();
        ui->Lbl_HC_EntryVec->show();
        ui->Led_HC_EntryVecX->show();
        ui->Led_HC_EntryVecY->show();
        ui->Led_HC_EntryVecZ->show();
        ui->Lbl_HC_EntryPara->show();
        ui->Led_HC_EntryPara->show();
    }
    else if((index == 3) || (index == 4)) // Uniform / nonuniform
    {
        ui->Btn_HC_EntryUploadFile->show();
        ui->Cmb_HC_EntryWaveType->hide();
        ui->Lbl_HC_EntryU->hide();
        ui->Led_HC_EntryUx->hide();
        ui->Led_HC_EntryUy->hide();
        ui->Led_HC_EntryUz->hide();
        //ui->Lbl_HC_EntryU->setText("Umean");
        ui->Lbl_HC_EntryOrigin->hide();
        ui->Led_HC_EntryOriginX->hide();
        ui->Led_HC_EntryOriginY->hide();
        ui->Led_HC_EntryOriginZ->hide();
        ui->Lbl_HC_EntryVec->hide();
        ui->Led_HC_EntryVecX->hide();
        ui->Led_HC_EntryVecY->hide();
        ui->Led_HC_EntryVecZ->hide();
        ui->Lbl_HC_EntryPara->hide();
        ui->Led_HC_EntryPara->hide();
    }
    else if((index == 6) || (index == 8)) // Flow rate and wall
    {
        if(index == 6)
        {
            ui->Lbl_HC_EntryU->setText("Flow rate");
            ui->Lbl_HC_EntryU->show();
            ui->Led_HC_EntryUx->show();
        }
        else
        {
            ui->Lbl_HC_EntryU->setText("Flow rate");
            ui->Lbl_HC_EntryU->hide();
            ui->Led_HC_EntryUx->hide();
        }
        ui->Btn_HC_EntryUploadFile->hide();
        ui->Cmb_HC_EntryWaveType->hide();
        ui->Led_HC_EntryUy->hide();
        ui->Led_HC_EntryUz->hide();
        ui->Lbl_HC_EntryOrigin->hide();
        ui->Led_HC_EntryOriginX->hide();
        ui->Led_HC_EntryOriginY->hide();
        ui->Led_HC_EntryOriginZ->hide();
        ui->Lbl_HC_EntryVec->hide();
        ui->Led_HC_EntryVecX->hide();
        ui->Led_HC_EntryVecY->hide();
        ui->Led_HC_EntryVecZ->hide();
        ui->Lbl_HC_EntryPara->hide();
        ui->Led_HC_EntryPara->hide();
    }
}

//*********************************************************************************
// Combobox for pressure BC: Entry face
//*********************************************************************************
void MainWindow::on_Cmb_HC_EntryPresBC_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->Lbl_HC_EntryPres->hide();
        ui->Led_HC_EntryPres->hide();
    }
    else
    {
        ui->Lbl_HC_EntryPres->show();
        ui->Led_HC_EntryPres->show();
        if((index == 2)||(index==3)) ui->Lbl_HC_EntryPres->setText("Pressure");
        else if(index==4) ui->Lbl_HC_EntryPres->setText("Pressure gradient");
    }
}

//*********************************************************************************
// Combobox for velocity BC: Exit face
//*********************************************************************************
void MainWindow::on_Cmb_HC_ExitUBC_currentIndexChanged(int index)
{
    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {

        if(index == 1) ui->Lbl_HC_ExitU->setText("Velocity");
        else if(index == 5) ui->Lbl_HC_ExitU->setText("UMean");
        else if(index == 7) ui->Lbl_HC_ExitU->setText("UMean");

        ui->Btn_HC_ExitUploadFile->hide();
        ui->Cmb_HC_ExitWaveType->hide();
        ui->Lbl_HC_ExitU->show();
        ui->Led_HC_ExitUx->show();
        ui->Led_HC_ExitUy->show();
        ui->Led_HC_ExitUz->show();
        ui->Lbl_HC_ExitOrigin->hide();
        ui->Led_HC_ExitOriginX->hide();
        ui->Led_HC_ExitOriginY->hide();
        ui->Led_HC_ExitOriginZ->hide();
        ui->Lbl_HC_ExitVec->hide();
        ui->Led_HC_ExitVecX->hide();
        ui->Led_HC_ExitVecY->hide();
        ui->Led_HC_ExitVecZ->hide();
        ui->Lbl_HC_ExitPara->hide();
        ui->Led_HC_ExitPara->hide();
    }
    else if(index == 2) // Wave input
    {
        ui->Btn_HC_ExitUploadFile->hide();
        ui->Cmb_HC_ExitWaveType->show();
        ui->Lbl_HC_ExitU->show();
        ui->Led_HC_ExitUx->show();
        ui->Led_HC_ExitUy->show();
        ui->Led_HC_ExitUz->show();
        ui->Lbl_HC_ExitU->setText("Umean");
        ui->Lbl_HC_ExitOrigin->show();
        ui->Led_HC_ExitOriginX->show();
        ui->Led_HC_ExitOriginY->show();
        ui->Led_HC_ExitOriginZ->show();
        ui->Lbl_HC_ExitVec->show();
        ui->Led_HC_ExitVecX->show();
        ui->Led_HC_ExitVecY->show();
        ui->Led_HC_ExitVecZ->show();
        ui->Lbl_HC_ExitPara->show();
        ui->Led_HC_ExitPara->show();
    }
    else if((index == 3) || (index == 4)) // Uniform / nonuniform
    {
        ui->Btn_HC_ExitUploadFile->show();
        ui->Cmb_HC_ExitWaveType->hide();
        ui->Lbl_HC_ExitU->hide();
        ui->Led_HC_ExitUx->hide();
        ui->Led_HC_ExitUy->hide();
        ui->Led_HC_ExitUz->hide();
        //ui->Lbl_HC_ExitU->setText("Umean");
        ui->Lbl_HC_ExitOrigin->hide();
        ui->Led_HC_ExitOriginX->hide();
        ui->Led_HC_ExitOriginY->hide();
        ui->Led_HC_ExitOriginZ->hide();
        ui->Lbl_HC_ExitVec->hide();
        ui->Led_HC_ExitVecX->hide();
        ui->Led_HC_ExitVecY->hide();
        ui->Led_HC_ExitVecZ->hide();
        ui->Lbl_HC_ExitPara->hide();
        ui->Led_HC_ExitPara->hide();
    }
    else if((index == 6) || (index == 8)) // Flow rate and wall
    {
        if(index == 6)
        {
            ui->Lbl_HC_ExitU->setText("Flow rate");
            ui->Lbl_HC_ExitU->show();
            ui->Led_HC_ExitUx->show();
        }
        else
        {
            ui->Lbl_HC_ExitU->setText("Flow rate");
            ui->Lbl_HC_ExitU->hide();
            ui->Led_HC_ExitUx->hide();
        }
        ui->Btn_HC_ExitUploadFile->hide();
        ui->Cmb_HC_ExitWaveType->hide();
        ui->Led_HC_ExitUy->hide();
        ui->Led_HC_ExitUz->hide();
        ui->Lbl_HC_ExitOrigin->hide();
        ui->Led_HC_ExitOriginX->hide();
        ui->Led_HC_ExitOriginY->hide();
        ui->Led_HC_ExitOriginZ->hide();
        ui->Lbl_HC_ExitVec->hide();
        ui->Led_HC_ExitVecX->hide();
        ui->Led_HC_ExitVecY->hide();
        ui->Led_HC_ExitVecZ->hide();
        ui->Lbl_HC_ExitPara->hide();
        ui->Led_HC_ExitPara->hide();
    }
}


//*********************************************************************************
// Combobox for pressure BC: Exit face
//*********************************************************************************
void MainWindow::on_Cmb_HC_ExitPresBC_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->Lbl_HC_ExitPres->hide();
        ui->Led_HC_ExitPres->hide();
    }
    else
    {
        ui->Lbl_HC_ExitPres->show();
        ui->Led_HC_ExitPres->show();
        if((index == 2)||(index==3)) ui->Lbl_HC_ExitPres->setText("Pressure");
        else if(index==4) ui->Lbl_HC_ExitPres->setText("Pressure gradient");
    }
}
