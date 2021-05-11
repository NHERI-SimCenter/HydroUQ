#include "buildings.h"
#include "ui_buildings.h"

//*********************************************************************************
// Building settings
//*********************************************************************************
buildings::buildings(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::buildings)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);

    // Set the simulation type
    simtype = type;
}

//*********************************************************************************
// Delete building settings
//*********************************************************************************
buildings::~buildings()
{
    delete ui;
}

//*********************************************************************************
// Refresh building settings
//*********************************************************************************
void buildings::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);

    // Set the simulation type
    simtype = type;
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void buildings::hideshowelems(int type)
{
    // Set the Combo box
    simtype = type;
    on_CmB_BuildData_currentIndexChanged(ui->CmB_BuildData->currentIndex());
}

//*********************************************************************************
// Get data from buildings
//*********************************************************************************
bool buildings::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;
    (void) type; // Variable is unused

    // Initialize simulation type
    simtype = type;

    // Define type of building definition
    if(ui->CmB_BuildData->currentIndex() == 0) //Manual by table
    {
        map.insert("BuildData","Manual");
        // Write data from the table
        map.insert("NumBuild",QString::number(ui->Tbl_Building->rowCount()));
        if(ui->Tbl_Building->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_Building->rowCount(); ++ii)
            {
                QString segdata = ui->Tbl_Building->item(ii,0)->text() +
                        "," + ui->Tbl_Building->item(ii,1)->text() +
                        "," + ui->Tbl_Building->item(ii,2)->text();
                map.insert("BuildingTable"+QString::number(ii),segdata);
            }
        }
    }
    else if(ui->CmB_BuildData->currentIndex() == 1) //From parameters
    {
        map.insert("BuildData","Parameters");
        map.insert("BuildDist",QString::number(ui->CmB_BuildDist->currentIndex()));
        map.insert("BuildShape",QString::number(ui->CmB_BuildShape->currentIndex()));
        map.insert("NumBuildX",ui->DSpBx_NumBuildX->textFromValue(ui->DSpBx_NumBuildX->value()));
        map.insert("NumBuildY",ui->DSpBx_NumBuildY->textFromValue(ui->DSpBx_NumBuildY->value()));
        map.insert("DistBuildX",ui->DSpBx_BuildDistX->textFromValue(ui->DSpBx_BuildDistX->value()));
        map.insert("DistBuildY",ui->DSpBx_BuildDistY->textFromValue(ui->DSpBx_BuildDistY->value()));
        map.insert("DistCoast",ui->DSpBx_CoastDist->textFromValue(ui->DSpBx_CoastDist->value()));
        map.insert("CoastX",ui->DSpBx_OffsetX->textFromValue(ui->DSpBx_OffsetX->value()));
        map.insert("CoastY",ui->DSpBx_OffsetY->textFromValue(ui->DSpBx_OffsetY->value()));
        map.insert("BuildSizePara01",ui->DSpBx_BuildSize01->textFromValue(ui->DSpBx_BuildSize01->value()));
        map.insert("BuildSizePara02",ui->DSpBx_BuildSize02->textFromValue(ui->DSpBx_BuildSize02->value()));
        map.insert("BuildSizePara03",ui->DSpBx_BuildSize03->textFromValue(ui->DSpBx_BuildSize03->value()));
    }

    // Upload only the first STL file
    if(STLfilenames.size() > 0)
    {
        QFile f(STLfilenames[0]);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());
        map.insert("BuildingSTLFile",filename);
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Put data into buildings from the JSON file
//*********************************************************************************
bool buildings::putData(QJsonObject &jsonObject,int stype, QString workpath)
{

    // Get the type of building definition
    int buildindex = -1;
    if(jsonObject.contains("BuildData"))
    {
        QString builddatatype = jsonObject["BuildData"].toString();

        // Set if it is manual or parameters
        if(QString::compare(builddatatype, "Manual", Qt::CaseInsensitive) == 0)
        {
            ui->CmB_BuildData->setCurrentIndex(0);
            buildindex = 0;
        }
        else if (QString::compare(builddatatype, "Parameters", Qt::CaseInsensitive) == 0)
        {
            ui->CmB_BuildData->setCurrentIndex(1);
            buildindex = 1;
        }
    }

    // Set up the building table
    if(buildindex == 0) // Manual
    {
        int numbuildings = jsonObject["NumBuild"].toString().toInt();
        if(numbuildings > 0)
        {
            for(int ii=0; ii<numbuildings; ++ii)
            {
                // Add a row for the building
                ui->Tbl_Building->insertRow(ui->Tbl_Building->rowCount());
                // Add the particular building parameters
                if(jsonObject.contains("BuildingTable"+QString::number(ii)))
                {
                    // Get the parameters for each building / building table row
                    QString building = jsonObject["BuildingTable"+QString::number(ii)].toString();
                    QStringList buildingdata = building.split(',');
                    if(buildingdata.size() == 4)
                    {
                        QTableWidgetItem* itemtoAdd = new QTableWidgetItem();
                        QTableWidgetItem* itemtoAdd2 = new QTableWidgetItem();
                        QTableWidgetItem* itemtoAdd3 = new QTableWidgetItem();
                        itemtoAdd->setText(buildingdata[0]);
                        ui->Tbl_Building->setItem(ii,0,itemtoAdd);
                        itemtoAdd2->setText(buildingdata[1]+","+buildingdata[2]);
                        ui->Tbl_Building->setItem(ii,1,itemtoAdd2);
                        itemtoAdd3->setText(buildingdata[3]);
                        ui->Tbl_Building->setItem(ii,2,itemtoAdd3);
                    }
                }
            }
        }
    }
    else if(buildindex == 1) // Parameters
    {
        // Set building distribution
        if(jsonObject.contains("BuildDist"))
            ui->CmB_BuildDist->setCurrentIndex(jsonObject["BuildDist"].toString().toInt());
        // Set building shape
        if(jsonObject.contains("BuildShape"))
            ui->CmB_BuildShape->setCurrentIndex(jsonObject["BuildShape"].toString().toInt());
        // Number of buildings in X-Y direction
        if(jsonObject.contains("NumBuildX"))
            ui->DSpBx_NumBuildX->setValue(jsonObject["NumBuildX"].toString().toDouble());
        if(jsonObject.contains("NumBuildY"))
            ui->DSpBx_NumBuildX->setValue(jsonObject["NumBuildY"].toString().toDouble());
        // Number of buildings in X-Y direction
        if(jsonObject.contains("DistBuildX"))
            ui->DSpBx_BuildDistX->setValue(jsonObject["DistBuildX"].toString().toDouble());
        if(jsonObject.contains("DistBuildY"))
            ui->DSpBx_BuildDistY->setValue(jsonObject["DistBuildY"].toString().toDouble());
        // Coordinate of coast in X-Y direction
        if(jsonObject.contains("CoastX"))
            ui->DSpBx_OffsetX->setValue(jsonObject["CoastX"].toString().toDouble());
        if(jsonObject.contains("CoastY"))
            ui->DSpBx_OffsetY->setValue(jsonObject["CoastY"].toString().toDouble());
        // Building size parameter 1 / 2/ 3
        if(jsonObject.contains("BuildSizePara01"))
            ui->DSpBx_BuildSize01->setValue(jsonObject["BuildSizePara01"].toString().toDouble());
        if(jsonObject.contains("BuildSizePara02"))
            ui->DSpBx_BuildSize02->setValue(jsonObject["BuildSizePara02"].toString().toDouble());
        if(jsonObject.contains("BuildSizePara03"))
            ui->DSpBx_BuildSize03->setValue(jsonObject["BuildSizePara03"].toString().toDouble());
    }

    // Get the custom STL file
    if(!workpath.isEmpty())
    {
        if(jsonObject.contains("BuildingSTLFile"))
        {
            // Set the STL file if exists
            QString filename = jsonObject["BuildingSTLFile"].toString();
            QFileInfo fi(QDir(workpath),filename);
            STLfilenames.append(fi.canonicalFilePath());
            ui->PText_CustomBuild->setText(STLfilenames.join(";\n\n"));
        }
    }

    // Return true
    return true;
}

