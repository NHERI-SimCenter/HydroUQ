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
// In this routines related to all parts of tree on LHS
//*********************************************************************************

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"

//*********************************************************************************
// Open relevant stack related to the particular item on the parameter tree
//*********************************************************************************
void MainWindow::on_SimOptions_itemClicked(QTreeWidgetItem *item, int column)
{
    // Get the string of hte selected item
    QString sel = item->text(column);

    // Get the index of the simulation type
    int simtypeindex = ui->CmB_AA_SimType->currentIndex();

    // Change stack to the relevant page index
    if(optiontree.indexOf(sel) != -1)
    {
        if(ui->OptionsStack->currentIndex() != optionmap(optiontree.indexOf(sel),simtypeindex))
            ui->OptionsStack->setCurrentIndex(optionmap(optiontree.indexOf(sel),simtypeindex));
    }

}

//*********************************************************************************
// What happens if we double click on the tree
//*********************************************************************************
void MainWindow::on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    QString sel = item->text(column);
    if((sel == "Create project") && (treeflag == 1))
    {
        // Create a dialog to get the project name
        bool ok;
        projname = QInputDialog::getText(this, tr("Create new project"),
                                                tr("Project name"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok);
        if (ok && !projname.isEmpty())
            ui->Lbl_ProjTitle->setText(projname);

        // Add children
        //addTreeChild(item, projname);

        // Create project tree
        QTreeWidgetItem *project = new QTreeWidgetItem(item, QStringList() << projname);

        // Create geometry
        QTreeWidgetItem *geometry = new QTreeWidgetItem(project, QStringList() << "Geometry");
        //QTreeWidgetItem *bathymetry = new QTreeWidgetItem(geometry, QStringList() << "Bathymetry");
        new QTreeWidgetItem(geometry, QStringList() << "Bathymetry");
        new QTreeWidgetItem(geometry, QStringList() << "SW-CFD interface");
        new QTreeWidgetItem(geometry, QStringList() << "Buildings");
        new QTreeWidgetItem(geometry, QStringList() << "Floating bodies");
        new QTreeWidgetItem(project, QStringList() << "Materials");
        QTreeWidgetItem *inicondition = new QTreeWidgetItem(project, QStringList() << "Initial condition");
        new QTreeWidgetItem(inicondition, QStringList() << "Velocity");
        new QTreeWidgetItem(inicondition, QStringList() << "Pressure");
        new QTreeWidgetItem(inicondition, QStringList() << "Phase");
        QTreeWidgetItem *boundarycondition = new QTreeWidgetItem(project, QStringList() << "Boundary condition");
        new QTreeWidgetItem(boundarycondition, QStringList() << "Velocity");
        new QTreeWidgetItem(boundarycondition, QStringList() << "Pressure");
        new QTreeWidgetItem(boundarycondition, QStringList() << "Phase");
        QTreeWidgetItem *solver = new QTreeWidgetItem(project, QStringList() << "Solvers");
        new QTreeWidgetItem(solver, QStringList() << "Basic");
        new QTreeWidgetItem(solver, QStringList() << "Advanced");
        new QTreeWidgetItem(project, QStringList() << "Create jobs");
        //QTreeWidgetItem *tacc = new QTreeWidgetItem(project, QStringList() << "Create jobs");

        // For now disable to not allow multiple project creation
        treeflag = -1;
    }
    else if(sel == "Create jobs")
    {
        QTreeWidgetItem *jobname = new QTreeWidgetItem(item, QStringList() << "trialjob");
    }
}
