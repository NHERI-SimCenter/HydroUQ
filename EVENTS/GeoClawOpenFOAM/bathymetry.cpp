#include "bathymetry.h"
#include "ui_bathymetry.h"

//*********************************************************************************
// Bathymetry settings
//*********************************************************************************
bathymetry::bathymetry(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::bathymetry)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete Bathymetry settings
//*********************************************************************************
bathymetry::~bathymetry()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void bathymetry::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void bathymetry::hideshowelems(int type)
{
    // Hide extra elements
    ui->Lbl_H1->hide();
    ui->CmB_FlumeGeoType->hide();
    ui->Lbl_SelFiles->hide();
    ui->Btn_UploadFiles->hide();
    ui->Btn_UploadSolution->hide();
    ui->PText_Files->hide();
    ui->PText_Solution->hide();
    ui->CmB_FileType->hide();
    ui->CmB_SolFormat->hide();
    ui->Lbl_Gravity->hide();
    ui->CmB_Grav01->hide();
    ui->CmB_Grav02->hide();
    ui->CmB_Library->hide();
    ui->Lbl_Notice->hide();
    ui->Lbl_TopViewH2->hide();
    ui->Lbl_TopView->hide();
    ui->Lbl_Breadth->hide();
    ui->DSpBx_Breadth->hide();
    ui->Lbl_Segments->hide();
    ui->Tbl_Segments->hide();
    ui->Btn_AddSeg->hide();
    ui->Btn_RemSeg->hide();

    // Show-Hide elements based on type of simulations
    // SW resolved with CFD
    if(type == 1) //SW solutions
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY AND SW SOLUTIONS</b>");
        ui->Lbl_H1->show();
        ui->Btn_UploadFiles->setText("Select bathymetry");
        ui->PText_Files->show();
        ui->Btn_UploadSolution->setText("Select solution");
        ui->PText_Solution->show();

        // Show bathy items
        ui->Btn_UploadFiles->show();
        ui->Btn_UploadSolution->show();
        ui->CmB_FileType->show();
        ui->CmB_SolFormat->show();

        // Show gravity
        ui->Lbl_Gravity->show();
        ui->CmB_Grav01->show();
        ui->CmB_Grav02->show();
    }

    // Bathymetry files only
    if(type == 2)
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY FILE SETTINGS</b>");
        ui->Lbl_H1->show();
        // Show bathy items
        ui->Btn_UploadFiles->setText("Select bathymetry");
        ui->PText_Files->show();
        ui->Btn_UploadFiles->show();
        ui->CmB_FileType->show();

        // Show gravity
        ui->Lbl_Gravity->show();
        ui->CmB_Grav01->show();
        ui->CmB_Grav02->show();
    }

    // STL files only
    if(type == 3)
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>STL FILE UPLOAD</b>");
        ui->Lbl_H1->show();
        ui->Btn_UploadFiles->setText("Select STL files");
        ui->Btn_UploadFiles->show();
        ui->PText_Files->show();
        ui->Lbl_Notice->setText("Check documentation to prepare files correctly.");
        ui->Lbl_Notice->show();
        // Show gravity
        ui->Lbl_Gravity->show();
        ui->CmB_Grav01->show();
        ui->CmB_Grav02->show();
    }

    // Wave flume digital twin
    if(type == 4)
    {
        // Set heading
        ui->Lbl_H1->setText("<b>WAVE FLUME SETTINGS</b>");
        ui->Lbl_H1->show();

        // Show wave flume types
        ui->CmB_FlumeGeoType->show();

        // Show elements for each type of flume definition
        // Provide coordinates
        if(ui->CmB_FlumeGeoType->currentIndex() == 0)
        {
            ui->Lbl_TopViewH2->show();
            ui->Lbl_TopView->show();
            ui->Lbl_Breadth->show();
            ui->DSpBx_Breadth->show();
            ui->Lbl_Segments->show();
            ui->Tbl_Segments->show();
            ui->Btn_AddSeg->show();
            ui->Btn_RemSeg->show();
        }

        // Standard OSU flume
        else if(ui->CmB_FlumeGeoType->currentIndex() == 1)
        {
            ui->Lbl_Notice->setText("Standard flume geometry will be used. Please check documentation for more details.");
            ui->Lbl_Notice->show();
        }
    }
}

