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
    if( ((type == 1)) ||
            ((type == 3) || (type == 4)) )
    {
        // Hide the notice
        ui->Lbl_Notice->hide();

        // Set the Combo box
        simtype = type;
        on_CmB_BuildData_currentIndexChanged(ui->CmB_BuildData->currentIndex());
    }
    else if( ((type == 2) || (type == 5)) ||
             ((type == 6) || (type == 7)) )
    {
        ui->Lbl_Notice->setText("This option will be coming soon. Keep yourself updated");
        ui->Lbl_Notice->show();
        ui->GroupPara->hide();
        ui->GroupNonpara->hide();
        ui->CmB_BuildData->hide();
    }
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
    else if(ui->CmB_BuildData->currentIndex() == 2) //From LIDAR Scan
    {
        map.insert("BuildData","LIDAR");
        // Write data from the table
        map.insert("NumRegionBuilds",QString::number(ui->Tbl_Building->rowCount()));
        if(ui->Tbl_Building->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_Building->rowCount(); ++ii)
            {
                QString segdata = ui->Tbl_Building->item(ii,0)->text() +
                        "," + ui->Tbl_Building->item(ii,1)->text() +
                        "," + ui->Tbl_Building->item(ii,2)->text();
                map.insert("BuildingRegion"+QString::number(ii),segdata);
            }
        }
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
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
    if(index == 0) // Manual using table
    {
        ui->GroupPara->hide();
        ui->GroupNonpara->show();
        ui->Tbl_Building->setHorizontalHeaderItem(0,new QTableWidgetItem("Type"));
        if(simtype == 4)
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
    }
    else if(index == 1) // Parametric
    {
        ui->GroupPara->show();
        ui->GroupNonpara->hide();
    }
    else if(index == 2) // LIDAR data
    {
        ui->GroupPara->hide();
        ui->GroupNonpara->show();
        ui->Tbl_Building->setHorizontalHeaderItem(0,new QTableWidgetItem("Region no"));
        if(simtype == 4)
        {
            ui->Tbl_Building->setHorizontalHeaderItem(1,new QTableWidgetItem("Center (x,y,z)"));
        }
        else
        {
            ui->Tbl_Building->setHorizontalHeaderItem(1,new QTableWidgetItem("Center (Lat,Long)"));
        }
        ui->Btn_AddBuild->setText("Add region");
        ui->Btn_RemBuild->setText("Remove region");
        ui->Lbl_Building->setText("Regions to scan");
    }
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool buildings::copyFiles(QString dirName,int type)
{
    // Initialize if has data
    bool hasdata = false;

    // For now we do not allow any uploads
    // Allow user upload of buildings in later stage

    // Return if data exists
    return hasdata;
}
