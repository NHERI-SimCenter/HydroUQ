//*****************************************************************************
// Function to plot bathymetry in Tab 0
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>
#include <../Eigen/Dense>

void MainWindow::plotbathy()
{

    //QTextStream out(stdout);
    //out << "Arrived here-x"<< xmin << "," << xmax << endl;
    //out << "Arrived here-y"<< ymin << "," << ymax << endl;

    // Setup the axis properties
    ui->Bathymetry->axisRect()->setupFullAxesBox(true);
    ui->Bathymetry->xAxis->setTickLabelFont(QFont(QFont().family(), 20));
    ui->Bathymetry->yAxis->setTickLabelFont(QFont(QFont().family(), 20));
    ui->Bathymetry->xAxis->setLabel("x-direction");
    ui->Bathymetry->xAxis->setLabelFont(QFont(QFont().family(), 20));
    ui->Bathymetry->yAxis->setLabel("y-direction");
    ui->Bathymetry->yAxis->setLabelFont(QFont(QFont().family(), 20));

    // Setup the colormap
    QCPColorMap *colorMap = new QCPColorMap(ui->Bathymetry->xAxis, ui->Bathymetry->yAxis);
    colorMap->data()->setSize(nx,ny);
    colorMap->data()->setRange(QCPRange(xmin,xmax), QCPRange(ymin,ymax));

    // Plot and complete
    for (int ii=0; ii<nx; ii++)
        for (int jj=0; jj<ny; jj++)
            colorMap->data()->setCell(ii, jj, Zdata(ii,jj));
    colorMap->setGradient(QCPColorGradient::gpPolar);
    colorMap->rescaleDataRange(true);
    ui->Bathymetry->rescaleAxes();
    ui->Bathymetry->replot();

}
