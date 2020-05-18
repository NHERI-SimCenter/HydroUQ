#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>
#include <QTableWidget>

//*************************************************************
// Start the main window function
//*************************************************************
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Initialize the UI
    ui->setupUi(this);

    // Get a input dialog file to get projectname
    bool ok;
    projname = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Enter Project Name:"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok);
    if (ok && !projname.isEmpty())
        ui->ProjectNameText->setText("Project: " + projname);
    if(projname.isEmpty())
    {
        projname = "Untitled";
        ui->ProjectNameText->setText("Project: " + projname);
    }
    // Style it up
    ui->ProjectNameText->setStyleSheet("font-weight: bold; font-size: 14; color: red");

    //Disable items and activate only after things have been set
    // Datafile, Interface and confirm boxes in first tab
    ui->Datafile_box->setEnabled(false);
    ui->Interface_box->setEnabled(false);
    ui->Tab1Accept->setEnabled(false);
    // Disable other tabs
    ui->GenBathymetry_tab->setEnabled(false);
    ui->bcondition_tab->setEnabled(false);
    ui->cfd_tab->setEnabled(true);
    ui->surrogate_tab->setEnabled(false);

}

//*************************************************************
// Delete the main window function
//*************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

//*************************************************************
// End of mainwindow.cpp
//*************************************************************


void MainWindow::on_GeoDataAccept_clicked()
{

    // Open output file
    std::ofstream opfiles;
    opfiles.open(opfilename,std::fstream::app);

    // Write out to file
    opfiles << "#WindFlume\n";
    opfiles << "b1, " << ui->B1_TEdit->toPlainText().toStdString() << "\n";
    //opfiles << "b2, " << ui->B2_TEdit->toPlainText().toStdString() << "\n";
    //opfiles << "Theta4" << ui->Theta4_TEdit->toPlainText().toStdString() << "\n";

    // Get number of rows in the table and write out the data
    opfiles << "Segments, " << ui->SegmentsTable->rowCount() << "\n";
    for(int ii = 0; ii < ui->SegmentsTable->rowCount(); ++ii)
    {
        for(int jj = 0; jj < ui->SegmentsTable->columnCount(); ++jj)
        {
            QTableWidgetItem *cell = ui->SegmentsTable->item(ii,jj);
            opfiles << cell->text().toStdString();
        }
        //int jj = 0;
        //QTableWidgetItem *item = ui->SegmentsTable->item(ii, jj);

        //opfiles << "Se"
    }
    //int count = ;
    //std::cout << "Number of segments = " << count;

}