//*********************************************************************************
// Get data from bathymetry
//*********************************************************************************
bool bathymetry::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=true;

    // Add the gravity direction
    int gravity = 0;
    if(ui->CmB_Grav01->currentIndex() == 0)
    {
        if(ui->CmB_Grav02->currentIndex() == 0)
            gravity = 11;
        else if(ui->CmB_Grav02->currentIndex() == 1)
            gravity = 12;
        else if(ui->CmB_Grav02->currentIndex() == 2)
            gravity = 13;
    }
    else if(ui->CmB_Grav01->currentIndex() == 1)
    {
        if(ui->CmB_Grav02->currentIndex() == 0)
            gravity = 21;
        else if(ui->CmB_Grav02->currentIndex() == 1)
            gravity = 22;
        else if(ui->CmB_Grav02->currentIndex() == 2)
            gravity = 23;
    }
    map.insert("Gravity",QString::number(gravity));

    // Shallow water bathymetry files
    if((type == 1) || (type == 2))
    {
        // Type of bathymetry
        map.insert("BathymetryFileType",QString::number(ui->CmB_FileType->currentIndex()));
        // Number of bathymetry files
        map.insert("NumBathymetryFiles",QString::number(bathfilenames.size()));
        // Write the bathymetry file names
        for (int ii=0; ii<bathfilenames.size(); ++ii)
        {
            QFile f(bathfilenames[ii]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("BathymetryFile"+QString::number(ii),filename);
        }
    }

    // Shallow water solutions
    if(type == 1)
    {
        map.insert("NumSolutionFiles",QString::number(solfilenames.size()));
        // Write the solution file names
        for (int ii=0; ii<solfilenames.size(); ++ii)
        {
            QFile f(solfilenames[ii]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("SWSolutionFile"+QString::number(ii),filename);
        }
        // Type of solution file
        map.insert("SolutionFileType",QString::number(ui->CmB_SolFormat->currentIndex()));
    }

    // STL file
    if(type == 3)
    {
        // Write the STL file names
        for (int ii=0; ii<6; ++ii)
        {
            QFile f(bathfilenames[ii]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("STLFiles"+QString::number(ii),filename);
        }
    }

    // Wave flume
    if(type == 4)
    {
        // Add flume info type to the map
        map.insert("FlumeInfoType",QString::number(ui->CmB_FlumeGeoType->currentIndex()));

        // If coordinates are specified
        if(ui->CmB_FlumeGeoType->currentIndex() == 0)
        {
            // Add flume breadth
            if(abs(ui->DSpBx_Breadth->value()) < 0.000001)
            {
                error.criterrormessage("Critical error: Flume breadth almost zero!");
                return false;
            }
            else
            {
                map.insert("FlumeBreadth",ui->DSpBx_Breadth->textFromValue(ui->DSpBx_Breadth->value()));
            }

            // Adding segment data directly to json file
            map.insert("NumFlumeSegments",QString::number(ui->Tbl_Segments->rowCount()));
            if(ui->Tbl_Segments->rowCount() > 0)
            {
                QString segdata = QString::number(ui->Tbl_Segments->rowCount());
                for(int ii=0;ii<ui->Tbl_Segments->rowCount(); ++ii)
                {
                    segdata = segdata + "," + ui->Tbl_Segments->item(ii,0)->text() +
                            "," + ui->Tbl_Segments->item(ii,1)->text();
                }
                map.insert("FlumeSegments",segdata);
            }
        }
    }

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Put data into bathymetry from the JSON file
//*********************************************************************************
bool bathymetry::putData(QJsonObject &jsonObject)
{

    // Get the simulation type
    if(jsonObject.contains("SimulationType"))
    {
        int stype = jsonObject["SimulationType"].toString().toInt();

        // SW - CFD simulation
        if( (stype == 1) || (stype == 3) )
        {

            // Bathymetry file type
            if(jsonObject.contains("BathymetryFileType"))
            {
                ui->CmB_FileType->setCurrentIndex(jsonObject["BathymetryFileType"].toString().toInt());
            }

            // Get the bathymetry file paths
            bathfilenames.clear();
            QMessageBox msgBox;
            msgBox.setText("File path to the bathymetry needs to be updated.");
            msgBox.setInformativeText("Select files?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();

            switch (ret)
            {
                case QMessageBox::Ok:
                {
                    bathfilenames.clear();
                    // Select the bathymetry files
                    QFileDialog selectfilesdialog(this);
                    selectfilesdialog.setDirectory(QDir::homePath());
                    selectfilesdialog.setFileMode(QFileDialog::ExistingFile);
                    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
                    selectfilesdialog.setWindowTitle("Select the bathymetry files");
                    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
                    // Show the file list in the plaintext
                    QString data;
                    data = QString();
                    for (int ii = 0; ii<bathfilenames.size(); ++ii)
                    {
                        if(ii == 0)
                            data = bathfilenames[ii] + "\n";
                        else
                            data = data + bathfilenames[ii] + "\n";
                    }
                    ui->PText_Files->document()->setPlainText(data);
                    break;
                }
                case QMessageBox::Cancel:
                {
                    bathfilenames.clear();
                    ui->PText_Files->clear();
                    break;
                }
                default:
                {
                    bathfilenames.clear();
                    ui->PText_Files->clear();
                    break;
                }
            }

            if(stype == 1)
            {
                // Solution file type
                if(jsonObject.contains("SolutionFileType"))
                {
                    ui->CmB_SolFormat->setCurrentIndex(jsonObject["SolutionFileType"].toString().toInt());
                }

                // Get paths to solution files from the user
                solfilenames.clear();
                QMessageBox msgBox2;
                msgBox2.setText("File path to the solutions needs to be updated.");
                msgBox2.setInformativeText("Select files?");
                msgBox2.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox2.setDefaultButton(QMessageBox::Ok);
                int ret2 = msgBox2.exec();

                switch (ret2)
                {
                    case QMessageBox::Ok:
                    {
                        solfilenames.clear();
                        // Get the updated solution files
                        QFileDialog selectfilesdialog(this);
                        selectfilesdialog.setDirectory(QDir::homePath());
                        selectfilesdialog.setFileMode(QFileDialog::ExistingFile);
                        selectfilesdialog.setNameFilter(tr("All files (*.*)"));
                        selectfilesdialog.setWindowTitle("Select the solution files");
                        if(selectfilesdialog.exec()) solfilenames = selectfilesdialog.selectedFiles();
                        // Update teh file names in plain text
                        QString data2;
                        data2 = QString();
                        for (int ii = 0; ii<solfilenames.size(); ++ii)
                        {
                            if(ii == 0)
                                data2 = solfilenames[ii] + ";\n";
                            else
                                data2 = data2 + solfilenames[ii] + ";\n";
                        }
                        ui->PText_Solution->document()->setPlainText(data2);
                        break;
                    }
                    case QMessageBox::Cancel:
                    {
                        solfilenames.clear();
                        ui->PText_Solution->clear();
                        break;
                    }
                    default:
                    {
                        solfilenames.clear();
                        ui->PText_Solution->clear();
                        break;
                    }
                }
            }
        }

        if(stype == 3)
        {
            bathfilenames.clear();
            QMessageBox msgBox;
            msgBox.setText("File path to the STL needs to be updated.");
            msgBox.setInformativeText("Select STL files?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();

            switch (ret)
            {
                case QMessageBox::Ok:
                {
                    bathfilenames.clear();
                    // Select the bathymetry files
                    QFileDialog selectfilesdialog(this);
                    selectfilesdialog.setDirectory(QDir::homePath());
                    selectfilesdialog.setFileMode(QFileDialog::ExistingFile);
                    selectfilesdialog.setNameFilter(tr("All files (*.stl)"));
                    selectfilesdialog.setWindowTitle("Select the STL files");
                    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
                    // Show the file list in the plaintext
                    QString data;
                    data = QString();
                    for (int ii = 0; ii<bathfilenames.size(); ++ii)
                    {
                        if(ii == 0)
                            data = bathfilenames[ii] + "\n";
                        else
                            data = data + bathfilenames[ii] + "\n";
                    }
                    ui->PText_Files->document()->setPlainText(data);
                    break;
                }
                case QMessageBox::Cancel:
                {
                    bathfilenames.clear();
                    ui->PText_Files->clear();
                    break;
                }
                default:
                {
                    bathfilenames.clear();
                    ui->PText_Files->clear();
                    break;
                }
            }
        }

        if(stype == 4)
        {
            // Wave flume definition
            if(jsonObject.contains("FlumeInfoType"))
            {
                ui->CmB_FlumeGeoType->setCurrentIndex(jsonObject["FlumeInfoType"].toString().toInt());
            }

            // Wave flume breadth
            if(jsonObject.contains("FlumeBreadth"))
            {
                ui->DSpBx_Breadth->setValue(jsonObject["FlumeBreadth"].toString().toDouble());
            }

            // Flume table
            if(jsonObject.contains("NumFlumeSegments"))
            {
                int numflumesegs = jsonObject["NumFlumeSegments"].toString().toInt();
                if(numflumesegs > 0)
                {
                    // Insert the required number of rows
                    for(int ii=0; ii<numflumesegs; ++ii)
                    {
                        ui->Tbl_Segments->insertRow(ui->Tbl_Segments->rowCount());
                    }

                    if(jsonObject.contains("FlumeSegments"))
                    {
                        // Get the flume segments
                        QString flusegs = jsonObject["FlumeSegments"].toString();

                        // Convert to a stringlist
                        QStringList elements = flusegs.split(',');

                        // Put elements into table
                        int ll=0;
                        for (int ii=0; ii<numflumesegs; ++ii)
                        {
                            QTableWidgetItem* itemtoAdd = new QTableWidgetItem();
                            itemtoAdd->setText(elements[2*ii+1]);
                            ui->Tbl_Segments->setItem(ll,0,itemtoAdd);

                            QTableWidgetItem* itemtoAdd2 = new QTableWidgetItem();
                            itemtoAdd2->setText(elements[2*ii+2]);
                            ui->Tbl_Segments->setItem(ll,1,itemtoAdd2);
                            ll = ll+1;
                        }
                    }
                }
            }
        }
    }
    else
    {
        error.criterrormessage("Simulation type not found. Geometry cannot be realized!");
        return false;
    }

    // Gravity
    if(jsonObject.contains("Gravity"))
    {
        int grav = jsonObject["Gravity"].toString().toInt();
        if(grav == 11)
        {
            ui->CmB_Grav01->setCurrentIndex(0);
            ui->CmB_Grav02->setCurrentIndex(0);
        }
        if(grav == 12)
        {
            ui->CmB_Grav01->setCurrentIndex(0);
            ui->CmB_Grav02->setCurrentIndex(1);
        }
        if(grav == 13)
        {
            ui->CmB_Grav01->setCurrentIndex(0);
            ui->CmB_Grav02->setCurrentIndex(2);
        }
        if(grav == 21)
        {
            ui->CmB_Grav01->setCurrentIndex(1);
            ui->CmB_Grav02->setCurrentIndex(0);
        }
        if(grav == 22)
        {
            ui->CmB_Grav01->setCurrentIndex(1);
            ui->CmB_Grav02->setCurrentIndex(1);
        }
        if(grav == 23)
        {
            ui->CmB_Grav01->setCurrentIndex(1);
            ui->CmB_Grav02->setCurrentIndex(2);
        }
    }

    // Return true if no errors
    return true;
}

//*********************************************************************************
// Select bathymetry files
//*********************************************************************************
void bathymetry::on_Btn_UploadFiles_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
    if(bathfilenames.size() == 0)
    {
        error.warnerrormessage("No files selected!");
    }
    else
    {
        QString data;
        data = QString();
        for (int ii = 0; ii<bathfilenames.size(); ++ii)
        {
            if(ii == 0)
                data = bathfilenames[ii] + "\n";
            else
                data = data + bathfilenames[ii] + "\n";
        }
        ui->PText_Files->document()->setPlainText(data);
    }
}

//*********************************************************************************
// Select SW solution files
//*********************************************************************************
void bathymetry::on_Btn_UploadSolution_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) solfilenames = selectfilesdialog.selectedFiles();
    if(solfilenames.size() == 0)
    {
        error.warnerrormessage("No files selected!");
    }
    else
    {
        QString data;
        data = QString();
        for (int ii = 0; ii<solfilenames.size(); ++ii)
        {
            if(ii == 0)
                data = solfilenames[ii] + ";\n";
            else
                data = data + solfilenames[ii] + ";\n";
        }
        ui->PText_Files->document()->setPlainText(data);
    }
}

//*********************************************************************************
// Add segments to flume
//*********************************************************************************
void bathymetry::on_Btn_AddSeg_clicked()
{
    ui->Tbl_Segments->insertRow(ui->Tbl_Segments->rowCount());
}

//*********************************************************************************
// Delete segments from flume
//*********************************************************************************
void bathymetry::on_Btn_RemSeg_clicked()
{
    ui->Tbl_Segments->removeRow(ui->Tbl_Segments->currentRow());
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool bathymetry::copyFiles(QString dirName,int type)
{

    // SW + CFD or CFD with bath
    if( (type == 1) || (type == 2) )
    {
        // Copy the bathymetry files
        for (int ii=0; ii<bathfilenames.size(); ++ii)
        {
            QFile fileToCopy(bathfilenames[ii]);
            QFileInfo fileInfo(bathfilenames[ii]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
        if(type == 1) // If SW + CFD
        {
            // Copy the solution files
            for (int ii=0; ii<solfilenames.size(); ++ii)
            {
                QFile fileToCopy(solfilenames[ii]);
                QFileInfo fileInfo(solfilenames[ii]);
                QString theFile = fileInfo.fileName();
                fileToCopy.copy(dirName + QDir::separator() + theFile);
            }
        }
    }

    // STL files
    if(type == 3)
    {
        // Copy the bathymetry files
        for (int ii=0; ii<6; ++ii)
        {
            QFile fileToCopy(bathfilenames[ii]);
            QFileInfo fileInfo(bathfilenames[ii]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
    }

    // Return true
    return true;
}

//*********************************************************************************
// Index of flume geometry box changed
//*********************************************************************************
void bathymetry::on_CmB_FlumeGeoType_currentIndexChanged(int index)
{

    ui->Lbl_TopViewH2->hide();
    ui->Lbl_TopView->hide();
    ui->Lbl_Breadth->hide();
    ui->DSpBx_Breadth->hide();
    ui->Lbl_Segments->hide();
    ui->Tbl_Segments->hide();
    ui->Btn_AddSeg->hide();
    ui->Btn_RemSeg->hide();
    ui->Lbl_Notice->hide();

    // Coordinate-based flume definition
    if(index == 0)
    {
        ui->Lbl_TopViewH2->show();
        ui->Lbl_TopView->show();
        ui->Lbl_Breadth->show();
        ui->DSpBx_Breadth->show();
        ui->Lbl_Segments->show();
        ui->Tbl_Segments->show();
        ui->Btn_AddSeg->show();
        ui->Btn_RemSeg->show();
    }

    // Standard OSU flume
    else if(index == 1)
    {
        ui->Lbl_Notice->setText("Standard flume geometry will be used. Please check documentation for more details.");
        ui->Lbl_Notice->show();
    }
}
