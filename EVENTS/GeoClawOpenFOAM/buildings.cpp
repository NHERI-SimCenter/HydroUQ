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
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void buildings::hideshowelems(int type)
{

    if( ((type == 1) || (type == 2)) ||
            ((type == 3) || (type == 4)) )
    {
        ui->Lbl_Notice->hide();
        ui->ChB_Parametric->show();
        if(ui->ChB_Parametric->isChecked())
            on_ChB_Parametric_stateChanged(2);
        else
            on_ChB_Parametric_stateChanged(-2);
    }
    else if( ((type == 5) || (type == 6)) || (type == 7))
    {
        ui->Lbl_Notice->setText("This option will be coming soon. Keep yourself \nupdated");
        ui->Lbl_Notice->show();
        ui->ChB_Parametric->hide();
        ui->GroupPara->hide();
        ui->GroupNonpara->hide();
    }
}

//*********************************************************************************
// Get data from buildings
//*********************************************************************************
bool buildings::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;
    (void) type; // Variable is unused

    // Info about check box
    if(ui->ChB_Parametric->isChecked())
        map.insert("Parametric Build",QString::number(1));
    else
        map.insert("Parametric Build",QString::number(0));

    // Parametric inputs
    map.insert("Number of building in X",ui->DSpBx_NumBuildX->textFromValue(ui->DSpBx_NumBuildX->value()));
    map.insert("Number of building in Y",ui->DSpBx_NumBuildY->textFromValue(ui->DSpBx_NumBuildY->value()));
    map.insert("Building distance along X",ui->DSpBx_BuildDistX->textFromValue(ui->DSpBx_BuildDistX->value()));
    map.insert("Building distance along Y",ui->DSpBx_BuildDistY->textFromValue(ui->DSpBx_BuildDistY->value()));
    map.insert("Distance from coast",ui->DSpBx_CoastDist->textFromValue(ui->DSpBx_CoastDist->value()));
    map.insert("OffsetX for coast",ui->DSpBx_OffsetX->textFromValue(ui->DSpBx_OffsetX->value()));
    map.insert("OffsetY for coast",ui->DSpBx_OffsetY->textFromValue(ui->DSpBx_OffsetY->value()));
    map.insert("Building size",ui->DSpBx_BuildSize->textFromValue(ui->DSpBx_BuildSize->value()));
    map.insert("Building distribution",QString::number(ui->CmB_BuildDist->currentIndex()));

    // Write data from the table
    if(ui->Tbl_Building->rowCount() > 0)
    {
        for(int ii=0;ii<ui->Tbl_Building->rowCount(); ++ii)
        {
            QString segdata = ui->Tbl_Building->item(ii,0)->text() +
                    "," + ui->Tbl_Building->item(ii,1)->text() +
                    "," + ui->Tbl_Building->item(ii,1)->text();
            map.insert("BuildingTable"+QString::number(ii),segdata);
        }
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Parametric building settings
//*********************************************************************************
void buildings::on_ChB_Parametric_stateChanged(int arg1)
{
    // Show parametric settings
    if(arg1 > 0) // Show
    {
        ui->GroupPara->show();
        ui->GroupNonpara->hide();
    }
    else // Hide
    {
        ui->GroupPara->hide();
        ui->GroupNonpara->show();
    }
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

}


