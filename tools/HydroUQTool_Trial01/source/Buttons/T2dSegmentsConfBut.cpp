//*****************************************************************************
// Button to set number of segments
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_SegmentsConf_But_clicked()
{
    // Get the number of segments and create the table
    // Number of buildings
    QString numsegment = ui->NumSegments_TEdit->toPlainText();
    int numsegs = numsegment.split(" ")[0].toInt();

    // Column headers
    QStringList headers;
    headers << "Length" << "Angle of inclination";

    // Initiate tables
    ui->SegmentTable->setRowCount(numsegs);
    ui->SegmentTable->setColumnCount(2);
    ui->SegmentTable->setHorizontalHeaderLabels(headers);

    // Deactivate this button now
    ui->SegmentsConf_But->setEnabled(false);

    // Activate buttons
    ui->AddSegment->setEnabled(true);
    ui->RemoveSegment->setEnabled(true);

}
