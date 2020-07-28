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
#include "interfaceframe.h"

//*********************************************************************************
// Open relevant stack related to the particular item on the parameter tree
//*********************************************************************************
void MainWindow::on_SimOptions_itemClicked(QTreeWidgetItem *item, int column)
{

    // Get the string of hte selected item
    QString sel = item->text(column);

    // Get the index of the simulation type
    int simtypeindex = ui->CmB_AA_SimType->currentIndex();

    // If no simulation type is selected go to project page
    if(simtypeindex == 0)
    {
        ui->OptionsStack->setCurrentIndex(0);
    }
    else
    {
        // If there is a page available
        if(optiontree.indexOf(sel) != -1)
        {
            if(ui->OptionsStack->currentIndex() != optionmap(optiontree.indexOf(sel),0))
                ui->OptionsStack->setCurrentIndex(optionmap(optiontree.indexOf(sel),0));
        }
    }
}

//*********************************************************************************
// What happens if we double click on the tree
//*********************************************************************************
void MainWindow::on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    // Get the item double clicked on
    QString sel = item->text(column);

    // To create an initial tree
    if((sel == "Create project") && (treeflag == 1))
    {
        // Create a dialog to get the project name
        bool ok;
        projname = QInputDialog::getText(this, tr("Create new project"),
                                                tr("Project name"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok);
        // If OK is pressed, set the project name
        if (ok && !projname.isEmpty())
        {
            ui->Lbl_ProjTitle->setText(projname);
            ui->Led_AA_PName->setText(projname);
        }
        if (projname.isEmpty())
        {
            ui->Lbl_ProjTitle->setText("Untitled");
            ui->Led_AA_PName->setText("Untitled");
        }

        // Create project tree
        QTreeWidgetItem *project = new QTreeWidgetItem(item, QStringList() << projname);

        // Replace the first option in optiontree with Project name
        optiontree[0] = projname;

        // Create the tree
        QTreeWidgetItem *geometry = new QTreeWidgetItem(project, QStringList() << "Geometry");
        //QTreeWidgetItem *bathymetry = new QTreeWidgetItem(geometry, QStringList() << "Bathymetry");
        new QTreeWidgetItem(geometry, QStringList() << "Bathymetry");
        new QTreeWidgetItem(geometry, QStringList() << "SW-CFD interface");
        new QTreeWidgetItem(geometry, QStringList() << "Buildings");
        new QTreeWidgetItem(geometry, QStringList() << "Floating bodies");
        new QTreeWidgetItem(project, QStringList() << "Meshing");
        new QTreeWidgetItem(project, QStringList() << "Materials");
        QTreeWidgetItem *inicondition = new QTreeWidgetItem(project, QStringList() << "Initial conditions");
        new QTreeWidgetItem(inicondition, QStringList() << "Velocity (IC)");
        new QTreeWidgetItem(inicondition, QStringList() << "Pressure (IC)");
        new QTreeWidgetItem(inicondition, QStringList() << "Phase (IC)");
        QTreeWidgetItem *boundarycondition = new QTreeWidgetItem(project, QStringList() << "Boundary conditions");
        new QTreeWidgetItem(boundarycondition, QStringList() << "Velocity (BC)");
        new QTreeWidgetItem(boundarycondition, QStringList() << "Pressure (BC)");
        new QTreeWidgetItem(boundarycondition, QStringList() << "Phase (BC)");
        QTreeWidgetItem *solver = new QTreeWidgetItem(project, QStringList() << "Solvers");
        new QTreeWidgetItem(solver, QStringList() << "Basic");
        new QTreeWidgetItem(solver, QStringList() << "Advanced");
        new QTreeWidgetItem(project, QStringList() << "Submit to TACC");
        //QTreeWidgetItem *tacc = new QTreeWidgetItem(project, QStringList() << "Create jobs");

        // For now disable to not allow multiple project creation
        treeflag = -1;
    }
    // To create SW-CFD Interface
    else if(sel == "SW-CFD interface")
    {

        bool ok;
        QString intername = QInputDialog::getText(this, tr("Interface Label"),
                                                tr("Interface name"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok);
        if (ok && !intername.isEmpty())
        {
            int internum = ui->SWg_BB_Interface->count();
            //ui->SWg_BB_Interface->insertWidget(internum,new InterfaceFrame(intername));
            ui->SWg_BB_Interface->addWidget(new InterfaceFrame(intername));
            ui->SWg_BB_Interface->setCurrentIndex(internum);
        }
        else
        {
            int internum = ui->SWg_BB_Interface->count();
            QString temp = intername + QString::number(internum);
            //ui->SWg_BB_Interface->insertWidget(internum,new InterfaceFrame(intername));
            ui->SWg_BB_Interface->addWidget(new InterfaceFrame(intername));
            ui->SWg_BB_Interface->setCurrentIndex(internum);
            qDebug() << "Count is: " << internum-1;
        }


    }
    else if(sel == "Boundary conditions")
    {
        qDebug() << "Clicked BC";
    }
    else if(sel == "Submit to TACC")
    {
        // Create a dialog to get the job name
        bool ok;
        QString TACCjobname = QInputDialog::getText(this, tr("Create new project"),
                                                tr("Project name"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok);
        if (ok && !projname.isEmpty())
            ui->Lbl_ProjTitle->setText(TACCjobname);

        new QTreeWidgetItem(item, QStringList() << TACCjobname);
        //QTreeWidgetItem *jobname = new QTreeWidgetItem(item, QStringList() << TACCjobname);
    }
}
