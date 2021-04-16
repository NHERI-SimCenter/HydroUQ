#include "boundarydata.h"
#include "ui_boundarydata.h"

//*********************************************************************************
// Boundary conditions data settings widget
//*********************************************************************************
boundaryData::boundaryData(const QString titleString, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::boundaryData)
{
    ui->setupUi(this);
    ui->Lbl_H1->setText(titleString);

    // Initialize to show / hide elements
    hideshowelems();
}

//*********************************************************************************
// Delete Boundary conditions data settings
//*********************************************************************************
boundaryData::~boundaryData()
{
    delete ui;
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void boundaryData::hideshowelems()
{
    // Patch location UI components
    on_Cmb_PatchLoc_currentIndexChanged(ui->Cmb_PatchLoc->currentIndex());

    // Vel UI components
    on_Cmb_UBC_currentIndexChanged(ui->Cmb_UBC->currentIndex());

    // Pres UI components
    on_Cmb_PresBC_currentIndexChanged(ui->Cmb_PresBC->currentIndex());
}

//*********************************************************************************
// Get data from meshing
//*********************************************************************************
bool boundaryData::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;
    (void) type;

    // Attach patch name
    //QString patchname = ui->Lbl_H1->text();
    QString patchname = ui->Cmb_PatchStdLoc->currentText();

    // Add patch location information
    //map.insert("LocationType_"+patchname,ui->Cmb_PatchLoc->currentText());
//    if(ui->Cmb_PatchLoc->currentIndex() == 0)
//        map.insert("PatchLocation",ui->Cmb_PatchStdLoc->currentText());
//    else
//        map.insert("PatchLocation",ui->Lbl_H1->text());

    // Get velocity information
    int index = ui->Cmb_UBC->currentIndex();
    map.insert("VelocityType_"+patchname,QString::number(ui->Cmb_UBC->currentIndex()));
    if( ((index == 1) || (index == 5)) || (index == 7) )
    {
        QString veldata = ui->DSpBx_UMeanX->textFromValue(ui->DSpBx_UMeanX->value()) +
                "," + ui->DSpBx_UMeanY->textFromValue(ui->DSpBx_UMeanY->value()) +
                "," + ui->DSpBx_UMeanZ->textFromValue(ui->DSpBx_UMeanZ->value());
        map.insert("Velocity_"+patchname,veldata);
    }
    else if(index == 2)
    {
        map.insert("WaveType_"+patchname,ui->Cmb_PatchStdLoc->currentText());
        QString veldata = ui->DSpBx_UMeanX->textFromValue(ui->DSpBx_UMeanX->value()) +
                "," + ui->DSpBx_UMeanY->textFromValue(ui->DSpBx_UMeanY->value()) +
                "," + ui->DSpBx_UMeanZ->textFromValue(ui->DSpBx_UMeanZ->value());
        map.insert("MeanVelocity_"+patchname,veldata);
        veldata = ui->DSpBx_OX->textFromValue(ui->DSpBx_OX->value()) +
                "," + ui->DSpBx_OY->textFromValue(ui->DSpBx_OY->value()) +
                "," + ui->DSpBx_OZ->textFromValue(ui->DSpBx_OZ->value());
        map.insert("Origin_"+patchname,veldata);
        veldata = ui->DSpBx_DirnX->textFromValue(ui->DSpBx_DirnX->value()) +
                "," + ui->DSpBx_DirnY->textFromValue(ui->DSpBx_DirnY->value()) +
                "," + ui->DSpBx_DirnZ->textFromValue(ui->DSpBx_DirnZ->value());
        map.insert("Direction_"+patchname,veldata);
        map.insert("WaveParameters_"+patchname,ui->Led_WavePara->text());
    }
    else if ((index == 3) || (index == 4))
    {
        if(velfilenames.size() > 0)
        {
            QFile f(velfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("VelocityBoundaryFiles_"+patchname,filename);
        }
    }
    else if(index == 6)
    {
        map.insert("MeanFlowRate_"+patchname, ui->DSpBx_UMeanX->textFromValue(ui->DSpBx_UMeanX->value()));
    }
    else if(index == 9) // Moving wall
    {
        if(velfilenames.size() > 0)
        {
            QFile f(velfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("MovingWall_"+patchname,filename);
        }
    }

    // Get pressure information
    index = ui->Cmb_PresBC->currentIndex();
    map.insert("PressureType",ui->Cmb_PresBC->currentText());
    if( (index == 2) || (index == 3) )
    {
        map.insert("Pressure_"+patchname,ui->DSpBx_Pres->textFromValue(ui->DSpBx_Pres->value()));
    }
    else if (index == 4)
    {
        map.insert("PressureGradient_"+patchname,ui->DSpBx_Pres->textFromValue(ui->DSpBx_Pres->value()));
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;

}

//*********************************************************************************
// Location combobox options
//*********************************************************************************
void boundaryData::on_Cmb_PatchLoc_currentIndexChanged(int index)
{
    if(index==0)
    {
        // Show standard options
        ui->Cmb_PatchStdLoc->show();
    }
    else
    {
        // Dont show standard options
        ui->Cmb_PatchStdLoc->hide();
    }
}

//*********************************************************************************
// When U-BC option is changed
//*********************************************************************************
void boundaryData::on_Cmb_UBC_currentIndexChanged(int index)
{

//    ui->Lbl_Sampling->hide();
//    ui->DSpBx_Sampling->hide();

    if(index == 0)
    {
        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->hide();
        ui->Lbl_Umean->hide();
        ui->DSpBx_UMeanX->hide();
        ui->DSpBx_UMeanY->hide();
        ui->DSpBx_UMeanZ->hide();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }

    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {
        if(index == 1) ui->Lbl_Umean->setText("Velocity");
        else if(index == 5) ui->Lbl_Umean->setText("UMean");
        else if(index == 7) ui->Lbl_Umean->setText("UMean");

        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->hide();
        ui->Lbl_Umean->show();
        ui->DSpBx_UMeanX->show();
        ui->DSpBx_UMeanY->show();
        ui->DSpBx_UMeanZ->show();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }
    else if(index == 2)
    {
        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->show();
        ui->Lbl_Umean->show();
        ui->Lbl_Umean->setText("Umean");
        ui->DSpBx_UMeanX->show();
        ui->DSpBx_UMeanY->show();
        ui->DSpBx_UMeanZ->show();
        ui->Lbl_Origin->show();
        ui->DSpBx_OX->show();
        ui->DSpBx_OY->show();
        ui->DSpBx_OZ->show();
        ui->Lbl_Dirn->show();
        ui->DSpBx_DirnX->show();
        ui->DSpBx_DirnY->show();
        ui->DSpBx_DirnZ->show();
        ui->Lbl_WavePara->show();
        ui->Led_WavePara->show();
    }
    else if((index == 3) || (index == 4))
    {
        ui->Btn_UploadFile->show();
        ui->Cmb_WaveType->hide();
        ui->Lbl_Umean->hide();
        ui->DSpBx_UMeanX->hide();
        ui->DSpBx_UMeanY->hide();
        ui->DSpBx_UMeanZ->hide();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }
    else if((index == 6) || (index == 8))
    {
        if(index == 6)
        {
            ui->Lbl_Umean->setText("Flow rate");
            ui->Lbl_Umean->show();
            ui->DSpBx_UMeanX->show();
        }
        else
        {
            ui->Lbl_Umean->hide();
            ui->DSpBx_UMeanX->hide();
        }
        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->hide();
        ui->DSpBx_UMeanY->hide();
        ui->DSpBx_UMeanZ->hide();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }
    else if(index == 9) // Moving wall
    {
        ui->Btn_UploadFile->show();
    }
    else if(index == 10) // SW solutions
    {
        ui->Btn_UploadFile->hide();
    }
}

//*********************************************************************************
// When pressure-BC option is changed
//*********************************************************************************
void boundaryData::on_Cmb_PresBC_currentIndexChanged(int index)
{
    if((index == 1) || (index == 0))
    {
        ui->Lbl_Pres->hide();
        ui->DSpBx_Pres->hide();
    }
    else
    {
        ui->Lbl_Pres->show();
        ui->DSpBx_Pres->show();
        if((index == 2)||(index==3)) ui->Lbl_Pres->setText("Pressure");
        else if(index == 4) ui->Lbl_Pres->setText("Pressure gradient");
    }
}

//*********************************************************************************
// When files are uploaded
//*********************************************************************************
void boundaryData::on_Btn_UploadFile_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) velfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool boundaryData::copyFiles(QString dirName,int type)
{
    (void) type;

    // Initialize if has data
    bool hasdata = false;

    // Get index of velocity
    int index = ui->Cmb_UBC->currentIndex();

    if( ((index == 3) || (index == 4)) || (index == 9))
    {
        if(velfilenames.size() == 0)
        {
            error.criterrormessage("No velocity boundary condition files selected!");
        }
        else
        {
            QFile fileToCopy(velfilenames[0]);
            QFileInfo fileInfo(velfilenames[0]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
    }


    // Return if data exists
    return hasdata;
}
