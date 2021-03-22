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
    // Hide - Show elements
    if(type == 4)
    {
        // Set heading
        ui->Lbl_H1->setText("<b>WAVE FLUME SETTINGS</b>");

        // Show wave flume
        ui->CmB_FlumeGeoType->show();
        if(ui->CmB_FlumeGeoType->currentIndex() == 0) // Provide coordinates
        {
            ui->Btn_UploadFiles->hide();
            ui->Lbl_TopViewH2->show();
            ui->Lbl_TopView->show();
            ui->Lbl_Breadth->show();
            ui->DSpBx_Breadth->show();
            ui->Lbl_Segments->show();
            ui->Tbl_Segments->show();
            ui->Btn_AddSeg->show();
            ui->Btn_RemSeg->show();
        }
        else if(ui->CmB_FlumeGeoType->currentIndex() == 1) // Upload LIDAR data
        {
            ui->Btn_UploadFiles->show();
            //ui->Btn_UploadFiles->setText("Upload LIDAR scan");
            ui->Btn_UploadFiles->setText("Coming soon");
            ui->Btn_UploadFiles->setEnabled(false);
            ui->Lbl_TopViewH2->hide();
            ui->Lbl_TopView->hide();
            ui->Lbl_Breadth->hide();
            ui->DSpBx_Breadth->hide();
            ui->Lbl_Segments->hide();
            ui->Tbl_Segments->hide();
            ui->Btn_AddSeg->hide();
            ui->Btn_RemSeg->hide();
        }
        else if(ui->CmB_FlumeGeoType->currentIndex() == 2) // Standard OSU flume
        {
            ui->Btn_UploadFiles->hide();
            ui->Lbl_TopViewH2->hide();
            ui->Lbl_TopView->hide();
            ui->Lbl_Breadth->hide();
            ui->DSpBx_Breadth->hide();
            ui->Lbl_Segments->hide();
            ui->Tbl_Segments->hide();
            ui->Btn_AddSeg->hide();
            ui->Btn_RemSeg->hide();
        }

        // Hide all other elements
        ui->Lbl_SelFiles->hide();
        ui->Btn_UploadSolution->hide();
        ui->CmB_FileType->hide();
        ui->CmB_SolFormat->hide();
        ui->CmB_Library->hide();
        ui->Lbl_Notice->hide();
    }
    else
    {
        // Hide wave flume
        ui->CmB_FlumeGeoType->hide();
        ui->Lbl_TopViewH2->hide();
        ui->Lbl_TopView->hide();
        ui->Lbl_Breadth->hide();
        ui->DSpBx_Breadth->hide();
        ui->Lbl_Segments->hide();
        ui->Tbl_Segments->hide();
        ui->Btn_AddSeg->hide();
        ui->Btn_RemSeg->hide();
    }

    // If STL / Maps / Surrogate - show only notice
    if( ((type == 5)
            || (type == 6))
            || (type == 7))
    {
        // Set heading and notice
        if(type == 5)
        {
            ui->Lbl_H1->setText("<b>STL/OBJ FILE SETTINGS</b>");
            ui->Lbl_Notice->setText("STL option is not yet available. "
                                       "Watch out for future updates");
        }
        else if(type == 6)
        {
            ui->Lbl_H1->setText("<b>BATHYMETRY USING MAPS</b>");
            ui->Lbl_Notice->setText("Maps option is not yet available. "
                                       "Watch out for future updates");
        }
        else if(type == 7)
        {
            ui->Lbl_H1->setText("<b>BATHYMETRY FOR SURROGATE MODELS</b>");
            ui->Lbl_Notice->setText("Surrogate model option is not yet available. "
                                       "Watch out for future updates");
        }

        // Show notice
        ui->Lbl_Notice->show();

        // Hide all other elements
        ui->Lbl_SelFiles->hide();
        ui->Btn_UploadFiles->hide();
        ui->Btn_UploadSolution->hide();
        ui->CmB_FileType->hide();
        ui->CmB_SolFormat->hide();
        ui->CmB_Library->hide();
    }
    else
    {
        // Hide the notice
        ui->Lbl_Notice->hide();
    }

    // Show-Hide elements based on type of simulations
    if(type == 1) //SW solutions
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY AND SW SOLUTIONS</b>");
        ui->Btn_UploadFiles->setText("Select bathymetry files");

        // Show bathy items
        ui->Btn_UploadFiles->show();
        ui->Btn_UploadSolution->show();
        ui->CmB_FileType->show();
        ui->CmB_SolFormat->show();

        // Hide library items
        ui->CmB_Library->hide();
    }
    else if(type == 2) //Library
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY AND SW LIBRRAY</b>");
        ui->Btn_UploadFiles->setText("Select bathymetry files");

        // Show library items
        ui->CmB_Library->show();

        // Hide bathy items
        ui->Btn_UploadFiles->hide();
        ui->Btn_UploadSolution->hide();
        ui->CmB_FileType->hide();
        ui->CmB_SolFormat->hide();
    }
    else if(type == 3) // Bathymetry files
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY FILE SETTINGS</b>");
        ui->Btn_UploadFiles->setText("Select bathymetry files");

        // Show bathy items
        ui->Btn_UploadFiles->show();
        ui->CmB_FileType->show();

        // Hide solutions and library items
        ui->Btn_UploadSolution->hide();
        ui->CmB_SolFormat->hide();
        ui->CmB_Library->hide();
    }
    /*else if(type == 5) // STL file
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>STL FILE UPLOAD</b>");
        ui->Btn_UploadFiles->show();
        ui->Btn_UploadFiles->setText("Select STL files");
        ui->Lbl_Notice->setText("Check documentation to prepare files correctly.");
    }*/
}

