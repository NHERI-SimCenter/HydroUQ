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
    // Hide all elements by default
    ui->Lbl_Interface->hide();
    ui->Lbl_Notice->hide();
    ui->Btn_UploadFile->hide();
    ui->Led_path->hide();

    if(type == 1)
    {
        ui->Btn_UploadFile->show();
        ui->Btn_UploadFile->setText("Upload interface files");
        ui->Lbl_Notice->show();
        ui->Lbl_Notice->setText("Check the documentation for format of interface files");
        ui->Led_path->show();
    }
    else
    {
        ui->Lbl_Notice->show();
        ui->Lbl_Notice->setText("This option is not available for this simulation type.");
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
        if(interffilenames.size() > 0)
        {
            // Write the interface file name
            QFile f(interffilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("SWCFDInteFile",filename);
            hasData = true;
        }
        else
        {
            error.warnerrormessage("No interface file provided. Entire domain shall be used!");
            hasData = true;
        }
    }

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Put data into SW-CFD from the JSON file
//*********************************************************************************
bool swcfdint::putData(QJsonObject &jsonObject,int stype,QString workpath)
{

    // Only if work dir is defined
    if(!workpath.isEmpty())
    {
        // Only if SW-CFD simulation
        if(stype == 1)
        {
            interffilenames.clear();
            // Check for the SW-CFD interface file
            if(jsonObject.contains("SWCFDInteFile"))
            {
                QString filename = jsonObject["SWCFDInteFile"].toString();
                QFileInfo fi(QDir(workpath),filename);
                interffilenames.append(fi.canonicalFilePath());
                ui->Led_path->setText(interffilenames.join(";\n\n"));
            }
        }
    }

    // Return true
    return true;
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

    // Set the path
    ui->Led_path->setText(interffilenames[0]);
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
        if(interffilenames.size() > 0)
        {
            QFile fileToCopy(interffilenames[0]);
            QFileInfo fileInfo(interffilenames[0]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);

            // Change data to true
            hasdata = true;
        }
    }

    // Return if data exists
    return hasdata;
}
