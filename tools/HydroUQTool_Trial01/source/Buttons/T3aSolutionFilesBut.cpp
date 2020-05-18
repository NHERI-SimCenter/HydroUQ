//*****************************************************************************
// Button to accept solution files
//*****************************************************************************
#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

void MainWindow::on_SolutionFiles_But_clicked()
{
    // Select the files related to the SW solutions
    // Here one can select multiple files
    // The selected files are stored in the String list SWsolutionfilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(defaultdir.toString());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) SWsolutionfilenames = selectfilesdialog.selectedFiles();
}
