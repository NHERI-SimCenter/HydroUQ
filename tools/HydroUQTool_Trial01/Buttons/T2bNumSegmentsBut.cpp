//*****************************************************************************
// Button to set number of segments in the ramp on the flume
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_SegmentsConfBut_clicked()
{
    // Number of buildings
    QString numsegments = ui->Segments_TEdit->toPlainText();
    int numsegs = numsegments.split(" ")[0].toInt();

    // Column headers
    QStringList headers;
    headers << "Length" << "Angle of inclination";

    // Initiate tables
    ui->SegmentsTable->setRowCount(numsegs);
    ui->SegmentsTable->setColumnCount(2);
    ui->SegmentsTable->setHorizontalHeaderLabels(headers);

    // Deactivate this button now
    ui->SegmentsConfBut->setEnabled(false);
}
