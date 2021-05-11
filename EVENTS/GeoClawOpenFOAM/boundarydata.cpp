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

    // Hide all velocity items by default
    ui->Cmb_UBC->show();
    ui->Btn_UploadFile->hide();
    ui->Btn_UploadFile_2->hide();
    ui->Led_WaterDisp->hide();
    ui->Led_WaterHeight->hide();
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


    // SW solutions (inlet)
    if(index == 1)
    {
        // No element needs to be activated
    }

    // Constant velocity (inlet)
    if(index == 2)
    {
        ui->Lbl_Umean->setText("Velocity");
        ui->Lbl_Umean->show();
        ui->DSpBx_UMeanX->show();
        ui->DSpBx_UMeanY->show();
        ui->DSpBx_UMeanZ->show();
    }

    // Moving wall (OSU Flume) (inlet)
    if(index == 3)
    {
        ui->Btn_UploadFile->show();
        ui->Btn_UploadFile_2->show();
        ui->Led_WaterDisp->show();
        ui->Led_WaterHeight->show();
        //ui->Btn_UploadFile->setText("\nUpload OSU wall motion .zip file\n");
    }

    // Moving wall (General flume) (inlet)
    if(index == 4)
    {
        ui->Btn_UploadFile->show();
        ui->Btn_UploadFile_2->show();
        ui->Led_WaterDisp->show();
        ui->Led_WaterHeight->show();
        //ui->Btn_UploadFile->setText("\nUpload wall motion .zip file\n");
    }

    // zeroGradient (outlet)
    if(index == 5)
    {
        // No element needs to be activated
    }

    // inletOutlet (outlet)
    if(index == 6)
    {
        ui->Lbl_Umean->setText("Velocity");
        ui->Lbl_Umean->show();
        ui->DSpBx_UMeanX->show();
        ui->DSpBx_UMeanY->show();
        ui->DSpBx_UMeanZ->show();
    }

    // noSlip (wall)
    if(index == 7)
    {
        // No element needs to be activated
    }
}

//*********************************************************************************
// When pressure-BC option is changed
//*********************************************************************************
void boundaryData::on_Cmb_PresBC_currentIndexChanged(int index)
{
    // Hide all components (by default)
    ui->Lbl_Pres->hide();
    ui->DSpBx_Pres->hide();

    // For default and zeroGradient
    if((index == 0) || (index == 1))
    {
        // Do nothing
    }
    // Fixed value
    if(index == 2)
    {
        ui->Lbl_Pres->setText("Pressure");
        ui->Lbl_Pres->show();
        ui->DSpBx_Pres->show();
    }
}

//*********************************************************************************
// When files are uploaded - water displacement
//*********************************************************************************
void boundaryData::on_Btn_UploadFile_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list velfilenames
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.txt)"));
    if(selectfilesdialog.exec()) dispfilenames = selectfilesdialog.selectedFiles();
    if(dispfilenames.size() > 0)
    {
        ui->Led_WaterDisp->setText(dispfilenames[0]);
    }
    else
    {
        error.warnerrormessage("No files selected!");
    }
}

//*********************************************************************************
// When files are uploaded - water height
//*********************************************************************************
void boundaryData::on_Btn_UploadFile_2_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list velfilenames
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.txt)"));
    if(selectfilesdialog.exec()) heightfilenames = selectfilesdialog.selectedFiles();
    if(heightfilenames.size() > 0)
    {
        ui->Led_WaterHeight->setText(heightfilenames[0]);
    }
    else
    {
        error.warnerrormessage("No files selected!");
    }
}

