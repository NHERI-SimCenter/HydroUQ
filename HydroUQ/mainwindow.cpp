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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfaceframe.h"

//*********************************************************************************
//Initialize the main window
//*********************************************************************************
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Start UI
    ui->setupUi(this);

    // Initialize items
    initialize();

}

//*********************************************************************************
//Delete the main window
//*********************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Btn_HB_NorthUploadFile_clicked()
{

}

void MainWindow::on_Btn_HB_SouthUploadFile_clicked()
{

}

void MainWindow::on_Btn_HB_EastUploadFile_clicked()
{

}

void MainWindow::on_Btn_HB_WestUploadFile_clicked()
{

}

void MainWindow::on_Btn_HC_EntryUploadFile_clicked()
{

}

void MainWindow::on_Btn_HC_ExitUploadFile_clicked()
{

}

//*********************************************************************************
// When the next button is clicked: SW-CFD Interface
//*********************************************************************************
void MainWindow::on_Btn_BB_Next_clicked()
{
    // Get total number of frames
    int totind = ui->SWg_BB_Interface->count();
    // Get current frame number
    int curind = ui->SWg_BB_Interface->currentIndex();
    // If current index is less than max then change
    if(curind < totind)
    {
        //qDebug() << "Current index is: " << curind;
        ui->SWg_BB_Interface->setCurrentIndex(curind+1);
    }
}

//*********************************************************************************
// When the previous button is clicked: SW-CFD Interface
//*********************************************************************************
void MainWindow::on_Btn_BB_Previous_clicked()
{
    // Get current frame number
    int curind = ui->SWg_BB_Interface->currentIndex();
    // If current index is less than max then change
    if(curind > 0)
    {
        //qDebug() << "Current index is: " << curind;
        ui->SWg_BB_Interface->setCurrentIndex(curind-1);
    }
}

void MainWindow::on_SWg_BB_Interface_currentChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->Btn_BB_Previous->setDisabled(true);
    }
    else if(arg1 == ui->SWg_BB_Interface->count())
    {
        ui->Btn_BB_Next->setDisabled(true);
    }
    else
    {
        ui->Btn_BB_Next->setDisabled(false);
        ui->Btn_BB_Previous->setDisabled(false);
    }
}