//*********************************************************************************
// Get data from bathymetry
//*********************************************************************************
bool bathymetry::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=true;

    // Shallow water bathymetry files
    if((type == 1) || (type == 3))
    {
        if(bathfilenames.size() > 0)
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
        else
        {
            error.criterrormessage("Bathymetry files not provided!");
            hasData=false;
        }
    }

    // Shallow water solutions
    if(type == 1)
    {
        if(solfilenames.size() > 0)
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
        else
        {
            error.criterrormessage("Solution files not provided!");
            hasData=false;
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
                error.warnerrormessage("Flume breadth almost zero!");
                map.insert("FlumeBreadth",ui->DSpBx_Breadth->textFromValue(ui->DSpBx_Breadth->value()));
            }

            // Create the file and add the segments
            if(ui->Tbl_Segments->rowCount() > 0)
            {
                // Create and open a text file
                QString filename = "FlumeData.txt";
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly))
                {
                    QTextStream stream(&file);
                    for(int ii=0;ii<ui->Tbl_Segments->rowCount(); ++ii)
                    {
                        QString segdata = ui->Tbl_Segments->item(ii,0)->text() +
                                "," + ui->Tbl_Segments->item(ii,1)->text();
                        stream << segdata << Qt::endl;
                    }
                }
                file.close();
            }
            else
            {
                error.criterrormessage("Flume outline coordinates not provided!");
                hasData=false;
            }
        }
        else if(ui->CmB_FlumeGeoType->currentIndex() == 1) // LIDAR data
        {
            if(bathfilenames.size() > 0)
            {
                map.insert("NumLIDARFiles",QString::number(bathfilenames.size()));
                // Write the LIDAR file names
                for (int ii=0; ii<bathfilenames.size(); ++ii)
                {
                    QFile f(bathfilenames[ii]);
                    QFileInfo fileInfo(f.fileName());
                    QString filename(fileInfo.fileName());
                    map.insert("LIDARFile"+QString::number(ii),filename);
                }
            }
            else
            {
                error.criterrormessage("LIDAR files not provided!");
                hasData=false;
            }
        }
    }

    // CFD with STL / Maps / Surrogate models
    if( (type == 2 || type == 5) || (type == 6 || type == 7) )
    {
        error.criterrormessage("This simulation type is not yet supported!");
        hasData=false;
    }

    // Return the bool
    return hasData;
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
    if( (type == 1) || (type == 3) )
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
    else if(type == 4) // CFD with Flume
    {
        if(ui->CmB_FlumeGeoType->currentIndex() == 0) // Coordinates
        {
            // Copy the segment coordinates file
            QFile fileToCopy("FlumeData.txt");
            QFileInfo fileInfo(fileToCopy);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
        else if(ui->CmB_FlumeGeoType->currentIndex() == 1) // LIDAR data
        {
            // Copy the LIDAR files
            for (int ii=0; ii<bathfilenames.size(); ++ii)
            {
                QFile fileToCopy(bathfilenames[ii]);
                QFileInfo fileInfo(bathfilenames[ii]);
                QString theFile = fileInfo.fileName();
                fileToCopy.copy(dirName + QDir::separator() + theFile);
            }
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
    if(ui->CmB_FlumeGeoType->currentIndex() == 0) // Provide coordinates
    {
        ui->Btn_UploadFiles->hide();
        ui->Lbl_TopViewH2->show();
        ui->Lbl_TopView->show();
        ui->Lbl_Breadth->show();
        ui->DSpBx_Breadth->show();
        ui->Lbl_Segments->show();
        ui->Tbl_Segments->show();
        ui->Btn_AddSeg->show();
        ui->Btn_RemSeg->show();
    }
    else if(ui->CmB_FlumeGeoType->currentIndex() == 1) // Upload LIDAR data
    {
        ui->Btn_UploadFiles->show();
        //ui->Btn_UploadFiles->setText("\nUpload LIDAR scan\n");
        ui->Btn_UploadFiles->setText("Coming soon");
        ui->Btn_UploadFiles->setEnabled(false);
        ui->Lbl_TopViewH2->hide();
        ui->Lbl_TopView->hide();
        ui->Lbl_Breadth->hide();
        ui->DSpBx_Breadth->hide();
        ui->Lbl_Segments->hide();
        ui->Tbl_Segments->hide();
        ui->Btn_AddSeg->hide();
        ui->Btn_RemSeg->hide();
    }
    else if(ui->CmB_FlumeGeoType->currentIndex() == 2) // Standard OSU flume
    {
        ui->Btn_UploadFiles->hide();
        ui->Lbl_TopViewH2->hide();
        ui->Lbl_TopView->hide();
        ui->Lbl_Breadth->hide();
        ui->DSpBx_Breadth->hide();
        ui->Lbl_Segments->hide();
        ui->Tbl_Segments->hide();
        ui->Btn_AddSeg->hide();
        ui->Btn_RemSeg->hide();
    }

    // Hide all other elements
    ui->Lbl_SelFiles->hide();
    ui->Btn_UploadSolution->hide();
    ui->CmB_FileType->hide();
    ui->CmB_SolFormat->hide();
    ui->CmB_Library->hide();
    ui->Lbl_Notice->hide();

    // Unused variables
    (void) index;

}
