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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "dependencies/Eigen/Dense"
#include "dependencies/rapidjson/document.h"
#include "dependencies/rapidjson/prettywriter.h"

//*********************************************************************************
// Include library headers
//*********************************************************************************
#include <QMainWindow>
#include <QTreeWidget>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QInputDialog>
#include <QStackedWidget>
#include <fstream>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    std::string toolname = "H20-UQ";
    std::string version = "0.1";
    std::string developer = "SimCenter, UC Berkeley (USA)";

private slots:

    // Item tree on left
    void on_SimOptions_itemClicked(QTreeWidgetItem *item, int column);

    // Options stack
    void on_OptionsStack_currentChanged(int arg1);

    // Project settings
    void on_Led_AA_PName_editingFinished();
    void on_Led_AA_PDesc_textChanged();
    void on_Btn_AA_WDir_clicked();

    // Bathymetry (SW solutions)
    void on_Btn_BA_SelFiles_clicked();
    void on_Btn_BA_UploadSolution_clicked();

    // Building
    void on_Btn_CA_AddBuild_clicked();
    void on_Btn_CA_RemBuild_clicked();

    // Meshing
    void on_Cmb_EAMeshType_currentIndexChanged(int index);
    void on_Btn_EA_UploadMesh_clicked();
    void on_Btn_EA_AddRegion_clicked();
    void on_Btn_EA_RemRegion_clicked();

    // Initial conditions
    void on_Btn_GA_AddRegion_clicked();
    void on_Btn_GA_RemRegion_clicked();

    // Boundary conditions - user bathymetry
    void on_SWg_HB_BConditions_currentChanged(int arg1);
    void on_Btn_HB_NorthUploadFile_clicked();
    void on_Btn_HB_SouthUploadFile_clicked();
    void on_Btn_HB_EastUploadFile_clicked();
    void on_Btn_HB_WestUploadFile_clicked();
    void on_Btn_HB_Previous_clicked();
    void on_Btn_HB_Next_clicked();
    void on_Cmb_HB_NorthVelBC_currentIndexChanged(int index);
    void on_Cmb_HB_SouthUBC_currentIndexChanged(int index);
    void on_Cmb_HB_EastUBC_currentIndexChanged(int index);
    void on_Cmb_HB_WestUBC_currentIndexChanged(int index);
    void on_Cmb_HB_NorthPresBC_currentIndexChanged(int index);
    void on_Cmb_HB_SouthPresBC_currentIndexChanged(int index);
    void on_Cmb_HB_EastPresBC_currentIndexChanged(int index);
    void on_Cmb_HB_WestPresBC_currentIndexChanged(int index);

    // Boundary conditions - Wave flume
    void on_SWg_HC_BConditions_currentChanged(int arg1);
    void on_Btn_HC_EntryUploadFile_clicked();
    void on_Btn_HC_ExitUploadFile_clicked();
    void on_Btn_HC_Previous_clicked();
    void on_Btn_HC_Next_clicked();
    void on_Cmb_HC_EntryUBC_currentIndexChanged(int index);
    void on_Cmb_HC_EntryPresBC_currentIndexChanged(int index);
    void on_Cmb_HC_ExitUBC_currentIndexChanged(int index);
    void on_Cmb_HC_ExitPresBC_currentIndexChanged(int index);

    // Solver
    void on_ChB_IA_Restart_stateChanged(int arg1);
    void on_Btn_IA_UploadFiles_clicked();

    // File generation
    void on_Btn_JA_GenFiles_clicked();
    void genJsonRJ();
    void genJsonQT(QJsonDocument doc);

    // Click item in the table
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Btn_BB_Next_clicked();

    void on_Btn_BB_Previous_clicked();

    void on_SWg_BB_Interface_currentChanged(int arg1);

private:

    // Initialize
    void initialize();

    Ui::MainWindow *ui;
    Eigen::MatrixXi optionmap; // Connects parameter tree to options widget
    int treeflag;
    QString projname;
    QUrl workdirUrl; // Default work directory

    QStringList interfacenames;

    QStringList optiontree,bathfilenames,solfilenames,intefilenames,restartfiles,meshfiles; // Filenames
    QStringList boundfiles01,boundfiles02,boundfiles03,boundfiles04;

    int boundaryCount;


};
#endif // MAINWINDOW_H
