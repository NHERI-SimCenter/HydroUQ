//*****************************************************************************
// Button to reset flume geometry
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_GenGeomReset_But_clicked()
{
    // Reset table to zero
    ui->SegmentTable->setEnabled(true);
    ui->SegmentTable->setRowCount(0);

    // Reset breadth & water depth
    ui->B1_TEdit->setEnabled(true);
    ui->B1_TEdit->setText("");
    ui->WaterDepth_TEdit->setEnabled(true);
    ui->WaterDepth_TEdit->setText("");

    // Segments data
    ui->NumSegments_TEdit->setEnabled(true);
    ui->NumSegments_TEdit->setText("");
    ui->SegmentsConf_But->setEnabled(true);
    ui->AddSegment->setEnabled(true);
    ui->RemoveSegment->setEnabled(true);

    // Confirm button
    ui->GenGeomConf_But->setEnabled(true);

}
