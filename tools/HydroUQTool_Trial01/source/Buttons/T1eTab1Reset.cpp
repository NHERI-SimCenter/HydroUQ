//*****************************************************************************
// Button to reset tab 01
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

void MainWindow::on_Tab1Reset_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("You would like to reset the data?");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    switch (ret)
    {
        // Discard was clicked
        case QMessageBox::Yes:
            // Set values to null
            defaultdir = QUrl();
            bathfilename = QString();
            bathfilenames = QStringList();
            nx = 0; ny = 0;
            dx = 0; dy = 0; xlower =0; ylower = 0;
            nodatavalue = 0;
            xmin = 0; xmax = 0; ymin = 0; ymax = 0;
            errorcode = 0;
            Zdata = Eigen::MatrixXd();
            Xdata = Eigen::VectorXd(); Ydata = Eigen::VectorXd();

            // Set the dir text
            ui->WorkDirText->setText("Not set");

            // Enable boxes
            ui->WorkDir_box->setEnabled(true);
            ui->SetWorkDirBut->setEnabled(true);

            // Disable boxes
            ui->Interface_box->setEnabled(false);
            ui->Datafile_box->setEnabled(false);

            // Reset combo boxes
            ui->BathType->setCurrentIndex(0);
            ui->Interface_type->setCurrentIndex(0);

            // Reset the text
            ui->Slope_textEdit->setText("");
            ui->Intercept_textEdit->setText("");

            // Reset the plot
            ui->Bathymetry->axisRect()->setupFullAxesBox(true);
            ui->Bathymetry->clearPlottables();

            break;

    case QMessageBox::No:
        // Do nothing
        break;
    }
}
