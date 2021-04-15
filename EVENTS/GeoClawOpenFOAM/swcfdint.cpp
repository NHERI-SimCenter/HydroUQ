#include "swcfdint.h"
#include "ui_swcfdint.h"

//*********************************************************************************
// SW-CFD settings
//*********************************************************************************
swcfdint::swcfdint(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::swcfdint)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete SW-CFD settings UI
//*********************************************************************************
swcfdint::~swcfdint()
{
    delete ui;
}

//*********************************************************************************
// Refreshdata
//*********************************************************************************
void swcfdint::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}


//*********************************************************************************
// Show hide elements
//*********************************************************************************
void swcfdint::hideshowelems(int type)
{
    if(type == 1)
    {
        ui->Lbl_Notice->hide();
        ui->Lbl_Interface->show();
        ui->Btn_UploadFile->show();
    }
    else
    {
        if(type == 2)
        {
            ui->Lbl_Notice->setText("This option is not yet available.");
        }
        else
        {
            ui->Lbl_Notice->setText("SW-CFD settings are not available for this option");
        }
        ui->Lbl_Notice->show();
        ui->Lbl_Interface->hide();
        ui->Btn_UploadFile->hide();
    }
}

//*********************************************************************************
// Get data from SW-CFD interface
//*********************************************************************************
bool swcfdint::getData(QMap<QString, QString>& map, int type)
{
    bool hasData=false;

    if(type == 1)
    {
        // Write the interface file name
        QFile f(interffilenames[0]);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());
        map.insert("SWCFDInteFile",filename);
        hasData = true;
    }
    // Return the bool
    return hasData;
}

//*********************************************************************************
// Select interface files
//*********************************************************************************
void swcfdint::on_Btn_UploadFile_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list interfilenames
    // For now it is limited to one file only
    // Change ExistingFile to ExistingFiles to allow multiple files
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setDirectory(QDir::homePath());
    selectfilesdialog.setFileMode(QFileDialog::ExistingFile);
    selectfilesdialog.setNameFilter(tr("All files (*.csv)"));
    if(selectfilesdialog.exec()) interffilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool swcfdint::copyFiles(QString dirName,int type)
{
    // Initialize if has data
    bool hasdata = false;

    // Only for SW + CFD (type = 1)
    if(type == 1)
    {
        QFile fileToCopy(interffilenames[0]);
        QFileInfo fileInfo(interffilenames[0]);
        QString theFile = fileInfo.fileName();
        fileToCopy.copy(dirName + QDir::separator() + theFile);

        // Change data to true
        hasdata = true;
    }

    // Return if data exists
    return hasdata;
}
