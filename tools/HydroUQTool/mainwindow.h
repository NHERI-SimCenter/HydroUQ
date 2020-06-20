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
#include "../Eigen/Dense"

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::string gettoolname();

protected:
    //std::string toolname = "H20-UQ";

private slots:

    // Item tree on left
    void on_SimOptions_itemClicked(QTreeWidgetItem *item, int column);

    // Options stack
    void on_OptionsStack_currentChanged(int arg1);

    // Project settings
    void on_Led_AA_PName_editingFinished();
    void on_Led_AA_PDesc_textChanged();
    void on_Btn_AA_WDir_clicked();

    // Bathymetry
    void on_ChB_BA_UploadBox_stateChanged(int arg1);
    void on_Btn_BA_UploadFile_clicked();

    void on_Btn_BA_S02AddPt_clicked();

    void on_Btn_BA_S02RemPt_clicked();



    void on_ChB_BB_UploadFile_stateChanged(int arg1);

    void on_Btn_BB_UploadFile_clicked();

    void on_Btn_BB_S02AddPt_clicked();

    void on_Btn_BB_S02RemPt_clicked();

private:

    // Initialize
    void initialize();

    Ui::MainWindow *ui;
    Eigen::MatrixXi optionmap; // Connects parameter tree to options widget
    std::string toolname = "H20-UQ";
    QUrl workdirUrl; // Default work directory
    QStringList optiontree,bathfilenames; // Bathymetry filenames



};
#endif // MAINWINDOW_H
