//*****************************************************************************
// Box to get the current index of the BathType combo box
//*****************************************************************************

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

void MainWindow::on_BathType_currentIndexChanged(int index)
{
    // Index selected if for generation of file
    if(index == 0)
    {
        ui->SelectBathFileBut->setText("Select File");
        ui->SelectBathFileBut->setEnabled(false);
    }
    else if(index == 1)
    {
        ui->SelectBathFileBut->setText("Generate File");
        ui->SelectBathFileBut->setEnabled(true);
    }
    else if(index == 3)
    {
        ui->SelectBathFileBut->setText("Not supported");
        ui->SelectBathFileBut->setEnabled(false);
    }
    else
    {
        ui->SelectBathFileBut->setText("Select File");
        ui->SelectBathFileBut->setEnabled(true);
    }
}
