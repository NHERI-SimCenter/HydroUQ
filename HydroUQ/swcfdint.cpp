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
    (void) type;
    if(ui->ChB_UploadFile->isChecked())
        ui->Btn_UploadFile->show();
    else
        ui->Btn_UploadFile->hide();
}

//*********************************************************************************
// Get data from SW-CFD interface
//*********************************************************************************
bool swcfdint::getData(QMap<QString, QString>& map, int type)
{
    bool hasData=false;
    (void) type;

    // Change hasData to be true
    hasData = true;

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
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) interffilenames = selectfilesdialog.selectedFiles();
}


//*********************************************************************************
// Next button
//*********************************************************************************
void swcfdint::on_Btn_Next_clicked()
{

}

//*********************************************************************************
// Previous button
//*********************************************************************************
void swcfdint::on_Btn_Previous_clicked()
{

}




