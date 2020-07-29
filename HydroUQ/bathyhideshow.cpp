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
// Hide-Show bathymetry elements
//*********************************************************************************
void MainWindow::BathyHideShow()
{
    // Show-hide elements for wave flume
    if(ui->CmB_AA_SimType->currentIndex() == 4)
    {
        // Set heading
        ui->Lbl_BA_H1->setText("<b>WAVE FLUME SETTINGS</b>");

        // Show wave flume
        ui->Lbl_BA_SideViewH2->show();
        ui->Lbl_BA_SideView->show();
        ui->Lbl_BA_Depth->show();
        ui->DSpBx_BA_Depth->show();
        ui->Lbl_BA_TopViewH2->show();
        ui->Lbl_BA_TopView->show();
        ui->Lbl_BA_Breadth->show();
        ui->DSpBx_BA_Breadth->show();
        ui->Lbl_BA_Segments->show();
        ui->Tbl_BA_Segments->show();
        ui->Btn_BA_AddSeg->show();
        ui->Btn_BA_RemSeg->show();

        // Hide all other elements
        ui->Lbl_BA_SelFiles->hide();
        ui->Btn_BA_SelFiles->hide();
        ui->Btn_BA_UploadSolution->hide();
        ui->CmB_BA_FileType->hide();
        ui->CmB_BA_SolFormat->hide();
        ui->CmB_BA_Library->hide();
        ui->Lbl_BA_Notice->hide();
    }
    else
    {
        // Hide wave flume
        ui->Lbl_BA_SideViewH2->hide();
        ui->Lbl_BA_SideView->hide();
        ui->Lbl_BA_Depth->hide();
        ui->DSpBx_BA_Depth->hide();
        ui->Lbl_BA_TopViewH2->hide();
        ui->Lbl_BA_TopView->hide();
        ui->Lbl_BA_Breadth->hide();
        ui->DSpBx_BA_Breadth->hide();
        ui->Lbl_BA_Segments->hide();
        ui->Tbl_BA_Segments->hide();
        ui->Btn_BA_AddSeg->hide();
        ui->Btn_BA_RemSeg->hide();
    }

    // If STL / Maps / Surrogate - show only notice
    if( ((ui->CmB_AA_SimType->currentIndex() == 5)
            || (ui->CmB_AA_SimType->currentIndex() == 6))
            || (ui->CmB_AA_SimType->currentIndex() == 7))
    {
        // Set heading and notice
        if(ui->CmB_AA_SimType->currentIndex() == 5)
        {
            ui->Lbl_BA_H1->setText("<b>STL/OBJ FILE SETTINGS</b>");
            ui->Lbl_BA_Notice->setText("STL option is not yet available. "
                                       "Watch out for future updates");
        }
        else if(ui->CmB_AA_SimType->currentIndex() == 6)
        {
            ui->Lbl_BA_H1->setText("<b>BATHYMETRY USING MAPS</b>");
            ui->Lbl_BA_Notice->setText("Maps option is not yet available. "
                                       "Watch out for future updates");
        }
        else if(ui->CmB_AA_SimType->currentIndex() == 7)
        {
            ui->Lbl_BA_H1->setText("<b>BATHYMETRY FOR SURROGATE MODELS</b>");
            ui->Lbl_BA_Notice->setText("Surrogate model option is not yet available. "
                                       "Watch out for future updates");
        }

        // Show notice
        ui->Lbl_BA_Notice->show();

        // Hide all other elements
        ui->Lbl_BA_SelFiles->hide();
        ui->Btn_BA_SelFiles->hide();
        ui->Btn_BA_UploadSolution->hide();
        ui->CmB_BA_FileType->hide();
        ui->CmB_BA_SolFormat->hide();
        ui->CmB_BA_Library->hide();
    }
    else
    {
        // Hide the notice
        ui->Lbl_BA_Notice->hide();
    }

    // Show-Hide elements based on type of simulations
    if(ui->CmB_AA_SimType->currentIndex() == 1) //SW solutions
    {
        // Set the heading
        ui->Lbl_BA_H1->setText("<b>BATHYMETRY AND SW SOLUTIONS</b>");

        // Show bathy items
        ui->Btn_BA_SelFiles->show();
        ui->Btn_BA_UploadSolution->show();
        ui->CmB_BA_FileType->show();
        ui->CmB_BA_SolFormat->show();

        // Hide library items
        ui->CmB_BA_Library->hide();
    }
    else if(ui->CmB_AA_SimType->currentIndex() == 2) //Library
    {
        // Set the heading
        ui->Lbl_BA_H1->setText("<b>BATHYMETRY AND SW LIBRRAY</b>");

        // Show library items
        ui->CmB_BA_Library->show();

        // Hide bathy items
        ui->Btn_BA_SelFiles->hide();
        ui->Btn_BA_UploadSolution->hide();
        ui->CmB_BA_FileType->hide();
        ui->CmB_BA_SolFormat->hide();

    }
    else if(ui->CmB_AA_SimType->currentIndex() == 3) // Bathymetry files
    {
        // Set the heading
        ui->Lbl_BA_H1->setText("<b>BATHYMETRY FILE SETTINGS</b>");

        // Show bathy items
        ui->Btn_BA_SelFiles->show();
        ui->CmB_BA_FileType->show();

        // Hide solutions and library items
        ui->Btn_BA_UploadSolution->hide();
        ui->CmB_BA_SolFormat->hide();
        ui->CmB_BA_Library->hide();
    }

}
