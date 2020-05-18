//*****************************************************************************
// To read individual bath file given in SimCenter format
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include "../Eigen/Dense"
#include <iostream>
#include <fstream>
#include <QTextStream>

int MainWindow::SCBathFileReader(QString filename)
{
    // Create a filestream
    std::ifstream bathfilest(filename.toStdString());

    // Check if it opens, else issue an errorcode
    if(bathfilest.is_open())
    {
        // Get the number of points
        bathfilest >> nx >> ny;

        // If these are <1, then we need to give an error message
        if((nx<1)||(ny<1))
        {
            QMessageBox msgbox;
            msgbox.setText("Number of points are given as zero or less in file " + filename + ". Please re-select file!");
            msgbox.exec();
            return 902;
        }
        // Else we will read the file and store them into variables
        else
        {
            // Get the data for dx and dy
            bathfilest >> dx >> dy;
            bathfilest >> xlower >> ylower;
            bathfilest >> nodatavalue;

            // Resize the arrays
            Xdata.resize(nx);
            Ydata.resize(ny);
            Zdata.resize(nx,ny);

            // Loop over all the data to get the data
            for(int ii=0; ii<nx; ii++)
            {
                for(int jj=0; jj<ny; jj++)
                {
                    // If End of file is reached before reading all points
                    // Note here that there is no check added for chekcing if there was an empty line
                    // Empty line will be considered as an input given
                    if(bathfilest.eof())
                    {
                        // If number of points is less than specified, terminate the process
                        QMessageBox msgbox;
                        msgbox.setText("Number of points is less than specified in file " + filename + ". Please re-select file!");
                        msgbox.exec();
                        return 902;
                    }
                    else bathfilest >> Zdata(ii,jj);
                }
            }
        }

    }
    else
    {
        // If file does not open, send error and stop
        QMessageBox msgbox;
        QString errmsg = "Cannot open bathymetry file: " + filename + "Please re-select files";
        msgbox.setText(errmsg);
        msgbox.exec();
        return 901;
    }

    // If all goes well return 0
    return 0;
}
