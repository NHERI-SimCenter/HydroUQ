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

//*********************************************************************************
// Accessor function to get the toolname
//*********************************************************************************
std::string MainWindow::gettoolname()
{
    return toolname;
}







void MainWindow::on_OptionsStack_currentChanged(int arg1)
{

    if(arg1 == 0) // Project settings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Please set the project settings"
                                  " before proceeding ahead");
    }
    else if(arg1 == 1) // Bathymetry (from SW simulation)
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the bathymetry data related to the "
                                  "simulation is initialized. In this case, upload "
                                  "the shallow water solutions and bathymetry data. Additionally "
                                  "provide the information of the interface between "
                                  "shallow-water and CFD domain either in the form of "
                                  "a table or as a .csv file");
    }
    else if(arg1 == 1) // Bathymetry (from SimLibrary)
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the bathymetry data related to the simulation is initialized."
                                  "Use this case if you do not have pre-existing shallow water solutions. "
                                  "You can choose simulation done on pre-selected subduction zone. "
                                  "Additionally provide the information of the interface between "
                                  "shallow-water and CFD domain either in the form of a table or as "
                                  "a .csv file");
    }

    ui->Lbl_Descript->setText("This is new text");

}









