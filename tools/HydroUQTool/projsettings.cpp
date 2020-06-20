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
// When button clicked to get default directory
//*********************************************************************************
void MainWindow::on_Btn_AA_WDir_clicked()
{
    // Open a file dialog and get work directory
    workdirUrl = QFileDialog::getExistingDirectoryUrl(this, tr("Open Directory"), QUrl("/home/Users"),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString workdir = workdirUrl.toString();

    // If the workdir is not empty or not, set the text accordingly
    if(workdir.isEmpty())
    {
        ui->Btn_AA_WDir->setText("\nSet working directory (Not set)\n");
    }
    else
    {
        ui->Btn_AA_WDir->setText("\nSet working directory (Set)\n");
    }
}

//*********************************************************************************
// Setup the project name
//*********************************************************************************
void MainWindow::on_Led_AA_PName_editingFinished()
{
    QString data = ui->Led_AA_PName->text();
    ui->Lbl_ProjTitle->setText(data);
}

//*********************************************************************************
// Setup the project description
//*********************************************************************************
void MainWindow::on_Led_AA_PDesc_textChanged()
{
    QString data = ui->Led_AA_PDesc->toPlainText();
    ui->Lbl_ProjDesc->setText(data);
}
