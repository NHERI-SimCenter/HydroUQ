/*********************************************************************************
**
** Copyright (c) 2020 The University of Notre Dame
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
// Written by Ajay B Harish, for SimCenter @ UC Berkeley, director: Sanjay GOvindjee at UC Berkeley

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <iostream>
#include <QFileDialog>
#include <QApplication>

//*********************************************************************************
//Initialize the main window
//*********************************************************************************
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup options
    setoptionmaps();

    // Start the UI
    ui->setupUi(this);

    // Set teh Stacked pages to status page
    ui->stackedWidget->setCurrentIndex(0);

}

//*********************************************************************************
//Delete the main window
//*********************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

//*********************************************************************************
//What happens when an item on the tree is clicked
//*********************************************************************************
void MainWindow::on_SimOptions_itemClicked(QTreeWidgetItem *item, int column)
{

    // Get the string of hte selected item
    QString sel = item->text(column);

    // Get the index of the simulation type
    int simtypeindex = ui->ProjSimType->currentIndex();

    // Do certain action depending on which item has been selected
    // Information about the project
    if(sel == "Project details")
    {
        // Get page index
        int pageindex = optionmap(1,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this for setting basic information about the project and intended simulation type.");
    }

    //Geometrical details
    else if(sel == "Bathymetry")
    {
        // Get page index
        int pageindex = optionmap(2,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this for information about the geometry of the simulation domain.");
    }

    // Buildings
    else if(sel == "Buildings")
    {
        // Get page index
        int pageindex = optionmap(3,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this for information about the geometry of the buildings in the simulation domain.");
    }

    // Meshing details
    else if(sel == "Meshing")
    {
        // Get page index
        int pageindex = optionmap(4,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this for setting the information about the meshing parameters.");
    }

    // Material properties
    else if(sel == "Materials")
    {
        // Get page index
        int pageindex = optionmap(5,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this for information about the properties of two fluids in the domain.");
    }

    // Boundary conditions
    else if(sel == "Boundary conditions")
    {
        int pageindex = optionmap(6,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this to finalize the settings for boundary conditions.");
    }

    // Turbulence
    else if(sel == "Turbulence")
    {
        int pageindex = optionmap(7,simtypeindex);
        ui->stackedWidget->setCurrentIndex(pageindex);
        ui->DescriptionBox->setText("Use this for information to setup turbulence properties for the simulation.");
    }

    // Solver settings
    else if(sel == "Basic")
    {
        ui->stackedWidget->setCurrentIndex(5);
        ui->DescriptionBox->setText("Use this for information to setup solver settings for TACC.");
    }

    // Solver settings
    else if(sel == "Advanced")
    {
        ui->stackedWidget->setCurrentIndex(6);
        ui->DescriptionBox->setText("Use this for information to setup solver settings for TACC.");
    }

}

//*********************************************************************************
// Setup option maps
//*********************************************************************************
void MainWindow::setoptionmaps()
{

    // Map for options
    optionmap.setZero(9,8);

    // Status page
    optionmap(0,0) = 0; // Select simtype
    optionmap(0,1) = 0; // CFD to resolve SW (with SW results)
    optionmap(0,2) = 0; // CFD to resolve SW (simlibrary results)
    optionmap(0,3) = 0; // CFD using bathymetry data
    optionmap(0,4) = 0; // CFD of wave flume
    optionmap(0,5) = 0; // CFD using STL
    optionmap(0,6) = 0; // CFD using maps
    optionmap(0,7) = 0; // CFD using surrogate

    // Project
    optionmap(1,0) = 1; // Select simtype
    optionmap(1,1) = 1; // CFD to resolve SW (with SW results)
    optionmap(1,2) = 1; // CFD to resolve SW (simlibrary results)
    optionmap(1,3) = 1; // CFD using bathymetry data
    optionmap(1,4) = 1; // CFD of wave flume
    optionmap(1,5) = 1; // CFD using STL
    optionmap(1,6) = 1; // CFD using maps
    optionmap(1,7) = 0; // CFD using surrogate

    // Geometry
    optionmap(2,0) = 0; // Select simtype
    optionmap(2,1) = 2; // CFD to resolve SW (with SW results)
    optionmap(2,2) = 3; // CFD to resolve SW (simlibrary results)
    optionmap(2,3) = 4; // CFD using bathymetry data
    optionmap(2,4) = 5; // CFD of wave flume
    optionmap(2,5) = 4; // CFD using STL
    optionmap(2,6) = 6; // CFD using maps
    optionmap(2,7) = 0; // CFD using surrogate

    // Buildings
    optionmap(3,0) = 0; // Select simtype
    optionmap(3,1) = 7; // CFD to resolve SW (with SW results)
    optionmap(3,2) = 7; // CFD to resolve SW (simlibrary results)
    optionmap(3,3) = 7; // CFD using bathymetry data
    optionmap(3,4) = 8; // CFD of wave flume
    optionmap(3,5) = 7; // CFD using STL
    optionmap(3,6) = 7; // CFD using maps
    optionmap(3,7) = 0; // CFD using surrogate

    // Meshing
    optionmap(4,0) = 0; // Select simtype
    optionmap(4,1) = 9; // CFD to resolve SW (with SW results)
    optionmap(4,2) = 9; // CFD to resolve SW (simlibrary results)
    optionmap(4,3) = 9; // CFD using bathymetry data
    optionmap(4,4) = 9; // CFD of wave flume
    optionmap(4,5) = 9; // CFD using STL
    optionmap(4,6) = 9; // CFD using maps
    optionmap(4,7) = 0; // CFD using surrogate

    // Materials
    optionmap(5,0) = 0; // Select simtype
    optionmap(5,1) = 10; // CFD to resolve SW (with SW results)
    optionmap(5,2) = 10; // CFD to resolve SW (simlibrary results)
    optionmap(5,3) = 10; // CFD using bathymetry data
    optionmap(5,4) = 10; // CFD of wave flume
    optionmap(5,5) = 10; // CFD using STL
    optionmap(5,6) = 10; // CFD using maps
    optionmap(5,7) = 0; // CFD using surrogate



}









