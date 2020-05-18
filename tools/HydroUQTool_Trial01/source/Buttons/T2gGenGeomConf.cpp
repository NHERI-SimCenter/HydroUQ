//*****************************************************************************
// Button to confirm flume geometry
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>

void MainWindow::on_GenGeomConf_But_clicked()
{

    std::cout << "Arrived to here" << std::endl;

    // Read the table and write to file
    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Write out some information
    opfiles << "#WalveFlume" << "\n";
    opfiles << "Breadth1, " << ui->B1_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "WaterDepth, " << ui->WaterDepth_TEdit->toPlainText().toStdString() << "\n";
    opfiles << "Segments, " << ui->NumSegments_TEdit->toPlainText().toStdString() << "\n";

    if((ui->SegmentTable->rowCount() > 0) && (ui->SegmentTable->columnCount() > 0))
    {
        for (int ii = 0; ii < ui->SegmentTable->rowCount(); ++ii)
        {
            for (int jj = 0; jj < ui->SegmentTable->columnCount(); ++jj)
            {
                QTableWidgetItem *cell = ui->SegmentTable->item(ii,jj);
                if(jj == ui->SegmentTable->columnCount()-1)
                    opfiles << cell->text().toStdString() << "\n";
                else
                    opfiles << cell->text().toStdString() << ", ";
            }
        }
    }
    opfiles << "\n";

    // Disable all items
    ui->B1_TEdit->setEnabled(false);
    ui->WaterDepth_TEdit->setEnabled(false);
    ui->NumSegments_TEdit->setEnabled(false);
    ui->SegmentsConf_But->setEnabled(false);
    ui->AddSegment->setEnabled(false);
    ui->RemoveSegment->setEnabled(false);
    ui->SegmentTable->setEnabled(false);
    ui->GenGeomConf_But->setEnabled(false);

    // Enable some items
    ui->BuildDataAcceptBut->setEnabled(true);

    // Close the files
    opfiles.close();

}
