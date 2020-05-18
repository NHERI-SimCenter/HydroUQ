//*****************************************************************************
// Button to set working directory
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>


void MainWindow::on_SetWorkDirBut_clicked()
{
    // Get the working directory
    // QUrl defaultdir("/home/Users");
    defaultdir = QFileDialog::getExistingDirectoryUrl(this, tr("Open Directory"), QUrl("/home/Users"),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // Show the working directory
    //if(defaultdir.toString() == "")
    if(defaultdir.isEmpty())
    {
        ui->WorkDirText->setText("Work directory not initialized");
    }
    else
    {

        // Show the path of the work directory
        ui->WorkDirText->setText(defaultdir.toString());

        // Get the file path as substring
        int leng = defaultdir.toEncoded().toStdString().size();
        defdir = defaultdir.toEncoded().toStdString().substr(7,leng);

        // Create a project file to which items can be later written
        opfilename = defdir+"/"+projname.toStdString()+".proj";
        std::fstream my_stream;
        my_stream.open(opfilename,std::fstream::binary | std::fstream::in | std::fstream::out);

        if(!my_stream)
        {
            //QTextStream out(stdout);
            //out << "Arrived here-x: "<< QString::fromStdString(filename) << endl;
            my_stream.open(opfilename,std::fstream::binary | std::fstream::trunc | std::fstream::out);
            my_stream.close();
            // re-open with original flags
            //my_stream.open(filename,std::fstream::binary | std::fstream::in | std::fstream::out);
            HydroHeader();
            //my_stream.close();
        }
        else
        {
            HydroHeader();
        }

        // Activate the next component: Datafile items
        ui->Datafile_box->setEnabled(true);
        ui->AcceptBathDataBut->setEnabled(false);
        ui->SelectBathFileBut->setEnabled(false);

        // Deactivate the set directory button
        ui->SetWorkDirBut->setEnabled(false);
    }
}

