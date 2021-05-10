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

    // Upload any STL files
    map.insert("NumSTLFiles",QString::number(STLfilenames.size()));
    // Write the bathymetry file names
    for (int ii=0; ii<STLfilenames.size(); ++ii)
    {
        QFile f(STLfilenames[ii]);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());
        map.insert("STLFile"+QString::number(ii),filename);
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Put data into bathymetry from the JSON file
//*********************************************************************************
bool buildings::putData(QJsonObject &jsonObject)
{
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
        // Copy the solution files
        for (int ii=0; ii<STLfilenames.size(); ++ii)
        {
            QFile fileToCopy(STLfilenames[ii]);
            QFileInfo fileInfo(STLfilenames[ii]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
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

    // Show for custom build
    if(index == 2)
    {
        ui->Btn_CustomBuild->show();
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
}