//*********************************************************************************
// Get data from boundary data
//*********************************************************************************
bool boundaryData::getData(QMap<QString, QString>& map,int type,int count)
{
    bool hasData=false;

    // Error for SW solutions
    if(type != 1)
    {
        if(ui->Cmb_UBC->currentIndex() == 1)
        {
            error.criterrormessage("SW solutions cannot be used for boundary conditions for this simulation type");
            return false;
        }
    }

    // Attach patch name
    // QString patchname = ui->Lbl_H1->text();
    QString patchname = ui->Cmb_PatchStdLoc->currentText();
    map.insert("BounPatch"+QString::number(count),patchname);

    // Get velocity information
    int index = ui->Cmb_UBC->currentIndex();
    map.insert("VelocityType_"+patchname,QString::number(ui->Cmb_UBC->currentIndex()));

    // SW solutions for velocity
    if(index == 1)
    {
        // No additional info
    }

    // Constant velocity
    if(index == 2)
    {
        QString veldata = ui->DSpBx_UMeanX->textFromValue(ui->DSpBx_UMeanX->value()) +
                "," + ui->DSpBx_UMeanY->textFromValue(ui->DSpBx_UMeanY->value()) +
                "," + ui->DSpBx_UMeanZ->textFromValue(ui->DSpBx_UMeanZ->value());
        map.insert("Velocity_"+patchname,veldata);
    }

    // Moving wall (OSU) for velocity
    if(index == 3)
    {
        if(dispfilenames.size() > 0)
        {
            QFile f(dispfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("OSUMovingWallDisp_"+patchname,filename);
        }

        if(heightfilenames.size() > 0)
        {
            QFile f(heightfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("OSUMovingWallHeight_"+patchname,filename);
        }
    }

    // Moving wall (General) for velocity
    if(index == 4)
    {
        if(dispfilenames.size() > 0)
        {
            QFile f(dispfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("MovingWallDisp_"+patchname,filename);
        }

        if(heightfilenames.size() > 0)
        {
            QFile f(heightfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("MovingWallHeight_"+patchname,filename);
        }
    }

    // zeroGradient for velocity
    if(index == 5)
    {
        // No data to be provided
    }

    // inletOutlet for velocity
    if(index == 6)
    {
        QString veldata = ui->DSpBx_UMeanX->textFromValue(ui->DSpBx_UMeanX->value()) +
                "," + ui->DSpBx_UMeanY->textFromValue(ui->DSpBx_UMeanY->value()) +
                "," + ui->DSpBx_UMeanZ->textFromValue(ui->DSpBx_UMeanZ->value());
        map.insert("Velocity_"+patchname,veldata);
    }

    // Wall  for velocity
    if(index == 7)
    {
        // Nothing to add
    }

    // Get pressure information
    index = ui->Cmb_PresBC->currentIndex();
    map.insert("PressureType_"+patchname,QString::number(ui->Cmb_PresBC->currentIndex()));

    // fixed Value
    if(index == 2)
    {
        map.insert("Pressure_"+patchname,ui->DSpBx_Pres->textFromValue(ui->DSpBx_Pres->value()));
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;

}

//*********************************************************************************
// Put data to boundary data
//*********************************************************************************
bool boundaryData::putData(QJsonObject &jsonObject,int stype, QString workpath, QString bpatchname)
{
    // Suppress warnings
    (void) stype;

    // Set the patch location
    int typeindex = 0;
    if(QString::compare(bpatchname,"Entry") == 0)
        typeindex = 0;
    else if(QString::compare(bpatchname,"Exit") == 0)
        typeindex = 1;
    else if(QString::compare(bpatchname,"Top") == 0)
        typeindex = 2;
    else if(QString::compare(bpatchname,"Bottom") == 0)
        typeindex = 3;
    else if(QString::compare(bpatchname,"Right") == 0)
        typeindex = 4;
    else if(QString::compare(bpatchname,"Left") == 0)
        typeindex = 5;
    ui->Cmb_PatchStdLoc->setCurrentIndex(typeindex);

    // Set the velocity boundary condition
    if(jsonObject.contains("VelocityType_"+bpatchname))
    {
        // Get the velocity index
        int velindex = jsonObject["VelocityType_"+bpatchname].toString().toInt();

        // Set the combobox accordingly
        ui->Cmb_UBC->setCurrentIndex(velindex);

        // Set the conditions for different index
        if( (velindex == 2) || (velindex == 6) ) // Constant velocity
        {
            if(jsonObject.contains("Velocity_"+bpatchname))
            {
                QString veldata = jsonObject["Velocity_"+bpatchname].toString();
                QStringList vellist = veldata.split(",");
                if(vellist.size() == 3)
                {
                    ui->DSpBx_UMeanX->setValue(vellist[0].toDouble());
                    ui->DSpBx_UMeanY->setValue(vellist[0].toDouble());
                    ui->DSpBx_UMeanZ->setValue(vellist[0].toDouble());
                }
            }
        }
        else if(velindex == 3) // OSU Flume
        {
            if(jsonObject.contains("OSUMovingWallDisp_"+bpatchname))
            {
                QString filename = jsonObject["OSUMovingWallDisp_"+bpatchname].toString();
                QFileInfo fi(QDir(workpath),filename);
                dispfilenames.append(fi.canonicalFilePath());
                ui->Led_WaterDisp->setText(dispfilenames.join(";\n\n"));
            }

            if(jsonObject.contains("OSUMovingWallHeight_"+bpatchname))
            {
                QString filename = jsonObject["OSUMovingWallHeight_"+bpatchname].toString();
                QFileInfo fi(QDir(workpath),filename);
                heightfilenames.append(fi.canonicalFilePath());
                ui->Led_WaterHeight->setText(heightfilenames.join(";\n\n"));
            }
        }
        else if(velindex == 4) // General Flume
        {
            if(jsonObject.contains("MovingWallDisp_"+bpatchname))
            {
                QString filename = jsonObject["MovingWallDisp_"+bpatchname].toString();
                QFileInfo fi(QDir(workpath),filename);
                dispfilenames.append(fi.canonicalFilePath());
                ui->Led_WaterDisp->setText(dispfilenames.join(";\n\n"));
            }

            if(jsonObject.contains("MovingWallHeight_"+bpatchname))
            {
                QString filename = jsonObject["MovingWallHeight_"+bpatchname].toString();
                QFileInfo fi(QDir(workpath),filename);
                heightfilenames.append(fi.canonicalFilePath());
                ui->Led_WaterHeight->setText(heightfilenames.join(";\n\n"));
            }
        }
    }

    // Set the pressure boundary condition
    if(jsonObject.contains("PressureType_"+bpatchname))
    {
        // Get the velocity index
        int presindex = jsonObject["PressureType_"+bpatchname].toString().toInt();

        // Set the combobox accordingly
        ui->Cmb_PresBC->setCurrentIndex(presindex);

        // Set the conditions for different index
        if( presindex == 2) // Constant pressure
        {
            if(jsonObject.contains("Pressure_"+bpatchname))
            {

                ui->DSpBx_Pres->setValue(jsonObject["Pressure_"+bpatchname].toString().toDouble());
            }
        }
    }


    // Return true
    return true;
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

    // Wall motion - OSU and general flume
    if( (index == 3) || (index == 4) )
    {
        // Copy water displacement file
        QFile fileToCopy(dispfilenames[0]);
        QFileInfo fileInfo(dispfilenames[0]);
        QString theFile = fileInfo.fileName();
        fileToCopy.copy(dirName + QDir::separator() + theFile);

        // Copy water velocity file
        QFile fileToCopy2(heightfilenames[0]);
        QFileInfo fileInfo2(heightfilenames[0]);
        QString theFile2 = fileInfo2.fileName();
        fileToCopy2.copy(dirName + QDir::separator() + theFile2);
    }

    // Return if data exists
    return hasdata;
}


