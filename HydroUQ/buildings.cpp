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
        ui->Lbl_Building->show();
        ui->Tbl_Building->show();
        ui->Btn_AddBuild->show();
        ui->Btn_RemBuild->show();
    }
    else if((type == 5) || (type == 6))
    {
        ui->Lbl_Notice->setText("This option will be coming soon. Keep yourself \nupdated");
        ui->Lbl_Notice->show();
        ui->Lbl_Building->hide();
        ui->Tbl_Building->hide();
        ui->Btn_AddBuild->hide();
        ui->Btn_RemBuild->hide();
    }
    else if(type == 7)
    {
        ui->Lbl_Notice->setText("This option is coming soon in the beta version. \nWatch out!");
        ui->Lbl_Notice->show();
        ui->Lbl_Building->hide();
        ui->Tbl_Building->hide();
        ui->Btn_AddBuild->hide();
        ui->Btn_RemBuild->hide();
    }
}

//*********************************************************************************
// Get data from buildings
//*********************************************************************************
bool buildings::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;

    // Write data from the table
    if(ui->Tbl_Building->rowCount() > 0)
    {
        for(int ii=0;ii<ui->Tbl_Building->rowCount(); ++ii)
        {
            QString segdata = ui->Tbl_Building->item(ii,0)->text() +
                    "," + ui->Tbl_Building->item(ii,1)->text() +
                    "," + ui->Tbl_Building->item(ii,1)->text();
            map.insert("Building"+QString::number(ii),segdata);
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

}
