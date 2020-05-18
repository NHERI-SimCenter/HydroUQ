//*****************************************************************************
// Button to accept the bathymetric data
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>
#include <../Eigen/Dense>

void MainWindow::on_AcceptBathDataBut_clicked()
{

    // Variables for plotting
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;

    // If the select file is only selected in combobox
    if(ui->BathType->currentIndex() == 0)
    {
        QMessageBox::information(this,"Error!","File format type not selected!");
    }
    // If the type is to generate file ourselves
    else if(ui->BathType->currentIndex() == 1)
    {
        // Generate the file
        // For the wave flume
        // Nothing more to do here
    }
    // If we are using SimCenter format instead
    else if(ui->BathType->currentIndex() == 2)
    {
        // Loop over the entire list
        for(int ii=0; ii<bathfilenames.size(); ii++)
        {

            // Get the individual file name
            QString filename = bathfilenames.at(ii);

            // Send the file to the file reader
            // If non-zero error code is returned
            // Error has been displayed and send code back
            int errorcode = SCBathFileReader(filename);
            // If failed, then stop process
            if(errorcode != 0)
            {
                // Reset to select new file
                ui->BathType->setCurrentIndex(0);
                ui->SelectBathFileBut->setEnabled(true);
                bathfilename = QString();
                bathfilenames = QStringList();
            }
            // Else plot the data
            else
            {
                // Set min and max
                if(ii==0)
                {
                    xmin = xlower;
                    xmax = xlower+dx*nx;
                    ymin = ylower;
                    ymax = ylower+dy*ny;
                }
                else
                {
                    if(xlower<xmin) xmin = xlower;
                    if(xlower+dx*nx>xmax) xmax = xlower+dx*nx;
                    if(ylower<ymin) ymin = ylower;
                    if(ylower+dy*ny>ymax) ymax = ylower+dy*ny;
                }
                // Once limits are set, now plot it
                plotbathy();
            }
        }

        // Activate all elements, if we are through here
        // Then likely all went well
        bathfilenamesSC = bathfilenames;
        ui->Datafile_box->setEnabled(false);
        ui->Interface_box->setEnabled(true);
    }
    else if(ui->BathType->currentIndex() == 3) // Topo type = 1
    {
        // Currently not supported
    }
    else if(ui->BathType->currentIndex() == 4) // Topo type = 2
    {

    }
    else if(ui->BathType->currentIndex() == 5) // Topo type = 3
    {

    }
    else if(ui->BathType->currentIndex() == 6) // STL (only CFD)
    {
        if(bathfilename.toStdString().empty())
        {
            QMessageBox msgbox;
            msgbox.setText("File not selected");
            msgbox.exec();
        }
        else
        {
            ui->Datafile_box->setEnabled(false);
            ui->Tab1Accept->setEnabled(true);
        }
    }



}