//*********************************************************************************
// Add building
//*********************************************************************************
void buildings::on_Btn_AddBuild_clicked()
{
    ui->Tbl_Building->insertRow(ui->Tbl_Building->rowCount());
}

//*********************************************************************************
// Delete building
//*********************************************************************************
void buildings::on_Btn_RemBuild_clicked()
{
    ui->Tbl_Building->removeRow(ui->Tbl_Building->currentRow());
}

//*********************************************************************************
// Combo box for building data
//*********************************************************************************
void buildings::on_CmB_BuildData_currentIndexChanged(int index)
{

    // Hide items by detault
    ui->GroupNonpara->hide();
    ui->GroupPara->hide();
    ui->Lbl_Notice->hide();
    ui->Btn_CustomBuild->hide();
    ui->PText_CustomBuild->hide();

    // Manually add buildings using table
    if(index == 0)
    {
        ui->GroupNonpara->show();
        ui->Tbl_Building->setHorizontalHeaderItem(0,new QTableWidgetItem("Type"));
        if((simtype == 3) || (simtype == 4))
        {
            ui->Tbl_Building->setHorizontalHeaderItem(1,new QTableWidgetItem("Center (x,y,z)"));
        }
        else
        {
            ui->Tbl_Building->setHorizontalHeaderItem(1,new QTableWidgetItem("Center (Lat,Long)"));
        }
        ui->Btn_AddBuild->setText("Add building");
        ui->Btn_RemBuild->setText("Remove building");
        ui->Lbl_Building->setText("Building table");
        ui->Lbl_Notice->show();
        ui->Lbl_Notice->setText("Check the documentation to prepare the STL files for custom building shapes");
        ui->Btn_CustomBuild->show();
        ui->PText_CustomBuild->show();
    }
    // Add buildings using parametric
    else if(index == 1)
    {
        ui->GroupPara->show();
        on_CmB_BuildShape_currentIndexChanged(ui->CmB_BuildShape->currentIndex());
    }
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool buildings::copyFiles(QString dirName,int type)
{

    // If files are selected, then copy the STL files
    if(STLfilenames.size() > 0)
    {
        QFile fileToCopy(STLfilenames[0]);
        QFileInfo fileInfo(STLfilenames[0]);
        QString theFile = fileInfo.fileName();
        fileToCopy.copy(dirName + QDir::separator() + theFile);
    }

    // Return if data exists
    return true;
}

//*********************************************************************************
// Building shape for parametric definition
//*********************************************************************************
void buildings::on_CmB_BuildShape_currentIndexChanged(int index)
{
    ui->Btn_CustomBuild->hide();
    ui->PText_CustomBuild->hide();

    // Show for custom build
    if(index == 2)
    {
        ui->Btn_CustomBuild->show();
        ui->PText_CustomBuild->show();
        ui->Lbl_Notice->show();
        ui->Lbl_Notice->setText("Check the documentation to prepare the STL files for custom building shapes");
    }
}

//*********************************************************************************
// Button click to upload STL file for custom building
//*********************************************************************************
void buildings::on_Btn_CustomBuild_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list STLfilenames
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.stl)"));
    if(selectfilesdialog.exec()) STLfilenames = selectfilesdialog.selectedFiles();
    if(STLfilenames.size() == 0)
    {
        error.warnerrormessage("No files selected!");
    }
    else
    {
        ui->PText_CustomBuild->setText(STLfilenames[0]);
    }
}
