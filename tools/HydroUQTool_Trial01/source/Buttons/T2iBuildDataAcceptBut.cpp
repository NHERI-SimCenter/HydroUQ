//*****************************************************************************
// Button to confirm building data
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

void MainWindow::on_BuildDataAcceptBut_clicked()
{
    // Read the table and write to file
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Write out some information
    opfiles << "#Building" << "\n";
    for (int ii = 0; ii < ui->BuildDataTable->rowCount(); ++ii)
    {
        if (ii > 0)
            opfiles << '\n';
        for (int jj = 0; jj < ui->BuildDataTable->columnCount(); ++jj)
        {
            QTableWidgetItem *cell = ui->BuildDataTable->item(ii,jj);
            if(jj == ui->BuildDataTable->columnCount()-1)
                opfiles << cell->text().toStdString();
            else
                opfiles << cell->text().toStdString() << ", ";
        }
    }
    opfiles << "\n\n";

    // Disable all items
    ui->BuildDataTable->setEnabled(false);
    ui->NumBuildingsBut->setEnabled(false);
    ui->NumBuildings_TEdit->setEnabled(false);
    ui->AddBuilding->setEnabled(false);
    ui->RemoveBuilding->setEnabled(false);
    ui->BuildDataAcceptBut->setEnabled(false);

    // Move back to interface tab
    ui->Datafile_box->setEnabled(false);
    ui->Interface_box->setEnabled(true);
    ui->HydroTabs->setCurrentIndex(0);


    // Close the files
    opfiles.close();
}
