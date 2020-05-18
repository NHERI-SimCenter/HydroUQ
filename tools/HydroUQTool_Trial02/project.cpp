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
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <string>

//*********************************************************************************
// What when project settings are accepted
//*********************************************************************************
void MainWindow::on_ProjAccept_clicked()
{

    // Setup the project name
    projname = ui->ProjNameTEdit->toPlainText();
    if(projname.isEmpty())
    {
        projname = "Untitled";
    }
    ui->ProjectName->setText(projname);

    // Setup the project description
    projdesc = ui->ProjDescTEdit->toPlainText();
    if(projdesc.isEmpty())
    {
        projdesc = "No description has been specified for this project";
    }
    ui->ProjectDesc->setText(projdesc);

    // Get the simulation type
    int simtype = ui->ProjSimType->currentIndex();
    int turbtype = ui->ProjTurbType->currentIndex();
    if(simtype == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Simulation type not set. Cannot proceed without it.");
        msgBox.exec();
    }
    else
    {
        // Update checkboxes on  status page
        ui->ProjCheckBox->setCheckable(true);
        ui->ProjCheckBox->setChecked(true);
        ui->ProjCheckBox->setEnabled(false);

        // Update buildings on status page
        if(!((simtype == 3) || (simtype == 4)))
        {
            ui->BuildingBox->setCheckable(true);
            ui->BuildingBox->setChecked(true);
            ui->BuildingBox->setEnabled(false);
        }

        // Update former simtype
        formersimtype = simtype;
        // Update former turbulence type
        formerturbtype = turbtype;
        // Go to status page
        ui->stackedWidget->setCurrentIndex(0);
    }
}

//*********************************************************************************
// What when project settings are cancelled
//*********************************************************************************
void MainWindow::on_ProjCancel_clicked()
{
    // Set the work directory back to former
    defaultdir = formerdefaultdir;
    setWorkDirText();

    // Reset project name
    ui->ProjNameTEdit->setPlainText(projname);

    // Reset project description
    ui->ProjDescTEdit->setPlainText(projdesc);

    // Change the simulation type combobox
    ui->ProjSimType->setCurrentIndex(formersimtype);

    // Change the turbulence type combobox
    ui->ProjTurbType->setCurrentIndex(formerturbtype);

    // Go back to status page
    ui->stackedWidget->setCurrentIndex(0);
}

//*********************************************************************************
// What happens work directory is selected
//*********************************************************************************
void MainWindow::on_WorkDirBut_clicked()
{
    // Set the former default dir
    formerdefaultdir = defaultdir;

    // Get the working directory
    defaultdir = QFileDialog::getExistingDirectoryUrl(this, tr("Open Directory"), QUrl("/home/Users"),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // Show the path of workign directory
    if(defaultdir.isEmpty())
    {
        ui->WorkDirBut->setText("Work directory \n not initialized");
    }
    else
    {
        setWorkDirText();
    }
}

//*********************************************************************************
// Set text for work dir button
//*********************************************************************************
void MainWindow::setWorkDirText()
{
    // Get the size of the path to see if it fits in the button
    // Else split it and write it
    QFont font = ui->WorkDirBut->property("font").value<QFont>();
    QFont myFont(font.family(), font.pointSize());
    QString str(defaultdir.toString());
    QFontMetrics fm(myFont);
    int width = fm.horizontalAdvance(str);
    if(width < 195)
    {
        // Show the path of the work directory
        ui->WorkDirBut->setText(defaultdir.toString());
    }
    else if(width > 195)
    {
        // Add a newline character after half of the characters
        int pathsize = defaultdir.toString().toStdString().size();
        std::string word = defaultdir.toString().toStdString().insert(0.5*pathsize,"\n");
        ui->WorkDirBut->setText(QString::fromStdString(word));
    }
}
