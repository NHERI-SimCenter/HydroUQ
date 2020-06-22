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
// For widgets related to Meshing
//*********************************************************************************

//*********************************************************************************
// When combobox related to type of mesh has been changed
//*********************************************************************************
void MainWindow::on_Cmb_EAMeshType_currentIndexChanged(int index)
{
    // Hide / Unhide elements based on mesh options
    if(index == 0) // In-built mesher
    {
        ui->Btn_EA_UploadMesh->hide();
        ui->Lbl_EA_FineH2->show();
        ui->HSl_EA_MeshSize->show();
        ui->Lbl_EA_CoarseMesh->show();
        ui->Lbl_EA_FineMesh->show();
        ui->Lbl_EA_H2Regions->show();
        ui->Tbl_EA_Regions->show();
        ui->Btn_EA_AddRegion->show();
        ui->Btn_EA_RemRegion->show();
    }
    else // Upload mesh / mesh dictionaries
    {
        ui->Btn_EA_UploadMesh->show();
        ui->Lbl_EA_FineH2->hide();
        ui->HSl_EA_MeshSize->hide();
        ui->Lbl_EA_CoarseMesh->hide();
        ui->Lbl_EA_FineMesh->hide();
        ui->Lbl_EA_H2Regions->hide();
        ui->Tbl_EA_Regions->hide();
        ui->Btn_EA_AddRegion->hide();
        ui->Btn_EA_RemRegion->hide();
    }

    // Change name on the button
    if(index == 1)
    {
        ui->Btn_EA_UploadMesh->setText("\nUpload mesh files\n");
    }
    else if(index == 2)
    {
        ui->Btn_EA_UploadMesh->setText("\nUpload mesh dictionary files\n");
    }
}

//*********************************************************************************
// Button to add regions of refinements
//*********************************************************************************
void MainWindow::on_Btn_EA_AddRegion_clicked()
{
    ui->Tbl_EA_Regions->insertRow(ui->Tbl_EA_Regions->rowCount());
}

//*********************************************************************************
// Button to remove regions of refinements
//*********************************************************************************
void MainWindow::on_Btn_EA_RemRegion_clicked()
{

}
