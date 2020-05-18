//*****************************************************************************
// Button to confirm time settings
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

void MainWindow::on_TimeSetConf_But_clicked()
{
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Get the index
    int ind = ui->TimeType->currentIndex();

    // Write out to file
    opfiles << "#TimeSettings\n";
    if(ind == 0) opfiles << "Adaptive\n";

    opfiles << "StartTime, " << ui->StartTime_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "EndTime, " << ui->EndTime_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "TimeInterval, " << ui->TimeInt_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "WriteInterval, " << ui->WriteInt_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "\n";

    // Close files
    opfiles.close();

    // Deactivate the button
    ui->TimeSetConf_But->setEnabled(false);
    ui->TimeType->setEnabled(false);
    ui->StartTime_TEdit->setEnabled(false);
    ui->EndTime_TEdit->setEnabled(false);
    ui->TimeInt_TEdit->setEnabled(false);
    ui->WriteInt_TEdit->setEnabled(false);
}
