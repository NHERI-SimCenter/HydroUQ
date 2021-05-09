#include "postprocess.h"
#include "ui_postprocess.h"

#include <QFileInfo>
#include <QDebug>

//*********************************************************************************
// Postprocessing settings
//*********************************************************************************
postprocess::postprocess(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::postprocess)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete Postprocessing settings
//*********************************************************************************
postprocess::~postprocess()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void postprocess::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements (initially at start)
//*********************************************************************************
void postprocess::hideshowelems(int type)
{
    (void) type;

    // Hide the Images checkbox
    ui->ChB_Images->hide();

    // Hide based on postprocessing combo box
    if(ui->CmB_PPFlag->currentIndex() == 0) // No postprocessing
    {
        ui->OpGroupBox->hide();
    }
    else if(ui->CmB_PPFlag->currentIndex() == 1) // Provide the python script
    {
        ui->OpGroupBox->show();
    }
}

//*********************************************************************************
// Get data from bathymetry
//*********************************************************************************
bool postprocess::getData(QMap<QString, QString>& map,int type)
{
    (void) type;
    bool hasData=false;

    if(ui->CmB_PPFlag->currentIndex() == 0)
    {
        // No postprocessing
        map.insert("Postprocessing","No");
    }
    else if(ui->CmB_PPFlag->currentIndex() == 1)
    {
        if(pprocessfilenames.size() > 0)
        {
            // Add postprocessing
            map.insert("Postprocessing","Yes");

            // Add pp file names
            QFile f(pprocessfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("PProcessFile",filename);

            // Insert data into map (Velocity)
            if(ui->ChB_Velocity->isChecked())
                map.insert("PPVelocity","Yes");
            else
                map.insert("PPVelocity","No");

            // Insert data into map (Pressure)
            if(ui->ChB_Pressure->isChecked())
                map.insert("PPPressure","Yes");
            else
                map.insert("PPPressure","No");
        }
        else
        {
            // No postprocessing
            map.insert("Postprocessing","No");
        }
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Click upload files
//*********************************************************************************
void postprocess::on_Btn_UploadFiles_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.csv)"));
    if(selectfilesdialog.exec()) pprocessfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// What to do when user chooses different option
//*********************************************************************************
void postprocess::on_CmB_PPFlag_currentIndexChanged(int index)
{
    (void) index;
    hideshowelems(0);
}

//*********************************************************************************
// Get data from solvers
//*********************************************************************************
bool postprocess::copyFiles(QString dirName,int type)
{
    (void) type;

    // Initialize
    bool hasdata = false;

    // If postprocessing is activated
    if(ui->CmB_PPFlag->currentIndex() > 0)
    {
        if(pprocessfilenames.size() == 0)
        {
            error.warnerrormessage("Postprocessing files not provided. Postprocessing disabled!");
        }
        else
        {
            QFile fileToCopy(pprocessfilenames[0]);
            QFileInfo fileInfo(pprocessfilenames[0]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
        // Change data to true
        hasdata = true;
    }

    // Return if data exists
    return hasdata;

}
